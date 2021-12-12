// pins for Cytron MDD10A motor driver
const byte dir1 = 13;   // Connect DIR1 of motor driver to pin 13
const byte dir2 = 12;   // Connect DIR2 of motor driver to pin 12
const byte pwm1 = 11;   // Connect PWM1 of motor driver to pin 11
const byte pwm2 = 10;   // Connect PWM2 of motor driver to pin 10

int motorspeed = 60;
int LSpeed = motorspeed; // initial motor speed
int RSpeed = motorspeed; // initial motor speed

// Proportional correction constants, to be found by trial-and-error
int K2 = 25;
int K3 = 17;
int K4 = 10;
int K7 = 10;
int K8 = 17;
int K9 = 25;

//boolean x = false; // to print LSA08 sensor data

int correction = 0;

int sensor[8]; // array to store LSA08 sensor (digital mode) data

void setup() {
    // Setting pin 2 - 9 as digital input pin for Cytron LSA08
    for(byte i = 2; i <= 9; i++) {
        pinMode(i, INPUT);
    }
    
    // Setting pin 10 - 13 as digital output pin for MDD10A
    for(byte i = 10; i <= 13; i++) {
        pinMode(i, OUTPUT);
    }
    
    // Setting the initial condition of motors, both PWM pins are LOW
    digitalWrite(pwm1, LOW);
    digitalWrite(pwm2, LOW);
    
    digitalWrite(dir1, HIGH);
    digitalWrite(dir2, HIGH);

    Serial.begin(9600);
}
