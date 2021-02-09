byte  startButton = 8;
bool startup =true;
int segmentPins[]= {5,4,3,2};
int displayPins[]= {10,11};  // V1 1,0  V2 10,11
byte digits[10][4]= {
  {0,0,0,0},  //0
  {0,0,0,1},  //1
  {0,0,1,0},  //2
  {0,0,1,1},  //3
  {0,1,0,0},  //4
  {0,1,0,1},  //5
  {0,1,1,0},  //6
  {0,1,1,1},  //7
  {1,0,0,0},  //8
  {1,0,0,1,}  //9
  
};

int intValue[] = {0,0};
int startTime;
byte numDisplay =sizeof(intValue)-1;  // Calulate the number of displays by the number of values to be shown.
byte currentDisplay =1; //Current display to be driven
byte lastDisplay=0; //Value for the last display digit
byte counter=0;   //Counter to slow the swapping of displays
unsigned int  displayDelay = 65535;    //delay used to control the timer interupt. 
unsigned int delayTime = 100; //delayTime to set OCRA0

#define TIMER1_INTERRUPTS_ON    TIMSK1 |=  (1 << OCIE1A);
#define TIMER1_INTERRUPTS_OFF   TIMSK1 &= ~(1 << OCIE1A);

void setup() {

  noInterrupts();  //disable interupt during setup.
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 1000;                             
  TCCR1B |= (1 << WGM12);
  TCCR1B |= ((1 << CS11) | (1 << CS10));
  interrupts();

   // Setup the pins.   

  pinMode(startButton, INPUT_PULLUP);   //Setup the startButton 
  for (int i=0; i<4; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i=0; i<sizeof(displayPins)-1; i++){
    pinMode(displayPins[i], OUTPUT);
    }
    TIMER1_INTERRUPTS_ON
  }

// ------------------------------------------------------------------------

    // Interrupt is called once a millisecond, to update the LEDs
    // Sweeper2 s not updated if the button on digital 2 is pressed.
  ISR(TIMER1_COMPA_vect)
    {
     // setSegments(intValue[counter], counter);
      counter++;
      if (counter>=4){
        counter=0;
      }
      
      if (counter<2){  //0~50 display 0
        currentDisplay=0;
      }
      if (counter>=2){
        currentDisplay=1;
      }
      
     setSegments(intValue[currentDisplay],currentDisplay);
     //   lastDisplay=currentDisplay;
     //   currentDisplay++;
     //   if (currentDisplay>=numDisplay) {
     //     currentDisplay=0;
        }
     /* }
      counter++;
      if (counter>5){
        counter=0;
      }
      
    } 

 */
// ------------------------------------------------------------------------

void loop() {
    
//  delayTime = map(analogRead(0),0,1024, 0, 512);  //Read pot for timer
//  OCR1A = delayTime;
if (startup){
  start_sequ();
  startup=false;
}
/*
  if (!digitalRead(startButton)){
    intValue[0] = random(1,7);
    intValue[1] = random(1,7);
  }
  delay(50);
  */
}


void start_sequ(){
 for (byte i = 0; i<100; i++){
  intValue[1]=i/10;
  intValue[0]=i%10; 
  delay(60); 
  }
 for (byte i = 99; i>0; i--){
  intValue[1]=i/10;
  intValue[0]=i%10; 
  delay(30); 
  }  
  intValue[1]=0;
  intValue[0]=0;
}

void setSegments(int n1, byte displayNo){
      for (int n=0; n<numDisplay; n++){
        digitalWrite(displayPins[n], HIGH);    //Turn off all display pins
      }
      
        /* if (i != displayNo){  
                  }
        else {
          digitalWrite(displayPins[i],HIGH);
        }
        
        */
        digitalWrite(displayPins[displayNo],LOW); //Turn on current display
 

  
  for (int i=0; i<4; i++){
    digitalWrite(segmentPins[i], digits[n1][i]);
  }
  
    
}
