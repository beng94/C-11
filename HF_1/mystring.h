#include <iostream>

class StringValue
{
    private:
        int ref_ = 1;
        char* str;
    public:
        StringValue (const char*);
        ~StringValue ();

        char* get_str ();

        void ref ();
        void unref ();
        bool deletable ();

#ifdef DEBUG
        int get_ref_cnt();
#endif
};

class MyString
{
    private:
        StringValue* ptr;
    public:
        MyString ();
        MyString (const char*);
        MyString (const MyString&);
        MyString& operator= (const MyString&);
        ~MyString ();

        int length();
        MyString operator+ (const MyString&);
        MyString operator+ (const char);
        void operator+= (const MyString&);
        void operator+= (const char);
        char& operator[] (int);

        friend std::ostream& operator<< (std::ostream&, const MyString&);

#ifdef DEBUG
        const char* get_str();
        StringValue* get_ptr();
        int get_ref_cnt();
#endif
};

std::ostream& operator<< (std::ostream& os, const MyString& rhs);
std::istream& operator>> (std::istream&, MyString&);
