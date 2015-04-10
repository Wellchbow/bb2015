#include "createDrive.h"

void driveTouch(speed) {
	int x = 0;
	create_drive_direct(-1*speed,-1*speed);
	while(x == 0) {
		if (get_create_lbump() == 1 || get_create_rbump() == 1) {
			x = 1;
		}
	}
	create_stop();
}

void raiseLowerArm(int destination, int time) {
	int increment;
	int initAngle = get_servo_position(0);
	int angle = initAngle;
	if(angle < destination) {
		increment = 1;
	} else {
		increment = -1;
	}	
	
	while(abs(angle - destination) > 5) {
		printf("%d\n", angle);
		angle += increment;
		set_servo_position(ARM_SERVO, angle);
		msleep(time / abs(destination - initAngle));
	}
}

void armMove(int destination, float time, int distance, int speed) {
	int increment;
	int initAngle = get_servo_position(0);
	int driveDone = 0;
	int armDone = 0;
	int angle = initAngle;
	if(angle < destination) {
		increment = 5;
	} else {
		increment = -5;
	}
	create_drive_straight(-speed);
	if(speed > 0) {
		set_create_distance(distance*10);
	} else {
		set_create_distance(0);
	}
		
	while(driveDone == 0 || armDone == 0) {
		printf("%d\n", angle);
		if(abs(angle - destination) > 5) {
			angle+=increment;
			set_servo_position(ARM_SERVO, angle);
			msleep(time / abs(destination - initAngle));
		} else {
			armDone = 1;
		}
		if(speed > 0) {
			if(get_create_distance()*10 <= 0) {
				create_stop();
				set_create_distance(10); //Just make up a position more than 0 so it doesn't stop the create again, slowing the program
				driveDone = 1;
			}
		} else {
			if(get_create_distance() >= distance*10) {
				create_stop();
				set_create_distance(0);
				driveDone = 1;
			}
		}
	}
}

void createDrive(float speed, float distance) {
	set_create_distance(distance*10);
	create_drive_straight(-speed);
	while (get_create_distance() >= 0){}
	create_stop();
}

void createDriveBack(float speed, float distance) {
	set_create_distance(0);
	create_drive_straight(speed);
	while (get_create_distance() <= distance*10){}
	create_stop();
}

void createTurnLeft(int degrees) {
	set_create_normalized_angle(0); //Reset the angle
	create_spin_CCW(250); //Spin at half power
	while(get_create_normalized_angle() < degrees - 20) {} //go most of the distance
	create_spin_CCW(50); //slow down as to not overshoot
	while(get_create_normalized_angle() < degrees) {} //and finish the turn
	create_stop();
}

void createTurnRight(int degrees) {
	set_create_normalized_angle(degrees); //Reset the angle
	create_spin_CW(250); //Spin at half power
	while(get_create_normalized_angle() > 20) {} //go most of the distance
	create_spin_CW(50); //slow down as to not overshoot
	while(get_create_normalized_angle() > 0) {} //and finish the turn
	create_stop();
}

void createBasketDump(){
	set_servo_position(SERVO_BASKET, BASKET_DUMPED);
	msleep(750);
	set_servo_position(SERVO_BASKET, 1200);
	msleep(250);
	set_servo_position(SERVO_BASKET, BASKET_DUMPED);
	msleep(250);
	set_servo_position(SERVO_BASKET, BASKET_RETURNED);
	msleep(750);
}

void createSquareUp(float speed,float time){
	create_drive_direct(-1*speed,-1*speed);
	msleep(time*1000);
	create_stop();
}

void createArmDrive(int armDestination, float armSleepTime, float moveDistance, float moveSpeed) {
	float angle = get_servo_position(ARM_SERVO);

	if (moveDistance > 0) {
		set_create_distance(moveDistance*10);
		create_drive_straight(-moveSpeed);
	}
	
	else {
		set_create_distance(0);
		create_drive_straight(moveSpeed);
	}

	int armComplete = 0;
	int moveComplete = 0;
	
	while(armComplete == 0 || moveComplete == 0) {
		if(armComplete == 0) {
			if (armDestination < get_servo_position(ARM_SERVO)) {
				angle -= 1;
			}
			else {
			angle += 1;
			}
			set_servo_position(ARM_SERVO, angle);
			
			if(angle >= armDestination) {
				armComplete = 1;
			}
		}

		if (moveComplete == 0) {
			if (get_create_distance() <= 0) {
				if (get_create_distance() >= 0) {
					create_stop();
					moveComplete = 1;
				}
			}
		}
		
			else {
				if (get_create_distance() <= 0) {
					create_stop();
					moveComplete = 1;
				}
			}
	
		msleep(armSleepTime*100);
	}
}

void createArmSquareUp(int armDestination, float armSleepTime, float moveTime, float moveSpeed) {
	float angleR = get_servo_position(ARM_SERVO);
//	float angleR = get_servo_position(SERVO_UP_DOWN_RIGHT);

	create_drive_straight(-moveSpeed);
	
	int armComplete = 0;
	int moveComplete = 0;
	
	while(armComplete == 0 || moveComplete == 0) {
		if(armComplete == 0) {
			if (armDestination < get_servo_position(ARM_SERVO)/* + offsetLeft*/) {
//				angleL -= 0.1;
				angleR -=0.1;
			}
			else {
//			angleL += 0.1;
			angleR += 0.1;
			}
			set_servo_position(ARM_SERVO, angleR/* + offsetLeft*/);
//			set_servo_position(SERVO_UP_DOWN_RIGHT, 2047 - angleR - offsetRight);
			
			if(angleR/* + offsetLeft*/ >= armDestination) {
				armComplete = 1;
			}
		}

		if (moveComplete == 0) {
			msleep(moveTime*1000);
			create_stop();
			moveComplete = 1;
		}
	
		msleep(armSleepTime*100);
	}
}

void enableDevices() {
	enable_servos();
	set_servo_position(SERVO_BASKET, BASKET_RETURNED);
	set_servo_position(ARM_SERVO, 1805);
	msleep(10000);
	create_connect();
}


/*
void servo_drive(int end, int time, float d_speed, float distance) //-d_speed means backwards
{
	set_create_distance(distance*10);
	if (d_speed > 0) 
	{
		set_create_distance(0);
	}
	printf("%d", get_create_distance());
	float increment = .01;
	float tune_time = 0.875;
	float curr,start = get_servo_position(ARM_SERVO) + OFFSET;
	float i = ((end-start)/(time*tune_time))*increment;
	curr = start;
	create_drive_straight(-d_speed);
	while((start > end && curr > end) || (start < end && curr < end))
	{
		if((get_create_distance()*10 <= 0 && d_speed < 0) || (get_create_distance()/10 >= distance && d_speed > 0))
		{
			create_stop();
		}
		set_servo_position(ARM_SERVO, curr + OFFSET);
		set_servo_position(SERVO_UP_DOWN_RIGHT, 2047 - curr - (OFFSET + 95));
		curr+=i;
		msleep((long)(increment*1000));
	}
	set_servo_position(ARM_SERVO, end + OFFSET);
	set_servo_position(SERVO_UP_DOWN_RIGHT, 2047 - end - (OFFSET + 95));
	while ((get_create_distance()*10 >= 0 && d_speed < 0) || (get_create_distance()/10 <= distance && d_speed > 0)) {}
	create_stop();
	
	/*int offset = 75;
	float increment = 0.05; 
	float tune_time = 0.19;
	float curr, start = get_servo_position(ARM_SERVO + offset);
	float i = ((end-start)/(time*tune_time))*increment;
	int driven = 0;
	int check = 0;
	if (-d_speed >= 0)
	{
		check = 1;
	}
	if (start > end)
	{
		set_create_distance(distance*10*check);
		create_drive_straight(-d_speed);
		while(curr > end - offset)
		{
			if (get_create_distance()*10 >= 0 && -d_speed > 0)
			{
				create_stop();
			}
			else if (get_create_distance()/10 <= 0)
			{
				create_stop();
			}
			set_servo_position(ARM_SERVO, curr + offset);
			set_servo_position(SERVO_UP_DOWN_RIGHT, 2047 - curr - offset);
			curr+=i;
			printf("1");
			msleep((long)(increment*1000));
			printf("1");
		}
		if (-d_speed > 0)
		{
			while (get_create_distance()*10 >= 0) {
			printf("4");
				}
		} 
		else if (-d_speed < 0)
		{
			while (get_create_distance()/10 <= 0) {}
		}
		create_stop();
	} 
	else if (start < end - offset)
	{
		set_create_distance(distance*10*check);
		create_drive_straight(-d_speed);
		while (curr < end)
		{
			if (get_create_distance()*10 >= 0 && -d_speed > 0)
			{
				create_stop();
			}
			else if (get_create_distance()/10 <= 0)
			{
				create_stop();
			}
			set_servo_position(ARM_SERVO, curr + offset);
			set_servo_position(SERVO_UP_DOWN_RIGHT, 2047 - curr - offset);
			curr+=i;
			printf("2");
			msleep((long)(increment*1000));
			printf("2");
		}
		if (-d_speed > 0)
		{
			while (get_create_distance()*10 >= 0) {
			printf("3");	
				}
			create_stop();
		} 
		else if (-d_speed < 0)
		{
			while (get_create_distance()/10 <= 0) {}
			create_stop();
		}
	}
	set_servo_position(ARM_SERVO, end + offset);
	set_servo_position(SERVO_UP_DOWN_RIGHT, 2047 - end - offset);
	create_stop();
}*/
