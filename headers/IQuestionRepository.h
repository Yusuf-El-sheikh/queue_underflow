#include <memory>
#include <string>
#include <vector>
#include "questions.h"
#include "repository.h"

class IQuestionRepository : public repository<questions>
{
public:
    [[nodiscard]] virtual vector<questions> find_by_user_id(int id) = 0 ;
    [[nodiscard]] virtual vector<questions> find_descendants(int parent_id) = 0 ;

    virtual void post_question(int from_user_id, const string &text, bool is_anonymous, int parent_question_id) = 0;

    virtual ~IQuestionRepository() = default ;
};