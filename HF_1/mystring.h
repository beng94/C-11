#include <iostream>

class StringValue
{
    private:
        int ref_ = 1;
        char* str;
    public:
        StringValue (const char*);
        ~StringValue ();

        char* get_str () const;

        void ref ();
        void unref ();
        bool deletable () const;

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

        int length() const;
        MyString operator+ (const MyString&) const;
        MyString operator+ (const char) const;
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
