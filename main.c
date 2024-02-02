#include "flight_geo.h"


double contingency_lateral()
{
    double gps_inaccuracy = 3.0; // m
    double position_holding_error = 3.0; // m
    double map_error = 1.0; // m
    double response_time = 1.0;
    double reaction_distance = DRONE_SPEED * response_time;
    // S = (1/2) * a * t^2 + v0 * t
    double contingency_maneuver = 0.5 * (pow(DRONE_SPEED, 2) / (9.81 * tan(45)));
    return(gps_inaccuracy + position_holding_error + map_error + reaction_distance + contingency_maneuver);///_distance + contingency_maneuver);
}
double contingency_vertical()
{
    double alt_error = 4.0; //for GPS-based altitude error measurement
    double response_time = 1.0;
    double response_height = DRONE_SPEED * 0.7 * response_time;
    double contingency_maneuver = 0.5 * (pow(DRONE_SPEED, 2) / (9.81));
    return (FG_HEIGHT + response_height + alt_error + contingency_maneuver);

}

double ground_risk_ballistic()
{
    double ground_risk = 0.0;
    double contingency_v = contingency_vertical();
    double value = ((2 * contingency_v) / 9.81);
    double formula = (sqrt(value));
    ground_risk = (DRONE_SPEED * formula) + (0.5 * DRONE_SIZE);
    return (ground_risk);
}

double ground_risk_buffer()
{
    // simplified approach for multirotor
    double contingency_v = contingency_vertical();
    double ground_risk = 0.0;
    ground_risk = contingency_v + (0.5 * DRONE_SIZE);
    return (ground_risk);
}

double altitude_LOS()
{
    // based on documentaion for multirotor
    return (327 * DRONE_SIZE + 20);
}

double detection_LOS()
{
    // based on documentaion GV can be changed in drone_config.h
    return (0.3 * GROUND_VISIBILITY);
}

double VLOS()
{
    // smaller value of ALOS and DLOS
    double alos = altitude_LOS();
    double dlos = detection_LOS();
    if (alos < dlos)
    {
        return (alos);
    }
    else
    {
        return (dlos);
    }
}

void display_pre_flight()
{
    printf("Pre-flight planning:\n");
    printf("Contingency lateral: %.2fm\n", contingency_lateral());
    printf("Contingency vertical: %.2fm\n", contingency_vertical());
    printf("Ground risk buffer (simple approach): %.2fm\n", ground_risk_buffer());
    printf("Ground risk buffer (ballistic approach): %.2fm\n", ground_risk_ballistic());
    printf("VLOS/BLOS: %.2fm\n", VLOS());
    printf("\n");
}

int main()
{
    if(DISPLAY_CONFIG)
    {
        printf("Drone configuration:\n");
        printf("Drone size: %.2fm\n", DRONE_SIZE);
        printf("Drone speed: %.2f m/s\n", DRONE_SPEED);
        printf("Drone altitude: %.2fm\n", DRONE_ALTITUDE);
        printf("\n");
    }
    display_pre_flight();

    return(0);
}
