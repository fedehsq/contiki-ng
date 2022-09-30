#include "my_sensor.h"
#include "random.h"
#include "os/dev/leds.h"
#include <stdio.h>
static int MAX_TEMPERATURE = 100;
static int MAX_HUMIDITY = 100;
static int MAX_BATTERY_LEVEL = 100;

int get_led_color(struct sensor *sensor)
{
    if (sensor->temperature < 25)
    {
        return LEDS_GREEN;
    }
    else if (sensor->temperature < 50)
    {
        return LEDS_YELLOW;
    }
    else
    {
        return LEDS_RED;
    }
    // if (sensor->temperature < 25 && sensor->humidity < 25 && sensor->battery_level > 75)
    //{
    //     puts("green");
    //     return LEDS_GREEN;
    // }
    // else if (sensor->temperature > 75 && sensor->humidity > 75 && sensor->battery_level < 25)
    //{
    //     puts("red");
    //     return LEDS_RED;
    // }
    // else
    //{
    //     puts("yellow");
    //     return LEDS_YELLOW;
    // }
}
void init_sensor(struct sensor *sensor)
{
    sensor->temperature = random_rand() % MAX_TEMPERATURE;
    sensor->humidity = random_rand() % MAX_HUMIDITY;
    sensor->battery_level = random_rand() % MAX_BATTERY_LEVEL;
}
