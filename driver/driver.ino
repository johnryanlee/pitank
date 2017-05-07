#include <Wire.h>

int I2C_ADDR = 8;
String I2C_INPUT;
String I2C_OUTPUT;
bool I2C_RECEIVED = false;

int M1_SPD_PIN = 5;
int M1_SPD = 0;
int M2_SPD_PIN = 6;
int M2_SPD = 0;
int M2_DIR_PIN = 7;
int M2_DIR = 0;
int M1_DIR_PIN = 8;
int M1_DIR = 0;
int MAX_FWD_SPD = 255;
int MAX_BACK_SPD = 255;
int TURN_SPD = 150;
int MAX_TURN_SPD = 150;
bool FORWARD = false;
bool BACKWARD = false;
bool TURNING_LEFT = false;
bool TURNING_RIGHT = false;
bool STOP = false;

int distance = 0;
#define DIST_FL_TRIG A1
#define DIST_FL_ECHO A0
#define DIST_FF_TRIG A3
#define DIST_FF_ECHO A2
int DIST_FR_TRIG = 2;
int DIST_FR_ECHO = 3;
int DIST_BACK_TRIG = 10;
int DIST_BACK_ECHO = 9;

String MESSAGE = "Hello, this is a message...";

void stop(void) {
// Halt motion
	analogWrite(M1_SPD_PIN, 0); 
	digitalWrite(M1_DIR_PIN, LOW);    
	analogWrite(M2_SPD_PIN, 0); 
	digitalWrite(M2_DIR_PIN, HIGH);    
	Serial.print("M1 SPD 0, LOW | ");
	Serial.println("M2 SPD 0, HIGH");
	FORWARD = false;
	BACKWARD = false;
	TURNING_LEFT = false;
	TURNING_RIGHT = false;
	STOP = true;
} 

void drive(bool direction, int spd) {
// Drive in direction at speed
// FWD: direction = high 
// BACK: direction = low
// SPD = how fast (0-255)
	analogWrite(M1_SPD_PIN, spd);
	analogWrite(M2_SPD_PIN, spd);
	if (direction) {
		digitalWrite(M1_DIR_PIN, HIGH);
		digitalWrite(M2_DIR_PIN, LOW);
		FORWARD = true;
		BACKWARD = false;
		Serial.print("M1 SPD ");
		Serial.print(spd);
		Serial.print(", HIGH | ");
		Serial.print("M2 SPD ");
		Serial.print(spd);
		Serial.println(", LOW");
	} else {
		digitalWrite(M1_DIR_PIN, LOW);
		digitalWrite(M2_DIR_PIN, HIGH);
		FORWARD = false;
		BACKWARD = true;
		Serial.print("M1 SPD ");
		Serial.print(spd);
		Serial.print(", LOW | ");
		Serial.print("M2 SPD ");
		Serial.print(spd);
		Serial.println(", HIGH");
	}
	TURNING_LEFT = false;
	TURNING_RIGHT = false;
	STOP = false;
}

void turn(bool direction, int spd) {
// Drive in direction at speed
// LEFT: direction = high 
// RIGHT: direction = low
// SPD = how fast (0-255)
	analogWrite(M1_SPD_PIN, spd);
	analogWrite(M2_SPD_PIN, spd);
	if (direction) {
		digitalWrite(M1_DIR_PIN, LOW);
		digitalWrite(M2_DIR_PIN, LOW);
		TURNING_LEFT = true;
		TURNING_RIGHT = false;
		Serial.print("M1 SPD ");
		Serial.print(spd);
		Serial.print(", LOW | ");
		Serial.print("M2 SPD ");
		Serial.print(spd);
		Serial.println(", LOW");
	} else {
		digitalWrite(M1_DIR_PIN, HIGH);
		digitalWrite(M2_DIR_PIN, HIGH);
		TURNING_LEFT = false;
		TURNING_RIGHT = true;
		Serial.print("M1 SPD ");
		Serial.print(spd);
		Serial.print(", HIGH | ");
		Serial.print("M2 SPD ");
		Serial.print(spd);
		Serial.println(", HIGH");
	}
	FORWARD = false;
	BACKWARD = false;
	STOP = false;
}


int distance_sensor(int sensor) {
// Calculate distance between object and respective sensor
// 0 = Back
// 1 = Front Left
// 2 = Front Front
// 3 = Front Right
	int duration = 0;
	if (sensor == 0) {
		// Back
		digitalWrite(DIST_BACK_TRIG, LOW);
		delayMicroseconds(2);
		digitalWrite(DIST_BACK_TRIG, HIGH);
		delayMicroseconds(10);
		digitalWrite(DIST_BACK_TRIG, LOW);
		duration = pulseIn(DIST_BACK_ECHO, HIGH);
		Serial.println("Back sensor queried");
	}
	if (sensor == 1) {
		// Front left
		digitalWrite(DIST_FL_TRIG, LOW);
		delayMicroseconds(2);
		digitalWrite(DIST_FL_TRIG, HIGH);
		delayMicroseconds(10);
		digitalWrite(DIST_FL_TRIG, LOW);
		duration = pulseIn(DIST_FL_ECHO, HIGH);
		Serial.println("FL sensor queried");
	}
	if (sensor == 2) {
		// Front Front
		digitalWrite(DIST_FF_TRIG, LOW);
		delayMicroseconds(2);
		digitalWrite(DIST_FF_TRIG, HIGH);
		delayMicroseconds(10);
		digitalWrite(DIST_FF_TRIG, LOW);
		duration = pulseIn(DIST_FF_ECHO, HIGH);
		Serial.println("FF sensor queried");
	}
	if (sensor == 3) {
		// Front Right
		digitalWrite(DIST_FR_TRIG, LOW);
		delayMicroseconds(2);
		digitalWrite(DIST_FR_TRIG, HIGH);
		delayMicroseconds(10);
		digitalWrite(DIST_FR_TRIG, LOW);
		duration = pulseIn(DIST_FR_ECHO, HIGH);
		Serial.println("FR sensor queried");
	}
	duration = duration /29 / 2;
	return duration;
}

void receiveData(int byteCount) {
	I2C_INPUT = "";
	Serial.println("Something received on I2C");
	Serial.print("Byte Count: ");
	Serial.println(byteCount);
	while (Wire.available()) {
		char c = Wire.read();
		Serial.print("data received: ");
		Serial.println(c);
	}
}

void sendData() {
	I2C_OUTPUT = "Testicles";
	Serial.print("Sending phrase: ");
	Serial.println(I2C_OUTPUT);
	int strlen = I2C_OUTPUT.length() -1;
	for (int i = 0; i <= strlen; i++) {
		char myChar = I2C_OUTPUT.charAt(i);
		Wire.write(myChar);
		Serial.print("Character being sent: ");
		Serial.println(myChar);
	}
}

void setup() {
	Serial.begin(19200);
	Serial.println("Started motor and distance sensor board!");
	Wire.begin(I2C_ADDR);
	Wire.onRequest(sendData);
	Wire.onReceive(receiveData);
	Serial.println("Ready!");
}

void loop() {
//	distance = distance_sensor(0);
//	Serial.print("Distance back: ");
//	Serial.println(distance);
	if(Serial.available()) {
		char val = Serial.read();
		if(val != -1) {
			switch(val) {
				case 'w'://Move Forward
					drive(true, MAX_FWD_SPD);   //move forward in max speed
					break;
				case 's'://Move Backward
					drive(false,MAX_BACK_SPD);   //move back in max speed
					break;
				case 'a'://Turn Left
					turn(true, MAX_TURN_SPD);        
					break;       
				case 'd'://Turn Right
					turn(false,MAX_TURN_SPD);
					break;
				case 'z':
					Serial.println(MESSAGE);
					break;
				case 'x':
					stop();
					break;
			}
		}
		else stop();  
	}
}
