#include "contiki.h"
#include "coap-engine.h"
/* Log configuration */
#include "sys/log.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "g_buf.h"
#include "node-id.h"
#define LOG_MODULE "RPL BR"
#define LOG_LEVEL LOG_LEVEL_INFO
#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678
#define SENSOR_ONE 2
#define SENSOR_TWO 3
#define SENSOR_THREE 4

static struct simple_udp_connection udp_conn;

static void udp_rx_callback(
    struct simple_udp_connection *c,
    const uip_ipaddr_t *sender_addr,
    uint16_t sender_port,
    const uip_ipaddr_t *receiver_addr,
    uint16_t receiver_port,
    const uint8_t *data,
    uint16_t datalen)
{
    LOG_INFO_6ADDR(sender_addr);
    LOG_INFO(" sent: %s\n", data);
    /*
     * The first character is the sensor number, 
     * the rest of the string is the sensor data
     */
    int id = data[0] - '0';
    if (id == SENSOR_ONE)
    {
        memcpy(g_buf_sensor_one, data, datalen);
    }
    else if (id == SENSOR_TWO)
    {
        memcpy(g_buf_sensor_two, data, datalen);
    }
    else if (id == SENSOR_THREE)
    {
        memcpy(g_buf_sensor_three, data, datalen);
    }
}
// Define the resource
extern coap_resource_t res_hello;
PROCESS(coap_server, "Coap server");
AUTOSTART_PROCESSES(&coap_server);
PROCESS_THREAD(coap_server, ev, data)
{
    PROCESS_BEGIN();
    simple_udp_register(&udp_conn, UDP_SERVER_PORT, NULL, UDP_CLIENT_PORT, udp_rx_callback);
    g_buf_sensor_one = (char *)calloc(64, sizeof(char));
    g_buf_sensor_two = (char *)calloc(64, sizeof(char));
    g_buf_sensor_three = (char *)calloc(64, sizeof(char));
    /* Activation of a resource */
    coap_activate_resource(&res_hello, "resources/hello");
#if BORDER_ROUTER_CONF_WEBSERVER
    PROCESS_NAME(webserver_nogui_process);
    process_start(&webserver_nogui_process, NULL);
#endif /* BORDER_ROUTER_CONF_WEBSERVER */

    LOG_INFO("Contiki-NG Border Router started\n");
    while (1)
    {
        PROCESS_WAIT_EVENT();
    }
    PROCESS_END();
}
