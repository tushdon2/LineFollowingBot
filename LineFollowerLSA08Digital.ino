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

void loop() {
    // reading LSA08 sensor data 
    for (int i = 2; i <= 9; i++){
        sensor[i - 2] = digitalRead(i);  
    }

    // printing LSA08 sensor data on serial monitor
//    if (!x)
//    {   
//        for (int i = 2; i <= 9; i++){
//            Serial.println(sensor[i-2]);
//            
//        }
//        x = true;
//    }

    correction = {K2 * sensor[0] + K3 * sensor[1] + K4 * sensor[2] - (K7 * sensor[5] + K8 * sensor[6] + K9 * sensor[7])};

    LSpeed = motorspeed - correction;
    RSpeed = motorspeed + correction;

    // motor speed is passed to MDD10A as pwm pulse, so it has to be constrained between 0 to 255. For eg. 255 will rotate a 300 rpm motor at the highest speed
    LSpeed = constrain(LSpeed, 0, 255);
    RSpeed = constrain(RSpeed, 0, 255);

    moveForward(LSpeed, RSpeed);
    // moveForward(255,255);
}

void moveForward(int LSpeed, int RSpeed) {
    // function to move the bot at a particular speed 
    digitalWrite(dir1, LOW);
    digitalWrite(dir2, LOW);
    analogWrite(pwm1, LSpeed); 
    analogWrite(pwm2, RSpeed);
}

void wait() {
    // Function to makes the robot stay
    analogWrite(pwm1, 0);
    analogWrite(pwm2, 0);
}
