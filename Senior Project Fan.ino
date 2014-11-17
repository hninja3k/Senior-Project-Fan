//#include <i2cmaster.h>
#include <Wire.h>
#include <Servo.h>
//#include <SoftwareSerial.h>

    Servo servoMain;
    int pos = 90;        //start servo in forward position
    //took out enables
    int incomingByte = 0; // for incoming serial data
    byte packet[2];
    byte sValue = 0;
    //int pIndex;
    int pinPIRright1 = 2; //SET EACH PIN FOR THE PIR SENSORS
    int pinPIRright2 = 8;
    int pinPIRleft1 = 4;
    int pinPIRleft2 = 9;
    int pinPIRfront = 12;

void setup()
{
    Serial.flush();
    
    pinMode(pinPIRright1, INPUT);
    pinMode(pinPIRright2, INPUT);
    pinMode(pinPIRleft1, INPUT);
    pinMode(pinPIRleft2, INPUT);
    pinMode(pinPIRfront, INPUT);
    
    digitalWrite(2, LOW);
    digitalWrite(8, LOW);
    digitalWrite(4, LOW);
    digitalWrite(9, LOW);
    digitalWrite(12, LOW);
    
    
    servoMain.attach(10);// attach servo to pin 10
    servoMain.write(pos); // use start position
    
    Serial.begin(9600);  

    delay(5);
   
    Serial.print("m = manual \n");
    Serial.print("h = heat \n");
    Serial.print("o = motion \n");
    Serial.print("a = a to b \n");
    Serial.print("SMART Fan\n");

}
void loop()
{
    if (Serial.available() > 0)
    {
   	 incomingByte = Serial.read();// read the incoming byte:
    }
    switch(incomingByte)
    {
   	 case 'm':
                 {
                  servoMain.write(90); 
                 delay(5);
                 Serial.println("manual\n");
                 delay(5);
                 Serial.flush();
                 //Serial.setTimeout(1000);
                 while(1)
                 {
                 int angle = Serial.parseInt();
                 //delay(15);
                 if(angle > 0){
                 servoMain.write(angle);
                 Serial.println("\n angle is :");
                 Serial.print(angle); 
                 }
                   } 
                 }              
                 /*packet[pIndex++] = Serial.read();
                 
                 if(pIndex >= 2){
                 
                 switch(packet[0]){
			case 's':
				sValue = packet[1];
				break;
                        default:
                                servoMain.write(90);
                                break;
                        }
                 }
   		 servoMain.write(sValue);
                 Serial.println(packet[1]);// 0 - 180
   		 incomingByte='*';
                 pIndex = 0;*/
         	 incomingByte='*';
   	 break;

   	 case 'h':
   		
   		 Serial.println("heat\n");
   		 incomingByte='*';
   	 break;
   	 case 'a':
   		
   		 Serial.println("a to b\n");
   		 incomingByte='*';
   	 break;
   	 
   	 case 'o':
                 Serial.println("motion\n");
      servoMain.write(30);              // tell servo to go to position in variable 'pos' 
      delay(30);  
      servoMain.write(60);              // tell servo to go to position in variable 'pos' 
      delay(30);  
      servoMain.write(30);              // tell servo to go to position in variable 'pos' 
      delay(30);  
      servoMain.write(60);              // tell servo to go to position in variable 'pos' 
      delay(30);  
   		if (digitalRead(pinPIRright1) == HIGH) {
                  pos = 180; 
                  servoMain.write(pos);
                  }else{

                  if (digitalRead(pinPIRright2) == HIGH) {
                  pos = 135; 
                  servoMain.write(pos);
                  }else{

                  if (digitalRead(pinPIRleft1) == HIGH) {
                  pos = 0;
                  servoMain.write(pos);
                  }else{

                  if (digitalRead(pinPIRleft2) == HIGH) {
                  pos = 45;
                  servoMain.write(pos);
                  }else{
    
                  if ((digitalRead(pinPIRright1) == HIGH) && (digitalRead(pinPIRright2) == HIGH)) {
                  pos = 23;
                  servoMain.write(pos);
                  }else{

                  if ((digitalRead(pinPIRleft1) == HIGH) && (digitalRead(pinPIRleft2) == HIGH)) {
                  pos = 157;
                  servoMain.write(pos);
                  }else{

                  if ((digitalRead(pinPIRfront) == HIGH) && (digitalRead(pinPIRright2) == HIGH)) {
                  pos = 113;
                  servoMain.write(pos);
                  }else{

                   if ((digitalRead(pinPIRfront) == HIGH) && (digitalRead(pinPIRleft2) == HIGH)) {
                  pos = 67;
                  servoMain.write(pos);
                  }else{
  
                  if (digitalRead(pinPIRfront) == HIGH) {
                  pos = 90;
                  servoMain.write(pos);
                  }
                  }
                  }
                  }
                  }
                  }
                  }
                  }
                  }
   		 incomingByte='*';     
   	 break;
   	 delay(500);
    }
}

