
#include "contiki.h"
#include <stdio.h>
#include "os/dev/leds.h"
#include "os/sys/etimer.h"

PROCESS(test_leds_blink, "Test e_timer");
AUTOSTART_PROCESSES(&test_leds_blink);
PROCESS_THREAD(test_leds_blink, ev, data)
{

  static struct etimer e_timer;
  PROCESS_BEGIN();

  etimer_set(&e_timer, CLOCK_SECOND * 2);

  while (1)
  {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&e_timer));
    leds_toggle(LEDS_NUM_TO_MASK(LEDS_GREEN) | LEDS_NUM_TO_MASK(LEDS_RED) | LEDS_NUM_TO_MASK(LEDS_YELLOW));
    etimer_reset(&e_timer);
  }

  PROCESS_END();
}