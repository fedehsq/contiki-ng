
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
void set_sensor_temperature(struct sensor *sensor);
void set_sensor_humidity(struct sensor *sensor);
void set_sensor_battery_level(struct sensor *sensor);
int get_sensor_temperature(struct sensor *sensor);
int get_sensor_humidity(struct sensor *sensor);
int get_sensor_battery_level(struct sensor *sensor);

#endif