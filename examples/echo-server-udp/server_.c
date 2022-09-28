#include "contiki.h"
#include "net/ipv6/uip.h"
#include "net/ipv6/uip-ds6.h"
#include "net/ipv6/uip-debug.h"
#include "simple-udp.h"
#include <stdio.h>

#define UDP_SERVER_PORT 5678
#define UDP_CLIENT_PORT 8765

PROCESS(echo_server_process, "echo_server_process");
AUTOSTART_PROCESSES(&echo_server_process);

void receiver_callback(struct simple_udp_connection *c,
                       const uip_ipaddr_t *sender_addr,
                       uint16_t sender_port,
                       const uip_ipaddr_t *receiver_addr,
                       uint16_t receiver_port,
                       const uint8_t *data,
                       uint16_t datalen)
{
    simple_udp_sendto(c, data, datalen, sender_addr);
}

PROCESS_THREAD(echo_server_process, ev, data)
{

    static struct simple_udp_connection server_connection;
    PROCESS_BEGIN();
    simple_udp_register(&server_connection, UDP_SERVER_PORT, NULL,
                        UDP_CLIENT_PORT, receiver_callback);
    PROCESS_END();
}
