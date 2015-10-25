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

        /* Subclass, hogy elérje a MyString privát adattagját. */
        class Proxy
        {
            private:
                int id;
                 MyString* mstrptr;

            public:
                Proxy() = delete;
                Proxy(int, MyString*);

                Proxy& operator= (char);
                operator char ();
        };

    public:
        MyString ();
        MyString (const char*);
        MyString (const MyString&);
        MyString (MyString&&) noexcept;
        MyString& operator= (const MyString&);
        ~MyString ();

        int length() const;
        MyString operator+ (const MyString&) const;
        MyString operator+ (const char) const;
        void operator+= (const MyString&);
        void operator+= (const char);
        Proxy operator[] (int);
        bool operator== (const MyString&) const;

        friend std::ostream& operator<< (std::ostream&, const MyString&);

#ifdef DEBUG
        const char* get_str();
        StringValue* get_ptr();
        int get_ref_cnt();
#endif
};

std::ostream& operator<< (std::ostream& os, const MyString& rhs);
std::istream& operator>> (std::istream&, MyString&);
