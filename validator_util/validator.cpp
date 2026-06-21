#include <regex>
#include "../headers/validator.h"

bool validator::validate_email(const string &email)
{
    const regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
    return regex_match(email, pattern);
}

bool validator::validate_password(const string &password)
{
    const regex pattern(R"(^(?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[#$%&*]).{8,}$)");
    return regex_match(password, pattern);
}

bool validator::validate_text_size(const string &text, int max_size)
{
    return text.size() <= max_size;
}