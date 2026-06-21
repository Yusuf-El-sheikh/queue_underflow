#include <memory>
#include <string>
#include <vector>
#include "answers.h"
#include "repository.h"

class IAnswerRepository : public repository<answers>
{
public:
    [[nodiscard]] virtual vector<answers> find_by_question_id(int id) = 0 ;

    virtual ~IAnswerRepository() = default ;
};