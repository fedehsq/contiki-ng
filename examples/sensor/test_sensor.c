
#include "contiki.h"
#include "os/sys/etimer.h"
#include "os/dev/leds.h"
#include "my_sensor.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(hello_world_process, ev, data)
{
  static struct etimer timer;
  static struct sensor sensor;

  PROCESS_BEGIN();

  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&timer, CLOCK_SECOND * 3);
  init_sensor(&sensor);

  while (1)
  {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    int led_color = get_led_color(&sensor);
    int temperature = get_sensor_temperature(&sensor);
    printf("Temperature: %d\n", temperature);
    leds_off(LEDS_ALL);
    leds_single_on(led_color);
    set_sensor_temperature(&sensor);
    set_sensor_battery_level(&sensor);
    set_sensor_humidity(&sensor);
    etimer_reset(&timer);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
