#include <bits/stdc++.h>
#include "questions_manager.h"
using namespace std;

class question_vote_manager
{
private:
    set<int> all_questions_ids;
    map<int, set<int>> all_question_upvotes;
    map<int, set<int>> all_question_downvotes;

public:
    question_vote_manager();

    void vote_loader();

    void vote_writer();

    void add_new_question(const int &question_id);
    
    void remove_question_votes(const int &question_id);

    int vote_count_getter(const int &question_id);

    int upvote_count_getter(const int &question_id);

    int downvote_count_getter(const int &question_id);

    bool upvote(const int &user_id, const int &question_id);

    bool downvote(const int &user_id, const int &question_id);

    bool has_user_upvoted(const int &user_id, const int &question_id);

    bool has_user_downvoted(const int &user_id, const int &question_id);
};