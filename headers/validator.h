#include <string>
using namespace std;

class validator
{
public:
    validator() = delete;

    static bool validate_email(const string &email);
    static bool validate_password(const string &password);
    static bool validate_text_size(const string &text, int max_size);
};