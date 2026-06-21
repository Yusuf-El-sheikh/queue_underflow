#include <iostream>
#include "../headers/questions.h"
using namespace std;

questions::questions(int question_id, int parent_question_id, int from_user_id, const string &question_text, bool is_anonymous, bool is_answered)
    : post(question_id, from_user_id, question_text, is_anonymous), is_answered(is_answered), parent_question_id(parent_question_id)
{
}

int questions::parent_question_id_getter() const
{
    return parent_question_id;
}

bool questions::is_answered_getter() const
{
    return is_answered;
}

void questions::display()
{
    cout << "Question ID: " << id_getter() << endl;
    if (parent_question_id != -1)
    {
        cout << "Parent Question ID: " << parent_question_id_getter() << endl;
    }
    cout << "From User ID: " << from_user_id_getter() << endl;
    cout << "Text: " << text_getter() << endl;
    cout << "Is Anonymous: " << (is_anonymous_getter() ? "Yes" : "No") << endl;
    cout << "Is Answered: " << (is_answered_getter() ? "Yes" : "No") << endl;
}