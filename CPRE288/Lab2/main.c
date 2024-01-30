// main file

#include "open_interface.h"
#include "movement.h"

void main() {
  oi_t *sensor_data = oi_alloc();
  oi_init(sensor_data);

  // Call a function to move robot
  //square(sensor_data);
  //turn_left(sensor_data, 90);
  two_meter_race(sensor_data);


  oi_free(sensor_data);
}




// function file


