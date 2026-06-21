#pragma once
#include <string>
#include <iostream>
using namespace std;

class post
{
    // base class attributes are protected as industry standards so derived classes can directly access them
protected:
    int id;
    int from_user_id;

    string text;

    bool is_anonymous;

    // methods definition : some may be virtual to be overloaded later and others will be concrete since they will need no change
public:
    post(int id, int from_user_id, const string &text, bool is_anonymous);

    /* about display function its a pure virtual function made to be an identifier to each object made of base class post
    to tell how it will behave, whether its a quetion or an answer, it also forbids the base class object from being created 
    since its now an abstracted class*/

    virtual void display() = 0 ;//pure virtual MUST IMPLEMENT

    [[nodiscard]] int id_getter() const ;
    [[nodiscard]] int from_user_id_getter() const ;

    [[nodiscard]] const string& text_getter() const;
    
    [[nodiscard]] bool is_anonymous_getter() const;

    /*operators overloading
    here operators will be overloaded to make it simpler for filtering and search functions to
    compare data instead of making lambdas in every single one of them as a comparator
    */

    bool operator<(const post &other) const;
    bool operator==(const post &other) const;

    //destructor  is virtual since each derived class will have to free its data in a specific way
    virtual ~post() = default;
};

/*
the output stream operator overload function shouldnt be a member function
meaning it shouldnt be a part of any class since the function itself belong to the ostream class which
we wont modify so we will keep it outside of this class
*/

ostream &operator<<(ostream &os, const post &other) ;
