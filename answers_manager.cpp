#include <bits/stdc++.h>
#include "answer_vote_manager.h"
#include "answers_manager.h"
#include "answers.h"
using namespace std;

answers_manager::answers_manager()
{
    answers_loader();
}

void answers_manager::answers_loader()
{
    answers answer;

    fstream answers_file("answers_file");

    if (!answers_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }

    string answers_data;
    string answers_text_lines = "";

    char next_char;

    while (getline(answers_file, answers_data))
    {
        int to_int_answered_question_id = stoi(answers_data);
        answer.answered_question_id_setter(to_int_answered_question_id);

        getline(answers_file, answers_data);

        int to_int_answer_id = stoi(answers_data);
        answer.answer_id_setter(to_int_answer_id);

        getline(answers_file, answers_data);

        int to_int_from_id = stoi(answers_data);
        answer.from_id_setter(to_int_from_id);

        getline(answers_file, answers_data);

        int length_of_answer_text = stoi(answers_data);

        getline(answers_file, answers_data);

        bool pref = (answers_data == "1" || answers_data == "true");
        answer.is_anonymous_setter(pref);

        for (int i = 0; i < length_of_answer_text; i++)
        {
            answers_file.get(next_char);
            answers_text_lines += next_char;
        }
        answers_file.ignore();
        answer.answer_text_setter(answers_text_lines);
        all_answers.push_back(answer);
        answers_text_lines = "";
    }

    sort(all_answers.begin(), all_answers.end(), [](const answers &a, const answers &b) -> bool
         { return a.answer_id_getter() < b.answer_id_getter(); });

    answers_file.close();
}

void answers_manager::answer_writer()
{
    fstream answers_file("answers_file", ios::out);

    if (!answers_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }

    for (auto &answer : all_answers)
    {
        answers_file << answer.answered_question_id_getter() << "\n";
        answers_file << answer.answer_id_getter() << "\n";
        answers_file << answer.from_id_getter() << "\n";
        answers_file << answer.answer_text_getter().size() << "\n";
        answers_file << (answer.is_anonymous_getter() ? "1" : "0") << "\n";
        answers_file << answer.answer_text_getter() << "\n";
    }

    answers_file.close();
}

void answers_manager::save_votes()
{
    a_vote_manager.vote_writer();
}

bool answers_manager::can_delete_answer(const int &current_user_id, const int &target_answer_id)
{
    auto it = lower_bound(all_answers.begin(), all_answers.end(), target_answer_id, [](const answers &a, const int &id)
                          { return a.answer_id_getter() < id; });

    if (it != all_answers.end() && it->answer_id_getter() == target_answer_id && it->from_id_getter() == current_user_id)
    {
        return true;
    }
    else if (it == all_answers.end() || it->answer_id_getter() != target_answer_id)
    {
        cout << "False answer id , this answer does not exist" << endl;
        return false;
    }
    else if (it->from_id_getter() != current_user_id)
    {
        cout << "This answer belongs to a different user , u can only delete your own answers" << endl;
        return false;
    }

    return false;
}

bool answers_manager::force_delete_answer(const int &answer_id)
{
    auto it = lower_bound(all_answers.begin(), all_answers.end(), answer_id,
                          [](const answers &a, const int &id)
                          { return a.answer_id_getter() < id; });

    if (it != all_answers.end() && it->answer_id_getter() == answer_id)
    {
        a_vote_manager.remove_answer_votes(answer_id);
        all_answers.erase(it);
        return true;
    }

    return false;
}

bool answers_manager::upvote_answer(const int &user_id, const int &answer_id)
{
    return a_vote_manager.upvote(user_id, answer_id);
}

bool answers_manager::downvote_answer(const int &user_id, const int &answer_id)
{
    return a_vote_manager.downvote(user_id, answer_id);
}

vector<answers>::const_iterator answers_manager::search_answers_by_id(const int &answer_id) const
{
    auto it = lower_bound(all_answers.begin(), all_answers.end(), answer_id, [](const answers &a, const int &id)
                          { return a.answer_id_getter() < id; });

    if (it == all_answers.end() || it->answer_id_getter() != answer_id)
    {
        return all_answers.end();
    }

    return it;
}

int answers_manager::id_generator()
{
    random_device randomizer;

    mt19937 gen(randomizer());
    uniform_int_distribution<> dist(10000000, 99999999);

    int answer_id = dist(gen);

    for (int i = 0; i < all_answers.size(); i++)
    {
        if (all_answers[i].answer_id_getter() == answer_id)
        {
            return id_generator();
        }
    }

    return answer_id;
}

vector<answers> answers_manager::answers_of_question_filter(const int &question_id)
{
    vector<answers> all_question_answers;

    for (const auto &i : all_answers)
    {

        if (i.answered_question_id_getter() == question_id)
        {
            all_question_answers.push_back(i);
        }
    }

    return all_question_answers;
}

const vector<answers> &answers_manager::get_answers() const
{
    return all_answers;
}

bool answers_manager::answer(const int &user_id, const int &question_id, const string &answer_text, bool is_anonymous)
{
    answers new_answer;

    if (answer_text.size() > 1000)
    {
        cout << "answer size limit is only 1000 letter !" << endl;
        return false;
    }

    new_answer.answered_question_id_setter(question_id);
    new_answer.is_anonymous_setter(is_anonymous);
    new_answer.answer_id_setter(id_generator());
    new_answer.answer_text_setter(answer_text);
    new_answer.from_id_setter(user_id);

    a_vote_manager.add_new_answer(new_answer.answer_id_getter());

    auto pos = std::lower_bound(all_answers.begin(), all_answers.end(), new_answer, [](const answers &a, const answers &b)
                                { return a.answer_id_getter() < b.answer_id_getter(); });
    all_answers.insert(pos, new_answer);

    cout << "Your answer was posted successfully ! " << endl;
    cout << "Refresh the homepage to check your answer!" << endl;

    return true;
}
