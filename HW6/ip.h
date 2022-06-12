#ifndef IP_H
#define IP_H

#include "field.h"
#include "string.h"

class Ip : public Field
{
private:
    String pattern;
    int slash;
public:
    Ip(String pat);
    ~Ip();
    bool set_value(String value);
    bool match_value(String value) const;
};

#endif 
