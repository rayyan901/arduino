/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {10, 11, 12, 13}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4,5,6,7}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int var1;
//===
int pump = 9;      // LED connected to digital pin 9
int inp1 = 2;
int inp2 = 3;
//int i;
//int analogPin = 3;   // potentiometer connected to analog pin 3
int val = 150; 
int flag2;
//====


void setup(){
  Serial.begin(9600);
  Serial.println();
  //===
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
lcd.backlight();//To Power ON the back light
//lcd.noBacklight();// To Power OFF the back light
//===
pinMode(pump, OUTPUT);  // sets the pin as output
  pinMode(inp1, OUTPUT);
  pinMode(inp2, OUTPUT);
  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
//==

  
}
  int i=0;
  int var2=0,len,masa;
  char key;
  int num[5];
  bool maxNum=0;
void loop(){
start:;
lcd.clear();//Clean the screen

lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print("enter time:"); //You can write 16 Characters per line .
Serial.print("enter time in milisecond and press A: ");
i=0;
key=0;
  while(key!='A'){
 do{
  key = keypad.getKey();
  
 }while(key==NO_KEY);

  
 // if (key){
 //     var2=key;
    
    
    if(key<48||key>57){
     // Serial.println("not number");
    goto notnum;
    }
    lcd.print(key);
    Serial.print(key);
    num[i]=key-0x30;
    i++;
    len=i;
//    for(i=0;i<(key-0x30+1);i++){
//      Serial.print(i);
    notnum:; 
    if(key=='D'){
     Serial.println();
    goto start;
    } 
    }
    var2=0;
    Serial.println();
    for(i=0;i<len;i++){
     Serial.print("num[");
      Serial.print(i);
      Serial.print("]= "); 
     Serial.println(num[i]); 
   
    }
    
     Serial.print("length: ");
     Serial.println(len);
//========
if(len<5){
int var4=len-1;
if(var4==0){
  masa=num[var4];
}
if(var4==1){
  masa=num[var4]+num[var4-1]*10;
}
if(var4==2){
  masa=num[var4]+num[var4-1]*10+num[var4-2]*100;
}
if(var4==3){
  masa=num[var4]+num[var4-1]*10+num[var4-2]*100+num[var4-3]*1000;
}
 Serial.print("masa= ");
     Serial.println(masa);
     maxNum=0;
} else{
  maxNum=1;
  Serial.println(" max 4 digit only ");
}
//=========
  
    Serial.println(" loop done");

if(maxNum==0){


do{
lcd.clear();//Clean the screen
lcd.setCursor(0,0); 
lcd.print("time:");
 lcd.print(masa);
  lcd.setCursor(0,1); 
 lcd.print("<, > or reset?");

 
Serial.println(" left, right or reset? :");
do{
  key = keypad.getKey();
  
  delay(1);
 }while(key==NO_KEY);
 lcd.print(key);
Serial.println(key);
 if(key=='*'){
  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
  flag2=0;
 }else  if(key=='#'){
  digitalWrite(inp1, LOW);
  digitalWrite(inp2, HIGH);
  flag2=0;
 }else{
  digitalWrite(inp1, LOW);
  digitalWrite(inp2, LOW);
  flag2=1;
 }
 if(flag2==0){
analogWrite(pump, val);

Serial.println(masa);  
  delay(masa);
  
analogWrite(pump, 0);
 }
}while(key!='D');

 
//=======
delay(50);
  
}

    

  
}
