#include <bits/stdc++.h>
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
    cout << "Answer ID: " << this->id << endl;
    cout << "Answered Question ID: " << this->answered_question_id << endl;
    cout << "From User ID: " << this->from_user_id << endl;
    cout << "Text: " << this->text << endl;
    cout << "Is Anonymous: " << (this->is_anonymous ? "Yes" : "No") << endl;
}
