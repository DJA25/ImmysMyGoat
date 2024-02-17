using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Left1;
extern motor Left2;
extern motor Left3;
extern motor Right1;
extern motor Right2;
extern motor Right3;
extern motor intake;
extern digital_out flaps;
extern digital_out blocker;
extern inertial Inertial20;
extern digital_out hang;
extern motor_group cata;
extern digital_out leftHang;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );