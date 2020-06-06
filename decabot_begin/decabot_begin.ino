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
      #include <EEPROM.h>
      char decabotName[5] = "A01  ";
      char decabotOwner[50] = "anybody@decabot.com";
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

    void recordingSound() {
      //sound played everytime something is recorded in EEPROM
      for(int x=0;x<3;x++){
        this->beep(50);
        delay(50);
      }
    }

    void boot(){
      //Boot sequence
      this->output(F("Initializing Decabot..."));
      this->resetMotor();
      this->soundBegin();
      this->whoami();
      this->output(F("READY!"));
    }

    void whoami() {
      //OUtputs tag name and owner e-mail of Decabot
      //UniqueIDdump(Serial);
      String tmp1 = F("Decabot Name: ");
      for(int i=896;i<=900;i++){
        tmp1.concat((char) EEPROM.read(i));
        decabotName[i - 896] = EEPROM.read(i);
      }
      this->output(tmp1);
      String tmp2 = F("Owner: ");
      for(int i=901;i<950;i++){
        tmp2.concat((char) EEPROM.read(i));
      }
      this->output(tmp2);
    }

    void yourNameIs(String parameter){
      //change Decabot's tag name on EEPROM
      this->recordingSound();
      parameter.toCharArray(decabotName,6);
      for(int i=0;i<=5;i++){
        EEPROM.write(i + 896,decabotName[i]);
      }
      this->output(F("new name:"));
      this->output(decabotName);
    }

    void yourOwnerIs(String parameter){
      //change decabot emails owner on EEPROM
      this->recordingSound();
      parameter.toCharArray(decabotOwner,50);
      for(int i=0;i<=50;i++){
        EEPROM.write(i + 902,decabotOwner[i]);
      }
      this->output(F("Decabot owner: "));
      this->output(decabotOwner);
    }

    void output(String message){
      //Terminal-like output, with timestamp
      //User must start serial in setup() to work
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
  delay(5000);
  robot.output("ok");
}
