#ifndef _WAYPOINT_H_
#define _WAYPOINT_H_

// Waypoint defined as a (latitude, longitude) duple
struct Waypoint {
    double lat;
    double lon;

    Waypoint(double in_lat, double in_lon) {
        lat = in_lat;
        lon = in_lon;
    }
};

#endif