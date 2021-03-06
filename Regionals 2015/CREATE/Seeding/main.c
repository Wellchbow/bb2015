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
	armMove(ARM_HIGH, 1000, 28, 350);
	//playCoin();
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
	createDrive(300, 14);
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
	createDriveBack(200, 7);
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
	createDrive(300, 11);
	raiseLowerArm(ARM_MEDIUM, 1000);
	playCoin();
}

void pingPongHigh2() {
	createDriveBack(100, 2);
	armMove(ARM_HIGH + 700, 1000, 8, -200);		//gets into position
	msleep(500);
	createTurnRight(20);
	armMove(ARM_HIGH, 1500, 22, 300);		//gets ping pong	
	raiseLowerArm(ARM_HIGH, 500);		//gets ping pong
	playCoin();
	createDriveBack(100, 15);
}

void pingPongMedium2() {
	createDriveBack(100, 2);
	armMove(ARM_MEDIUM + 300, 1000, 15, -100);		//gets into position
	createTurnRight(20);
	createDrive(300, 18);
	raiseLowerArm(ARM_HIGH, 1000);		//gets ping pong
	playCoin();
	msleep(500);
}

void scrape() {
	raiseLowerArm(ARM_HIGH, 3000);
	msleep(2000);
	createTurnLeft(-35);
	createTurnRight(-35);
	driveTouch(-200);
	createDrive(100, 10);
	createTurnLeft(3);
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
	createTurnLeft(54);
	//createSquareUp(500, 3.9);
	//createSquareUp(300, 1.2);
	squareAndSound();
	set_servo_position(ARM_SERVO, ARM_DRIVE_HEIGHT);
	createDriveBack(200, 5);
	createTurnRight(77);
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
	createTurnLeft(3);
	createBasketDump();
	createSquareUp(100, 0.5);
}

void createMain() { //This is being programmed for the actual competion now
	pingPong();
	preparePingPong();
	pingPong2();
	dump();
	dump2();
	scrape();
}


int main() {
	enableDevices();
	//createDrive(100, 10);
	//raiseLowerArm(ARM_HIGH, 1000);
	wait_for_light(0);
	shut_down_in(120);
	prepareDevices();
	createMain();
//	playTunes();
	playWin();
	return 0;
}
