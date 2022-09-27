#include "my_sensor.h"
#include "lib/random.h"
#include <stdio.h>
#define GREEN 0
#define RED 2
#define YELLOW 1

static int MAX_TEMPERATURE = 100;
static int MAX_HUMIDITY = 100;
static int MAX_BATTERY_LEVEL = 100;

int get_led_color(struct sensor *sensor)
{
    if (sensor->temperature < 25 && sensor->humidity < 25 && sensor->battery_level > 75)
    {
        return GREEN;
    }
    else if (sensor->temperature > 75 && sensor->humidity > 75 && sensor->battery_level < 25)
    {
        return RED;
    }
    else
    {
        return YELLOW;
    }
}
void init_sensor(struct sensor *sensor)
{
    random_init(1);
    sensor->temperature = random_rand() % MAX_TEMPERATURE;
    sensor->humidity = random_rand() % MAX_HUMIDITY;
    sensor->battery_level = random_rand() % MAX_BATTERY_LEVEL;
}

void set_sensor_temperature(struct sensor *sensor)
{
    sensor->temperature = random_rand() % MAX_TEMPERATURE;
}

void set_sensor_humidity(struct sensor *sensor)
{
    sensor->humidity = random_rand() % MAX_HUMIDITY;
}

void set_sensor_battery_level(struct sensor *sensor)
{
    sensor->battery_level = random_rand() % MAX_BATTERY_LEVEL;
}

int get_sensor_temperature(struct sensor *sensor)
{
    return sensor->temperature;
}

int get_sensor_humidity(struct sensor *sensor)
{
    return sensor->humidity;
}

int get_sensor_battery_level(struct sensor *sensor)
{
    return sensor->battery_level;
}