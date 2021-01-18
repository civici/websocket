#pragma once

#include <openssl/ssl.h>
#include "sock.h"

#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "libcrypto.lib")

typedef byte uint8_t;

SSL* openssl_conn(SOCKET conn);

int ssl_recv(SSL* ssl, char* buffer);

void ssl_send(SSL* ssl, char* input, int byte_amount);