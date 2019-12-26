
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
#include <Stepper.h>

//==
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6,7,8,9};//{10, 11, 12, 13}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2,3,4,5}; //{4,5,6,7}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//int var1;
//====
int knownSpeed=20;
int knownSteps=20;
char key;
boolean err=0;

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 10,11,12,13);

int i,incomingByte = 0,num=0;
String data;
char d[10];
//=======
void kypreadstring()
{
 
 //char *b;  
 int i=0;
  while(key!='#'&& i<7){
 do{
  key = keypad.getKey();
  
 }while(key==NO_KEY);
 Serial.print(key);
 if(key!='#'){
 lcd.print(key);
 }
 d[i]=key;
 i++;
  }
  Serial.println();
  i=i-1;
  
  key=0;
  d[i]='\0';
//b=&d[0];
    
    }


//============
void setup() {
  // set the speed at 60 rpm:
  
  myStepper.setSpeed(20);
  Serial.begin(9600);

  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
lcd.backlight();//To Power ON the back light
//lcd.noBacklight();// To Power OFF the back light

  lcd.clear();//Clean the screen

lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print("Peristaltic");
lcd.setCursor(0,1); //Defining positon to write from first row,first column .
lcd.print("Pump");
delay(2000);

}

void loop() {
  start:

 
int dataKyp;
String kyp2;


  
while(1){
  lcd.clear();//Clean the screen

lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print("Speed?:"); //You can write 16 Characters per line 
  Serial.println("enter speed: ");

kypreadstring();
kyp2=d;  
dataKyp=kyp2.toInt();
//while(Serial.available()==0);
//data=Serial.readString();
 //num=data.toInt();
 num=dataKyp;
if(num>0&&num<121){
  myStepper.setSpeed(num);
  Serial.print("speed: ");
  Serial.println(num,DEC);
  knownSpeed=num;
}else{
err=1;  
myStepper.setSpeed(knownSpeed);
}
Serial.println("enter steps: ");
lcd.setCursor(0,1);
lcd.print("Steps?:");
//while(Serial.available()==0);
//data=Serial.readString();

kypreadstring();
kyp2=d;  
dataKyp=kyp2.toInt();

 Serial.print("steps: ");
    Serial.println(dataKyp);
//   num=data.toInt();
    num=dataKyp;
    if((num>0&&num<10001)&& err==0 ){
    knownSteps=num; 
Serial.println("clockwise");
Serial.print("speed: ");
Serial.println(knownSpeed);
Serial.print("steps: ");
Serial.println(knownSteps);
//==============init stepper
myStepper.step(-1);
myStepper.step(1);
delay(100);
//==============
  for(i=0;i<num;i++){
  myStepper.step(1);  
  }
    myStepper.step(0);  
////==
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
//==    
    }else{
      Serial.println("invalid, press '*'");
      lcd.clear();//Clean the screen
      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print("invalid input!");
      lcd.setCursor(0,1);
      lcd.print("press '*'");
      err=1;
      //delay(2000);
    }
//======
if(err==0){
lcd.clear();//Clean the screen
lcd.setCursor(0,0);
lcd.print("#-> turn again");
lcd.setCursor(0,1);
lcd.print("*-> reset");
}
//===
do{
do{
  key = keypad.getKey();
  
 }while(key==NO_KEY);
 Serial.print(key);
 //lcd.print(key);
 if(key=='#'&& err==0){
    Serial.println("clockwise");
Serial.print("speed: ");
Serial.println(knownSpeed);
Serial.print("steps: ");
Serial.println(knownSteps);
myStepper.setSpeed(knownSpeed);

//==============init stepper
myStepper.step(-1);
myStepper.step(1);
delay(100);
//==============

  for(i=0;i<knownSteps;i++){
  myStepper.step(1);  
  }
  myStepper.step(0);  

  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
 }

 
}while(key!='*');
err=0;
//=====    
} 
//goto start;
//=======================================================================  
  // step one revolution  in one direction:
//  Serial.println("clockwise");
//  myStepper.step(stepsPerRevolution);
// // delay(500);
//
//goto start;
//    
//  // step one revolution in the other direction:
//  Serial.println("counterclockwise");
//  myStepper.step(-stepsPerRevolution);
//  delay(500);
  //======================================================
  
}
//==================
