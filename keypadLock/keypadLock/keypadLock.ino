#include <Servo.h>
#include <Keypad.h>

Servo myservo;
String password="0000";
String typedPassword="";

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = { 6, 5, 4, 3 };
byte colPins[COLS] = { 2, 8, 9,7 };

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  
  Serial.begin(9600);
  delay(200);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  myservo.attach(13);
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
    case '*': //Serial.print(password);
              checkPassword(); 
              delay(1);
              typedPassword="";
              break;
    
    case '#': password=typedPassword;
              delay(1);
              typedPassword=""; 
              break;
    
     default: typedPassword += ekey; delay(1);
}
}
}

void checkPassword(){
  
if (strcmp(password,typedPassword)){  //if password is right open
    
    Serial.println("Accepted");
    
    delay(10);
    
    myservo.write(150); //deg
    
    digitalWrite(11, HIGH);
    delay(9000); 
    digitalWrite(11, LOW);
    myservo.write(0);
    
    
}else{
    Serial.println("Denied"); //if passwords wrong keep locked
    //Serial.write(254);
    delay(10);
    password=
    //add code to run if it did not work
    myservo.write(0);
    digitalWrite(12, HIGH);
    delay(3000); 
    digitalWrite(12, LOW);
    
}


}



