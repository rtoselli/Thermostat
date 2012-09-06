
byte numbers[] = {
//habcdefg  
 B01111110, //0
 B00110000, //1
 B01101101, //2
 B01111001, //3
 B00110011, //4
 B01011011, //5
 B00011111, //6
 B01110000, //7
 B01111111, //8
 B01110011  //9
 
};

//Pino para o ST_CP do 74HC595
//to ST_CP 74HC595
int latchPin = 1;

//Pino para o SH_CP do 74HC595
// to SH_CP 74HC595
int clockPin = 0;

//pino para o DS do 74HC595
//to DS 74HC595

int dataPin = 2;

//pino de leitura do lm35
// TO AOUT lm35
int tempPin = 3;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  animate();
}

void loop() {
  //measure up routine
   int reading = analogRead(tempPin);
   float temperatura =  ( 5 * reading * 100) / 1024 ;
   delay(500);
   
    int uni = ((int)temperatura % 10);
    int dec = temperatura / 10;

  
    shiftMe(numbers[uni]);
    shiftMe(numbers[dec]);
 
} 

void animate()
{
  byte init = B00000001;
  
   for (int i = 0; i<8; i++)
  {
    init = init << 1;
    shiftMe(init);
    shiftMe(init);    
    delay(500);
  } 
  
}

void shiftMe(byte data)
{
      //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, data);  

    //return the latch pin high to signal chip that it
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);

  
}
