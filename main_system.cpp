#include <bits/stdc++.h>
#include "main_system.h"
using namespace std;

main_system::main_system() {}

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
    cin >> choice;

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
        cout << "Invalid choice! Try again." << endl;
        pause_screen();
    }
}

void main_system::display_user_dashboard()
{
    clear_screen();
    cout << "================================================================================" << endl;
    cout << "                          QUEUE UNDERFLOW DASHBOARD                             " << endl;
    cout << "================================================================================" << endl;
    cout << "  Logged in as: " << users.current_user->username_getter() << endl;
    cout << "================================================================================" << endl;
    cout << endl;
    cout << "  1. View Feed (All Questions)                                                  " << endl;
    cout << "  2. Ask a Question                                                             " << endl;
    cout << "  3. Answer a Question                                                          " << endl;
    cout << "  4. View My Questions                                                          " << endl;
    cout << "  5. Delete My Question                                                         " << endl;
    cout << "  6. Delete My Answer                                                           " << endl;
    cout << "  7. Vote on Question                                                           " << endl;
    cout << "  8. Vote on Answer                                                             " << endl;
    cout << "  9. Logout                                                                     " << endl;
    cout << endl;
    cout << "================================================================================" << endl;
    cout << "  Enter your choice: ";
    
    int choice;
    cin >> choice;
    
    switch(choice)
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
            users.logout();
            break;
        default:
            cout << "Invalid choice! Try again." << endl;
            pause_screen();
    }
}

void main_system::handle_signup()
{
    clear_screen();
    users.sign_up();
    pause_screen();
}

void main_system::handle_login()
{
    clear_screen();
    users.login();
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
    
    questions.ask(users.current_user->user_id_getter(), question_text, is_anonymous);
    
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
    cin >> question_id;
    
    auto it = questions.search_questions_by_id(question_id);
    if (it == questions.search_questions_by_id(-1))
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
    
    answers.answer(users.current_user->user_id_getter(), question_id, answer_text, is_anonymous);
    
    pause_screen();
}

void main_system::save_all_data()
{
    users.data_writer();

    questions.question_writer();
    questions.save_votes();

    answers.answer_writer();
    answers.save_votes();
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