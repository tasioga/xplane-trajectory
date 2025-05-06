#include "trajectory.h"

#include <iostream>
#include <exception>
#include <GeographicLib/Rhumb.hpp>
#include <GeographicLib/Constants.hpp>
#include <GeographicLib/Geodesic.hpp>

using namespace GeographicLib;
using namespace std;

// Create a trajectory starting 5 nautical miles south eas from KSQL runway 30
// and ending 10 nautical miles north west of KSQL runway 30
void create_trajectory(std::vector<Waypoint>& trajectory)
{
    // Nautical mile to kilometer
    const double nm_to_m = 1852;

    try {
        // Origin at KSQL, runway 30
        double ksql_lat = 37.509187, ksql_lon = -122.246506;
        
        // Starting point is 0.1 nautical miles south east (138 deg) from KSQL rwy 30
        double lat1, lon1;
        const Geodesic& geod = Geodesic::WGS84();
        geod.Direct(ksql_lat, ksql_lon, 138.0, 0.1*nm_to_m, lat1, lon1);
    
        // End point is 1 nautical miles north west (318 deg) from KSQL rwy 30
        double lat2, lon2;
        geod.Direct(ksql_lat, ksql_lon, 318.0, 1.0*nm_to_m, lat2, lon2);
    
        // Rhumb line between (lat1, lon1) and (lat2, lon2)
        const Rhumb& rhumb = Rhumb::WGS84();
        double s12, azi12;
        rhumb.Inverse(lat1, lon1, lat2, lon2, s12, azi12);
        RhumbLine line = rhumb.Line(lat1, lon1, azi12);
    
        double ds0 = 0.5;                   // Nominal distance between points = 0.5 m
        int num = int(ceil(s12 / ds0));     // The number of intervals
        double ds = s12 / num;              // Use intervals of equal length
          
        for (int i = 0; i <= num; ++i) {
            double lat, lon;
            line.Position(i * ds, lat, lon);
            
            // Add new waypoint to trajectory
            trajectory.push_back(Waypoint(lat, lon));
        }
      }
      catch (const exception& e) {
        cerr << "Caught exception: " << e.what() << "\n";
      }
}
