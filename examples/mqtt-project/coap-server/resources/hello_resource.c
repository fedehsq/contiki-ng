#include <stdlib.h>
#include <string.h>
#include "../g_buf.h"
#include "coap-engine.h"

static void res_get_handler(coap_message_t *request,
                            coap_message_t *response,
                            uint8_t *buffer,
                            uint16_t preferred_size,
                            int32_t *offset);
RESOURCE(res_hello,
         "title=\"Hello world\";rt=\"Text\"",
         res_get_handler, // GET Handler
         NULL,            // POST Handler
         NULL,            // PUT Handler
         NULL);           // DELETE Handler

static void res_get_handler(coap_message_t *request,
                            coap_message_t *response,
                            uint8_t *buffer,
                            uint16_t preferred_size,
                            int32_t *offset)
{
    int length = strlen(g_buf_sensor_one) + strlen(g_buf_sensor_two) + strlen(g_buf_sensor_three) + 3;
    memcpy(buffer, g_buf_sensor_one, strlen(g_buf_sensor_one));
    // new line
    memcpy(buffer + strlen(g_buf_sensor_one), "\n", 1);
    memcpy(buffer + strlen(g_buf_sensor_one) + 1, g_buf_sensor_two, strlen(g_buf_sensor_two));
    // new line
    memcpy(buffer + strlen(g_buf_sensor_one) + 1 + strlen(g_buf_sensor_two), "\n", 1);
    memcpy(buffer + strlen(g_buf_sensor_one) + 1 + strlen(g_buf_sensor_two) + 1, g_buf_sensor_three, strlen(g_buf_sensor_three));
    coap_set_header_content_format(response, TEXT_PLAIN);
    coap_set_header_etag(response, (uint8_t *)&length, 1);
    coap_set_payload(response, buffer, length);
}