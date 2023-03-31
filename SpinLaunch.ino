//Spin Launch MFer. AIAA 2023
//NOTES: DOnt connect arduino through red wire. Signal and ground only.
// Make sure power supply is not going to destroy esc

//include for esc
#include <Servo.h>

//arduino for rpm shit from sensor 1
float REV = 0;
int throttle = 50;
int RPM_VALUE;
int PREVIOUS = 0;
int TIME;
void INTERRUPT() //https://forum.arduino.cc/t/difference-between-attachinterrupt-and-isr/168771/5
{
  REV++;
}

//arduino to control esc
Servo myservo; // create servo object to control a servo


void setup() {
//stuff for ESC
  Serial.begin(115200);
  myservo.attach(9); //PWM Pin Connection // attaches the servo on pin 9 to the servo object

//  myservo.write(180);
//  delay(20*1000);
//  myservo.write(0);//Required to activate ESC. DOnt change. // tell servo to go to position in variable '10 degrees' 0 to 180
//  delay(1000);//needed for the motor
  myservo.write(10);
  delay(500);
  myservo.write(0);

  //STuff for IR sensor
  attachInterrupt(3, INTERRUPT, RISING); //not really sure tbh

  Serial.println("Ready!");
}

void loop() {


//doesnt start till the motor works
  while (!Serial.available()){
    //stuff for ir sensor
    delay(1000);
    detachInterrupt(0);                   
    TIME = millis() - PREVIOUS;    //Returns the number of milliseconds passed since the Arduino board began running the current program. 
    //                                This number will overflow (go back to zero), after approximately 50 days.      
    RPM_VALUE = (REV/TIME) * 60000;   //60,000ms = 1min    
    PREVIOUS = millis();                  
    REV = 0;
    Serial.print("RPM: ");
    Serial.println(RPM_VALUE);
    attachInterrupt(1, INTERRUPT, RISING);
  } //https://www.javatpoint.com/arduino-serial-available
  String value = "";
  while (Serial.available()) {
    int charIn = Serial.read();
    if (isDigit(charIn))
      value += (char) charIn;
  }
  throttle = value.toInt();
  Serial.print("Throttle: ");
  Serial.println(throttle);
//esc shit
//Note:Used for communication between the Arduino board and a computer or other devices. 
//All Arduino boards have at least one serial port (also known as a UART or USART), and some have several.

//    int val = Serial.parseInt(); //reads integer value through serial moniter and Looks for the next valid integer in the incoming serial. The function terminates if it times out
//    Serial.println(val);  //displays read int values or Prints data to the serial port as human-readable
    myservo.write(throttle); //writes read value into esc

    
//-----------------------------------------------------------------------------------------------------------------------

  //    shit for average from rpm. take multiple values and average them
  
  //    switch to cut off voltage from electromagnet
  
}
