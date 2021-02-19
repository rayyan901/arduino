#include <BMI160Gen.h>

const int select_pin = 10;
const int i2c_addr = 0x68;
#define ACC_LSB_2_G        16384.0  // [bit/gravity]
#define RAD_2_DEG          57.29578 // [°/rad]
float temp, accX, accY, accZ;
float angleX,angleY,avgX,agX=0,avX[10],avX2[10],cax,cax2,cax3,n0;
int i=0,j;
 int ax,ay,az;



//====
float movingAvg(float *ptrArrNumbers, float *ptrSum, int pos, int len, float nextNum)
{
  //Subtract the oldest number from the prev sum, add the new number
  *ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;
  //Assign the nextNum to the position in the array
  ptrArrNumbers[pos] = nextNum;
  //return the average
  return *ptrSum / len;
}


//===

 //int sample[] = {50, 10, 20, 18, 20, 100, 18, 10, 13, 500, 50, 40, 10};
  // the size of this array represents how many numbers will be used
  // to calculate the average
  float arrNumbers[10] = {0};

  int pos = 0;
  float newAvg = 0;
  float sum = 0;
  int len = 10; //sizeof(arrNumbers) / sizeof(int);
 // int count = sizeof(sample) / sizeof(int);

void setup() {
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
 // BMI160.begin(BMI160GenClass::SPI_MODE, select_pin);
  BMI160.begin(BMI160GenClass::I2C_MODE, i2c_addr);
 delay(50);
j=0;
for(i=0;i<10;i++){
BMI160.readAccelerometer(ax,ay,az);
  accX = ((float)ax) / ACC_LSB_2_G;
  accY = ((float)ay) / ACC_LSB_2_G;
  accZ = ((float)az) / ACC_LSB_2_G;

  angleX = asin(accX) * RAD_2_DEG;
  //Serial.println(angleX);
  angleY = asin(accY) * RAD_2_DEG;

  
  avX[i]=angleX;
  avX2[j]=angleX;
  agX=agX+avX[i];
  j++;
  delay(50);
}
  avgX=agX/10;  
  agX=avgX;
  cax=agX;
  n0=avX[0];
//Serial.println(agX);
 i=0; 
}

void loop() {
  int gx, gy, gz;         // raw gyro values
 
  
  // read raw gyro measurements from device
  BMI160.readGyro(gx, gy, gz);
  BMI160.readAccelerometer(ax,ay,az);

  accX = ((float)ax) / ACC_LSB_2_G;
  accY = ((float)ay) / ACC_LSB_2_G;
  accZ = ((float)az) / ACC_LSB_2_G;

  angleX = asin(accX) * RAD_2_DEG;
  angleY = asin(accY) * RAD_2_DEG;

  avX[i]=angleX;
  //==============

 
    newAvg = movingAvg(arrNumbers, &sum, pos, len, angleX);
    
    pos++;
    if (pos >= len){
      pos = 0;
    }
 
//================
for(j=9;j>0;j--){
  avX2[j-1]=avX2[j];
}
avX2[9]=angleX;
cax3=0;
for(j=0;j<10;j++){
  cax3=cax3+avX[j];

}
cax3=cax3/10;
//==============

  cax=(cax+angleX)/2;
 // cax2=
  agX=agX+avX[i];
  i++;
  if(i>9){
   i=0;
   
  avgX=agX/11;  
  agX=avgX;
  }
  
 

 // Serial.print("a:\t");
  //Serial.print(ax);
  Serial.print(angleX);
  Serial.print("\t");
  
  Serial.print(cax3);
  Serial.print("\t");
  
//  Serial.print(cax+1);
//  Serial.print("\t");

  Serial.print(cax3+2);
  Serial.print("\t");
  
//
//    Serial.print(avgX+3);
//  Serial.print("\t");

    Serial.print(newAvg+3);
  Serial.print("\t");

  Serial.println();

  delay(100);
}
