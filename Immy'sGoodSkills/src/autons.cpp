#include "vex.h"
/*---------------------------------------------------------------------------*/
/*                              PID CONSTANTS                                */
/*---------------------------------------------------------------------------*/
void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).

  // chassis.set_heading_constants(12, .25, 0.2, 1.6, 0);
  chassis.set_heading_constants(12, .25, 0, 1.6, 0);
    // chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .37, 0.03, 3, 15);

  // chassis.set_turn_constants(12, .33, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  // chassis.set_drive_constants(12, 1.688, 0.4, 0.5, 0);
  chassis.set_drive_constants(12, 0.9, 0, 10, 0);
  // chassis.set_drive_constants(12, 0.67, 0, 2, 0);

  // Each exit condition set is in the form (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}
/*---------------------------------------------------------------------------*/
/*                             Defining Functions                           */
/*---------------------------------------------------------------------------*/
//Stops Drivetrain
void drive_stop() {
  Right1.stop();
  Right2.stop();
  Right3.stop();
  Left1.stop();
  Left2.stop();
  Left3.stop();
}
void drive_pls(int volts, bool go_forward) {
  if(go_forward) {
    Right1.spin(forward, volts, voltageUnits::volt);
    Right2.spin(forward, volts, voltageUnits::volt);
    Right3.spin(forward, volts, voltageUnits::volt);

    Left1.spin(forward, volts, voltageUnits::volt);
    Left2.spin(forward, volts, voltageUnits::volt);
    Left3.spin(forward, volts, voltageUnits::volt);
  }
  else {
    Right1.spin(reverse, volts, voltageUnits::volt);
    Right2.spin(reverse, volts, voltageUnits::volt);
    Right3.spin(reverse, volts, voltageUnits::volt);

    Left1.spin(reverse, volts, voltageUnits::volt);
    Left2.spin(reverse, volts, voltageUnits::volt);
    Left3.spin(reverse, volts, voltageUnits::volt);
  }
}
void setVelocity(int percentage) {
    Right1.setVelocity(percentage, percent);
    Right2.setVelocity(percentage, percent);
    Right3.setVelocity(percentage, percent);
    Left1.setVelocity(percentage, percent);
    Left2.setVelocity(percentage, percent);
    Left3.setVelocity(percentage, percent);
  }

void pidTest() {
  // chassis.drive_distance(25, 90);
  chassis.turn_to_angle(90);
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            AUTON ROUTES                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                             CLOSE SIDE                                    */
/*---------------------------------------------------------------------------*/

void superSafeAWP() {
  chassis.drive_distance(-11); //backup
  hang.set(true); // AWP Descore Mech
  wait(1, seconds);
  chassis.drive_distance(13); // Descore
  intake.spin(reverse);
  // wait(0.5,seconds);
  chassis.turn_to_angle(-75); // Spin to remove triball
  hang.set(false); // pick up descore mech
  wait(0.5,seconds);

  // touch bar:
  chassis.turn_to_angle(-22);
  chassis.drive_distance(12);
  chassis.drive_distance(26.5, -39, 7, 7);
  chassis.drive_distance(-1);
  intake.stop();
}

// void SafeAWP() {
//   chassis.drive_distance(-12);
//   wait(0.5, seconds);
//   flaps.set(true);
//   wait(0.5, seconds);
//   intake.spin(reverse);
//   chassis.drive_distance(10, -30);
//   flaps.set(false);
//   wait(0.2, seconds);

//   chassis.drive_distance(-15, 30);
//   chassis.drive_distance(-10);
//   chassis.drive_distance(-12, 56, 12, 12, 1.5, 300, 1000);

//   chassis.drive_distance(10);
//   chassis.turn_to_angle(5);
//   chassis.drive_distance(23);
//   chassis.turn_to_angle(-38);
  
//   chassis.drive_distance(39);
//   chassis.drive_distance(-1);
//   intake.stop();
// }

// void close_side(){
//   intake.spin(reverse);
//   chassis.drive_distance(-15);

//   chassis.drive_distance(-10, 15);

//   chassis.set_drive_exit_conditions(1.5, 300, 5000);
//   chassis.set_turn_exit_conditions(1, 300, 3000);
//   chassis.set_swing_exit_conditions(1, 300, 3000);

//   chassis.drive_distance(1);

//   drive_pls(12, false);
//   wait(0.8, seconds);
//   drive_stop();
//   wait(0.1, seconds);

//   chassis.drive_distance(10, -5);
//   hang.set(true);
//   chassis.drive_distance(15, -33);
//   hang.set(false);
//   wait(1, seconds);
//   chassis.drive_distance(6.5, -54);
//   chassis.drive_distance(13, -70);
//   chassis.drive_distance(13, -60);
//   chassis.drive_distance(4.5);
//   intake.stop();
//   return;

//   intake.stop();
//   //score
//   // drive_pls(12, true);
//   // wait(0.8, seconds);
//   // drive_stop();
//   // chassis.set_drive_exit_conditions(1.5, 300, 800);

//   chassis.drive_distance(25);

//   chassis.set_drive_exit_conditions(1.5, 300, 5000);
//   chassis.set_turn_exit_conditions(2.5, 300, 800);
//   //Back up, point towards the match load zone, and drive over there
//   // chassis.drive_distance(-17);
//   chassis.turn_to_angle(214);
//   chassis.drive_distance(42);

//   //take triball out from zone
//   flaps.set(true);  
//   wait(.2, seconds);
//   chassis.drive_distance(4, 90);
//   chassis.drive_distance(9, 98);
//   flaps.set(false);
//   wait(0.7, seconds);

//   //go to touch hang bar
//   chassis.drive_distance(6, 90);
//   chassis.turn_to_angle(120);
//   chassis.drive_distance(22, 90);
//   chassis.drive_distance(3.3, 90, 4, 4);
// }
/*---------------------------------------------------------------------------*/
/*                             FAR SIDE                                      */
/*---------------------------------------------------------------------------*/

void far_side_safe() { // this is 5 ball auto
  // outtake preload
  intake.spin(reverse);
  // descore matchload acorn
  hang.set(true);
  wait(0.2, seconds);
  chassis.drive_distance(13);
  chassis.turn_to_angle(-45);
  hang.set(false);
  wait(0.2, seconds);
  // score 2 acorns with back of bot
  chassis.turn_to_angle(164);
  chassis.drive_distance(-20, 145, 12, 12, 0, 0, 950);

  // move to and intake center of middle bar acorn
  chassis.drive_distance(25, 274);
  intake.spin(forward);
  chassis.set_drive_exit_conditions(2.5, 100, 2000);
  chassis.set_turn_exit_conditions(2.5, 100, 1500);
  chassis.drive_distance(50, 274, 12, 1, 2, 300, 2000);
  chassis.turn_to_angle(305+97);
  flaps.set(true);

  // outtake middle of bar acorn; score that acorn
  // and the one in path to goal
  intake.spin(reverse);
  chassis.drive_distance(30, 305+97, 12, 1, 1, 0, 1000);

  // move to other middle bar acorn and intake
  chassis.drive_distance(-15);
  flaps.set(false);
  chassis.turn_to_angle(305+90+142);
  intake.spin(forward);
  // outtake and score it
  chassis.drive_distance(27, 305+90+142, 12, 1, 2, 300, 1000);
  chassis.drive_distance(-5);
  chassis.turn_to_angle(305+90+142-147);
  intake.spin(reverse);
  chassis.drive_distance(50, 305+90+142-147, 12, 1, 1, 300, 1200);
  // backup to prevent touching any scored acorns and set driver up
  chassis.drive_distance(-10);
}

void far_side() {
chassis.set_turn_exit_conditions(6, 0,1500);
//hit preload
flaps.set(true);
wait(0.3,seconds);
flaps.set(false);

//intake 1st ball
intake.spin(forward, 12, voltageUnits::volt);
// chassis.drive_distance(64);
chassis.drive_distance(64.7, 0, 12, 12, 1.5, 0, 1800);
// wait(0.3,seconds);
chassis.turn_to_angle(125);
//score
flaps.set(true);
intake.spin(reverse);
chassis.set_drive_exit_conditions(1.5, 0, 900);
chassis.drive_distance(38);
//back up
flaps.set(false);
chassis.drive_distance(-5);
chassis.set_turn_exit_conditions(2.5,100,1500);
chassis.turn_to_angle(280);

//get third ball
intake.spin(forward);
chassis.drive_distance(31);
//go back to goal and outtake
chassis.set_turn_exit_conditions(6, 0,1500);
chassis.turn_to_angle(165); 

chassis.drive_distance(45);

  chassis.turn_to_angle(80);
  intake.spin(reverse);
  
  //get ball under alley
  chassis.drive_distance(-11);
  
  intake.spin(forward);
  chassis.turn_to_angle(308);
  chassis.drive_distance(38,308); // used to be 30, 308
  // chassis.drive_distance(3, 303, 8, 8);
  //wait(0.2,seconds);

  //back out and turn around
  chassis.drive_distance(-35);
  chassis.turn_to_angle(90);
  intake.stop();
  hang.set(true);
  wait(0.25,seconds);
  intake.spin(reverse);
  //get corner ball out 
  //old shit
  chassis.set_turn_exit_conditions(6, 0,1500);
  chassis.set_drive_exit_conditions(2, 0,1500);
  chassis.drive_distance(15.5);
  chassis.drive_distance(9.5,45,12,12);
  // chassis.turn_to_angle(38);
  hang.set(false);
  // wait(0.25, seconds);
  intake.stop();
  chassis.turn_to_angle(250);
  //score remanining 4 balls 
  drive_pls(12, false);
  wait(.8, seconds);
  drive_stop();
  chassis.drive_distance(7);

  drive_pls(12, false);
  wait(.5, seconds);
  drive_stop();
  chassis.drive_distance(20);

}
/*---------------------------------------------------------------------------*/
/*                            CLOSE SIDE ELIMS                               */
/*---------------------------------------------------------------------------*/
void close_side_elims() {
  //outtake preload
  intake.spin(reverse, 12, voltageUnits::volt);
  wait(0.5, seconds);
  //intake first ball
  chassis.turn_to_angle(40);
  intake.spin(forward);
  chassis.drive_distance(53);
  flaps.set(true);
  wait(0.2,seconds);
  //knock ball to other side
  chassis.turn_to_angle(125);
  intake.spin(reverse);
  chassis.drive_distance(20, 125, 12, 12, 2, 300, 1000);
  flaps.set(false);
  intake.spin(forward, 4, voltageUnits::volt);

  //go score preload
  chassis.drive_distance(-40,60, 9, 12);
  chassis.drive_distance(-25,197, 12, 10, 2, 0, 0);
  drive_pls(12, false);
  wait(1.0, seconds);
  drive_stop();
  intake.spin(reverse);

  // descore matchload acorn
  chassis.drive_distance(13);
  chassis.turn_to_angle(162);
  hang.set(true);
  wait(0.2, seconds);
  chassis.drive_distance(22);
  chassis.turn_to_angle(85);
  chassis.turn_to_angle(115);
  hang.set(false);

  // push descored acorn and hang acorn over;
  // touch elevation bar
  intake.spin(reverse);
  chassis.drive_distance(40,115);
  chassis.drive_distance(-40);
  chassis.turn_to_angle(295);
}
/*---------------------------------------------------------------------------*/ 




/*---------------------------------------------------------------------------*/      
/*                              SKILLS                                       */
/*---------------------------------------------------------------------------*/

int autonskillsStart() { 
  chassis.set_drive_exit_conditions(1.5, 50, 5000);
  chassis.set_turn_exit_conditions(2, 50, 3000);
  chassis.set_swing_exit_conditions(1, 50, 3000);

  // push acorn in

  chassis.drive_distance(-35, 0, 12, 12, 1, 300, 1000);
  chassis.drive_distance(10, 93, 12, 6.7, 1, 50, 750); 

  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(2, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);

 
  flaps.set(true);
  Left1.setBrake(hold);
  Left2.setBrake(hold);
  Left3.setBrake(hold);
  Right1.setBrake(hold);
  Right2.setBrake(hold);
  Right3.setBrake(hold);
  Left1.spin(forward, 1, voltageUnits::volt);
  Left2.spin(forward, 1, voltageUnits::volt);
  Left3.spin(forward, 1, voltageUnits::volt);
  cata.setVelocity(85, percent);
  cata.spin(forward);
  double currentAngle = Inertial20.heading();
  wait(16, seconds); // wait for shots
  // wait(.5, seconds);
  cata.stop();
  flaps.set(false);
  
  Left1.setBrake(coast);
  Left2.setBrake(coast);
  Left3.setBrake(coast);
  Right1.setBrake(coast);
  Right2.setBrake(coast);
  Right3.setBrake(coast);

  wait(0.2, seconds);
  // Controller1.Screen.print(currentAngle);
  return currentAngle;
}


int skillsStart() {  

  chassis.set_drive_exit_conditions(1.5, 50, 5000);
  chassis.set_turn_exit_conditions(2, 50, 3000);
  chassis.set_swing_exit_conditions(1, 50, 3000);

  // push acorn in

  chassis.drive_distance(-35, 0, 12, 12, 1, 300, 1000);
  chassis.drive_distance(9, 87, 12, 6.7, 1, 50, 750); 

  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(2, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);


 
  flaps.set(true);
  // Left1.setBrake(hold);
  // Left2.setBrake(hold);
  // Left3.setBrake(hold);
  // Right1.setBrake(hold);
  // Right2.setBrake(hold);
  // Right3.setBrake(hold);

  drive_pls(1, true);

  cata.spin(forward);
  cata.setVelocity(80, percent);
  cata.spin(forward);
  double currentAngle = Inertial20.heading();

  // Controller1.Screen.print(currentAngle);
  return currentAngle;
}

/*---------------------------------------------------------------------------*/
/*                            AUTON SKILLS                                   */
/*---------------------------------------------------------------------------*/


void autonSkillsNoOdom() {

  chassis.set_drive_exit_conditions(1.5, 50, 5000);
  chassis.set_turn_exit_conditions(2, 50, 3000);
  chassis.set_swing_exit_conditions(1, 50, 3000);

  // push acorn in

  chassis.drive_distance(-35, 0, 12, 12, 1, 300, 1000);
  chassis.drive_distance(10, 93, 12, 6.7, 1, 50, 750); 

  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(2, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);

 
  flaps.set(true);
  Left1.setBrake(hold);
  Left2.setBrake(hold);
  Left3.setBrake(hold);
  Right1.setBrake(hold);
  Right2.setBrake(hold);
  Right3.setBrake(hold);
  Left1.spin(forward, 1, voltageUnits::volt);
  Left2.spin(forward, 1, voltageUnits::volt);
  Left3.spin(forward, 1, voltageUnits::volt);
  cata.setVelocity(80, percent);
  cata.spin(forward);
  double currentAngle = Inertial20.heading();
  wait(17, seconds); // wait for shots
  // wait(3, seconds);
  cata.stop();
  flaps.set(false);
  
  Left1.setBrake(coast);
  Left2.setBrake(coast);
  Left3.setBrake(coast);
  Right1.setBrake(coast);
  Right2.setBrake(coast);
  Right3.setBrake(coast);

  wait(0.2, seconds);
  // Controller1.Screen.print(currentAngle);


  currentAngle = 95;
  //shoot preload next to goal
  
  chassis.set_drive_exit_conditions(2.25, 300, 5000);
  chassis.set_turn_exit_conditions(3, 300, 3000);
  chassis.set_swing_exit_conditions(2, 300, 3000);

  // cross field
  intake.setVelocity(10, percent);
  intake.spin(reverse);
  
// cross barrier

  chassis.drive_distance(-5);
  chassis.turn_to_angle(currentAngle+58);
  chassis.drive_distance(-38);
  chassis.turn_to_angle(currentAngle+14);
  // wait(5, seconds);
  chassis.set_drive_exit_conditions(2, 0, 10000);
  chassis.set_turn_exit_conditions(2, 0, 3000);
  chassis.set_swing_exit_conditions(2, 0, 3000);

  chassis.drive_distance(-72);

  chassis.set_drive_exit_conditions(2, 0, 5000);

// turn for hit w/ back of bot

  chassis.drive_distance(-10, currentAngle);
  chassis.drive_distance(-17, currentAngle-45);

  chassis.set_drive_exit_conditions(1.5, 300, 1000);
  chassis.set_turn_exit_conditions(2, 300, 1000);
  chassis.set_swing_exit_conditions(1, 300, 1000);

// hit 1

  chassis.drive_distance(-100, currentAngle-72, 12, 8);

  // wait(0.25, seconds);


// sidehit 2
  chassis.drive_distance(10, currentAngle-67);
  // wait(0.05, seconds);
  drive_pls(12, false);
  wait(1, seconds);
  drive_stop();


  intake.spin(reverse);

  currentAngle = 21;
  intake.setVelocity(10, percent);
  intake.spin(reverse);
 
  // double currentAngle = 0;
  // setup for turn

  chassis.drive_distance(15, 116+currentAngle);
  chassis.drive_distance(40);
  chassis.turn_to_angle(235+currentAngle);
  flaps.set(true);
  wait(0.1, seconds);
  chassis.drive_distance(50, 250+currentAngle, 12, 12, 1, 300, 1200);


// return;

//   chassis.drive_distance(5, 80+currentAngle, 12, 11, 1, 50, 1000); // 9, 8 if u need to switch back
//   chassis.drive_distance(9, 120+currentAngle, 12, 11, 1, 50, 1000);
//   chassis.drive_distance(5, 135+currentAngle, 12, 11, 1, 50, 1000);
//   chassis.drive_distance(13, 150+currentAngle, 12, 11, 1, 50, 1000);
//   chassis.drive_distance(10, 150+currentAngle, 12, 11, 1, 50, 1000);
//   chassis.drive_distance(13, 270+currentAngle, 12, 11, 1, 50, 1000);


//   // the push

//   chassis.set_drive_exit_conditions(1.5, 100, 1500);
  // chassis.drive_distance(50, 270+currentAngle, 12, 12, 2, 300, 1600);


  // second push:
  // flaps.set(false);
  // wait(0.2, seconds);
  // chassis.drive_distance(-25, 270);
  // flaps.set(true);
  // wait(0.2, seconds);
  // chassis.drive_distance(35, 270, 12, 12, 2, 100, 800);


  // backup

  flaps.set(false);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(2, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);

  // currentAngle+=20;

  chassis.drive_distance(-7);
  chassis.drive_distance(-27, 250+currentAngle, 12, 12, 1.5, 300, 1500);
  chassis.drive_distance(5, 170+currentAngle, 8.5, 7.5);

  // drive parallel to middle bar
  chassis.drive_distance(42, 168.4+currentAngle, 7, 7, 1.5, 300, 2400);

  // turn for final pushes



  chassis.turn_to_angle(335, 10.5);
  flaps.set(true);

  // push 1
  chassis.drive_distance(40, 280, 12, 4, 1.5, 300, 1100);

  flaps.set(false);
  wait(0.2, seconds);
  chassis.drive_distance(-28);
  flaps.set(true);
  wait(0.2, seconds);

  // // push 2
  // chassis.drive_distance(35, 280, 12, 4, 1.5, 300, 1200);

  // push in mid net
  chassis.drive_distance(-30, 280, 12, 4, 1.5, 300, 1100);
  chassis.turn_to_angle(275);
  chassis.drive_distance(50, 275, 12, 4, 1.5, 300, 1200);
  flaps.set(false);

  chassis.drive_distance(-12);
  chassis.turn_to_angle(210);
  chassis.drive_distance(52);

  chassis.turn_to_angle(162);
  chassis.drive_distance(20, 115);
  chassis.turn_to_angle(93);
  // chassis.drive_distance(15, 120);
  chassis.set_drive_exit_conditions(1.5, 0, 1500);
  chassis.set_turn_exit_conditions(2, 0, 1500);
  chassis.set_swing_exit_conditions(1, 0, 1500);
  chassis.drive_distance(-30, 135);
  chassis.drive_distance(-30, 200, 12, 7, 1, 300, 2000);
  // chassis.drive_distance(-20, 210, 12, 12, 1, 300, 900);
  chassis.drive_distance(12);
  chassis.drive_distance(-20, 190, 12, 12, 1, 300, 900);
  chassis.drive_distance(10);
}

void getLoc() {
  Controller1.Screen.print(chassis.get_X_position());
  Controller1.Screen.print(" ");
  Controller1.Screen.print(chassis.get_Y_position());
  Controller1.Screen.newLine();
}

//Command F FIND
void riskyAutonSkillsOdom() { 
  chassis.set_coordinates(0, 0, 0);
  //score 2 and begin launching
  autonskillsStart();

  chassis.set_drive_exit_conditions(1.5, 100, 5000);
  chassis.set_turn_exit_conditions(2, 100, 3000);
  chassis.set_swing_exit_conditions(1, 100, 3000);

  //drive towards middle barrier
  chassis.drive_distance(-10);
  // wait(1, seconds);
  // flaps.set(true);
  // wait(0.3,seconds);
  // flaps.set(false);
  // chassis.turn_to_angle(288);



  chassis.turn_to_angle(288);  
  //turn to plow the acorns
  chassis.drive_distance(37);
  chassis.turn_to_angle(210);
  flaps.set(true);
  //push acorns
  // chassis.drive_distance(32, 210,10,10,2,0,1500);
  chassis.drive_distance(200, 210,12,0,2,0,1400);
  //second push
  chassis.drive_distance(-10);
  chassis.drive_distance(100, 200, 12, 12, 1, 300, 300);
  // chassis.drive_distance(-13);
  chassis.drive_to_point(-56.84, -63.50, 12, 12, 2, 300, 1000);
  // getLoc();
  flaps.set(false);
  //turn to back left corner
  chassis.turn_to_angle(330);

  // Controller1.Screen.print(chassis.get_absolute_heading());

  // chassis.drive_distance(-41);
  chassis.drive_to_point(-39.06, -97.87, 12, 12, 2.5, 100, 1400);

  //wallride
  chassis.turn_to_angle(60);
  chassis.drive_distance(-18, 60, 12,12,1,200, 500);
  //push acorns down alley and change constants for wall rides
  chassis.turn_to_angle(108);
  // chassis.turn_to_point(-125.3, -81.02);
  chassis.set_drive_exit_conditions(1.5, 0, 1500);
  chassis.set_turn_exit_conditions(2, 0, 1500);
  chassis.set_swing_exit_conditions(1, 0, 1500);
  chassis.drive_distance(-81.7, 108, 12, 12, 1.5, 0, 5000);
  // chassis.drive_to_point(-125.3, -81.02);
  //wall ride and score
  chassis.set_drive_exit_conditions(1.5, 0, 700);
  //complicated way of saying go around the matchload bar and push in
  chassis.turn_to_angle(132, 12);
  // chassis.turn_to_point(-138.62, -64.84);
  hang.set(true);
  chassis.drive_distance(-20, 132, 12, 12);
  // chassis.drive_to_point(-138.62, -64.84);
  chassis.turn_to_angle(155, 12);
  hang.set(false);
  // chassis.turn_to_point(-144.52, -50.66);
  chassis.drive_distance(-18, 155, 12, 12);

  leftHang.set(true);
  // chassis.drive_to_point(-144.52, -50.66);
  //push #1
  chassis.turn_to_angle(190, 12);
  // chassis.turn_to_point(-142.10, -35.97);
  chassis.drive_distance(-100);
  // getLoc();
  //push #2
  chassis.drive_distance(12);
  hang.set(false);
  wait(0.1, seconds);
  chassis.turn_to_angle(185);
  // chassis.drive_to_point(-145.32, -44.35);
  // getLoc();
  chassis.drive_distance(-100, 190);
  leftHang.set(false);
  // return;
  //turn to middle barrier
  chassis.drive_distance(12);
  chassis.turn_to_angle(100);
   hang.set(true);
  //drive to middle barrier
  chassis.drive_distance(50);
  hang.set(false);
  chassis.drive_distance(18);
  wait(0.1,seconds);
  //grab acorns around corner
  chassis.turn_to_angle(26,8);
  chassis.drive_distance(3);
  flaps.set(true);
  //first front push
  chassis.drive_distance(40,-64,12,12,4,200,1200);
  flaps.set(false);
  //back up
  chassis.drive_distance(-40,-20);
  // hang.set(true);
  //go to spot for second push
  chassis.turn_to_angle(23);
  chassis.drive_distance(47+5);
  chassis.turn_to_angle(250);
  hang.set(false);
  wait(0.1,seconds);
  //second push
  flaps.set(true);
  chassis.drive_distance(45,-64, 12,12,1,200,1200);
  //back up 
  flaps.set(false);
  chassis.drive_distance(-20,-90);
  //third push
  chassis.set_drive_exit_conditions(1.5, 300, 1500);
  chassis.set_turn_exit_conditions(2, 300, 1500);
  chassis.set_swing_exit_conditions(1, 300, 1500);
  flaps.set(true);
  chassis.drive_distance(30,-64, 12, 12, 1, 300, 750);
  flaps.set(false);
  //back up to middle barand turn to right corner
  chassis.drive_distance(-30);
  chassis.turn_to_angle(-4.5);
  flaps.set(true);

  //herd to corner
  chassis.drive_distance(31);
  flaps.set(false);
  wait(0.2,seconds);
  //go under alley
  chassis.drive_distance(36);
  chassis.set_drive_exit_conditions(2.5, 0, 1000);
  chassis.set_turn_exit_conditions(3, 0, 1000);
  chassis.set_swing_exit_conditions(2, 0, 1000);
  //back up a little 
  chassis.turn_to_angle(100);
  chassis.drive_distance(15);
  chassis.turn_to_angle(117);
  //change constants for wall rides

  //wallride
  chassis.drive_distance(-20);
  chassis.turn_to_angle(85);
  chassis.drive_distance(-20);
  chassis.turn_to_angle(68);
  chassis.drive_distance(-18);
  //backshot
  chassis.turn_to_angle(38);
  chassis.drive_distance(-100, 29, 12, 12, 1, 0, 500);
  //backshot #2
  chassis.drive_distance(10);
  chassis.drive_distance(-100, 29, 12, 12, 1, 0, 500);
  chassis.drive_distance(5);
}

void autonSkillsOdom() {

  autonskillsStart();

  double currentAngle = 95;
  //shoot preload next to goal
  chassis.set_drive_exit_conditions(2.25, 300, 5000);
  chassis.set_turn_exit_conditions(3, 300, 3000);
  chassis.set_swing_exit_conditions(2, 300, 3000);
  // cross field
  intake.setVelocity(10, percent);
  intake.spin(reverse);
// cross barrier
  chassis.drive_distance(-5);
  chassis.turn_to_angle(currentAngle+58);
  chassis.drive_distance(-42);
  chassis.turn_to_angle(currentAngle+14);
  chassis.set_drive_exit_conditions(2, 0, 10000);
  chassis.set_turn_exit_conditions(2, 0, 3000);
  chassis.set_swing_exit_conditions(2, 0, 3000);
  chassis.drive_distance(-72);
  chassis.set_drive_exit_conditions(2, 0, 5000);
// turn for hit w/ back of bot
  chassis.drive_distance(-10, currentAngle);
  chassis.drive_distance(-17, currentAngle-45);
  chassis.set_drive_exit_conditions(1.5, 300, 1000);
  chassis.set_turn_exit_conditions(2, 300, 1000);
  chassis.set_swing_exit_conditions(1, 300, 1000);
// hit 1
  chassis.drive_distance(-100, currentAngle-72, 12, 8);
// sidehit 2
  chassis.drive_distance(10, currentAngle-67);
  drive_pls(12, false);
  wait(1, seconds);
  drive_stop();

  // setup for first front push
  intake.spin(reverse);
  currentAngle = 21;
  intake.setVelocity(10, percent);
  intake.spin(reverse);
  chassis.drive_distance(15, 116+currentAngle);
  chassis.drive_distance(40);
  chassis.turn_to_angle(235+currentAngle);
  flaps.set(true);
  wait(0.1, seconds);
  // first push
  chassis.drive_distance(50, 250+currentAngle, 12, 12, 1, 300, 1200);

  // backup
  flaps.set(false);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(2, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
  chassis.drive_distance(-7);
  chassis.drive_distance(-27, 250+currentAngle, 12, 12, 1.5, 300, 1500);
  chassis.drive_distance(5, 172+currentAngle, 8.5, 7.5);
  // drive parallel to middle bar
  chassis.drive_distance(42, 172+currentAngle, 7, 7, 1.5, 300, 2400);
  // turn for final pushes
  chassis.turn_to_angle(335, 10.5);
  flaps.set(true);
  // push 1
  chassis.drive_distance(40, 280, 12, 4, 1.5, 300, 1100);
  // backup
  flaps.set(false);
  wait(0.2, seconds);
  chassis.drive_distance(-28);
  flaps.set(true);
  wait(0.2, seconds);
  // push 2 in mid net
  chassis.drive_distance(-30, 280, 12, 4, 1.5, 300, 1100);
  // go to side of net
  chassis.turn_to_angle(275);
  chassis.drive_distance(50, 275, 12, 4, 1.5, 300, 1200);
  flaps.set(false);
  // backup to push
  chassis.drive_distance(-12);
  chassis.turn_to_angle(210);
  chassis.drive_distance(55);
  chassis.turn_to_angle(162);
  chassis.drive_distance(20, 115);
  // build momentum and push
  chassis.turn_to_angle(93);
  chassis.set_drive_exit_conditions(1.5, 0, 1500);
  chassis.set_turn_exit_conditions(2, 0, 1500);
  chassis.set_swing_exit_conditions(1, 0, 1500);
  // push 1
  chassis.drive_distance(-30, 135);
  chassis.drive_distance(-30, 200, 12, 7, 1, 300, 2000);
  // push 2
  chassis.drive_distance(12);
  chassis.drive_distance(-20, 190, 12, 12, 1, 300, 900);
  chassis.drive_distance(10);
}
void autonSkillsOldRoute() {

  autonskillsStart();
  double currentAngle = 95;
  //shoot preload next to goal
  
  chassis.set_drive_exit_conditions(2.25, 300, 5000);
  chassis.set_turn_exit_conditions(3, 300, 3000);
  chassis.set_swing_exit_conditions(2, 300, 3000);

  // cross field
  intake.setVelocity(10, percent);
  intake.spin(reverse);
  
// cross barrier

  chassis.drive_distance(-5);
  chassis.turn_to_angle(currentAngle+58);
  chassis.drive_distance(-40);
  chassis.turn_to_angle(currentAngle+14);
  // wait(5, seconds);
  chassis.set_drive_exit_conditions(2, 0, 10000);
  chassis.set_turn_exit_conditions(2, 0, 3000);
  chassis.set_swing_exit_conditions(2, 0, 3000);

  chassis.drive_distance(-72);

  chassis.set_drive_exit_conditions(2, 0, 5000);

// turn for hit w/ back of bot

  chassis.drive_distance(-10, currentAngle-10);
  chassis.drive_distance(-17, currentAngle-50);

  chassis.set_drive_exit_conditions(1.5, 300, 1000);
  chassis.set_turn_exit_conditions(2, 300, 1000);
  chassis.set_swing_exit_conditions(1, 300, 1000);

// hit 1

  chassis.drive_distance(-100, currentAngle-72, 12, 8);

  // wait(0.25, seconds);


// sidehit 2
  chassis.drive_distance(10, currentAngle-67);
  // wait(0.05, seconds);
  drive_pls(12, false);
  wait(1, seconds);
  drive_stop();


  intake.spin(reverse);

  currentAngle = 21;
  intake.setVelocity(10, percent);
  intake.spin(reverse);

  // setup for turn

  chassis.drive_distance(7.5, 60+currentAngle);
  flaps.set(true);
  // chassis.drive_distance(, 60+currentAngle);
  chassis.set_drive_exit_conditions(1.5, 0, 5000);
  chassis.set_turn_exit_conditions(2, 0, 3000);
  chassis.set_swing_exit_conditions(1, 0, 3000);

  // the turn

  chassis.drive_distance(5, 80+currentAngle, 12, 11, 1, 50, 1000); // 9, 8 if u need to switch back
  chassis.drive_distance(9, 120+currentAngle, 12, 11, 1, 50, 1000);
  chassis.drive_distance(5, 135+currentAngle, 12, 11, 1, 50, 1000);
  chassis.drive_distance(13, 150+currentAngle, 12, 11, 1, 50, 1000);
  chassis.drive_distance(10, 150+currentAngle, 12, 11, 1, 50, 1000);
  chassis.drive_distance(13, 270+currentAngle, 12, 11, 1, 50, 1000);


  // the push

  chassis.set_drive_exit_conditions(1.5, 100, 1500);
  chassis.drive_distance(50, 270+currentAngle, 12, 12, 2, 300, 1600);


  // second push:
  // flaps.set(false);
  // wait(0.2, seconds);
  // chassis.drive_distance(-25, 270);
  // flaps.set(true);
  // wait(0.2, seconds);
  // chassis.drive_distance(35, 270, 12, 12, 2, 100, 800);


  // backup

  flaps.set(false);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(2, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);

  chassis.drive_distance(-7);
  chassis.drive_distance(-27, 250+currentAngle, 12, 12, 1.5, 300, 1500);
  chassis.drive_distance(5, 170+currentAngle, 8.5, 7.5);

  // drive parallel to middle bar
  chassis.drive_distance(46, 168.4+currentAngle, 7, 7, 1.5, 300, 2400);

  // turn for final pushes

  chassis.turn_to_angle(335, 10.5);
  flaps.set(true);

  // push 1
  chassis.drive_distance(40, 270, 12, 4, 1.5, 300, 1100);

  flaps.set(false);
  wait(0.2, seconds);
  chassis.drive_distance(-28);
  flaps.set(true);
  wait(0.2, seconds);

  // // push 2
  // chassis.drive_distance(35, 280, 12, 4, 1.5, 300, 1200);

  // push in mid net
  chassis.drive_distance(-30, 280, 12, 4, 1.5, 300, 1100);
  // chassis.turn_to_angle(300);
  chassis.drive_distance(50, 280, 12, 4, 1.5, 300, 1200);
  flaps.set(false);

  chassis.drive_distance(-28);
  chassis.turn_to_angle(230);
  chassis.drive_distance(66);

  chassis.turn_to_angle(150);
  chassis.drive_distance(10, 132);
  // chassis.drive_distance(15, 120);
  chassis.set_drive_exit_conditions(1.5, 0, 5000);
  chassis.set_turn_exit_conditions(2, 0, 3000);
  chassis.set_swing_exit_conditions(1, 0, 3000);
  chassis.drive_distance(-16, 140);
  chassis.drive_distance(-22, 210, 12, 7);
  chassis.drive_distance(-20, 210, 12, 12, 1, 300, 900);
  chassis.drive_distance(12);
  chassis.drive_distance(-20, 210, 12, 12, 1, 300, 900);
  chassis.drive_distance(10);
}

/*---------------------------------------------------------------------------*/






