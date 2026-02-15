#include <bits/stdc++.h>
#include "answer_vote_manager.h"
using namespace std;

answer_vote_manager::answer_vote_manager()
{
    vote_loader();
}

void answer_vote_manager::vote_loader()
{
    string line;

    int answer_id;
    int user_id;

    fstream answer_votes_file("answer_votes_file");

    if (!answer_votes_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }

    while (getline(answer_votes_file, line))
    {
        if (line.substr(0, 12) == "answer_id#")
        {
            answer_id = stoi(line.substr(12));
            all_answers_ids.insert(answer_id);
        }
        
        else if (line == "#upvotes")
        {
            while (getline(answer_votes_file, line) && line != "#downvotes")
            {
                user_id = stoi(line);

                all_answer_upvotes[answer_id].insert(user_id);
            }
        }
        
        else if (line == "#downvotes")
        {
            while (getline(answer_votes_file, line) && (line.size() < 12 || line.substr(0, 12) != "answer_id#"))
            {
                user_id = stoi(line);

                all_answer_downvotes[answer_id].insert(user_id);
            }
        }
    }

    answer_votes_file.close();
}

void answer_vote_manager::vote_writer()
{
    fstream answer_votes_file("answer_votes_file", ios::out);

    if (!answer_votes_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }

    for (const auto &answer_id : all_answers_ids)
    {
        answer_votes_file << "answer_id#" << answer_id << endl;
        answer_votes_file << "#upvotes" << endl;

        if (all_answer_upvotes.count(answer_id))
        {
            for (const auto &upvotes : all_answer_upvotes[answer_id])
            {
                answer_votes_file << upvotes << endl;
            }
        }
        
        answer_votes_file << "#downvotes" << endl;

        if (all_answer_downvotes.count(answer_id))
        {
            for (const auto &downvotes : all_answer_downvotes[answer_id])
            {
                answer_votes_file << downvotes << endl;
            }
        }
    }

    answer_votes_file.close() ;
}

void answer_vote_manager::add_new_answer(const int &answer_id)
{
    all_answers_ids.insert(answer_id);
}

void answer_vote_manager::remove_answer_votes(const int &answer_id)
{
    all_answers_ids.erase(answer_id) ;

    all_answer_upvotes.erase(answer_id) ;

    all_answer_downvotes.erase(answer_id) ;
}

int answer_vote_manager::vote_count_getter(const int &answer_id)
{
    return all_answer_upvotes[answer_id].size() - all_answer_downvotes[answer_id].size() ;
}

int answer_vote_manager::upvote_count_getter(const int &answer_id)
{
    return all_answer_upvotes[answer_id].size() ;
}

int answer_vote_manager::downvote_count_getter(const int &answer_id)
{
    return all_answer_downvotes[answer_id].size() ;
}

bool answer_vote_manager::upvote(const int &user_id, const int &answer_id)
{
    if(all_answer_upvotes[answer_id].find(user_id) != all_answer_upvotes[answer_id].end())
    {
        //button toggle mechanism
        all_answer_upvotes[answer_id].erase(user_id) ;

        return false ;
    }

    else if(all_answer_downvotes[answer_id].find(user_id) != all_answer_downvotes[answer_id].end())
    {
        //button toggle mechanism
        all_answer_downvotes[answer_id].erase(user_id) ;
        all_answer_upvotes[answer_id].insert(user_id) ;
        return true ;
    }

    all_answer_upvotes[answer_id].insert(user_id) ;
    
    return true ;
}

bool answer_vote_manager::downvote(const int &user_id, const int &answer_id)
{
    if(all_answer_downvotes[answer_id].find(user_id) != all_answer_downvotes[answer_id].end())
    {
        //button toggle mechanism
        all_answer_downvotes[answer_id].erase(user_id) ;

        return false ;
    }

    else if(all_answer_upvotes[answer_id].find(user_id) != all_answer_upvotes[answer_id].end())
    {
        //button toggle mechanism
        all_answer_upvotes[answer_id].erase(user_id) ;
        all_answer_downvotes[answer_id].insert(user_id) ;

        return true ;
    }

    all_answer_downvotes[answer_id].insert(user_id) ;
    return true ;
}

bool answer_vote_manager::has_user_upvoted(const int &user_id, const int &answer_id)
{
    if(all_answer_upvotes[answer_id].find(user_id) != all_answer_upvotes[answer_id].end())
    {
        return true ;
    }
    return false;
}

bool answer_vote_manager::has_user_downvoted(const int &user_id, const int &answer_id)
{
    if(all_answer_downvotes[answer_id].find(user_id) != all_answer_downvotes[answer_id].end())
    {
        return true ;
    }
    return false ;
}
