#include <memory>
#include <string>
#include <vector>
#include "answers.h"

class IAnswerRepository
{
public:
    virtual vector<answers> find_by_question_id(int id) = 0 ;

    virtual ~IAnswerRepository() = default ;
};