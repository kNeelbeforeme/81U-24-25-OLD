#include "main.h"
#include "organiz/organize.h"

void intake_func() {
    pros::c::optical_rgb_s_t rgbval = color_checker.get_rgb();
    if (rgbval.blue > 230 && rgbval.red < 230) {
        //blue ring is in the intake
        
    } else if (rgbval.red > 230 && rgbval.blue < 230) {
        //red ring is in the intake
        
    } else {
        
    }
}

const int numStates = 3;
int states[numStates] = [0, 30, 200];
int currState = 0;
int target = 0;

void lb_nextState() {
    currState += 1;
    if (currState == numStates) {
        currState = 0;
    }
    target = states[currState];
}

void lb_liftControl() {
    double kP = 1;
    double error = target - ladyBrownSensor.get_position();
    double velocity = kP * error;

    ladybrown.move(velocity);

}
