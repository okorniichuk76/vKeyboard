#ifndef vKeyboard_h
#define vKeyboard_h
#include <Arduino.h>
//-----------------------------------
// код кнопок при короткому натисканні
#define vBut_NONE 0
#define vBut_ESC 1
#define vBut_LEFT 2
#define vBut_UP 3
#define vBut_DOWN 4
#define vBut_RIGHT 5
#define vBut_OK 6
//-----------------------------------
// код кнопок при довгому натисканні
#define vBut_LONG_ESC 21
#define vBut_LONG_LEFT 22
#define vBut_LONG_UP 23
#define vBut_LONG_DOWN 24
#define vBut_LONG_RIGHT 25
#define vBut_LONG_OK 26
//-----------------------------------
class vKeyboard {
  public :
    uint8_t read() {
      int Result = vBut_NONE;
      reading  = readKey();
      if (reading  != vBut_NONE && lastReading == vBut_NONE) {
        onTime = millis();
        key = reading;
      }
      if (reading  != vBut_NONE && lastReading != vBut_NONE) {
        if ((millis() - onTime) >holdTime) {
          hold = true;
        }
      }
      if (reading  == vBut_NONE && lastReading != vBut_NONE) {
        if (((millis() - onTime) > rattleDelays) && !hold) {
          lastSwitchTime = millis();
          single = true;
        }
      }
      if (hold) {
        // довге натискання
        hold = false;
        single = false;
        Result = key + 10;
        key = 0;
      }
      if (single && (millis() - lastSwitchTime)) {
        // одиночне натискання
        single = false;
        Result = key;
        key = 0;
      }
	  if (Result == 10 ) Result = vBut_NONE;
      lastReading = reading ;
      return Result;
    }
	uint8_t rattleDelays = 10; // затримка для придушення брязкоту 
	int holdTime = 500;  // час визначення довгого натискання
	uint8_t port = A0;
  private:
    int8_t readKey() {
      int val;
      val = analogRead(port);
      if (val > 900) return vBut_NONE;
      else if (val < 300) return vBut_ESC;
      else if (val < 450) return vBut_LEFT;
      else if (val < 620) return vBut_UP;
      else if (val < 720) return vBut_DOWN;
      else if (val < 780) return vBut_RIGHT;
      else if (val < 820) return vBut_OK;
	  // Serial.println("val = "+String(val));
}
  uint8_t lastReading ;
  bool single = false;
  bool hold = false;
  unsigned long onTime = 0;
  unsigned long lastSwitchTime = 0;
  uint8_t reading ;
  uint8_t key;
};
#endif
