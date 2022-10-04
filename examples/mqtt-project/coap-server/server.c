#include "contiki.h"
#include "coap-engine.h"
/* Log configuration */
#include "sys/log.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "g_buf.h"
#include "node-id.h"
#include <stdio.h>

// Define the resource
extern coap_resource_t res_hello;
PROCESS(coap_server, "Coap server");
AUTOSTART_PROCESSES(&coap_server);
PROCESS_THREAD(coap_server, ev, data)
{
    PROCESS_BEGIN();
    g_buf_sensor_one = (char *)calloc(64, sizeof(char));
    g_buf_sensor_two = (char *)calloc(64, sizeof(char));
    g_buf_sensor_three = (char *)calloc(64, sizeof(char));
    /* Activation of a resource */
    coap_activate_resource(&res_hello, "resources/hello");
#if BORDER_ROUTER_CONF_WEBSERVER
    PROCESS_NAME(webserver_nogui_process);
    process_start(&webserver_nogui_process, NULL);
#endif /* BORDER_ROUTER_CONF_WEBSERVER */

    puts("Contiki-NG Border Router started\n");
    while (1)
    {
        PROCESS_WAIT_EVENT();
    }
    PROCESS_END();
}
