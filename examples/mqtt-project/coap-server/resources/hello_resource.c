#include <stdlib.h>
#include <string.h>
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
    int length = strlen("Hello world");
    coap_set_header_content_format(response, TEXT_PLAIN);
    coap_set_header_etag(response, (uint8_t *)&length, 1);
    coap_set_payload(response, buffer, length);
}