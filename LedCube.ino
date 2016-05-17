/*
 * UNIVERSITY of WESTERN MACEDONIA
 *        ICTE Department
 * 
 * ARDUINO LED CUBE
 * 
 * -----------Made by-----------------
 * George Kortsaridis
 * email : gkortsaridis@gmail.com
 * web   : gkortsaridis.noip.me
 * 
 * Vicky Fiska
 * email : 
 * web   : 
 * -----------------------------------
 * 
 * --------Supervised by-------------
 * Dasygenis Minas
 * email : mdasyg@ieee.com
 * web   : arch.icte.uowm.gr
 * -----------------------------------
 */

int column[] = {
  30,28,26,24,22,
  31,29,27,25,23,
  41,39,37,35,33,
  44,42,47,45,43,
  40,38,36,34,32
  };
int row[] = {7,5,3,6,4};

int irLed = A0;
int irInput = A1;
int irBackup;

int state = 7;

int testAnimation[] = {0,1,2,3,4,5};

const int anim_frames = 3;
int animation[anim_frames][125] = {{1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial3.begin(9600);  
  
  for(int i=0; i<27; i++){
    pinMode(column[i],OUTPUT);
  }

  for(int i=0; i<5; i++){
    pinMode(row[i],OUTPUT);
  }

  pinMode(irLed, OUTPUT);
  digitalWrite(irLed,HIGH);
  delay(1000);
  irBackup = analogRead(irInput);
  
  
    
}

void loop() {
  // put your main code here, to run repeatedly:

  if(state == 0){
    allOff();
  }else if(state == 1){
    allOn();
  }else if(state == 2){
    ledRun(50);
  }else if(state == 3){
    columnRun(100);
  }else if(state == 4){
    randomParty(25);
  }else if(state == 5){
    reflective();
  }else if(state == 6){
    fromIntArrayToState(testAnimation, 250, 6);
  }else if(state == 7){
    fromIntIntArrayToAnimation(250);
  }
  

}

void led(int which,int what){
  digitalWrite(row[which/25],what);
  digitalWrite(column[which%25],what);
}

void columnRun(int del){
  allOff();
  for(int i=0; i<5; i++){
    digitalWrite(row[i],HIGH);
  }

  for(int i=0; i<25; i++){
    digitalWrite(column[i],HIGH);
    delay(del);
  }
  
}

void ledRun(int del){
  for(int i=0; i<125; i++){
    led(i,HIGH);
    delay(del);
    led(i,LOW);
  }
}

void allOn(){
  for(int i=0; i<25; i++){
    digitalWrite(column[i],HIGH);
  }
  for(int i=0; i<5; i++){
    digitalWrite(row[i],HIGH);
  }
}

void allOff(){
  for(int i=0; i<25; i++){
    digitalWrite(column[i],LOW);
  }
  for(int i=0; i<5; i++){
    digitalWrite(row[i],LOW);
  }
}

void randomParty(int del){
  for(int i=0; i<100; i++){
    int l = random(0,124);
    led(l,HIGH);
    delay(del);
    led(l,LOW);  
  }
}

void serialEvent3(){
  int someInt;
  // send data only when you receive data:
  if (Serial3.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial3.read();
    someInt = incomingByte - '0';

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte);
  }
  state = someInt;
}


void reflective(){
  int val = analogRead(irInput);    // read the input pin
  if(val < irBackup){
    allOn();
  }else{
    allOff();
  }
  Serial.println(val); 
}

void fromIntArrayToState(int intarray[] , int del, int arraySize){
    for(int i=0; i<arraySize; i++){
      if(intarray[i] >= 0 && intarray[i] <= 124){
        led(intarray[i],HIGH);
        delay(del);
      }
    }
    allOff();
}

void fromIntIntArrayToAnimation(int del){
  for(int i=0; i<anim_frames; i++){
    allOff();
    for(int j=0; j<125; j++){
       led(j,animation[i][j]);
       delay(1);
    }
    delay(del);
    
  }
}

