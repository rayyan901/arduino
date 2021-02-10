#include <BMI160Gen.h>

const int select_pin = 10;
const int i2c_addr = 0x68;
#define ACC_LSB_2_G        16384.0  // [bit/gravity]
#define RAD_2_DEG          57.29578 // [°/rad]
float temp, accX, accY, accZ;
float angleX,angleY;
void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
 // BMI160.begin(BMI160GenClass::SPI_MODE, select_pin);
  BMI160.begin(BMI160GenClass::I2C_MODE, i2c_addr);
}

void loop() {
  int gx, gy, gz;         // raw gyro values
  int ax,ay,az;
  // read raw gyro measurements from device
  BMI160.readGyro(gx, gy, gz);
  BMI160.readAccelerometer(ax,ay,az);

  accX = ((float)ax) / ACC_LSB_2_G;
  accY = ((float)ay) / ACC_LSB_2_G;
  accZ = ((float)az) / ACC_LSB_2_G;

  angleX = asin(accX) * RAD_2_DEG;
  angleY = asin(accY) * RAD_2_DEG;
  //accZ = ((float)rawData[2]) / ACC_LSB_2_G;
  // display tab-separated gyro x/y/z values
//  Serial.print("g:\t");
//  Serial.print(gx);
//  Serial.print("\t");
//  Serial.print(gy);
//  Serial.print("\t");
//  Serial.print(gz);
//  Serial.println();

 // Serial.print("a:\t");
  //Serial.print(ax);
  Serial.print(angleX);
  Serial.print("\t");
  //Serial.print(ay);
  //Serial.print(accY);
  Serial.print(angleY);
  Serial.print("\t");
//  Serial.print(az);
//Serial.print(accZ);
  Serial.println();

  delay(100);
}
