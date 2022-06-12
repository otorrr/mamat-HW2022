
#include "ip.h"
#include "string.h"

using namespace std;

Ip::Ip(String pat) : Field(pat) , slash(0) 
{
    pattern = pat;
    slash = 0;
}

Ip::~Ip() {}

bool Ip::match_value(String value) const
{
    String* packet;
    size_t packet_size = 0;
    value.split(",",&packet,&packet_size);
    if(packet_size != 4)
        {
            delete[] packet;
            return false;
        }
    String* packet_2;
    size_t packet_size_2 = 0;
    int bite = 0;
    String* ip_output;
    size_t ip_size = 0;
    for(size_t i = 0; i < 4; i++)
        {
            packet[i].split("=",&packet_2,&packet_size_2);
            if(packet_size_2 == 2)
                {
                    if(packet_2[0].trim().equals(pattern.trim()))
                    {
                        packet_2[1].split(".",&ip_output,&ip_size);
                        if(ip_size == 4)
                            {
                                for(int j = 0; j < 4; j++)
                                    {
                                        bite = ip_output[j].trim().to_integer();
                                        if(bite < 0 || bite > 255)
                                        {
                                            delete[] packet;
                                            delete[] packet_2;
                                            delete[] ip_output;
                                            return false;
                                        }
                                    }
                                delete[] packet;
                                delete[] packet_2;
                                delete[] ip_output;
                                return true;
                            }
                        else
                            {
                                delete[] packet;
                                delete[] packet_2;
                                delete[] ip_output;
                                return false;
                            }

                    }
                        delete[] packet_2;
                }
            else
                {
                    delete[] packet;
                    delete[] packet_2;
                    delete[] ip_output;
                    return false;
                }
        }
            delete[] packet;
            delete[] packet_2;
            delete[] ip_output;
            return false;
}

bool Ip::set_value(String value)
{
    String* output;
    size_t size = 0;
    value.split(".,/",&output ,&size);
    if((output == NULL) || size != 5)
        {
            return false;
        }
    slash = output[4].trim().to_integer();
    if(slash < 0 || slash > 32)
        {
            delete[] output;
            return false;
        }
    int bite = 0;
    for(size_t i = 0; i < size - 1; i++)
    {
        bite = output[i].trim().to_integer();
        if(bite < 0 || bite > 255)
            {
                delete[] output;
                return false;
            }
    }
    delete[] output;
    return true;
}
