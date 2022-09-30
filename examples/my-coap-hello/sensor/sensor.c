#include "contiki.h"
#include "net/routing/routing.h"
#include "random.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "node-id.h"
#include "os/dev/leds.h"
#include "my_sensor.h"
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO
#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678
#define START_INTERVAL (5 * CLOCK_SECOND)

PROCESS(udp_client_process, "UDP client");
AUTOSTART_PROCESSES(&udp_client_process);
PROCESS_THREAD(udp_client_process, ev, data)
{
  static struct simple_udp_connection udp_conn;
  static struct sensor sensor;
  static struct etimer periodic_timer;
  uip_ipaddr_t server_ipaddr;
  uip_ip6addr(&server_ipaddr, 0xfd00, 0, 0, 0, 0x0201, 0x0001, 0x0001, 0x0001);
  PROCESS_BEGIN();
  simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL, UDP_SERVER_PORT, NULL);
  etimer_set(&periodic_timer, START_INTERVAL);
  static char buf[70];
  while (1)
  {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    sprintf(buf, "%d: Temperature: %d, Humidity: %d, Battery Level: %d", node_id, sensor.temperature, sensor.humidity, sensor.battery_level);
    leds_off(LEDS_ALL);
    leds_single_on(get_led_color(&sensor));
    init_sensor(&sensor);
    simple_udp_sendto(&udp_conn, buf, strlen(buf) + 1, &server_ipaddr);
    etimer_reset(&periodic_timer);
  }
  PROCESS_END();
}
