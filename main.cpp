#include <iostream>
#include <vector>
#include <iomanip>
#include "trajectory.h"
#include "xplaneConnect/xplaneConnect.h"

using namespace std;

int main() {
    vector<Waypoint> trajectory;

    // Create new trajectory as a vector of waypoints
    create_trajectory(trajectory);

    // Attempt to connect to X-Plane instance
    // Open socket
    const char* IP = "127.0.0.1";  // Localhost or IP Address of computer running X-Plane
    XPCSocket sock = openUDP(IP);

    float tVal[1];
    int tSize = 1;
    if (getDREF(sock, "sim/test/test_float", tVal, &tSize) < 0) {
        cout << "Unable to connect with X-Plane" << endl;
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < trajectory.size(); i++) {
        double ac_pose[9] = { 0.0 };        // Aircraft pose
	    ac_pose[0] = trajectory[i].lat;     // Lat
        ac_pose[1] = trajectory[i].lon;     // Lon
        ac_pose[2] = 50;                    // Alt m above MSL
        ac_pose[3] = 0;                     // Pitch
        ac_pose[4] = 0;                     // Roll
        ac_pose[5] = 318;                   // Heading (deg true)
        ac_pose[6] = 1;                     // Gear down

#ifdef DEBUG
        cout << fixed << setprecision(15) << ac_pose[0] << " " << ac_pose[1] << ac_pose[2] << "\n";
#endif        
        // Set position of the aircraft to X-Plane
	    sendPOSI(sock, ac_pose, 7, 0);

	    sleep(0.5);             // Pause for 0.5 seconds
    }

    pauseSim(sock, 1);          // Sending 1 to pause so the aircraft doesn't crash	

    return 0;
}