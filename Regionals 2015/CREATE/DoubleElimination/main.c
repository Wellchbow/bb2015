#include "template.h"

//main file gets run by robot calls methods in all other files

void playTunes() {
	enableDevices();
	playPowerup();
	playCoin();
}

void pingPongHigh() {
	//raiseLowerArm(ARM_HIGH - 200, 0.5);		//drives with raised arm
	//createDrive(100, 26);	
	armMove(ARM_HIGH, 4000, 31, 110);	    //puts arm into position
	playCoin();
//	raiseLowerArm(ARM_HIGH, 1);					//gets ping pong ball
	msleep(500);
	//createDriveBack(100, 8);
	//msleep(500);
}

void pingPongMedium() {
	//raiseLowerArm(ARM_MEDIUM - 200, 1);
	//msleep(500);
	createDriveBack(200, 2);
	armMove(ARM_MEDIUM + 300, 1000, 15, -100);		//gets into position
	createTurnLeft(19);
	createDrive(300, 15);
	raiseLowerArm(ARM_MEDIUM, 500);
	playCoin();
	//gets ping pong
	msleep(500);
	//createDriveBack(100, 12);
	//msleep(500);
}
	
void pingPongLow() {
	//raiseLowerArm(ARM_LOW - 100, 1);
	createDriveBack(200, 3);
	armMove(ARM_LOW + 450, 1000, 9, -150);		//gets into position
	msleep(500);
	createTurnLeft(16);
	createDrive(300, 26);
	raiseLowerArm(ARM_LOW-100, 500);
	playCoin();
	//gets ping pong	
	createDriveBack(200, 5);
	raiseLowerArm(ARM_DRIVE_HEIGHT-50, 500);
}

void pingPong() {
	pingPongHigh();
	pingPongMedium();
	pingPongLow();
}

void pingPong2() {
	pingPongLow2();
	pingPongMedium2();
		pingPongHigh2();
}

void pingPongLow2() {
	armMove(ARM_LOW+500, 1000, 10, 100);
	createDrive(300, 10);
	raiseLowerArm(ARM_LOW, 1000);
	playCoin();
}

void pingPongHigh2() {
	createDriveBack(100, 2);
	armMove(ARM_HIGH + 700, 1000, 8, -200);		//gets into position
	msleep(500);
	createTurnRight(18);
	armMove(ARM_HIGH, 4500, 26, 250);		//gets ping pong	
	playCoin();
	createDriveBack(100, 15);
}

void pingPongMedium2() {
	createDriveBack(100, 2);
	armMove(ARM_MEDIUM + 300, 1000, 14, -100);		//gets into position
	createTurnRight(20);
	createDrive(300, 18);
	raiseLowerArm(ARM_HIGH, 1000);		//gets ping pong
	playCoin();
	msleep(500);
}



void scrape() {
	raiseLowerArm(ARM_HIGH, 3000);
	msleep(2000);
	createTurnLeft(-20);
	createTurnRight(-20);
	driveTouch(-200);
	createDrive(100, 10);
	createScrapeBasket();
	createSquareUp(100, 5);
}

void squareAndSound() {
	create_drive_straight(-500);
	playStar();
	msleep(950);
	create_drive_straight(-300);
	msleep(1200);
}

void preparePingPong() {
	createTurnLeft(55);
	//createSquareUp(500, 3.9);
	//createSquareUp(300, 1.2);
	squareAndSound();
	set_servo_position(ARM_SERVO, ARM_DRIVE_HEIGHT);
	createDriveBack(200, 5);
	createTurnRight(75);
	driveTouch(-100);	
}

void dump() {
	raiseLowerArm(ARM_DRIVE_HEIGHT, 1000);
	createTurnRight(49);
	driveTouch(-400);
	createDrive(300, 125);
	raiseLowerArm(ARM_VERY_HIGH, 1000);
	createTurnLeft(91);
	createSquareUp(300, 1);
	createBasketDump();
}

void dump2() {
	createDriveBack(100, 45);
	createTurnRight(3);
	raiseLowerArm(ARM_DOWN, 1000);
	msleep(10000);
	raiseLowerArm(ARM_VERY_HIGH, 1000);
	createTurnLeft(2);
	createSquareUp(300, 3);
	playWin();
	createBasketDump();
}

void calderaBlock(time) {
	createTurnLeft(90);
	createDrive(500, 4);
	create_drive_direct(-280, -500);
	msleep(2350);
	createSquareUp(500, 1);
	set_servo_position(SERVO_BASKET, 0);
	msleep(1000);
	create_stop();
	msleep(time*100);
	set_servo_position(SERVO_BASKET, BASKET_RETURNED);
	driveTouch(-400);
	createDrive(100, 3);
	createTurnRight(90);
	createSquareUp(400, 2);
	createDriveBack(100, 5);
	createTurnLeft(180);
	driveTouch(-300);
	createTurnRight(93);
	driveTouch(-400);
	set_servo_position(ARM_SERVO, ARM_DOWN);
}

void createMain() { //This is being programmed for the actual competion now
	calderaBlock(3);
	pingPong();
	preparePingPong();
	pingPong2();
	dump();
	dump2();
	scrape();
}

int main() {
	shut_down_in(120);
	enableDevices();
	createMain();
//	playTunes();
	return 0;
}
