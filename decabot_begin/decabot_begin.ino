/*
 *  Decabot 0.01
 *  
 *  Codes for creation of basic Decabot Lib with step motors
 *  
 *  Daniel Chagas
 *  
 */

class Decabot {
  private:
    //private vars
      int latchPin = 8;   //Pin connected to ST_CP of 74HC595
      int clockPin = 7;   //Pin connected to SH_CP of 74HC595
      int dataPin = 6;    //Pin connected to DS of 74HC595
      int buzzerPin = 3;  //Pin connected to buzzer
      int ledPin = 2;     //Pin connected to frontal LED
  public:
    //constructor
    Decabot(int nothing) {
      //define pin modes for shift register, buzzer and LED
      pinMode(buzzerPin, OUTPUT);
      pinMode(ledPin, OUTPUT);
      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
    }

    void resetMotor() {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, B00000000); //Send all off to 74HC595
      digitalWrite(latchPin, HIGH);
    }

    void soundBegin() {
      digitalWrite(ledPin, HIGH);
      for(int i=400;i<1000;i++){
        tone(buzzerPin, i, 3);
        delay(3);
      }
      noTone(buzzerPin);
      delay(50);
      this->beep(50);
      delay(50);
      this->beep(50);
      digitalWrite(ledPin, LOW);
    }

    void beep(int time){
      tone(buzzerPin, 1000, 50);
      delay(time);
      noTone(buzzerPin);
      delay(time);
    }

    void boot(){
      //Boot sequence
      this->soundBegin();
    }
    
};

Decabot robot(1); //create object Decabot

void setup() {
  robot.boot();
}

void loop() {
  delay(1000);
}
