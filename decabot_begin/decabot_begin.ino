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
      #define latchPin  8 //Pin connected to ST_CP of 74HC595
      #define clockPin  7 //Pin connected to SH_CP of 74HC595
      #define dataPin   6 //Pin connected to DS of 74HC595
      #define buzzerPin 3 //Pin connected to buzzer
      #define ledPin    2 //Pin connected to frontal LED
  public:
    //constructor
    Decabot(int serialSpeed) {
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
      this->output(F("Reset motors"));
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
      this->output(F("Initializing Decabot..."));
      this->resetMotor();
      this->soundBegin();
      this->output(F("READY!"));
    }

    void output(String message){
      String msg = "";
      msg.concat(String(millis()/1000.0,2));
      msg.concat(F(">"));
      msg.concat(message);
      Serial.println(msg);
    }
    
};

Decabot robot(9600); //create object Decabot

void setup() {
  Serial.begin(9600);
  robot.boot();
}

void loop() {
  delay(1000);
  robot.output("ok");
}
