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
    printf("Received message from ");
    uip_debug_ipaddr_print(sender_addr);
    printf("\n");
    simple_udp_sendto(c, data, datalen, sender_addr);
}

PROCESS_THREAD(echo_server_process, ev, data)
{

    static struct simple_udp_connection server_connection;
    PROCESS_BEGIN();
    printf("qua\n\n\n\n");

    /* Get the current address */
    uip_ipaddr_t curr_addr;
    curr_addr = uip_ds6_get_link_local(-1)->ipaddr;
    uip_debug_ipaddr_print(&uip_ds6_get_global(ADDR_PREFERRED)->ipaddr);

    /* Construct ipv6 address */
    uip_ipaddr_t new_addr;
    uip_ip6addr(&new_addr, 0xfd00, 0, 0, 0, 0, 0, 0, 0);

    /* Configure the interface */
    uip_lladdr_t client_lladdr;
    uip_ds6_set_addr_iid(&curr_addr, &client_lladdr);

    /* Add a unicast address to the interface */
    uip_ds6_addr_add(&new_addr, 0, ADDR_AUTOCONF);
    uip_debug_ipaddr_print(&uip_ds6_get_global(ADDR_PREFERRED)->ipaddr);

    simple_udp_register(&server_connection, UDP_SERVER_PORT, NULL,
                        UDP_CLIENT_PORT, receiver_callback);
    PROCESS_END();
}
