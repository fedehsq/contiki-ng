#include "os/dev/serial-line.h"
#include <stdio.h>
#include <string.h>
#include "os/dev/leds.h"
PROCESS(serial_line_test, "Test serial line");
AUTOSTART_PROCESSES(&serial_line_test);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(serial_line_test, ev, data)
{
  PROCESS_BEGIN();
  while (1)
  {
      PROCESS_WAIT_EVENT_UNTIL(ev == serial_line_event_message);
      if (strcmp((char*)data, "GREEN") == 0) {
          leds_off(LEDS_ALL);
          leds_single_on(LEDS_GREEN);
      } else if (strcmp((char*)data, "RED") == 0) {
          leds_off(LEDS_ALL);
          leds_single_on(LEDS_RED);
      } else if (strcmp((char*)data, "YELLOW") == 0) {
          leds_off(LEDS_ALL);
          leds_single_on(LEDS_YELLOW);
      }
  }
  PROCESS_END();
}