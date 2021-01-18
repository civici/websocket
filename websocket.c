#include "websocket.h"

WEBSOCKET* websocket(char* url, char* port){

    WEBSOCKET* socket = malloc(sizeof(WEBSOCKET));
    SOCKET s = OpenConnection(url, port);
    socket->ssl = openssl_conn(s);
    int urllen = strlen(url);
    char* req = calloc(137 + urllen, 1);
    ;
    snprintf(req, 137 + urllen, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: upgrade\r\nUpgrade: websocket\r\nSec-Websocket-Key: RCQCWB5InH/Zx7O8ezw==\r\nSec-WebSocket-Version: 13\r\n\r\n", url);
    printf("line2: %s strlen :%d\n", req, strlen(req));
    for (int i = 0; i < 137 + urllen; i++){
        printf("%c %d\n", req[i], req[i]);
    }
    ssl_send(socket->ssl, req, strlen(req));
    char* resp;
    ssl_recv(socket->ssl, resp);
    printf("%s\n", resp);
    return websocket;
}

byte* websocket_recv(SSL* ssl){
    byte* resp;
    int bytes = ssl_recv(ssl, resp);
    char* payload_data = parse_frame(resp, bytes);
    puts(payload_data);
    return payload_data;
}

byte* websocket_send(SSL* ssl, char* payload_data){
    FRAME* frame = make_frame(payload_data);
    ssl_send(ssl, frame->payload, frame->bytes_to_send);
    return websocket_recv(ssl);
}

