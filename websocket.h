#pragma once

#include "SSLhelper.h"
#include "payload.h"
#include <stdlib.h>

typedef struct WEBSOCKET WEBSOCKET;

struct WEBSOCKET{
    SSL* ssl;
};

WEBSOCKET* websocket(char* url, char* port);

byte* websocket_recv(SSL* ssl);

byte* websocket_send(SSL* ssl, char* payload_data);