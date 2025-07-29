#include "mono2025.h"

void start() {
  matrix_reset();
  servo(SERVO_MAX);
}

void loop() {
  static byte bar_gage = 0;
  static byte bar_color = 0;
  static byte pos = SERVO_MAX;
  if (!isToggleEnabled()) {
    dc(S);
    syncPot();
  } else {
    dc(RT);
    stepper();
  }
  if (isTactPressed(RL) && bar_gage > 1) {
    bar_gage--;
    buzz(MI, 0.2);
  } else if (isTactPressed(RR) && bar_gage < 10) {
    bar_gage++;
    buzz(HI, 0.2);
  }
  if (isTactPressed(LL) && bar_color > 1) {
    bar_color--;
    buzz(MI, 0.2);
  } else if (isTactPressed(LR) && bar_color < 8) {
    bar_color++;
    buzz(HI, 0.2);
  }
  bar(lineIndex[bar_gage - 1], ledIndex[bar_color - 1]);
  Serial.println(bar_gage);
  syncArrow();
  if (isTactPressed(TL) && pos < SERVO_MAX) pos++;
  if (isTactPressed(TR) && pos > SERVO_MIN) pos--;
}
