#include <Servo.h>
#include <SoftwareSerial.h>
#include <Key.h>
#include <Keypad.h>
#include <SPI.h>
#include <gfxfont.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_PCD8544.h>
#define PASSWORD_LENGTH 5


                         //Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(38,36,34,30,32);
//SoftwareSerial s(6,7);

int flag1=1, lockPin=6, pos;
char pass[4];
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns/ 
int count=0;
bool door=true;
char enteredPass[PASSWORD_LENGTH], actualPass[PASSWORD_LENGTH]="1234";
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {13,12,11,10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Servo locker;
void setup()   {
  Serial.begin(9600);
  locker.attach(8);
  closeLock();
 // s.begin(9600);
  pinMode(lockPin,OUTPUT);
  
  display.begin();
  display.setContrast(57);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  
}

void loop() {

  if(door==0){
    char key = keypad.getKey();   //read the pressed key


    //lock the door when '#' is pressed
    if(key=='#'){
      display.clearDisplay();
      closeLock();
      display.println("The door is locked");
      display.display();
      digitalWrite(lockPin,HIGH);  //send message to NodeMCU saying the door has been locked
      delay(3500);
      door=1;
      flag1=1;
      display.clearDisplay();
    }
  }
  else doorOpen();
}
void doorOpen(){
  //check if door is locked, if locked ask for password
  if(flag1==1)
  {
    display.setCursor(0,0);
    display.println("Enter password");
    digitalWrite(lockPin,HIGH);
    display.display();
    flag1=0;
  }
 
  char key = keypad.getKey();
  if(key && key != '*'){
     enteredPass[count++]=key;
     display.print(key);
     display.display();
     
  }
  char enter=keypad.getKey();
  if(enter =='*'){
    if (!strcmp(enteredPass, actualPass)) 
    {
      display.clearDisplay();
      openLock();
      display.println("Door is Open");
      display.display();
      digitalWrite(lockPin,LOW);
      door = 0;
    }
    else
    {
      display.clearDisplay();
      display.println("Wrong Password");
      display.display();
      delay(1000);
      door = 1;
      flag1=1;
      digitalWrite(lockPin,LOW);
      display.clearDisplay();
    }
    clearPass();
  }
}
void clearPass(){
  while(count!=0){
    enteredPass[count--]=0;
  }
}
void openLock(){
  for (pos = 90; pos >= 0; pos -= 5) { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    locker.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 5ms for the servo to reach the position
  }
}
void closeLock(){
  for (pos = 0; pos <= 90; pos += 5) { // goes from 90 degrees to 0 degrees
    locker.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);   
}
}
