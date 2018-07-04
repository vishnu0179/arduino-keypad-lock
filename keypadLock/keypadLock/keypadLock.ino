

#include <Servo.h>
#include <Keypad.h> // Downlload and install this library before using code http://www.arduino.cc/playground/uploads/Code/Keypad.zip
                     

Servo myservo;
String password="0000";  //DEFAULT PASSWORD
String typedPassword="";

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
{'1','2','3','A'},    // Row1
{'4','5','6','B'},    // Row2
{'7','8','9','C'},    // Row3
{'*','0','#','D'}     // Row4
};

byte rowPins[ROWS] = { 6, 5, 4, 3 };  // Connect Row Pins 1-4 in these Digital Pins
byte colPins[COLS] = { 2, 8, 9,7 };   // Connect Column Pins 1-4 in these Digital Pins

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  
  Serial.begin(9600);
  delay(200);
  pinMode(11, OUTPUT); // Green LED
  pinMode(12, OUTPUT); // Red LED
  myservo.attach(13);  // Servo Motor
  keypad.addEventListener(keypadEvent);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  keypad.getKey();
  myservo.write(0);
}

void keypadEvent(KeypadEvent eKey){
  
  switch (keypad.getState()){
  case PRESSED:
  
  Serial.print("Enter:");
  Serial.println(eKey);
  delay(10);
  
 // Serial.write(254);
  
  switch (eKey){
    case '*': checkPassword(); 
              delay(1);
              typedPassword="";
              break;
    
    case '#': password=typedPassword;
              delay(1);
              typedPassword=""; 
              break;
    
     default: typedPassword += eKey; 
              delay(1);
}
}
}

void checkPassword(){
  
if (password==typedPassword){  //if password is right open
    
    Serial.println("Accepted");
    
    delay(10);
    
    myservo.write(150); //degree of rotation of servo
    
    digitalWrite(11, HIGH);  // Green LED ON
    delay(9000);             // Duration for which the lock is open
    digitalWrite(11, LOW);   // Green LED OFF
    myservo.write(0);        // Auto LOCK
    
    
}else{
    Serial.println("Denied"); //if passwords wrong keep locked
    
    delay(10);
    
    //add code to run if it did not work
    myservo.write(0);
    digitalWrite(12, HIGH);  // RED LED ON
    delay(3000); 
    digitalWrite(12, LOW);    // Red LED OFF
    
}


}



