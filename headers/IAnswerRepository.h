#include <memory>
#include <string>
#include <vector>
#include "answers.h"
#include "repository.h"

class IAnswerRepository : public repository<answers>
{
public:
    [[nodiscard]] virtual vector<answers> find_by_question_id(int id) = 0 ;

    virtual void post_answer(int answered_question_id, int from_user_id, const string &answer_text, bool is_anonymous) = 0;

    virtual ~IAnswerRepository() = default ;
};