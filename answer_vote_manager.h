#include <bits/stdc++.h>
#include "answers_manager.h"
using namespace std;

class answer_vote_manager
{
    private:

    set<int> all_answers_ids ;
    map<int, set<int>> all_answer_upvotes;
    map<int, set<int>> all_answer_downvotes;

    public:

    answer_vote_manager();

    void vote_loader();

    void vote_writer();

    void add_new_answer(const int &answer_id) ;

    void remove_answer_votes(const int &answer_id) ;

    int vote_count_getter(const int &answer_id);

    int upvote_count_getter(const int &answer_id);

    int downvote_count_getter(const int &answer_id);

    bool upvote(const int &user_id, const int &answer_id);

    bool downvote(const int &user_id, const int &answer_id);

    bool has_user_upvoted(const int &user_id, const int &answer_id);

    bool has_user_downvoted(const int &user_id, const int &answer_id);
};