#pragma once
#include <bits/stdc++.h>
#include "user_manager.h"
#include "questions_manager.h"
#include "answers_manager.h"
using namespace std;

class main_system
{
private:

    user_manager users_mgr ;

    questions_manager questions_mgr ;
    
    answers_manager answers_mgr ;

    void display_main_menu();
    void handle_login();
    void handle_signup();

    void display_user_dashboard();
    void display_feed();

    void handle_ask_question();
    void handle_view_my_questions();
    void handle_delete_question();
    void handle_vote_on_question();

    void handle_answer_question();
    void handle_view_question_with_answers();
    void handle_delete_answer();
    void handle_vote_on_answer();

    void save_all_data();
    void clear_screen();
    void pause_screen();

public:

    main_system();

    bool get_valid_input(int &value);

    void run();

    ~main_system();
};