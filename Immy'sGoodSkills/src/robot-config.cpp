#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Left1 = motor(PORT18, ratio6_1, true);
motor Left2 = motor(PORT19, ratio6_1, true);
motor Left3 = motor(PORT8, ratio6_1, true);
motor Right1 = motor(PORT11, ratio6_1, false);
motor Right2 = motor(PORT12, ratio6_1, false);
motor Right3 = motor(PORT2, ratio6_1, false);
motor intake = motor(PORT17, ratio6_1, true);
digital_out flaps = digital_out(Brain.ThreeWirePort.C);
digital_out blocker = digital_out(Brain.ThreeWirePort.A);
inertial Inertial20 = inertial(PORT20);
digital_out hang = digital_out(Brain.ThreeWirePort.B);
motor cataMotorA = motor(PORT1, ratio18_1, true);
motor cataMotorB = motor(PORT10, ratio18_1, false);
motor_group cata = motor_group(cataMotorA, cataMotorB);
digital_out leftHang = digital_out(Brain.ThreeWirePort.H);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}