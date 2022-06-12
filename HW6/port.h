//
// Created by htc-i7 on 6/8/2022.
//

#ifndef PORT_H
#define PORT_H

#include "field.h"

class Port : public Field
{
private:
    String pattern;
    int min_port;
    int max_port;
public:
    Port(String pat);
    ~Port();
    bool set_value(String value);
    bool match_value(String value) const;
};

#endif 
