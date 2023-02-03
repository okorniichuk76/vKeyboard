
#include <vKeyboard.h>
vKeyboard vKey;
//vBut_NONE   0
//vBut_ESC    1
//vBut_LEFT   2
//vBut_UP     3
//vBut_DOWN   4
//vBut_RIGHT  5
//vBut_OK     6
//-----------------------------------
// код кнопок при довгому натисканні
//vBut_LONG_ESC   11
//vBut_LONG_LEFT  12
//vBut_LONG_UP    13
//vBut_LONG_DOWN  14
//vBut_LONG_RIGHT 15
//vBut_LONG_OK    16
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("OK");
  vKey.port = A0;        // порт зчитування
  vKey.rattleDelays = 10; // затримка для придушення брязкоту
  vKey.holdTime = 500;  // час визначення довгого натискання
  Serial.println("TEST KEYBOARD");
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t k = vKey.read();
  if (k != vBut_NONE) {
    
    if (k==vBut_OK) { 
      Serial.print("KEY = OK");
    }
    
  }
}
