#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Left1                motor         18              
// Left2                motor         19              
// Left3                motor         8               
// Right1               motor         11              
// Right2               motor         12              
// Right3               motor         2               
// intake               motor         17              
// flaps                digital_out   C               
// blocker              digital_out   A               
// Inertial20           inertial      20              
// hang                 digital_out   B               
// cata                 motor_group   1, 10           
// leftHang             digital_out   H               
// ---- END VEXCODE CONFIGURED DEVICES ----
using namespace vex;
competition Competition;
//test message for my glorious coder DJA
/*---------------------------------------------------------------------------*/
/*                            DRIVE INITIALIZATION                           */
/*---------------------------------------------------------------------------*/
Drive chassis(

//Specify your drive setup below. There are eight options:
//ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
//For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
 ZERO_TRACKER_NO_ODOM,
// TANK_TWO_ROTATION, // skillschange
//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(Left1, Left2, Left3),

//Right Motors:
motor_group(Right1, Right2, Right3),

//Port number of inertial sensors.
PORT20, PORT3, PORT4,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.75,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3, 

//Input the Forward Tracker diameter (reverse it to make the direction switch):
3.25,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
6.5, // TODO: RE-MEASURE (HALF WIDTH TO CENTER OF EACH WHEEL)

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
PORT13, 

//Sideways tracker diameter (reverse to make the direction switch):
2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
-7 // TODO: REMEASURE

);


/*---------------------------------------------------------------------------*/
/*                           VARIABLE DECLARATIONS                           */
/*---------------------------------------------------------------------------*/
int current_auton_selection = 0;                                             
bool auto_started = false;                                                   
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                            PRE-AUTON                                      */
/*---------------------------------------------------------------------------*/
//Period before match start when bot is sitting on field
void pre_auton(void) {
  vexcodeInit();
  default_constants();
  // Inertial20.calibrate();
  //select auton
  while(auto_started == false){            
    switch(current_auton_selection){       
      case 0:
        Brain.Screen.printAt(50, 50, "Close side AWP");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "Far Side");
        break;
      case 2:
        Brain.Screen.printAt(50, 50, "Close Side Elims");
        break;
    //fix over-count
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 3){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }
}
}
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                            AUTON FUNCTIONS                                */
/*---------------------------------------------------------------------------*/
void autonomous(void) {
  auto_started = true;
  intake.setVelocity(100, percent);
  switch(current_auton_selection){  
    case 0:
      //   pidTest();
         //far_side();
      // far_side_safe();
      //  close_side();
       //SafeAWP();
      //  superSafeAWP();
      autonSkillsNoOdom();
      // close_side_elims();
      // riskyAutonSkillsOdom(); 
      break;      
    case 1: 
      far_side();
      break;
    case 2:
      close_side_elims();
      break;
 }
}
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                                                           */
/*                             USER CONTROL TASK                             */
/*                                                                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            PNEUMATICS                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                              FLAPS                                        */
/*---------------------------------------------------------------------------*/
void Flaps() {
  //flip value to the opposite 
  flaps.set(!flaps.value());
}
/*---------------------------------------------------------------------------*/
/*                              BLOCKER                                      */
/*---------------------------------------------------------------------------*/
void Blocker() {
  //flip value to the opposite 
  blocker.set(!blocker.value());
}
/*---------------------------------------------------------------------------*/
/*                              HANG                                         */
/*---------------------------------------------------------------------------*/
void Hang() {
  //flip value to the opposite 
  hang.set(!hang.value());
}
void LeftHang() {
  //flip value to the opposite 
  leftHang.set(!leftHang.value());
}
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                          VARIOUS FUNCTIONS                                */
/*---------------------------------------------------------------------------*/
/*                              CataStop                                     */
/*---------------------------------------------------------------------------*/
void CataStop() {
  cata.stop();
}
/*---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             DRIVER CODE                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
void usercontrol(void) {

  // THESE VARS ARE FOR PRESS TO START/STOP MATCHLOAD PRACTICE PROGRAMS ONLY, OTHERWISE DO NOT CHANGE:
  bool skillsTest = false;
  bool firing = false;


  //set motors and pneumatics at start of match
  flaps.set(false);
  blocker.set(false);
  hang.set(false);

  Right1.stop();
  Right2.stop();
  Right3.stop();
  Left1.stop();
  Left2.stop();
  Left3.stop();
  /*--------------------------------------------------------------------------*/
  /*                           DRIVER SKILLS                                   */ 
  /*---------------------------------------------------------------------------*/                      
  bool skills = true;
  if(skills) {
    skillsStart(); 
    while(true) {
      if(Controller1.ButtonA.pressing()) {
        cata.stop();
        flaps.set(false);
        
        Left1.setBrake(coast);
        Left2.setBrake(coast);
        Left3.setBrake(coast);
        Right1.setBrake(coast);
        Right2.setBrake(coast);
        Right3.setBrake(coast);
        Right1.stop();
        Right2.stop();
        Right3.stop();
        Left1.stop();
        Left2.stop();
        Left3.stop();
        wait(0.2, seconds); 
        break;
      }
    }

  }
  /*---------------------------------------------------------------------------*/
  while (1) {
    /*---------------------------------------------------------------------------*/
    /*                              INTAKE                                       */
    /*---------------------------------------------------------------------------*/
    if (Controller1.ButtonR1.pressing()) {
      intake.spin(forward, 100,  voltageUnits::volt);
    } 
    else if (Controller1.ButtonR2.pressing()) {
       intake.spin(reverse, 100,  voltageUnits::volt);
    } 
    else {
      intake.stop();
    }
    /*---------------------------------------------------------------------------*/
    /*                              CATAPULT                                     */
    /*---------------------------------------------------------------------------*/
    cata.setVelocity(85, percent);

    if(Controller1.ButtonL1.pressing()) {
      //set matchloading speed
      if(skillsTest) {
        if(firing) {
          cata.stop();
          firing = false;
        }
        else {
          cata.spin(forward);
          firing = true;
        }
      }
      else {
        cata.spin(forward);
      }
    }
    
    /*---------------------------------------------------------------------------*/
    /*                          PNEUMATIC FUNCTIONS                              */
    /*---------------------------------------------------------------------------*/
    //Callbacks to the functions above
    Controller1.ButtonL2.pressed(Flaps);
    Controller1.ButtonB.pressed(Blocker);
    Controller1.ButtonRight.pressed(LeftHang);
    Controller1.ButtonY.pressed(Hang);
    if(!skillsTest) {
      Controller1.ButtonL1.released(CataStop);
    }
    /*---------------------------------------------------------------------------*/
    
    //Driving style
    chassis.control_tank();

    wait(20, msec);           
  }
}
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                                 MAIN                                      */
/*---------------------------------------------------------------------------*/
int main() {
  //set pneumatics
  flaps.set(false);
  blocker.set(false);
  hang.set(false);

  //set max speeds
  cata.setVelocity(100, percent);


  //callbacks
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  wait(15, msec);
  pre_auton();
}
/*---------------------------------------------------------------------------*/
