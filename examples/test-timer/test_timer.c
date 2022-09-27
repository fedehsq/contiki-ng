/*
• Exercise 1: test-timers.c
• Write a program with one process (test_timers) that
• Starting from t=0 and every 3 seconds, prints the number of
seconds elapsed (etimer);
• Every 10 seconds calls a function that prints “x seconds are gone”,
were x is incremented each time by 10 (ctimer)
*/
#include "contiki.h"
#include <stdio.h>
#include "os/sys/etimer.h"
#include "os/sys/ctimer.h"
static struct etimer e_timer;
static struct ctimer c_timer;
static int x = 0;

static void c_timer_callback(void *ptr)
{
  printf("\n");
  x += 10;
  printf("Elapsed time: %ds\n", x);
  ctimer_reset(&c_timer);
}

PROCESS(test_timer, "Test e_timer");
AUTOSTART_PROCESSES(&test_timer);
PROCESS_THREAD(test_timer, ev, data)
{

  PROCESS_BEGIN();

  etimer_set(&e_timer, CLOCK_SECOND * 3);
  ctimer_set(&c_timer, CLOCK_SECOND * 10, c_timer_callback, NULL);

  while (1)
  {
    printf("\n");
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&e_timer));
    printf("Elapsed time: %lds\n", etimer_expiration_time(&e_timer) / 1000);
    etimer_reset(&e_timer);
  }

  PROCESS_END();
}