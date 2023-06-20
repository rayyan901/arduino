void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // Default communication rate of the Bluetooth module
  Serial.println("serial initialised...");
}
char serData;
String btData = ""; 
signed int medVol = 0;
void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available() > 0){ // Checks whether data is comming from the serial port


   
   btData = Serial.readString(); 
   medVol = btData.toInt();
   Serial.print("received: ");
  Serial.println(medVol);
  Serial.print("enter int num: ");
  //} 
//myStepper.setCurrentPosition(0);
//myStepper.moveTo(medVol);
}

//
}
