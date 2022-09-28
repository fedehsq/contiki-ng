#include "contiki.h"
#include "net/ipv6/uip.h"
#include "net/ipv6/uip-ds6.h"
#include "net/ipv6/uip-debug.h"
#include "simple-udp.h"
#include <stdio.h>
#define UDP_SERVER_PORT 5678
#define UDP_CLIENT_PORT 8765

PROCESS(echo_client_process, "ipv6 example");
AUTOSTART_PROCESSES(&echo_client_process);

void receiver_callback(struct simple_udp_connection *c,
                       const uip_ipaddr_t *sender_addr,
                       uint16_t sender_port,
                       const uip_ipaddr_t *receiver_addr,
                       uint16_t receiver_port,
                       const uint8_t *data,
                       uint16_t datalen)
{
    printf("Received message from ");
    uip_debug_ipaddr_print(sender_addr);
    printf(" on port %d from port %d with length %d: %s\n",
           receiver_port, sender_port, datalen, data);
}


PROCESS_THREAD(echo_client_process, ev, data)
{

    PROCESS_BEGIN();
    static struct simple_udp_connection server_connection;
    static struct etimer periodic_timer;
    uip_ipaddr_t addr;
    simple_udp_register(&server_connection, UDP_CLIENT_PORT, NULL,
                        UDP_SERVER_PORT, receiver_callback);
    etimer_set(&periodic_timer, 3 * CLOCK_SECOND);
    static char buf[13] = "Hello World!";
    while (1)
    {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
        uip_create_linklocal_allnodes_mcast(&addr);
        simple_udp_sendto(&server_connection, buf, strlen(buf) + 1,
                          &addr);
        etimer_reset(&periodic_timer);
    }
    PROCESS_END();
}
