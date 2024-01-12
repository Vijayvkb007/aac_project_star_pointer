// #include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define MPU_ADD 0x68
#define STEPPER_PIN_1 4
#define STEPPER_PIN_2 5
#define STEPPER_PIN_3 6
#define STEPPER_PIN_4 7
#define STEPPER_PIN_5 8
#define STEPPER_PIN_6 9
#define STEPPER_PIN_7 10
#define STEPPER_PIN_8 11


double current_angle_x;
double current_angle_y;

double ac_x;
double ac_y;
double ac_z;
double gy_x;
double gy_y;
double gy_z;
double deg_x;
double deg_y;
double dgy_x;
double dgy_y;

float stardata[12][2] = {
    {101.28, -16.71},
    {78.64, -8.2},
    {37.95, 89.26},
    {116.33, 28.03},
    {114.83, 5.23},
    {88.79, 7.41},
    {68.98, 16.51},
    {79.17, 46},
    {300,8.86},
    {213.75, 19.2},
    {219.75, -60.83},
    {279.0, 38.47}};

const float pi = 3.141592;
float Azimuth, altitude, hourangle, latitude = 13, longitude = 74.80;
int starNo, localDay, localTime;

float DtoR(float degree) {
  return degree / 360 * 2 * pi;
}

float RtoD(float radian) {
  return radian / (2 * pi) * 360;
}

void findAa(double declination) {
  Azimuth = RtoD(atan(sin(DtoR(hourangle)) / (cos(DtoR(hourangle)) * sin(DtoR(latitude)) - tan(DtoR(declination)) * cos(DtoR(latitude)))));
  altitude = RtoD(asin(sin(DtoR(latitude)) * sin(DtoR(declination)) + cos(DtoR(latitude)) * cos(DtoR(declination)) * cos(DtoR(hourangle))));
}

void findHourangle(double rightAscention) {
  hourangle = (localDay * 0.0657098) + (localTime * 1.002737) + 6.1265 - (longitude - 136) / 15;
  if (hourangle < 0)
    hourangle += 24;
  else if (hourangle >= 24)
    hourangle -= 24;
  hourangle = hourangle / 24 * 360;
  hourangle -= rightAscention;
  if (hourangle < 0)
    hourangle += 360;
}

void calc(int N) {
  findHourangle(stardata[N - 1][0]);
  findAa(stardata[N - 1][1]);
}

void inputstarNo() {
  Serial.println("Hello. Which star should I point?");
  Serial.println("1.Sirius 2.Rigel 3.Polaris 4.Pollux");
  Serial.println("5.Procyon 6.Betelgeuse 7.Aldebaran 8.Capella");
  Serial.println("9.Altair 10.Arcturus 11.Alpha Centauri 12.Vega");
  while (1) {
    if (Serial.available()) {
      starNo = Serial.parseInt();
      if (starNo >= 1 && starNo <= 12)
        break;
      else
        Serial.println("You Just Exceeded the Star limit !!!!");
    }
  }
  Serial.print("Finding ");
  Serial.print(starNo);
  Serial.println(".........");
}

void turnStepper1(float angle, int way) {
  float steps = (angle / 360) * (2048);
  int countstep = 0;
  int delaytime = 5000;
  if (way == - 1) {
    while (countstep < steps) {
      digitalWrite(STEPPER_PIN_1, HIGH);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3,LOW);
 digitalWrite(STEPPER_PIN_4,HIGH);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_1,LOW);
 digitalWrite(STEPPER_PIN_2,LOW);
 digitalWrite(STEPPER_PIN_3,HIGH);
 digitalWrite(STEPPER_PIN_4,HIGH);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_1,LOW);
 digitalWrite(STEPPER_PIN_2,HIGH);
 digitalWrite(STEPPER_PIN_3,HIGH);
 digitalWrite(STEPPER_PIN_4,LOW);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_1,HIGH);
 digitalWrite(STEPPER_PIN_2,HIGH);
 digitalWrite(STEPPER_PIN_3,LOW);
 digitalWrite(STEPPER_PIN_4,LOW);
 countstep++;
 delayMicroseconds(delaytime);
    }
  } else if (way == 1) {
    while (countstep < steps) {
      digitalWrite(STEPPER_PIN_1, HIGH);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3,LOW);
 digitalWrite(STEPPER_PIN_4,HIGH);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_1,HIGH);
 digitalWrite(STEPPER_PIN_2,HIGH);
 digitalWrite(STEPPER_PIN_3,LOW);
 digitalWrite(STEPPER_PIN_4,LOW);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_1,LOW);
 digitalWrite(STEPPER_PIN_2,HIGH);
 digitalWrite(STEPPER_PIN_3,HIGH);
 digitalWrite(STEPPER_PIN_4,LOW);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_1,LOW);
 digitalWrite(STEPPER_PIN_2,LOW);
 digitalWrite(STEPPER_PIN_3,HIGH);
 digitalWrite(STEPPER_PIN_4,HIGH);
 countstep++;
 delayMicroseconds(delaytime);
 
      // Implement other stepper control logic here
    }
  }
}

void turnStepper2(float angle, int way) {
  float steps = (angle / 360) * (2048);
  int countstep = 0;
  int delaytime = 5000;
  if (way == 1) {
    while (countstep < steps) {
      digitalWrite(STEPPER_PIN_5, HIGH);
      digitalWrite(STEPPER_PIN_6, LOW);
      digitalWrite(STEPPER_PIN_7,LOW);
 digitalWrite(STEPPER_PIN_8,HIGH);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_5,LOW);
 digitalWrite(STEPPER_PIN_6,LOW);
 digitalWrite(STEPPER_PIN_7,HIGH);
 digitalWrite(STEPPER_PIN_8,HIGH);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_5,LOW);
 digitalWrite(STEPPER_PIN_6,HIGH);
 digitalWrite(STEPPER_PIN_7,HIGH);
 digitalWrite(STEPPER_PIN_8,LOW);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_5,HIGH);
 digitalWrite(STEPPER_PIN_6,HIGH);
 digitalWrite(STEPPER_PIN_7,LOW);
 digitalWrite(STEPPER_PIN_8,LOW);
 countstep++;
 delayMicroseconds(delaytime);

      // Implement other stepper control logic here
    }
  } else if (way == -1) {
    while (countstep < steps) {
      digitalWrite(STEPPER_PIN_5, HIGH);
      digitalWrite(STEPPER_PIN_6, LOW);
      digitalWrite(STEPPER_PIN_7,LOW);
 digitalWrite(STEPPER_PIN_8,HIGH);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_5,HIGH);
 digitalWrite(STEPPER_PIN_6,HIGH);
 digitalWrite(STEPPER_PIN_7,LOW);
 digitalWrite(STEPPER_PIN_8,LOW);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_5,LOW);
 digitalWrite(STEPPER_PIN_6,HIGH);
 digitalWrite(STEPPER_PIN_7,HIGH);
 digitalWrite(STEPPER_PIN_8,LOW);
 countstep++;
 delayMicroseconds(delaytime);

 digitalWrite(STEPPER_PIN_5,LOW);
 digitalWrite(STEPPER_PIN_6,LOW);
 digitalWrite(STEPPER_PIN_7,HIGH);
 digitalWrite(STEPPER_PIN_8,HIGH);
 countstep++;
 delayMicroseconds(delaytime);
      // Implement other stepper control logic here
    }
  }
}

void getaccdata() {
  Wire.beginTransmission(MPU_ADD);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADD, 6, true);
  ac_x = Wire.read() << 8 | Wire.read();
  ac_y = Wire.read() << 8 | Wire.read();
  ac_z = Wire.read() << 8 | Wire.read();
}

void getgyrdata() {
  Wire.beginTransmission(MPU_ADD);
  Wire.write(0x43);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADD, 6, true);
  gy_x = Wire.read() << 8 | Wire.read();
  gy_y = Wire.read() << 8 | Wire.read();
  gy_z = Wire.read() << 8 | Wire.read();
}

void curang() {
  deg_x = atan2(ac_x, ac_z) * 180 / PI;
  deg_y = atan2(ac_y, ac_z) * 180 / PI;
  dgy_x = gy_x / 131. ;
  dgy_y = gy_y / 131. ;
  current_angle_x = (0.95 * (current_angle_x + (dgy_x * 0.001))) + (0.05 * deg_x);
  current_angle_y = (0.95 * (current_angle_y + (dgy_y * 0.001))) + (0.05 * deg_y);
}

void MPUreceive() {
  int a = 0;
  while (a++ < 160) {
    getaccdata();
    getgyrdata();

    curang();
    Serial.println(current_angle_y);
  }
}

void resetaltitude() {
  MPUreceive();
  if (current_angle_y > 0)
    turnStepper1(current_angle_y, 1);
  else if (current_angle_y < 0)
    turnStepper1(-current_angle_y, -1);
}

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADD);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);

  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  resetaltitude();
  Serial.println("What day it is of the year???, what time is it???");
  while (1) {
    if (Serial.available()) {
      localDay = Serial.parseInt();
      if (localDay >= 1 && localDay <= 366)
        break;
      Serial.println("Invalid INPUT DATE !!!!");
    }
  }
  while (1) {
    if (Serial.available()) {
      localTime = Serial.parseInt();
      if (localTime >= 1 && localTime <= 24)
        break;
      Serial.println("Invalid Input Time !!!!");
    }
  }
}

void loop() {
  inputstarNo();
  calc(starNo);
  Serial.println(altitude);
  Serial.println(Azimuth);
  if (Azimuth < 0)
    Azimuth += 360;
  if (altitude < 0) {
    Serial.println("The star isn't here now, it's below horizon as of now. Check for some other time or some other star ..... ");
  } else {
    turnStepper1(altitude, 1);
    turnStepper2(Azimuth, 1);
    delay(10000);
    turnStepper1(altitude, -1);
    turnStepper2(Azimuth, -1);
  }
}
