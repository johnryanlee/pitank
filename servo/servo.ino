#include <Wire.h>
#include <Servo.h>

Servo pan;
Servo tilt;
int PAN_POS = 0;
int PAN_CENTER = 90;
int PAN_MIN = 20;
int PAN_MAX = 160;
int PAN_PIN = 10;
int PAN_STEP = 1;
int PAN_DELAY = 15;
int TILT_POS = 0;
int TILT_CENTER = 92;
int TILT_MIN = 20;
int TILT_MAX = 160;
int TILT_PIN = 9;
int TILT_STEP = 1;
int TILT_DELAY = 15;

int I2C_ADDR = 9;
bool I2C_RECEIVED = false;
char I2C_CHAR;

void receiveData(int byteCount) {
	while (1 < Wire.available()) { // loop through all but the last
		I2C_CHAR = Wire.read(); // receive byte as a character
		Wire.write(I2C_CHAR);         // print the character
		I2C_RECEIVED = true;
	}
}

void sendData() {
}

void setup() {
	Wire.begin(I2C_ADDR);
	Wire.onReceive(receiveData);
	Wire.onRequest(sendData);
	pan.attach(PAN_PIN);
	pan.write(PAN_POS);
	tilt.attach(TILT_PIN);
	tilt.write(TILT_POS);
	/*for (int i = 0; i <= 2; i++) {
		delay(100);
		for (int x = PAN_MIN; x <= PAN_MAX; x += PAN_STEP) {
			pan.write(x);
			delay(PAN_DELAY);
		}
		for (int x = PAN_MAX; x >= PAN_MIN; x -= PAN_STEP) {
			pan.write(x);
			delay(PAN_DELAY);
		}
		for (int x = TILT_MIN; x <= TILT_MAX; x += TILT_STEP) {
			tilt.write(x);
			delay(TILT_DELAY);
		}
		for (int x = TILT_MAX; x >= TILT_MIN; x -= TILT_STEP) {
			tilt.write(x);
			delay(TILT_DELAY);
		}
	}*/
	pan.write(PAN_CENTER);
	tilt.write(TILT_CENTER);
}

void loop() {
	delay(100);
}
