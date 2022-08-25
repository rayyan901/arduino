void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("initilaised...");

}
typedef union
{
  float number;
  uint8_t bytes[4];
} floatUnion;



 


void loop() {
  // put your main code here, to run repeatedly:

  floatUnion myFloat;
myFloat.number = -123.456; // Assign a number to the float
for (int i=0; i<4; i++)
{
  Serial.print(myFloat.bytes[i], HEX); // Print the hex representation of the float
  Serial.print(' ');
}
Serial.println();


byte buf[4];
buf[0]=myFloat.bytes[0];
buf[1]=myFloat.bytes[1];
buf[2]=myFloat.bytes[2];
buf[3]=myFloat.bytes[3];

float newfloat=bytesToFloat(buf,0);
Serial.println(newfloat);

while(1);
}

float bytesToFloat(uint8_t *bytes, bool big_endian) {
    float f;
    uint8_t *f_ptr = (uint8_t *) &f;
    if (big_endian) {
        f_ptr[3] = bytes[0];
        f_ptr[2] = bytes[1];
        f_ptr[1] = bytes[2];
        f_ptr[0] = bytes[3];
    } else {
        f_ptr[3] = bytes[3];
        f_ptr[2] = bytes[2];
        f_ptr[1] = bytes[1];
        f_ptr[0] = bytes[0];
    }
    return f;
}
