#include <memory>
#include <string>
#include "user_info.h"
#include "repository.h"

using namespace std;
/*
this interface was made in case any changes happened to the service 
layer that it would make it easier to apply by simply swapping the implementation of the 
interfaces rather than scrapping concrete logic
*/
class IUserRepository : public repository<user_info>
{
public:
    [[nodiscard]] virtual unique_ptr<user_info> find_by_email(const string &email) = 0;
    [[nodiscard]] virtual bool validate_credentials(const string &email, const string &password) = 0;

    virtual ~IUserRepository() = default ; 
};