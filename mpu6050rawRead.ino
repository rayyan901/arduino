/*  
 *  How I2C Communication Protocol Works - Arduino I2C Tutorial
 *  
 *   by Dejan, www.HowToMechatronics.com 
 *   
 */

#include <Wire.h>

int mpuAddress = 0x68; // Device address in which is also included the 8th bit for selecting the mode, read in this case.

float temp, accX, accY, accZ; //, gyroX, gyroY, gyroZ;


//=====

#define MPU6050_ADDR         0x68
#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1a
#define MPU6050_GYRO_CONFIG  0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_WHO_AM_I     0x75
#define MPU6050_PWR_MGMT_1   0x6b
#define MPU6050_TEMP_H       0x41
#define MPU6050_TEMP_L       0x42

#define GYRO_LSB_2_DEGSEC  65.5     // [bit/(°/s)]
#define ACC_LSB_2_G        16384.0  // [bit/gravity]
#define RAD_2_DEG          57.29578 // [°/rad]
#define GYRO_OFFSET_NB_MES 3000     //
#define TEMP_LSB_2_DEGREE  340.0    // [bit/celsius]
#define TEMP_LSB_OFFSET    12412.0  //

#define DEFAULT_GYRO_COEFF 0.98
//====
int X0,X1,X_out;

void setup() {
  Wire.begin(); // Initiate the Wire library
  Serial.begin(9600);
  delay(100);
  Serial.println(F("Iniatialising  MPU6050"));
  MPU6050_begin();
  // Enable measurement
  //Wire.beginTransmission(mpuAddress);
 // Wire.write(Power_Register);
  // Bit D3 High for measuring enable (0000 1000)
  //Wire.write(8);  
  //Wire.endTransmission();
   Serial.println("Done!\n");
}

void loop() {

MPU6050_update();
Serial.println(accX);
Serial.println(accY);
Serial.println(accZ);  
//  Serial.print("X0= ");
//  Serial.print(X0);
//  Serial.print("   X1= ");
//  Serial.println(X1);
delay(1000);
}

//====================================================
void writeMPU6050(byte reg, byte data){
  Wire.beginTransmission(mpuAddress);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

void MPU6050_begin(){
  writeMPU6050(MPU6050_SMPLRT_DIV, 0x00);
  writeMPU6050(MPU6050_CONFIG, 0x00);
  writeMPU6050(MPU6050_GYRO_CONFIG, 0x08);
  writeMPU6050(MPU6050_ACCEL_CONFIG, 0x00);
  writeMPU6050(MPU6050_PWR_MGMT_1, 0x01);
}

void MPU6050_update(){
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom((int)MPU6050_ADDR, 14);

  int16_t rawData[7]; // [ax,ay,az,temp,gx,gy,gz]

  for(int i=0;i<7;i++){
  rawData[i]  = Wire.read() << 8;
    rawData[i] |= Wire.read();
  }

  accX = ((float)rawData[0]) / ACC_LSB_2_G;
  accY = ((float)rawData[1]) / ACC_LSB_2_G;
  accZ = ((float)rawData[2]) / ACC_LSB_2_G;
  temp = (rawData[3] + TEMP_LSB_OFFSET) / TEMP_LSB_2_DEGREE;
//  gyroX = ((float)rawData[4]) / GYRO_LSB_2_DEGSEC - gyroXoffset;
//  gyroY = ((float)rawData[5]) / GYRO_LSB_2_DEGSEC - gyroYoffset;
//  gyroZ = ((float)rawData[6]) / GYRO_LSB_2_DEGSEC - gyroZoffset;
//  
//  float sgZ = (accZ>=0)-(accZ<0);
//  angleAccX = atan2(accY, sgZ*sqrt(accZ*accZ + accX*accX)) * RAD_2_DEG;
//  angleAccY = - atan2(accX, sqrt(accZ*accZ + accY*accY)) * RAD_2_DEG;
//
//  unsigned long Tnew = millis();
//  float dt = (Tnew - preInterval) * 1e-3;
//  preInterval = Tnew;
//
//  angleX = (gyroCoef * (angleX + gyroX*dt)) + (accCoef * angleAccX);
//  angleY = (gyroCoef * (angleY + gyroY*dt)) + (accCoef * angleAccY);
//  angleZ += gyroZ*dt;

}
