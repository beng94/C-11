#include <iostream>

#ifdef DEBUG
    #include <string.h>
    #include <assert.h>
    #include <sstream>
#endif

#include "mystring.h"

/* Szerettem volna kipróbálni a DEBUG makrót/flag-et, hogy a
 * Makefile-ból kapja meg az értékét. Így utólag elég fölöslegesnek
 * tűnik ez a sok ifdef, de mindenképpen érdemes volt egyszer
 * kipróbálni.
 *
 * Assert-ekkel ellenőrzöm mindig a változók helyes értékét,
 * illetve hogy a belső változókban is helyes érték van-e.
 *
 * A tesztesetek szerintem magukért beszélnek, ezért nem
 * írtam hozzá kommenteket.*/
int main()
{
    MyString a;
    #ifdef DEBUG
        std::cout << "Testing MyString(): ";
        assert(strcmp(a.get_str(), "") == 0);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    MyString b("monkey");
    #ifdef DEBUG
        std::cout << "Testing MyString(const char*): ";
        assert(strcmp(b.get_str(), "monkey") == 0);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    MyString c(b);
    #ifdef DEBUG
        std::cout << "Testing MyString(const MyString&): ";
        assert(strcmp(c.get_str(), "monkey") == 0 &&
               strcmp(b.get_str(), "monkey") == 0 &&
               b.get_ref_cnt() == 2 &&
               b.get_ptr() == c.get_ptr());
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    MyString d, e;
    d = e = "monkey";
    #ifdef DEBUG
        std::cout << "Testring MyString operator= (const MyString&): ";
        assert(strcmp(d.get_str(), e.get_str()) == 0 &&
               strcmp(d.get_str(),"monkey") == 0 &&
               d.get_ptr() == e.get_ptr() &&
               d.get_ref_cnt() == 2);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    #ifdef DEBUG
        std::cout << "Testing length(): ";
        assert(d.length() == 6);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    MyString f("little");
    MyString g("donkey");
    MyString h = f + g;
    #ifdef DEBUG
        std::cout << "Testing MyString operator+ (const MyString&): ";
        assert(strcmp(h.get_str(), "littledonkey") == 0 &&
               h.get_ref_cnt() == 1);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    MyString i = f + '?';
    #ifdef DEBUG
        std::cout << "Testing MyString operator+ (const char): ";
        assert(strcmp(i.get_str(), "little?") == 0 &&
               i.get_ref_cnt() == 1);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    MyString j = "small";
    MyString k = "pig";
    j += k;
    #ifdef DEBUG
        std::cout << "Testing MyString oprator+= (const MyString&): ";
        assert(strcmp(j.get_str(), "smallpig") == 0 &&
               j.get_ref_cnt() == 1 &&
               strcmp(k.get_str(), "pig") == 0);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    MyString l = "small";
    l += '?';
    #ifdef DEBUG
        std::cout << "Testing MyString operator+= (const char): ";
        assert(strcmp(l.get_str(), "small?") == 0 &&
               l.get_ref_cnt() == 1);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    MyString m = "big";
    #ifdef DEBUG
        std::cout << "Testing char& operator[] (int): ";
        char n = m[0];
        m[0] = '!';
        assert(strcmp(m.get_str(), "!ig") == 0 &&
               n == 'b');
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    MyString o = "elephant";
    #ifdef DEBUG
        std::cout << "Testing std::ostream& operator<<(): ";
        std::stringstream ss;
        ss << o;
        assert(strcmp(ss.str().c_str(), "elephant") == 0);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    #ifdef DEBUG
        std::cout << "Testing std::istream& operator(): ";
        std::stringstream ss_1 ("monkey");
        MyString p;
        ss_1 >> p;
        assert(strcmp(p.get_str(), "monkey") == 0 &&
               p.get_ref_cnt() == 1);
        std::cout << "\033[1;32mSuccessful\033[0m" << std::endl;
    #endif

    return 0;
}
