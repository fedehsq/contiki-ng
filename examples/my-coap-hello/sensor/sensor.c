#include "contiki.h"
#include "net/routing/routing.h"
#include "random.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "node-id.h"
#include "os/dev/leds.h"
#include "my_sensor.h"
#include "g_sensors.h"
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
  uip_ipaddr_t server_ipaddr;//, sensor_one_ipaddr, sensor_two_ipaddr, sensor_three_ipaddr;
  uip_ip6addr(&server_ipaddr, 0xfd00, 0, 0, 0, 0x0201, 0x0001, 0x0001, 0x0001);
  // uip_ip6addr(&sensor_one_ipaddr, 0xfe80, 0, 0, 0, 0x0202, 0x0002, 0x0002, 0x0002);
  // uip_ip6addr(&sensor_two_ipaddr, 0xfe80, 0, 0, 0, 0x0203, 0x0003, 0x0003, 0x0003);
  // uip_ip6addr(&sensor_three_ipaddr, 0xfe80, 0, 0, 0, 0x0204, 0x0004, 0x0004, 0x0004);
  PROCESS_BEGIN();
  simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL, UDP_SERVER_PORT, udp_rx_callback);
  etimer_set(&periodic_timer, START_INTERVAL);
  while (1)
  {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    static char buf[70];
    // compare the current id with the sensor id
    if (node_id == 1) {
      sprintf(buf, "Temperature: %d, Humidity: %d, Battery Level: %d", sensor_one.temperature, sensor_one.humidity, sensor_one.battery_level);
      leds_off(LEDS_ALL);
      leds_single_on(get_led_color(&sensor_one));
      init_sensor(&sensor_one);
    } else if (node_id == 2) {
      sprintf(buf, "Temperature: %d, Humidity: %d, Battery Level: %d", sensor_two.temperature, sensor_two.humidity, sensor_two.battery_level);
      leds_off(LEDS_ALL);
      leds_single_on(get_led_color(&sensor_two));
      init_sensor(&sensor_two);
    } else if (node_id == 3) {
      sprintf(buf, "Temperature: %d, Humidity: %d, Battery Level: %d", sensor_three.temperature, sensor_three.humidity, sensor_three.battery_level);
      leds_off(LEDS_ALL);
      leds_single_on(get_led_color(&sensor_three));
      init_sensor(&sensor_three);
    }
    simple_udp_sendto(&udp_conn, buf, strlen(buf) + 1, &server_ipaddr);
    etimer_reset(&periodic_timer);
    puts("Sent");
  }
  PROCESS_END();
}
