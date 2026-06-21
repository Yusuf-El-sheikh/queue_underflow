#include <iostream>
#include "../headers/answers.h"
using namespace std;

answers::answers(int answer_id, int answered_question_id, int from_user_id, const string &answer_text, bool is_anonymous)
:post(answer_id, from_user_id, answer_text, is_anonymous), answered_question_id(answered_question_id) 
{
}

int answers::answered_question_id_getter() const
{
    return answered_question_id;
}

void answers::display()
{
    cout << "Answer ID: " << id_getter() << endl;
    cout << "Answered Question ID: " << answered_question_id_getter() << endl;
    cout << "From User ID: " << from_user_id_getter() << endl;
    cout << "Text: " << text_getter() << endl;
    cout << "Is Anonymous: " << (is_anonymous_getter() ? "Yes" : "No") << endl;
}
