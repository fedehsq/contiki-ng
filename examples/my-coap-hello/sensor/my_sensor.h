
#ifndef SENSOR_H_
#define SENSOR_H_

struct sensor
{
  int temperature;
  int humidity;
  int battery_level;
};

int get_led_color(struct sensor *sensor);
void init_sensor(struct sensor *sensor);
//void reset_my_sensor(struct sensor *sensor)
#endif