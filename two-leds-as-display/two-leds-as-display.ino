unsigned long time1;
unsigned long previousTime;
bool enterFunction = true;
unsigned long time2;
unsigned long previousTime2;
bool enterFunction2 = true;
bool blinkingtens= false;
bool enteredtens= false;
int doubletens= 0;
bool blinkingunits = false;
bool enteredunit = false;
int doubleunit = 0;
int unit = 0;
int tens = 0;
bool waittime = true;
bool startedwait = false;
long elapsedtime;
int analoginput;

int digituponentering = 1;


void setup() {
  
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {

  time1 = micros();
  time2 = micros();
  if (enterFunction == true) {
    previousTime = time1;
    
    // Start your code below
    //-----------------------

    if(blinkingtens == true && blinkingunits == false){
      digitalWrite(7, LOW);
      if(enteredtens == false){
        enteredtens = true;
        doubletens = 2 * tens;
        if(doubletens == 0){
          doubletens= 1;
        }
      }
      doubletens --;
      if(doubletens != 0){
        digitalWrite(6, !digitalRead(6));
      }else{
        blinkingunits = true;
        blinkingtens = false;
      }

    }else if(blinkingunits == true && blinkingtens == false){
      digitalWrite(6, LOW);
      blinkingtens= false;
      if(enteredunit == false){
        enteredunit = true;
        doubleunit = 2 * unit;
        if(doubleunit == 0){
          doubleunit= 1;
        }
      }
      doubleunit --;
      if(doubleunit != 0){
        digitalWrite(7, !digitalRead(7));
      }else{
        waittime = true;
        blinkingunits = false;
        startedwait = true;
      }

    }else if(waittime == true){
      if(startedwait == true){
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
        startedwait = false;
        elapsedtime = millis();
      }
      if(millis() - elapsedtime > 698){
        waittime = false;
      }

    }else{
      blinkingtens= true;
      enteredtens = false;
      enteredunit = false;
    }  
    
    //-----------------------
    // End of your code
  }

  if (enterFunction2 == true && waittime == true) { //Enter this function every xx milisseconds and IF LEDs are not blinking
    previousTime2 = time2;

    // Le o sensor algumas vezes
    analoginput= map(analogRead(A1), 0, 1023, 0, 99);
    Serial.println(analoginput);
    
    if(analoginput < 10){
      tens= 0;
      unit= analoginput;
    }else if(analoginput >= 10 && analoginput < 20){
       tens= 1;
       unit= analoginput - 10;
    }else if(analoginput >= 20 && analoginput < 30){
      tens= 2;
      unit= analoginput - 20;
    }else if(analoginput >= 30 && analoginput < 40){
      tens= 3;
      unit= analoginput - 30;
    }else if(analoginput >= 40 && analoginput < 50){
      tens= 4;
      unit= analoginput - 40;
    }else if(analoginput >= 50 && analoginput < 60){
      tens= 5;
      unit= analoginput - 50;
    }else if(analoginput >= 60 && analoginput < 70){
      tens= 6;
      unit= analoginput - 60;
    }else if(analoginput >= 70 && analoginput < 80){
      tens= 7;
      unit= analoginput - 70;
    }else if(analoginput >= 80 && analoginput < 90){
      tens= 8;
      unit= analoginput - 80;
    }else if(analoginput >= 90 && analoginput < 100){
      tens= 9;
      unit= analoginput - 90;
    }else{
      tens= 0;
      unit= 0;
    }
  }


  // The DELAY time is adjusted in the constant below >>
  if (time1 - previousTime < 299990) { // 1 million microsencods= 1 second delay
    /* I have actually used 0.999990 seconds, in a trial to compensate the time that
       this IF function takes to be executed. this is really a point that
       need improvement in my code */
    enterFunction = false;
  }
  else {
    enterFunction = true;
  }
  if (time2 - previousTime2 < 49990) { // 1 million microsencods= 1 second delay
    /* I have actually used 0.999990 seconds, in a trial to compensate the time that
       this IF function takes to be executed. this is really a point that
       need improvement in my code */
    enterFunction2 = false;
  }
  else {
    enterFunction2 = true;
  }

}