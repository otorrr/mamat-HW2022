
#include "port.h"

using namespace std;



Port::Port(String pat) : Field("port") , min_port(0) , max_port(65535)
{
    pattern = pat ;
}

Port::~Port() {}

bool Port::match_value(String value) const
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
    size_t packet_size_2;
    int port = 0;
    for(int i = 0; i < 4; i++)
        {
            packet[i].split("=",&packet_2,&packet_size_2);
            if(packet_size_2 == 2)
                {
                    if(packet_2[0].trim().equals(pattern.trim()))
                        {
                            port = packet_2[1].trim().to_integer();
                            if(port > -1 && port < 65536)
                                {
                                    delete[] packet;
                                    delete[] packet_2;
                                    return true;

                                }

                        }
                    delete[] packet_2;
                }
            else
                {
                    delete[] packet;
                    delete[] packet_2;
                    return false;
                }
        }
    delete[] packet;
    delete[] packet_2;
    return false;
}

bool Port::set_value(String value)
{
    String* output;
    size_t size = 0;
    value.split("-",&output ,&size);
    if((output == NULL) || size != 2)
        {
            return false;
        }
    min_port = output[0].trim().to_integer();
    max_port = output[1].trim().to_integer();
    if(min_port < 0 || max_port > 65535 || max_port < min_port)
        {
            delete[] output;
            return false;
        }
    delete[] output;
    return true;
}

