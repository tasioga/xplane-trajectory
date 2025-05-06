#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include <vector>

// A trajectory will be defined as an array of waypoints, 
// and a waypoint is just a duple (latitude, longitude)
struct Waypoint {
    double lat;
    double lon;

    Waypoint(double in_lat, double in_lon) {
        lat = in_lat;
        lon = in_lon;
    }
};


// Create a new trajectory as a vector of waypoints
void create_trajectory(std::vector<Waypoint>& trajectory);

#endif
