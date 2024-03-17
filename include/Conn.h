#pragma once

#include <cstdint>

class Conn{
    public:
        enum MY_CONN_TYPE{
            listen = 1,
            client = 2,
        };

        uint8_t type;
        int fd;
        uint32_t service_id;
};