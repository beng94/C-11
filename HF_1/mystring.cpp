#include <string.h>
#include <stdexcept>
#include <map>

#include "mystring.h"

StringValue::StringValue (const char* str)
{
    /* Lemásolom a kapott karaktertömböt */
    size_t size = strlen(str);
    this->str = new char[size + 1];
    strcpy(this->str, str);
    this->str[size] = '\0';
}

StringValue::~StringValue ()
{
    delete[] this->str;
}

/* Segédfüggvény, hogy a MyString elérje a beslő string értéket */
char* StringValue::get_str () const
{
    return this->str;
}

/* Referencia számláló növelése */
void StringValue::ref ()
{
    (this->ref_)++;
}

/* Referencia számláló csökkentése */
void StringValue::unref ()
{
    (this->ref_)--;
}

/* Megadja, hogy a StringValue felszabadítható-e az alapján,
 * hogy van-e még rá valahol hivatkozás. */
bool StringValue::deletable () const
{
    return this->ref_ == 0;
}

/* Segédosztály, hogy a map-ban tárolt char*-okat össze tudjam hasonlítani */
struct cmp_str
{
    bool operator() (const char* a, const char* b)
    {
        return strcmp(a, b) < 0;
    }
};

static std::map<const char*, StringValue*, cmp_str> str_container;

/* Megkeresem, hogy van-e már ilyen string a tárolóban,
 * ha igen, visszaadom a StringValue címét, egyébkétn nullpptr-t */
static StringValue* find (const char* str)
{
    auto id = str_container.find(str);

    /* Megtaláltam */
    if (id != str_container.end())
        return id->second;

    return nullptr;
}


/* Ezzel a függvénnyel tud a MyString új StringValue*-t kérni,
 * ha már van ilyen string tartalmú StringValue, akkor megkapja
 * azt a pointert, ha nincsen, akkor létrehozok egyet. */
static StringValue* create_string(const char* str)
{
    /* Megkeresem a tárolóban a string értéket */
    StringValue* val = find(str);
    if(val != nullptr)
    {
        /* Ha megtaláltam, növelem a referencia számlálót és visszaadom
         * a megtalált pointert */
        val->ref();
        return val;
    }

    /* Ha nem találtam meg a keresett string-et, akkor létrehozok egy
     * új StringValue-t a kívánt string értékkel és hozzáadom
     * a tárolóhoz. */
    val = new StringValue(str);
    /* Sok időt spórolhat az ember, ha nem a globális str-t helyezi
     * el a map-ben, hanem a StringValue-ben tárolt értéket... */
    str_container.insert(std::pair<const char*, StringValue*>(val->get_str(), val));

    return val;
}

/* Ezzel a függvénnyel jelzi a MyString, hogy a továbbiakban
 * nincsen szüksége a StringValue*-re. */
static void del_str (StringValue* str)
{
    auto id = str_container.find(str->get_str());

    /* Biztosan benne van a tárolóban az elem, úgyhogy nincs szükség
     * leellenőrizni az id-t. Törlöm a tárolóból a bejegyzést. */
    str_container.erase(id);

    delete str;
}

/* Default ctor, üres string-et hoz létre */
MyString::MyString ()
{
    ptr = create_string("");
}

/* Ctor char*-ból */
MyString::MyString (const char* str)
{
    ptr = create_string(str);
}

/* Copy ctor, lemásolom a pointert, növelem a referencia számlálót. */
MyString::MyString (const MyString& str)
{
    this->ptr = str.ptr;
    this->ptr->ref();
}

MyString& MyString::operator= (const MyString& rhs)
{
    /* Aktuális pointerre már nincs szükség, csökkentem a
     * referencia számlálót */
    this->ptr->unref();
    /* Ha már senki más nem hivatkozik a StringValue-ra, akkor
     * felszabadítom a pointert. */
    if (this->ptr->deletable())
        del_str(this->ptr);

    /* Beállítom az új pointert és növelem az új érték
     * referencia számlálóját. */
    this->ptr = rhs.ptr;
    this->ptr->ref();

    return *this;
}

MyString::~MyString ()
{
    /* Rerefencia számláló csökkentése */
    this->ptr->unref();

    /* StringValue felszabadítása, ha más már nem hivatkozik rá */
    if (this->ptr->deletable())
        del_str(this->ptr);
}

/* Visszaadja a string hosszát */
int MyString::length () const
{
    return strlen(this->ptr->get_str());
}

/* Tagfüggvényként írtam meg az operátorokat, mert nem
 * akartam gettereket írni. */

MyString MyString::operator+ (const MyString& rhs) const
{
    /* Azt mondta a fordító, hogy nem illik változó méretű
     * tömböt létrehozni, úgyhogy dinamikusan foglalom a
     * segéd tömböt, amiben egymás után fűzöm a két stringet */
    const size_t size = strlen(this->ptr->get_str()) + strlen(rhs.ptr->get_str()) + 1;
    char* tmp_str = new char[size];
    strcpy(tmp_str, this->ptr->get_str());
    strcat(tmp_str, rhs.ptr->get_str());
    tmp_str[size] = '\0';

    /* Elmentem a visszatérési értéket, mivel fel kell szabadítani
     * a dinamikusan foglalt tmp_str tömböt. */
    MyString ret_value(tmp_str);
    delete tmp_str;

    return ret_value;
}

MyString MyString::operator+ (const char c) const
{
    /* Visszavezetem az előző függvényre. Mivel const char*-ot
     * vár a MyString ctor-a, létrehozok a char-ból egy char*-ot. */
    char array[2];
    array[0] = c;
    array[1] = '\0';

    return *this + MyString(array);
}

/* Visszavezetem az előző függvényre */
void MyString::operator+= (const MyString& rhs)
{
    *this = *this + rhs;
}

/* Visszavezetem az előző függvényekre */
void MyString::operator+= (const char c)
{
    *this = *this + c;
}

/* Referenciát adok vissza, hogy meg lehessen változtatni a
 * char értékét. */
char& MyString::operator[] (int index)
{
    /* Indexelés ellenőrzése */
    if (index > this->length() - 1 || index < 0)
        throw std::out_of_range("MyString::operator[]");

    /* Létrehozok egy új StringValue-t */
    StringValue* p = create_string(this->ptr->get_str());

    /* Törlöm az eddig tárolt pointert */
    this->ptr->unref();
    if(this->ptr->deletable())
        del_str(this->ptr);

    /* Lecserélem az aktuális pointert az újjonnan létrehozottra,
     * hogy ha valaki megváltoztatja a függvény általn visszaadott
     * char&-t, akkor ne változzon meg minden az azonos StringValue-re
     * hivatkozó MyString-ekben az adott karaktert. */
    this->ptr = p;

    /* Visszaadom a kért karakter referenciáját */
    return this->ptr->get_str()[index];
}

std::ostream& operator<< (std::ostream& os, const MyString& rhs)
{
    /* Kiírom a string értékét */
    os << rhs.ptr->get_str();

    return os;
}

/* A megadott bemenetről beolvas egy stringet, dinamikus
 * memóriakezelést használ. Opcionális megoldás lett volna,
 * hogy egy 'nagy' fix méretű tömbbe olvasok be, de az úgy
 * nem izgalmas :)*/
static const char* read(std::istream& in)
{
    size_t size = 20;
    char* str = new char[size];

    /* Addig megy, amíg hiba nélkül be nem olvassa a karaktereket,
     * vagyis amígy tud még karaktert olvasni */
    do
    {
        /* Törli a failbit-et (és minden egyéb bitet is) */
        in.clear();

        /* Ideiglenes változóba beolvasom a karaktereket */
        char* tmp = new char[size];
        in.getline(tmp, size);

        /* Ha nem tudott mindent beolvasni */
        if (in.fail())
        {
            /* Létrehozok egy kétszer nagyobb tömböt és belemásolom
             * a régi string értéket, majd hozzáfűzöm az új értéket */
            char* tmp_str = new char[size * 2];
            strcpy(tmp_str, str);
            strcat(tmp_str, tmp);

            /* Frissítem az str értékét a temporális változóval */
            delete str;
            str = new char[size * 2];
            str = tmp_str;
            size *= 2;
        }

        /* Ha sikeresen beolvasott minden karaktert, akkor csak
         * hozzáfűzöm az új karaktereket */
        else
            strcat(str, tmp);
    } while(in.fail());

    return str;
}

std::istream& operator>> (std::istream& in, MyString& rhs)
{
    const char* str = read(in);

    rhs = MyString(str);
    /* Fel kell szabadítanom a read-ben lefoglalt memóriát */
    delete str;

    return in;
}

/* Debuggoláshoz használt függvények, hogy elérjem a változók
 * privát értékeit */
#ifdef DEBUG
int StringValue::get_ref_cnt()
{
    return this->ref_;
}

const char* MyString::get_str()
{
    return this->ptr->get_str();
}

StringValue* MyString::get_ptr()
{
    return this->ptr;
}

int MyString::get_ref_cnt()
{
    return this->ptr->get_ref_cnt();
}
#endif
