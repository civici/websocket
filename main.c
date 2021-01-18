#include "sock.h"
#include "SSLhelper.h"
#include "websocket.h"

int main(){
    
    WEBSOCKET* ws = websocket("gateway.discord.gg", "443");
    websocket_recv(ws->ssl);
    puts("done");

}