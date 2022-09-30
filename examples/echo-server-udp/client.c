#include "contiki.h"
#include "net/routing/routing.h"
#include "random.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "node-id.h"

#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO
#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678
static struct simple_udp_connection udp_conn;
#define START_INTERVAL (5 * CLOCK_SECOND)

PROCESS(udp_client_process, "UDP client");
AUTOSTART_PROCESSES(&udp_client_process);
/*---------------------------------------------------------------------------*/
static void udp_rx_callback(struct simple_udp_connection *c, const uip_ipaddr_t *sender_addr,
                            uint16_t sender_port, const uip_ipaddr_t *receiver_addr, uint16_t receiver_port, const uint8_t *data, uint16_t datalen)
{
  LOG_INFO("\nReceived: %s from: ", data);
  LOG_INFO_6ADDR(sender_addr);
}

PROCESS_THREAD(udp_client_process, ev, data)
{
  static struct etimer periodic_timer;
  uip_ipaddr_t dest_ipaddr;
  uip_ip6addr(&dest_ipaddr, 0xfe80, 0, 0, 0, 0x0201, 0x0001, 0x0001, 0x0001);
  PROCESS_BEGIN();
  simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL, UDP_SERVER_PORT, udp_rx_callback);
  etimer_set(&periodic_timer, START_INTERVAL);
  while (1)
  {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    char buf[13] = "Hello World!";
    simple_udp_sendto(&udp_conn, buf, strlen(buf) + 1, &dest_ipaddr);
    etimer_reset(&periodic_timer);
  }
  PROCESS_END();
}
