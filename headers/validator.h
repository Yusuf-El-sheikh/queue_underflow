#include <string>
using namespace std;

class validator
{
public:
    static constexpr int MAX_POST_LENGTH = 1000;

    validator() = delete;

    [[nodiscard]] static bool validate_email(const string &email);
    [[nodiscard]] static bool validate_password(const string &password);
    [[nodiscard]] static bool validate_text_size(const string &text, int max_size);
};