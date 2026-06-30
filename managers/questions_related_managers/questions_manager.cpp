#include "../headers/questions_manager.h"

questions_manager::questions_manager(unique_ptr<IQuestionRepository> repo) : questions_repo(std::move(repo)) {}

void questions_manager::post_question(int from_user_id, const string &text , bool is_anonymous, int parent_question_id = -1)
{
    /*gotta fix up the questions and answers dao by changing the fact that it takes an object of each type
    so it can save, which is incompatible due to the fact that i cant just build a quiestion by assigning its id
    which gets me stuck into a loop where i cant make an object to call save and cant call save cuz i need an object*/
}

void questions_manager::delete_question(int question_id)
{
    questions_repo->remove(question_id);
}

vector<questions> questions_manager::get_all_questions()
{
    return questions_repo->find_all();
}

vector<questions> questions_manager::get_user_questions(int from_user_id)
{
    return questions_repo->find_by_user_id(from_user_id);
}

unique_ptr<questions> questions_manager::get_question(int question_id)
{
    return questions_repo->find_by_id(question_id) ;
}

