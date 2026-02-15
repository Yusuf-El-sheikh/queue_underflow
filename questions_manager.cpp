#include <bits/stdc++.h>
#include "question_vote_manager.h"
#include "questions_manager.h"
#include "user_manager.h"
using namespace std;

questions_manager::questions_manager() 
{
    questions_loader();
}

void questions_manager::questions_loader()
{
    questions question;

    fstream questions_file("questions_file");

    if (!questions_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }

    string question_data;
    string questions_lines_of_text = "";

    char next_char;

    while (getline(questions_file, question_data))
    {
        int to_int_parent_id = stoi(question_data);
        question.parent_question_id_setter(to_int_parent_id);

        getline(questions_file, question_data);

        int to_int_question_id = stoi(question_data);
        question.question_id_setter(to_int_question_id);

        getline(questions_file, question_data);

        int to_int_from_id = stoi(question_data);
        question.from_id_setter(to_int_from_id);

        getline(questions_file, question_data);

        bool pref = (question_data == "1" || question_data == "true");
        question.is_anonymous_setter(pref);

        getline(questions_file, question_data);

        bool answered = (question_data == "1" || question_data == "true");
        question.is_answered_setter(answered);

        getline(questions_file, question_data);

        int length_of_question_text = stoi(question_data);

        for (int i = 0; i < length_of_question_text; i++)
        {
            questions_file.get(next_char);
            questions_lines_of_text += next_char;
        }
        question.question_text_setter(questions_lines_of_text);
        all_questions.push_back(question);
        questions_lines_of_text = "";
    }

    sort(all_questions.begin(), all_questions.end(), [](const questions &a, const questions &b) -> bool
         { return a.question_id_getter() < b.question_id_getter(); });

    questions_file.close();
}

void questions_manager::question_writer()
{
    fstream questions_file("questions_file", ios::out);

    if (!questions_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }

    for (auto &question : all_questions)
    {
        questions_file << question.parent_question_id_getter() << "\n";
        questions_file << question.question_id_getter() << "\n";
        questions_file << question.from_id_getter() << "\n";
        questions_file << (question.is_anonymous_getter() ? "1" : "0") << "\n";
        questions_file << (question.is_answered_getter() ? "1" : "0") << "\n";
        questions_file << question.question_text_getter().size() << "\n";
        questions_file << question.question_text_getter();
    }

    questions_file.close();
}

bool questions_manager::delete_question(const int &current_user_id, const int &target_question_id)
{
    auto it = lower_bound(all_questions.begin(), all_questions.end(), target_question_id, [](const questions &a, const int &id)
                          { return a.question_id_getter() < id; });

    if (it != all_questions.end() && it->question_id_getter() == target_question_id && it->from_id_getter() == current_user_id)
    {
        q_vote_manager.remove_question_votes(target_question_id);
        all_questions.erase(it);

        cout << "Your question was deleted successfully" << endl;

        return true;
    }
    else if (it == all_questions.end() || it->question_id_getter() != target_question_id)
    {
        cout << "False question id , this question does not exist" << endl;
        return false;
    }
    else if (it->from_id_getter() != current_user_id)
    {
        cout << "This question belongs to a different user , u can only delete your own questions" << endl;
        return false;
    }

    return false;
}

vector<questions>::const_iterator questions_manager::search_questions_by_id(const int &question_id) const
{
    auto it = lower_bound(all_questions.begin(), all_questions.end(), question_id, [](const questions &a, const int &id)
                          { return a.question_id_getter() < id; });

    if (it == all_questions.end() || it->question_id_getter() != question_id)
    {
        cout << "False question id , this question does not exist" << endl;
        return all_questions.end();
    }

    return it;
}

vector<questions> questions_manager::questions_of_user_filter(const int &current_user_id)
{
    vector<questions> all_user_questions;

    for (const auto &i : all_questions)
    {

        if (i.from_id_getter() == current_user_id)
        {
            all_user_questions.push_back(i);
        }
    }

    return all_user_questions;
}

int questions_manager::id_generator()
{
    random_device randomizer;

    mt19937 gen(randomizer());
    uniform_int_distribution<> dist(10000000, 99999999);

    int question_id = dist(gen);

    for (int i = 0; i < all_questions.size(); i++)
    {
        if (all_questions[i].question_id_getter() == question_id)
        {
            return id_generator();
        }
    }

    return question_id;
}

bool questions_manager::ask(const int &user_id, const string &user_question_text, bool is_anonymous, int parent_id)
{
    questions new_question;

    if (user_question_text.size() > 1000)
    {
        cout << "question size limit is only 1000 letter !" << endl;
        return false;
    }

    new_question.parent_question_id_setter(parent_id);
    new_question.is_anonymous_setter(is_anonymous);
    new_question.is_answered_setter(false);
    new_question.question_id_setter(id_generator());
    new_question.question_text_setter(user_question_text);
    new_question.from_id_setter(user_id);

    q_vote_manager.add_new_question(new_question.question_id_getter()) ;

    auto pos = std::lower_bound(all_questions.begin(), all_questions.end(), new_question, [](const questions &a, const questions &b)
                                { return a.question_id_getter() < b.question_id_getter(); });
    all_questions.insert(pos, new_question);

    cout << "Your question was posted successfully ! " << endl;
    cout << "Refresh the homepage to check your post!" << endl;

    return true;
}
