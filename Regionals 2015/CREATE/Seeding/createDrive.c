#include "createDrive.h"


void raiseLowerArmNew(int destination) {
	/*-----------------------------------------------\
	| If looking at the Link screen right side up... |
	| Servo 0 is the left one						 |
	| Servo 1 is the right one						 |
	| Servo 0 ground is 500; increasing raises arm   |
	| Servo 1 ground is 1240; decreasing raises arm  |
	\_______________________________________________*/

	//0 is ground, 520 is horizontal
	int offset = 200;
	set_servo_position(SERVO_UP_DOWN_LEFT, 500 + destination - offset);
	set_servo_position(SERVO_UP_DOWN_RIGHT, 1240 - destination + offset);
}


void createDrive (float speed, float distance) {
	set_create_distance(0);
	create_drive_direct(speed,speed);
	while (get_create_drive_distance*10 <= distance){}
	create_stop();
}

void createTurnLeft(int degrees) {
	set_create_normalized_angle(0); //Reset the angle
	create_spin_CCW(250); //Spin at half power
	while(get_create_normalized_angle() <= degrees - 20) {} //go most of the distance
	create_spin_CCW(50); //slow down as to not overshoot
	while(get_create_normalized_angle() <= degrees) {} //and finish the turn
	create_stop();
}

void createTurnRight(int degrees) {
	set_create_normalized_angle(degrees); //Reset the angle
	create_spin_CW(250); //Spin at half power
	while(get_create_normalized_angle() >= 20) {} //go most of the distance
	create_spin_CW(50); //slow down as to not overshoot
	while(get_create_normalized_angle() >= 0) {} //and finish the turn
	create_stop();
}

void createBasketDump(){
	set_servo_position(SERVO_BASKET, BASKET_DUMPED);
}

void createBasketReturn(){
	set_servo_position(SERVO_BASKET, BASKET_RETURNED);
}

void createSquareUp(float speed,float time){
	create_drive_direct(-1*speed,-1*speed);
	msleep(time*1000);
}





