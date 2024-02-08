#include "vex.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
// There is probably a more efficient way to reduce angles than the ones specified below,
// but these work without question, and you really only have to reduce them once or twice at 
// a max.

float reduce_0_to_360(float angle) {
  while(!(angle >= 0 && angle < 360)) {
    if( angle < 0 ) { angle += 360; }
    if(angle >= 360) { angle -= 360; }
  }
  return(angle);
}

float reduce_negative_180_to_180(float angle) {
  while(!(angle >= -180 && angle < 180)) {
    if( angle < -180 ) { angle += 360; }
    if(angle >= 180) { angle -= 360; }
  }
  return(angle);
}

float reduce_negative_90_to_90(float angle) {
  while(!(angle >= -90 && angle < 90)) {
    if( angle < -90 ) { angle += 180; }
    if(angle >= 90) { angle -= 180; }
  }
  return(angle);
}

float to_rad(float angle_deg){
  return(angle_deg/(180.0/M_PI));
}

float to_deg(float angle_rad){
  return(angle_rad*(180.0/M_PI));
}

float clamp(float input, float min, float max){
  if( input > max ){ return(max); }
  if(input < min){ return(min); }
  return(input);
}

bool is_reversed(double input){
  if(input<0) return(true);
  return(false);
}

float to_volt(float percent){
  return(percent*12.0/100.0);
}

int to_port(int port){
  if(port>8){
    return(0);
  }
  return(port-1);
} // To_port just keeps a number over 7 from being passed as a threewire port.

float deadband(float input, float width){
  if (fabs(input)<width){
    return(0);
  }
  return(input);
}

double angleDistance(double angle1, double angle2) {
    double diff = std::fabs(reduce_0_to_360(angle1) - reduce_0_to_360(angle2));
    return std::min(diff, 360 - diff);
}

double medianAngle(double angle1, double angle2, double angle3) {
    // Normalize angles
    angle1 = reduce_0_to_360(angle1);
    angle2 = reduce_0_to_360(angle2);
    angle3 = reduce_0_to_360(angle3);

    std::vector<double> angles = {angle1, angle2, angle3};
    std::vector<double> distances(3, 0); // Store sums of distances to other angles

    // Calculate sum of distances for each angle
    for (int i = 0; i < 3; ++i) {
        distances[i] = angleDistance(angles[i], angles[(i + 1) % 3]) +
                       angleDistance(angles[i], angles[(i + 2) % 3]);
    }

    // Identify the angle with the minimum sum of distances (this will be the median in the circular sense)
    int minIndex = std::distance(distances.begin(), std::min_element(distances.begin(), distances.end()));
    return angles[minIndex];
}