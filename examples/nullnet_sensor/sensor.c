#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "sys/log.h"
#include "sys/etimer.h"
#include "my_sensor.h"
#include "os/dev/leds.h"

// LOG for our application (you cannot downgrade this log at run time
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Traffic rate(8s) */
#define SEND_INTERVAL (8 * CLOCK_SECOND)

/* Link-layer address */
static linkaddr_t gateway = {{0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}};
static struct sensor sensor;
PROCESS(m_sensor, "unicast example");
AUTOSTART_PROCESSES(&m_sensor);

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
        /* Creation of the message to be sent */
        static char uni_msg[70];
        sprintf(uni_msg, "Temperature: %d, Humidity: %d, Battery Level: %d", sensor.temperature, sensor.humidity, sensor.battery_level);
        leds_off(LEDS_ALL);
        leds_single_on(get_led_color(&sensor));
        init_sensor(&sensor);
        nullnet_buf = (uint8_t *)uni_msg;
        nullnet_len = strlen(uni_msg) + 1;
        NETSTACK_NETWORK.output(&gateway);
    }
}

PROCESS_THREAD(m_sensor, ev, data)
{
    PROCESS_BEGIN();
    nullnet_set_input_callback(input_callback);
    PROCESS_END();
}
