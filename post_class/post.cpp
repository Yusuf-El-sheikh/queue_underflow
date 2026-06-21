#include <iostream>
#include "../headers/post.h"

using namespace std;

/*using intializer lists are the only way of handeling const variables cleanly(in case there is any)*/
post::post(int id, int from_user_id, const string &text, bool is_anonymous)
    : id(id), from_user_id(from_user_id), text(text), is_anonymous(is_anonymous)
{
}

int post::id_getter() const
{
    return id;
}

int post::from_user_id_getter() const
{
    return from_user_id;
}

const string& post::text_getter() const
{
    return text;
}

bool post::is_anonymous_getter() const
{
    return is_anonymous;
}

bool post::operator<(const post &other) const
{
    return this->id < other.id;
}

bool post::operator==(const post &other) const
{
    return this->id == other.id;
}

ostream& operator<<(ostream &os, const post &other)
{
    os << "Post ID: " << other.id_getter() << endl;
    os << "From User ID: " << other.from_user_id_getter() << endl;
    os << "Text: " << other.text_getter() << endl;
    os << "Is Anonymous: " << (other.is_anonymous_getter() ? "Yes" : "No") << endl;
    return os;
}
