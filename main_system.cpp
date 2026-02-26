#include <bits/stdc++.h>
#include "main_system.h"
using namespace std;

main_system::main_system() {}

bool main_system::get_valid_input(int &value)
{
    if(cin >> value)
    {
        return true ;
    }

    cin.clear();
    cin.ignore(10000 , '\n');

    return false ;
}

void main_system::display_main_menu()
{
    clear_screen();
    cout << "    ____                                         _            __ _               " << endl;
    cout << "   /___ \\_   _  ___ _   _  ___   /\\ /\\ _ __   __| | ___ _ __ / _| | _____      __" << endl;
    cout << "  //  / / | | |/ _ \\ | | |/ _ \\ / / \\ \\ '_ \\ / _` |/ _ \\ '__| |_| |/ _ \\ \\ /\\ / /" << endl;
    cout << " / \\_/ /| |_| |  __/ |_| |  __/ \\ \\_/ / | | | (_| |  __/ |  |  _| | (_) \\ V  V / " << endl;
    cout << " \\___,_\\ \\__,_|\\___|\\__,_|\\___|  \\___/|_| |_|\\__,_|\\___|_|  |_| |_|\\___/ \\_/\\_/  " << endl;
    cout << endl;
    cout << "================================================================================" << endl;
    cout << "                    WELCOME TO YOUR Q&A COMMUNITY!                              " << endl;
    cout << "================================================================================" << endl;
    cout << endl;
    cout << "  1. Login                                                                      " << endl;
    cout << "  2. Sign Up                                                                    " << endl;
    cout << "  3. Exit                                                                       " << endl;
    cout << endl;
    cout << "================================================================================" << endl;

    int choice;

    while(!get_valid_input(choice))
    {
        cout << "Invalid input , please try again !" << endl;
    }
    switch (choice)
    {
    case 1:
        handle_login();
        break;
    case 2:
        handle_signup();
        break;
    case 3:
        cout << "Goodbye!" << endl;
        save_all_data();
        exit(0);
        break;
    default:
        cout << "Invalid choice , pick 1 , 2 , 3" << endl ;
        pause_screen();
    }
}

void main_system::display_user_dashboard()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                          QUEUE UNDERFLOW DASHBOARD                             " << endl;
    cout << "================================================================================" << endl;
    cout << "  Logged in as: " << users_mgr.current_user->username_getter() << endl;
    cout << "================================================================================" << endl;
    cout << endl;
    cout << "  1. View Feed (All Questions)                                                  " << endl;
    cout << "  2. Ask a Question                                                             " << endl;
    cout << "  3. Answer a Question                                                          " << endl;
    cout << "  4. View My Profile                                                            " << endl;
    cout << "  5. Delete My Question                                                         " << endl;
    cout << "  6. Delete My Answer                                                           " << endl;
    cout << "  7. Vote on Question                                                           " << endl;
    cout << "  8. Vote on Answer                                                             " << endl;
    cout << "  9. Logout                                                                     " << endl;
    cout << endl;
    cout << "================================================================================" << endl;
    cout << "  Enter your choice: ";

    int choice;
    
    while(!get_valid_input(choice))
    {
        cout << "  Invalid input , please try again !" << endl;
        cout << "  Enter your choice: ";
    }

    switch (choice)
    {
    case 1:
        display_feed();
        break;
    case 2:
        handle_ask_question();
        break;
    case 3:
        handle_answer_question();
        break;
    case 4:
        handle_view_my_questions();
        break;
    case 5:
        handle_delete_question();
        break;
    case 6:
        handle_delete_answer();
        break;
    case 7:
        handle_vote_on_question();
        break;
    case 8:
        handle_vote_on_answer();
        break;
    case 9:
        users_mgr.logout();
        break;
    default:
        cout << "Invalid choice! Try again." << endl;
        pause_screen();
    }
}

void main_system::handle_signup()
{
    clear_screen();
    users_mgr.sign_up();
    pause_screen();
}

void main_system::handle_login()
{
    clear_screen();
    users_mgr.login();
    pause_screen();
}

void main_system::handle_ask_question()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                              ASK A QUESTION                                    " << endl;
    cout << "================================================================================" << endl;

    cin.ignore();

    cout << "Enter your question (max 1000 characters): " << endl;
    string question_text;
    getline(cin, question_text);

    cout << "Post anonymously? (y/n): ";
    char anon_choice;
    cin >> anon_choice;

    bool is_anonymous = (tolower(anon_choice) == 'y');

    questions_mgr.ask(users_mgr.current_user->user_id_getter(), question_text, is_anonymous);

    pause_screen();
}

void main_system::handle_answer_question()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                            ANSWER A QUESTION                                   " << endl;
    cout << "================================================================================" << endl;

    cout << "Enter the Question ID you want to answer: ";
    int question_id;
    
    while(!get_valid_input(question_id))
    {
        cout << "Invalid input , please try again !" << endl;
    }

    auto it = questions_mgr.search_questions_by_id(question_id);
    if (it == questions_mgr.search_questions_by_id(-1))
    {
        pause_screen();
        return;
    }

    cin.ignore();

    cout << "Enter your answer (max 1000 characters): " << endl;
    string answer_text;
    getline(cin, answer_text);

    cout << "Post anonymously? (y/n): ";
    char anon_choice;
    cin >> anon_choice;

    bool is_anonymous = (tolower(anon_choice) == 'y');

    answers_mgr.answer(users_mgr.current_user->user_id_getter(), question_id, answer_text, is_anonymous);

    pause_screen();
}

void main_system::handle_delete_question()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                           DELETE MY QUESTION                                   " << endl;
    cout << "================================================================================" << endl;

    cout << "Enter the Question ID to delete: ";
    int question_id;
    
    while(!get_valid_input(question_id))
    {
        cout << "Invalid input , please try again !" << endl;
    }

    if (!questions_mgr.can_delete_question(users_mgr.current_user->user_id_getter(), question_id))
    {
        pause_screen();
        return;
    }

    vector<int> descendants = questions_mgr.collect_all_descendants(question_id);
    descendants.push_back(question_id);

    for (int qid : descendants)
    {
        vector<answers> question_answers = answers_mgr.answers_of_question_filter(qid);
        for (const auto &ans : question_answers)
        {
            answers_mgr.force_delete_answer(ans.answer_id_getter());
        }
    }

    for (int qid : descendants)
    {
        questions_mgr.force_delete_question(qid);
    }

    cout << "Question thread deleted successfully!" << endl;
    pause_screen();
}

void main_system::handle_delete_answer()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                             DELETE MY ANSWER                                   " << endl;
    cout << "================================================================================" << endl;

    cout << "Enter the Answer ID to delete: ";
    int answer_id;
    
    while(!get_valid_input(answer_id))
    {
        cout << "Invalid input , please try again !" << endl;
    }

    if (!answers_mgr.can_delete_answer(users_mgr.current_user->user_id_getter(), answer_id))
    {
        pause_screen();
        return;
    }

    answers_mgr.force_delete_answer(answer_id);
    cout << "Answer deleted successfully!" << endl;
    pause_screen();
}

void main_system::handle_vote_on_question()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                          VOTE ON QUESTION                                      " << endl;
    cout << "================================================================================" << endl;

    cout << "Enter Question ID: ";
    int question_id;
    
    while(!get_valid_input(question_id))
    {
        cout << "Invalid input , please try again !" << endl;
    }

    cout << "1. Upvote" << endl;
    cout << "2. Downvote" << endl;
    cout << "Choice: ";
    int vote_choice;

    while(!get_valid_input(vote_choice))
    {
        cout << "Invalid input , please try again !" << endl;
    }

    switch (vote_choice)
    {
    case 1:
        questions_mgr.upvote_question(users_mgr.current_user->user_id_getter(), question_id);
        cout << "Vote recorded!" << endl;
        break;
    case 2:
        questions_mgr.downvote_question(users_mgr.current_user->user_id_getter(), question_id);
        cout << "Vote recorded!" << endl;
        break;
    default:
        cout << "Invalid choice!" << endl;
    }

    pause_screen();
}

void main_system::handle_vote_on_answer()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                           VOTE ON ANSWER                                       " << endl;
    cout << "================================================================================" << endl;

    cout << "Enter Answer ID: ";
    int answer_id;
    while(!get_valid_input(answer_id))
    {
        cout << "Invalid input , please try again !" << endl;
    }

    cout << "1. Upvote" << endl;
    cout << "2. Downvote" << endl;
    cout << "Choice: ";
    
    int vote_choice;
    while(!get_valid_input(vote_choice))
    {
        cout << "Invalid input , please try again !" << endl;
    }

    switch (vote_choice)
    {
    case 1:
        answers_mgr.upvote_answer(users_mgr.current_user->user_id_getter(), answer_id);
        cout << "Vote recorded!" << endl;
        break;
    case 2:
        answers_mgr.downvote_answer(users_mgr.current_user->user_id_getter(), answer_id);
        cout << "Vote recorded!" << endl;
        break;
    default:
        cout << "Invalid choice!" << endl;
    }

    pause_screen();
}

void main_system::handle_view_my_questions()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                               MY PROFILE                                       " << endl;
    cout << "================================================================================" << endl;
    
    vector<questions> my_questions = questions_mgr.questions_of_user_filter(users_mgr.current_user->user_id_getter());
    
    if (my_questions.empty())
    {
        cout << "You haven't asked any questions yet." << endl;
    }
    else
    {
        for (const auto &q : my_questions)
        {
            cout << "\n[Question ID: " << q.question_id_getter() << "]" << endl;
            cout << q.question_text_getter() << endl;
            cout << "Anonymous: " << (q.is_anonymous_getter() ? "Yes" : "No") << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
        }
    }
    
    pause_screen();
}

void main_system::display_feed()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                            QUEUE UNDERFLOW                                     " << endl;
    cout << "================================================================================" << endl;
    
    const vector<questions>& all_questions = questions_mgr.get_questions();
    
    if (all_questions.empty())
    {
        cout << "\nNo questions posted yet. Be the first to ask!" << endl;
    }
    else
    {
        cout << "\nShowing all questions:\n" << endl;
        
        for (const auto &q : all_questions)
        {
            cout << "[Question ID: " << q.question_id_getter() << "]" << endl;
            
            if (q.is_anonymous_getter())
            {
                cout << "By: Anonymous" << endl;
            }
            else
            {
                user_info* author = users_mgr.search_user(q.from_id_getter());
                if (author != nullptr)
                {
                    cout << "By: " << author->username_getter() << endl;
                }
            }
            
            cout << "Question: " << q.question_text_getter() << endl;
            cout << "Upvotes: " << questions_mgr.get_upvote_count(q.question_id_getter()) 
                 << " | Downvotes: " << questions_mgr.get_downvote_count(q.question_id_getter()) << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
        }
    }
    
    pause_screen();
}

void main_system::run()
{
    while (true)
    {
        if (users_mgr.current_user == nullptr) 
        {
            display_main_menu();
        }
        else 
        {
            display_user_dashboard();
        }
    }
}

void main_system::save_all_data()
{
    users_mgr.data_writer();

    questions_mgr.question_writer();
    questions_mgr.save_votes();

    answers_mgr.answer_writer();
    answers_mgr.save_votes();
}

void main_system::clear_screen()
{
    system("cls");
}

void main_system::pause_screen()
{
    cout << "\nPress enter to continue...\n";

    cin.ignore();
    cin.get();
}

main_system::~main_system()
{
    save_all_data();
    cout << "System shutdown. All data saved." << endl;
}