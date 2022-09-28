#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "sys/log.h"
#include "sys/etimer.h"

// LOG for our application (you cannot downgrade this log at run time
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Traffic rate(8s) */
#define SEND_INTERVAL (8 * CLOCK_SECOND)

/* Link-layer address */
static linkaddr_t sensor_one = {{0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}};
static linkaddr_t sensor_two = {{0x0003, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}};
PROCESS(gateway, "multicast example");
AUTOSTART_PROCESSES(&gateway);

/* Callback for message reception */
static void input_callback(const void *data, uint16_t len, const linkaddr_t *src, const linkaddr_t *dest)
{
    char received_data[strlen((char *)data) + 1];
    if (len == strlen((char *)data) + 1)
    {
        memcpy(&received_data, data, strlen((char *)data) + 1);
        LOG_INFO("Received \"%s\", from ", received_data);
        LOG_INFO_LLADDR(src);
        LOG_INFO_("\n");
    }
}

PROCESS_THREAD(gateway, ev, data)
{
    static struct etimer periodic_timer;

    /* Creation of the message to be sent */
    static char uni_msg[70];
    sprintf(uni_msg, "Gimme sensor values");

    PROCESS_BEGIN();
    /* Set input_callback () as the callback when a message is */
    nullnet_buf = (uint8_t *)uni_msg;
    nullnet_set_input_callback(input_callback);
    /* Send data: every node different from 2 can send */
    if (!linkaddr_cmp(&sensor_one, &linkaddr_node_addr) && !linkaddr_cmp(&sensor_two, &linkaddr_node_addr))
    {
        etimer_set(&periodic_timer, SEND_INTERVAL);
        while (1)
        {
            PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
            LOG_INFO("TIMESTAMP: %lu, Sending BROADCAST \"%s\"\n", clock_seconds(), uni_msg);
            nullnet_len = strlen(uni_msg) + 1;
            NETSTACK_NETWORK.output(NULL);
            etimer_reset(&periodic_timer);
        }
    }
    PROCESS_END();
}