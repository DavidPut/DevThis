#include <Servo.h>

//Pins
const int buttonPin = 2;  
int ledPin = 13;
int cameraPin = 12;

//Button 
boolean currentState = LOW;
boolean lastState = LOW;
int count = 0;

//Servo
Servo myservo;

//PIR sensor
int pirPin = 3;
int calibrationTime = 30;
boolean startDetection = false;
byte pirLastState=LOW;

int pos;
 
void setup() {
  //Initialize the serial port
  Serial.begin(9600);
  
  //Initialize
  pinMode(buttonPin, INPUT); 
  digitalWrite(buttonPin, HIGH);  
  pinMode(ledPin, OUTPUT);
  pinMode(cameraPin, OUTPUT);
  
  //Servo attach
  myservo.attach(9);
  
  //Default position
  myservo.write(60); 
  
}

void loop(){ 
  //Serial.println(myservo.read());

  currentState = digitalRead(buttonPin);
  if (currentState == HIGH && lastState == LOW){ 
    delay(1);
    
  } else if(currentState == LOW && lastState == HIGH){
    Serial.println("pressed");   
    //Add 1 to count
    count++; 
    
    Serial.println(count);
    
    if (count == 1) {
      Serial.println("Count is 1 // Activate doorlock");
      
      //Start servo function
      
      startServo(); 
      
      //Simulate camera
      startCamera();  
    
      //Set PIR detection on true
      delay(500);
      startDetection = true;     
                        
    } 
    else if (count == 2) {
       Serial.println("Count is 2 // Reset");
       
       //Reset function
       reset();      
    }    
    delay(1);
  }
  lastState = currentState; 
  
  if(startDetection == true){
    startMovementDetection();
  }
  else{
    //Nothing
  }
}

  void startServo(){      
     
      for(pos = 60; pos>=20; pos-=1)// goes from 60 degrees to 20 degrees
      {                                
        myservo.write(pos);              
        delay(15);     
      } 
  }
  
  void startCamera(){        
       //Simulate camera
      digitalWrite(cameraPin,HIGH);
  }
  
  void startMovementDetection(){ 
      
      byte sensor = digitalRead(pirPin);
      if((sensor==HIGH && pirLastState==LOW) || (sensor==LOW && pirLastState==HIGH)) {
        //Movement detected
        alarm();
        pirLastState=sensor;
      } 
       digitalWrite(pirPin,LOW);
  }
  
  void alarm(){
    Serial.println("Alarm!");    
    //Simulate alarm
    digitalWrite(ledPin, HIGH);
            
    tone(8,1000); 
 
  }
  
  void reset(){
      //Reset count
      count = 0;

      for(pos = 20; pos<=60; pos+=1)// goes from 20 degrees to 60 degrees
      {                                
        myservo.write(pos);              
        delay(15);     
      }            
       
      //Reset movement detection
      startDetection = false;
      
      //Reset alarm
      Serial.println("Alarm off"); 
      digitalWrite(ledPin, LOW);  
      noTone(8);     
      
      //Reset camera simulation
      digitalWrite(cameraPin,LOW);
       
  }
  
