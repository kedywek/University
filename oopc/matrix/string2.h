#ifndef __RCSTRING_H__
#define __RCSTRING_H__
#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
using namespace std;

class rcstring {
    struct rctext;
    rctext* data;

  public:
    class Range {};
    class Cref;
    rcstring();
    rcstring(const char*);
    rcstring(const rcstring&);
    ~rcstring();
    rcstring& operator=(const rcstring&);
    rcstring& operator+=(const rcstring&);
    rcstring operator+(const rcstring&) const;
    friend ostream& operator<<(ostream&, const rcstring&);
    void check(unsigned int i) const;
    char read(unsigned int i) const;
    void write(unsigned int i, char c);
    char operator[](unsigned int i) const;
    Cref operator[](unsigned int i);
};

struct rcstring::rctext {
    char* s;
    unsigned int size;
    unsigned int n;

    rctext(unsigned int nsize, const char* p)
    {
        n = 1;
        size = nsize;
        s = new char[size + 1];
        strncpy(s, p, size);
        s[size] = '\0';
    };
    ~rctext()
    {
        delete[] s;
    };
    rctext* detach()
    {
        if (n == 1)
            return this;
        rctext* t = new rctext(size, s);
        n--;
        return t;
    };

  private:
    rctext(const rctext&);
    rctext& operator=(const rctext&);
};

class rcstring::Cref {
    friend class rcstring;
    rcstring& s;
    int i;
    Cref(rcstring& ss, unsigned int ii) : s(ss), i(ii){};

    public:
    operator char() const
    {
        cout << "operator char() const" << endl;
        return s.read(i);
    }
    rcstring::Cref& operator=(char c)
    {
        cout << "void operator = (char c)" << endl;
        s.write(i, c);
        return *this;
    }
    rcstring::Cref& operator=(const Cref& ref)
    {
        return operator=((char)ref);
    }
};
inline rcstring::rcstring()
{
    data = new rctext(0, "");
}

inline rcstring::rcstring(const rcstring& x)
{
    x.data->n++;
    data = x.data;
}
inline rcstring::~rcstring()
{
    if (--data->n == 0)
        delete data;
}

rcstring& rcstring::operator=(const rcstring& x)
{
    x.data->n++;
    if (--data->n == 0)
        delete data;
    data = x.data;
    return *this;
}

rcstring::rcstring(const char* s)
{
    data = new rctext(strlen(s), s);
}

ostream& operator<<(ostream& o, const rcstring& s)
{
    return o << s.data->s;
}

rcstring& rcstring::operator+=(const rcstring& s)
{
    unsigned int newsize = data->size + s.data->size;
    rctext* newdata = new rctext(newsize, data->s);
    strcat(newdata->s, s.data->s);
    if (--data->n == 0)
        delete data;
    data = newdata;
    return *this;
}

rcstring rcstring::operator+(const rcstring& s) const
{
    return rcstring(*this) += s;
}

inline void rcstring::check(unsigned int i) const
{
    if (data->size <= i)
        throw Range();
}
inline char rcstring::read(unsigned int i) const
{
    return data->s[i];
}
inline void rcstring::write(unsigned int i, char c)
{
    data = data->detach();
    data->s[i] = c;
}

char rcstring::operator[](unsigned int i) const
{
    cout << "char rcstring::operator[](unsigned int i) const" << endl;
    check(i);
    return data->s[i];
}

rcstring::Cref rcstring::operator[](unsigned int i)
{
    cout << "Cref rcstring::operator[](unsigned int i)" << endl;
    check(i);
    return Cref(*this, i);
}

#endif