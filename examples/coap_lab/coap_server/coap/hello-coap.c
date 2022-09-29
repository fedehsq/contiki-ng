
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiki.h"
#include "coap-engine.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_APP

/* Declare and auto-start this file's process */
PROCESS(contiki_ng_coap_server, "Contiki-NG CoAP Server");
AUTOSTART_PROCESSES(&contiki_ng_coap_server);

extern coap_resource_t res_hello;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(contiki_ng_coap_server, ev, data){
  PROCESS_BEGIN();
  LOG_INFO("Starting Erbium Example Server\n");
  coap_activate_resource(&res_hello, "test/hello");
  PROCESS_END();
}
