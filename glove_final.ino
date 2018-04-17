//Program by Paul Velarde. 2018

#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
//#define DEBUG
//#define DEBUG_FLEX

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
long currentMillis;
int analogArray[15];
int helloArray[10];
long cMillis;

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    Serial.begin(38400);
    pinMode(13, OUTPUT);
    accelgyro.initialize();

    // verify connection
    //Serial.println("Testing device connections...");
    //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");



}

void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  #ifdef DEBUG 
        // accel and gyro debug
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.println(az); Serial.print("\t");
        //Serial.println(gx); Serial.print("\t");
        //Serial.print(gy); Serial.print("\t");
        //Serial.println(gz);
  #endif
    //Fetch flex data
    analogArray[0] = analogRead(A0);
    analogArray[1] = analogRead(A1);
    analogArray[2] = analogRead(A2);
    analogArray[3] = analogRead(A3);
    analogArray[4] = analogRead(A6);

    //correlate flex data
    #ifdef DEBUG_FLEX
    Serial.print(analogArray[0]); Serial.print(", ");     //PINKY
    Serial.print(analogArray[1]); Serial.print(", ");     //RING
    Serial.print(analogArray[2]); Serial.print(", ");     //MIDDLE
    Serial.print(analogArray[3]); Serial.print(", ");     //INDEX
    Serial.println(analogArray[4]);                       //THUMB
    #endif   

    
    
    //Database start

    if (ay > 31000 &&
        analogArray[0] >= 65 && analogArray[0] <= 100 &&
        analogArray[1] >= 65 && analogArray[1] <= 100 &&
        analogArray[2] >= 65 && analogArray[2] <= 100 &&
        analogArray[3] >= 65 && analogArray[3] <= 100 &&
        analogArray[4] >= 27 && analogArray[4] <= 35)
        { serial_send("Hello");}  
    else if (abs(ax) > 25000 &&
        analogArray[0] >= 35 && analogArray[0] <= 45 &&
        analogArray[1] >= 25 && analogArray[1] <= 40 &&
        analogArray[2] >= 30 && analogArray[2] <= 45 &&
        analogArray[3] >= 69 && analogArray[3] <= 80 &&
        analogArray[4] >= 22 && analogArray[4] <= 30)
        {serial_send("this is");}
    else if (ax > 15000 && abs(ay) < 7000 && abs(az) < 7000 &&
        analogArray[0] >= 55 && analogArray[0] <= 80 &&
        analogArray[1] >= 30 && analogArray[1] <= 40 &&
        analogArray[2] >= 30 && analogArray[2] <= 49 &&
        analogArray[3] >= 65 && analogArray[3] <= 87 &&
        analogArray[4] >= 25 && analogArray[4] <= 35)
        {serial_send("Voice Avenue");}
    else if (abs(az) > 15000 && abs(ay) > 15000 &&
        analogArray[0] >= 31 && analogArray[0] <= 40 &&
        analogArray[1] >= 30 && analogArray[1] <= 40 &&
        analogArray[2] >= 31 && analogArray[2] <= 40 &&
        analogArray[3] >= 30 && analogArray[3] <= 36 &&
        analogArray[4] >= 22 && analogArray[4] <= 28)
        {serial_send("we are");}
    else if (ay < -20000 && 
        analogArray[0] >= 65 && analogArray[0] <= 100 &&
        analogArray[1] >= 65 && analogArray[1] <= 100 &&
        analogArray[2] >= 65 && analogArray[2] <= 100 &&
        analogArray[3] >= 65 && analogArray[3] <= 100 &&
        analogArray[4] >= 19 && analogArray[4] <= 23)
        {serial_send("students of");}
    else if ( ay > 25000 && 
        analogArray[0] >= 58 && analogArray[0] <= 75 &&
        analogArray[1] >= 30 && analogArray[1] <= 44 &&
        analogArray[2] >= 33 && analogArray[2] <= 45 &&
        analogArray[3] >= 30 && analogArray[3] <= 45 &&
        analogArray[4] >= 24 && analogArray[4] <= 29)
        {serial_send("j");}
    else if (
        analogArray[0] >= 40 && analogArray[0] <= 45 &&
        analogArray[1] >= 30 && analogArray[1] <= 36 &&
        analogArray[2] >= 41 && analogArray[2] <= 47 &&
        analogArray[3] >= 40 && analogArray[3] <= 46 &&
        analogArray[4] >= 20 && analogArray[4] <= 24)
        {
          cMillis = millis();
          
            serial_send("C");
            cMillis = 0;
        }
    else if (az > 25000 && ax < -23000 &&
        analogArray[0] >= 35 && analogArray[0] <= 45 &&
        analogArray[1] >= 30 && analogArray[1] <= 40 &&
        analogArray[2] >= 66 && analogArray[2] <= 85 &&
        analogArray[3] >= 60 && analogArray[3] <= 85 &&
        analogArray[4] >= 23 && analogArray[4] <= 28)
        {serial_send("My");}  
    else if (ay > 20000 &&   
        analogArray[0] >= 33 && analogArray[0] <= 45 &&
        analogArray[1] >= 66 && analogArray[1] <= 85 &&
        analogArray[2] >= 66 && analogArray[2] <= 85 &&
        analogArray[3] >= 66 && analogArray[3] <= 85 &&
        analogArray[4] >= 20 && analogArray[4] <= 28)
        {serial_send("name is");}   
    else if (ax > 15000 && abs(ay) < 7000 && abs(az) < 7000 &&
        analogArray[0] >= 35 && analogArray[0] <= 45 &&
        analogArray[1] >= 30 && analogArray[1] <= 40 &&
        analogArray[2] >= 68 && analogArray[2] <= 85 &&
        analogArray[3] >= 60 && analogArray[3] <= 100 &&
        analogArray[4] >= 23 && analogArray[4] <= 28)
        {serial_send("U");}
    else if (ax > 15000 && abs(ay) < 7000 && abs(az) < 7000 &&
        analogArray[0] >= 31 && analogArray[0] <= 40 &&
        analogArray[1] >= 30 && analogArray[1] <= 40 &&
        analogArray[2] >= 31 && analogArray[2] <= 40 &&
        analogArray[3] >= 30 && analogArray[3] <= 36 &&
        analogArray[4] >= 22 && analogArray[4] <= 28)
        {serial_send("S");}
    else if (ax > 15000 && abs(ay) < 7000 && abs(az) < 7000 &&
        analogArray[0] >= 65 && analogArray[0] <= 80 &&
        analogArray[1] >= 70 && analogArray[1] <= 80 &&
        analogArray[2] >= 70 && analogArray[2] <= 80 &&
        analogArray[3] >= 75 && analogArray[3] <= 85 &&
        analogArray[4] >= 18 && analogArray[4] <= 23)
        {serial_send("B");}
    else if (ax < 7000 && az < -30000 && ay < 5000 &&
        analogArray[0] >= 65 && analogArray[0] <= 80 &&
        analogArray[1] >= 65 && analogArray[1] <= 80 &&
        analogArray[2] >= 65 && analogArray[2] <= 80 &&
        analogArray[3] >= 65 && analogArray[3] <= 80 &&
        analogArray[4] >= 24 && analogArray[4] <= 30)
        {serial_send("Think you");}    
    else if (abs(az) > 15000 && abs(ay) > 15000 &&
        analogArray[0] >= 55 && analogArray[0] <= 80 &&
        analogArray[1] >= 30 && analogArray[1] <= 40 &&
        analogArray[2] >= 30 && analogArray[2] <= 49 &&
        analogArray[3] >= 65 && analogArray[3] <= 87 &&
        analogArray[4] >= 25 && analogArray[4] <= 35)
        {serial_send("I'm fine");}
    if (ax < -10000 && az < -20000 &&
        analogArray[0] >= 65 && analogArray[0] <= 100 &&
        analogArray[1] >= 65 && analogArray[1] <= 100 &&
        analogArray[2] >= 65 && analogArray[2] <= 100 &&
        analogArray[3] >= 65 && analogArray[3] <= 100 &&
        analogArray[4] >= 18 && analogArray[4] <= 23)
        { serial_send("good afternoon");}
}



void serial_send(String x){
    if(millis()-currentMillis > 1200){
     #ifndef DEBUG 
      Serial.print(x);
     #endif
      currentMillis =  millis();
    }
}

