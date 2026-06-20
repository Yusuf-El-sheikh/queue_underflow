#include <memory>
#include <string>
#include <vector>
#include "questions.h"

class IQuestionRepository
{
public:
    [[nodiscard]] virtual vector<questions> find_by_user_id(int id) = 0 ;
    [[nodiscard]] virtual vector<questions> find_descendants(int parent_id) = 0 ;

    virtual ~IQuestionRepository() = default ;
};