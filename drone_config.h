#ifndef DRONE_CONFIG_H
#define DRONE_CONFIG_H

// change to 0 to disable Displaying Config
#define DISPLAY_CONFIG 1

// Drone configuration
#define DRONE_SPEED 10.0 // m/s
#define DRONE_ALTITUDE 100.0 // m
#define DRONE_SIZE 1.4  // m

// Flight grid configuration in meters
// Must be at least 3 times the DRONE_SIZE
#define FG_WIDTH 100
#define FG_HEIGHT 100
#define GROUND_VISIBILITY 5000 // m (5km) assumed to be the maximum visibility of the ground


#endif