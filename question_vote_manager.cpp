#include <bits/stdc++.h>
#include "question_vote_manager.h"
using namespace std;

question_vote_manager::question_vote_manager()
{
    vote_loader();
}

void question_vote_manager::vote_loader()
{
    string line;

    int question_id;
    int user_id;

    fstream question_votes_file("question_votes_file");

    if (!question_votes_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }

    while (getline(question_votes_file, line))
    {
        if (line.substr(0, 12) == "question_id#")
        {
            question_id = stoi(line.substr(12));
            all_questions_ids.insert(question_id);
        }
        else if (line == "#upvotes")
        {
            while (getline(question_votes_file, line) && line != "#downvotes")
            {
                user_id = stoi(line);

                all_question_upvotes[question_id].insert(user_id);
            }
        }
        else if (line == "#downvotes")
        {
            while (getline(question_votes_file, line) && (line.size() < 12 || line.substr(0, 12) != "question_id#"))
            {
                user_id = stoi(line);

                all_question_downvotes[question_id].insert(user_id);
            }
        }
    }

    question_votes_file.close();
}

void question_vote_manager::vote_writer()
{
    fstream question_votes_file("question_votes_file", ios::out);

    if (!question_votes_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }

    for (const auto &question_id : all_questions_ids)
    {
        question_votes_file << "question_id#" << question_id << endl;
        question_votes_file << "#upvotes" << endl;

        if (all_question_upvotes.count(question_id))
        {
            for (const auto &upvotes : all_question_upvotes[question_id])
            {
                question_votes_file << upvotes << endl;
            }
        }
        
        question_votes_file << "#downvotes" << endl;

        if (all_question_downvotes.count(question_id))
        {
            for (const auto &downvotes : all_question_downvotes[question_id])
            {
                question_votes_file << downvotes << endl;
            }
        }
    }

    question_votes_file.close() ;
}

void question_vote_manager::add_new_question(const int &question_id)
{
    all_questions_ids.insert(question_id);
}

void question_vote_manager::remove_question_votes(const int &question_id)
{
    all_questions_ids.erase(question_id) ;

    all_question_upvotes.erase(question_id) ;

    all_question_downvotes.erase(question_id) ;
}

int question_vote_manager::vote_count_getter(const int &question_id)
{
    return all_question_upvotes[question_id].size() - all_question_downvotes[question_id].size() ;
}

int question_vote_manager::upvote_count_getter(const int &question_id)
{
    return all_question_upvotes[question_id].size() ;
}

int question_vote_manager::downvote_count_getter(const int &question_id)
{
    return all_question_downvotes[question_id].size() ;
}

bool question_vote_manager::upvote(const int &user_id, const int &question_id)
{
    if(all_question_upvotes[question_id].find(user_id) != all_question_upvotes[question_id].end())
    {
        //button toggle mechanism
        all_question_upvotes[question_id].erase(user_id) ;

        return false ;
    }

    else if(all_question_downvotes[question_id].find(user_id) != all_question_downvotes[question_id].end())
    {
        //button toggle mechanism
        all_question_downvotes[question_id].erase(user_id) ;
        all_question_upvotes[question_id].insert(user_id) ;
        return true ;
    }

    all_question_upvotes[question_id].insert(user_id) ;
    
    return true ;
}

bool question_vote_manager::downvote(const int &user_id, const int &question_id)
{
    if(all_question_downvotes[question_id].find(user_id) != all_question_downvotes[question_id].end())
    {
        //button toggle mechanism
        all_question_downvotes[question_id].erase(user_id) ;

        return false ;
    }

    else if(all_question_upvotes[question_id].find(user_id) != all_question_upvotes[question_id].end())
    {
        //button toggle mechanism
        all_question_upvotes[question_id].erase(user_id) ;
        all_question_downvotes[question_id].insert(user_id) ;

        return true ;
    }

    all_question_downvotes[question_id].insert(user_id) ;
    return true ;
}

bool question_vote_manager::has_user_upvoted(const int &user_id, const int &question_id)
{
    if(all_question_upvotes[question_id].find(user_id) != all_question_upvotes[question_id].end())
    {
        return true ;
    }
    return false;
}

bool question_vote_manager::has_user_downvoted(const int &user_id, const int &question_id)
{
    if(all_question_downvotes[question_id].find(user_id) != all_question_downvotes[question_id].end())
    {
        return true ;
    }
    return false ;
}
