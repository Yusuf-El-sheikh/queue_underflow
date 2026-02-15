#include <bits/stdc++.h>
#include "user_manager.h"
using namespace std;

user_manager::user_manager()
{
    data_loader();
}

void user_manager::data_loader()
{
    string email_of_user;
    string password_of_user;
    string id_of_user;
    string username_of_user;
    string preference_of_user;

    fstream users_info_file("users_info_file");

    if (!users_info_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }

    while (getline(users_info_file, email_of_user))
    {
        getline(users_info_file, password_of_user);
        getline(users_info_file, id_of_user);
        getline(users_info_file, username_of_user);
        getline(users_info_file, preference_of_user);

        int to_intger_id = stoi(id_of_user);
        bool pref = (preference_of_user == "1" || preference_of_user == "true");

        user_info user;

        user.user_email_setter(email_of_user);
        user.user_password_setter(password_of_user);
        user.user_id_setter(to_intger_id);
        user.username_setter(username_of_user);
        user.preference_setter(pref);

        all_users.push_back(user);
    }

    users_info_file.close();
}

void user_manager::data_writer()
{
    fstream users_info_file("users_info_file", ios::out);

    if (!users_info_file.is_open())
    {
        throw "ERROR , file does not exist! \n";
    }
    
    for (const auto &i : all_users)
    {
        users_info_file << i.user_email_getter() << endl;
        users_info_file << i.user_password_getter() << endl;
        users_info_file << i.user_id_getter() << endl;
        users_info_file << i.username_getter() << endl;
        users_info_file << i.preference_getter() << endl;
    }

    users_info_file.close();
}

void user_manager::sign_up()
{
    cout << "WELCOME TO QUEUE UNDERFLOW" << endl;
    cout << "  LET'S GET YOU STARTED  " << endl;
    cout << "==========================" << endl;

    user_info new_user;

    cout << "Please enter your email address (gmail/yahoo/outlook)" << endl;
    string input_email;
    cin >> input_email;

    while (!user_email_authentication(input_email))
    {
        cin >> input_email;
    }

    new_user.user_email_setter(input_email);

    cout << "Please set your account password -should be eight characters or more with symbols , numbers and uppercase and lowercase letters" << endl;
    string input_password;
    string check;

    cin >> input_password;

    while (!user_password_authenticaton(input_password))
    {
        cin >> input_password;
    }

    new_user.user_password_setter(input_password);

    cout << "Please re-enter the same password to be sure \n";
    cin >> check;

    while (input_password != check)
    {
        cout << "ERROR , passwords do not match , please re-enter \n";
        cin >> check;
    }

    cout << "Please enter you username" << endl;
    string input_username;
    cin >> input_username;
    new_user.username_setter(input_username);

    cout << "Would you like your posts to be anonymous? (Y/N)" << endl;
    char pref;
    bool input_preference;

    cin >> pref;
    pref = tolower(pref);

    while (tolower(pref) != 'y' && tolower(pref) != 'n')
    {
        cout << "ERROR please pick a given options \n";

        cin >> pref;
    }

    if (pref == 'y')
    {
        new_user.preference_setter(true);
    }
    else if (pref == 'n')
    {
        new_user.preference_setter(false);
    }

    int new_id = id_generator();

    new_user.user_id_setter(new_id);

    all_users.push_back(new_user);
}

void user_manager::login()
{
    cout << "      L O G I N          " << endl;
    cout << "=========================" << endl;
    cout << "Please , enter your email" << endl;

    string login_email;
    bool found = false;
    vector<user_info>::iterator found_account_iterator = all_users.end();
    cin >> login_email;

    while (!found)
    {
        for (auto i = all_users.begin(); i != all_users.end(); i++)
        {
            if (login_email == i->user_email_getter())
            {
                found = true;
                found_account_iterator = i;
                break;
            }
        }
        if (!found)
        {
            cout << "email not found in system , please try again" << endl;
            cin >> login_email;
        }
    }
    cout << "Welcome back , " << found_account_iterator->username_getter() << endl;

    cout << "Please , enter your password" << endl;

    string login_password;
    cin >> login_password;

    while (login_password != found_account_iterator->user_password_getter())
    {
        cout << "Incorrect password , please try again" << endl;
        cin >> login_password;
    }

    cout << "Logged in successfully!" << endl;

    current_user = &(*found_account_iterator);
}

void user_manager::logout()
{
    cout << "    L O G G I N G   O U T    " << endl;
    cout << "=================================" << endl;
    cout << "Are you sure you want to log out? (Y/N)" << endl;

    char choice;
    cin >> choice;

    while (tolower(choice) != 'y' && tolower(choice) != 'n')
    {
        cout << "Invalid option , please re-enter your choice" << endl;
        cin >> choice;
    }

    if (tolower(choice) == 'y')
    {
        current_user = nullptr;
        cout << "Logged out successfully" << endl;
        return;
    }

    else if (tolower(choice) == 'n')
    {
        return;
    }
}

user_info *user_manager::search_user(const int &id)
{
    user_info *searched_user;

    for (auto it = all_users.begin(); it != all_users.end(); it++)
    {
        if (it->user_id_getter() == id)
        {
            searched_user = &(*it);

            return searched_user;
        }
    }

    cout << "This user cant be found" << endl;

    return nullptr;
}

int user_manager::id_generator()
{
    random_device randomizer;

    mt19937 gen(randomizer());
    uniform_int_distribution<> dist(10000000, 99999999);

    int id = dist(gen);

    for (const auto &i : all_users)
    {
        if (i.user_id_getter() == id)
        {
            return id_generator();
        }
    }

    return id;
}

bool user_manager::user_email_authentication(const string &email)
{
    int check_at_count = 0;

    int at_index = -1;

    string address;

    for (int i = 0; i < email.size(); i++)
    {
        if (email[i] == '@')
        {
            check_at_count++;

            at_index = i;
        }
    }

    if (check_at_count != 1)
    {
        cout << "I N V A L I D  E M A I L , your email must contain only one '@' , please enter a correct email address \n";

        return false;
    }

    address = email.substr(at_index + 1);

    for (int i = 0; i < address.size(); i++)
    {
        address[i] = tolower(address[i]);
    }

    if (!(address == "gmail.com" || address == "yahoo.com" || address == "outlook.com"))
    {
        cout << "I N V A L I D  E M A I L , your email must have gmail , yahoo or outlook address ! \n";

        return false;
    }

    for (const auto &i : all_users)
    {
        if (i.user_email_getter() == email)
        {
            cout << "This email is already used by another user" << endl;

            return false;
        }
    }

    return true;
}

bool user_manager::user_password_authenticaton(const string &password)
{
    bool password_has_uppercase_letter = false;
    bool password_has_lowercase_letter = false;
    bool password_has_number = false;
    bool password_has_symbol = false;

    if (password.size() >= 8)
    {
        for (int i = 0; i < password.size(); i++)
        {
            if ((password[i] >= 35 && password[i] <= 38) || password[i] == 42)
            {
                password_has_symbol = true;
            }
            else if (password[i] >= 65 && password[i] <= 90)
            {
                password_has_uppercase_letter = true;
            }
            else if (password[i] >= 97 && password[i] <= 122)
            {
                password_has_lowercase_letter = true;
            }
            else if (password[i] >= 48 && password[i] <= 57)
            {
                password_has_number = true;
            }
            if (password_has_lowercase_letter && password_has_uppercase_letter && password_has_number && password_has_symbol)
            {
                return true;
            }
        }

        cout << "Your password must contain numbers , symbols (# , $ , % , & , *) , uppercase and lowercase characters \n";

        return false;
    }

    else
    {
        cout << "Your password is too short" << endl;
        return false;
    }
}
