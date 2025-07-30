/*
  Copyright 2025 Syuugo
  
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
      http://www.apache.org/licenses/LICENSE-2.0
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 */

/*
 *  関数の説明
 *
 * ・secs()
 *   経過時間を秒単位で返す。小数第一位まで対応。
 * 
 * ・delaySecs(secs_val)
 *   秒単位で遅延させる。小数第一位まで対応。
 * 
 * ・stepper(reverse)
 *   ステッピングモーター制御関数
 *   3°ずつ動く。
 *   引数なしでは時計回りに動く。
 *   引数の reverse を true にすると、反時計回りに動く。
 *   DC モーターとの両立はできない。
 * 
 * ・dc(action)
 *   DCモーターを制御する。
 *   引数には、RT(Right Turn：右回り)、LT(Left Turn：左回り)、S(Stop：即停止)、F(Free：減速)がある。
 *   引数の文字にダブルクォーテーションは不要。
 *   ステッピングモーターとの両立はできない。
 * 
 * ・buzz(tone_type, duration)
 *   ブザー鳴動関数。
 *   tone_type は周波数で、HI(高音)、MI(中音)、LO(低音)がある。
 *   これらにダブルクォーテーションは不要。
 *   音の長さは２つ目の引数である duration に秒数で入れる。小数第一位まで対応。
 * 
 * ・servo(angle)
 * 　サーボモーター制御関数。
 * 　引数には何度の位置まで移動させるかを入れる。
 * 
 * ・seg(mask)
 *   7セグ制御関数。
 *   以下は引数の例：
 *   番号：num[8]
 *   アルファベット：SEG_A
 *   特定のセグ：(L1 + R2 + C3)
 *   小数点は POINT を使用する。
 * 
 * ・matrix(pattern, duration)
 * 　LEDマトリックス制御関数。
 * 　pattern に次の定数を入れる
 *   MATRIX_[UP, DOWN, LEFT, RIGHT], MATRIX_[LEFT, UP]_[1-8]
 * 　または、int[8] で自作のデザインを作る。
 * 　duration は表示する長さ。規定は 100ms。
 * 
 * ・bar(line, color)
 * 　10色LEDバー制御関数。
 * 　line には、P[1-10] を入れる。
 * 　(P1 | P6) の様に足し算も可能。
 * 　color は、RGBWCYMK を入れる。
 * 
 * ・isPhotoEnabled()
 *   フォトインタラプタが遮断されている間 true を返す。
 * 
 * ・isPhotoPassed(rotation)
 *   羽が引数に指定した回数通過した瞬間 true を返す。
 * 
 * ・isToggleEnabled()
 *   トグルスイッチが上向きの状態なら true を返す。
 * 
 * ・isTogglePulled()
 *   トグルスイッチが上向きになった一瞬のみ true を返す。
 * 
 * ・isTactEnabled(side)
 *   タクトスイッチが押され続けている間は true を返す。
 *   引数は、TL, TR, LL, LR, RL, RR の６つある。
 *   引数の文字にダブルクォーテーションは不要。
 * 
 * ・isTactPressed(side)
 *   タクトスイッチが押された一瞬のみ true を返す。
 *   引数は Enabled 版と同じ。
 * 
 */

#ifndef MONO2025_H
#define MONO2025_H

#include <Servo.h>

/***********
 * 制御ピン *
 ***********/

// ステッピングモーター
const byte STEPPER_MOTOR_1_PIN = 32;
const byte STEPPER_MOTOR_2_PIN = 33;
const byte STEPPER_MOTOR_3_PIN = 34;
const byte STEPPER_MOTOR_4_PIN = 35;
// DCモーター
const byte DC_MOTOR_1_PIN = 30;
const byte DC_MOTOR_2_PIN = 31;
// 10色LEDバー
const byte LED_RED_PIN = 7;
const byte LED_GREEN_PIN = 8;
const byte LED_BLUE_PIN = 9;
const byte LED_BAR_1_PIN = 22;
const byte LED_BAR_2_PIN = 23;
const byte LED_BAR_3_PIN = 24;
const byte LED_BAR_4_PIN = 25;
const byte LED_BAR_5_PIN = 26;
const byte LED_BAR_6_PIN = 2;
const byte LED_BAR_7_PIN = 3;
const byte LED_BAR_8_PIN = 4;
const byte LED_BAR_9_PIN = 5;
const byte LED_BAR_10_PIN = 6;
// ブザー
const byte BUZZER_PIN = 27;
// モード切替
const byte MODE_PIN = 29;
// 7セグ
const byte SEG_MODE_PIN = 28;
const byte SEG_L1_PIN = 32;
const byte SEG_L2_PIN = 33;
const byte SEG_C1_PIN = 37;
const byte SEG_C2_PIN = 31;
const byte SEG_C3_PIN = 34;
const byte SEG_R1_PIN = 36;
const byte SEG_R2_PIN = 35;
const byte SEG_POINT_PIN = 30;
// サーボモーター
const byte SERVO_PIN = 41;
// LED マトリックス
const byte SER_PIN = 38; // シリアル入力
const byte SRCLK_PIN = 39; // シフトクロック
const byte RCLK_PIN = 40; // ラッチクロック

// フォトインタラプタ
const byte PHOTO_INTERRUPTER_PIN = 42;
// 可変抵抗器
const byte POTENTIOMETER_PIN = A15;
// タクトスイッチ
const byte TACT_TEST_LEFT_PIN = 44;
const byte TACT_TEST_RIGHT_PIN = 45;
const byte TACT_LEFT_LEFT_PIN = 48;
const byte TACT_LEFT_RIGHT_PIN = 49;
const byte TACT_RIGHT_LEFT_PIN = 50;
const byte TACT_RIGHT_RIGHT_PIN = 51;
// トグルスイッチ
const byte TOGGLE_PIN = 52;
// ジョイスティック
const byte JOYSTICK_X_PIN = A1;
const byte JOYSTICK_Y_PIN = A2;
// 読み込みピン
const byte PIN_READ[] = { PHOTO_INTERRUPTER_PIN, TOGGLE_PIN, TACT_TEST_LEFT_PIN, TACT_TEST_RIGHT_PIN, TACT_LEFT_LEFT_PIN, TACT_LEFT_RIGHT_PIN, TACT_RIGHT_LEFT_PIN, TACT_RIGHT_RIGHT_PIN, POTENTIOMETER_PIN, JOYSTICK_X_PIN, JOYSTICK_Y_PIN };

/***********
 * 補助関数 *
 ***********/

// デジタルピンに書き込み
inline void ren(byte pin, byte level) {
  digitalWrite(pin, level);
}

// 秒数計算
inline float secs() {
  return millis() / 1000.0f;
}

// 秒単位で遅延
void delaySecs(float secs_val) {
  delay((word) (secs_val * 1000.0f));
}

/***************
 * 処理ここから *
 ***************/

/**********************
 * ステッピングモーター *
 **********************/

boolean stepper_started = false;

// ステッピングモーター
void stepper(boolean reverse = false) {
  // 初回実行時にピンモード指定
  if (!stepper_started) {
    pinMode(STEPPER_MOTOR_1_PIN, OUTPUT);
    pinMode(STEPPER_MOTOR_2_PIN, OUTPUT);
    pinMode(STEPPER_MOTOR_3_PIN, OUTPUT);
    pinMode(STEPPER_MOTOR_4_PIN, OUTPUT);
    pinMode(MODE_PIN, OUTPUT);
    stepper_started = true;
  }
  // 書き換え前準備
  ren(MODE_PIN, HIGH);
  // 回数フラグ
  static byte stepper_flag = 0;
  stepper_flag++;

  switch (stepper_flag) {

    case 1:
      ren(STEPPER_MOTOR_1_PIN, HIGH);
      ren(STEPPER_MOTOR_2_PIN, LOW);
      ren(STEPPER_MOTOR_3_PIN, LOW);
      ren(STEPPER_MOTOR_4_PIN, LOW);
      break;

    case 2:
      ren(STEPPER_MOTOR_1_PIN, LOW);
      ren(STEPPER_MOTOR_2_PIN, reverse ? LOW : HIGH);
      ren(STEPPER_MOTOR_3_PIN, LOW);
      ren(STEPPER_MOTOR_4_PIN, reverse ? HIGH : LOW);
      break;

    case 3:
      ren(STEPPER_MOTOR_1_PIN, LOW);
      ren(STEPPER_MOTOR_2_PIN, LOW);
      ren(STEPPER_MOTOR_3_PIN, HIGH);
      ren(STEPPER_MOTOR_4_PIN, LOW);
      break;

    case 4:
      ren(STEPPER_MOTOR_1_PIN, LOW);
      ren(STEPPER_MOTOR_2_PIN, reverse ? HIGH : LOW);
      ren(STEPPER_MOTOR_3_PIN, LOW);
      ren(STEPPER_MOTOR_4_PIN, reverse ? LOW : HIGH);
      stepper_flag = 0;
      break;
  }
  // 書き換え
  ren(MODE_PIN, LOW);
  ren(MODE_PIN, HIGH);
  // セグを消灯
  ren(SEG_MODE_PIN, LOW);
}

/*************
 * DCモーター *
 *************/

boolean dc_started = false;

// DC モーターコントローラー
void dc_ctr(boolean left_ctrl = false, boolean right_ctrl = false) {
  // 初回実行時にピンモード指定
  if (!dc_started) {
    pinMode(DC_MOTOR_1_PIN, OUTPUT);
    pinMode(DC_MOTOR_2_PIN, OUTPUT);
    pinMode(MODE_PIN, OUTPUT);
    dc_started = true;
  }
  // ２ピンを４パターンで制御
  ren(DC_MOTOR_1_PIN, left_ctrl ? HIGH : LOW);
  ren(DC_MOTOR_2_PIN, right_ctrl ? HIGH : LOW);
  // 書き換え
  ren(MODE_PIN, LOW);
  ren(MODE_PIN, HIGH);
  // セグを消灯
  ren(SEG_MODE_PIN, LOW);
}

// DCモーターの動作モードを定義する列挙型
enum DCMotor { LT, RT, S, F };

// DCモーター制御
inline void dc(DCMotor action) {
  switch (action) {
    case LT: dc_ctr(true, false); break;
    case RT: dc_ctr(false, true); break;
    case S: dc_ctr(true, true); break;
    case F: dc_ctr(false, false); break;
  }
}

/**********
 * ブザー *
 **********/

// ブザー鳴動
const uint16_t BEEP_LOW_FREQ = 400;    // 低音の周波数
const uint16_t BEEP_MID_FREQ = 800;    // 中音の周波数
const uint16_t BEEP_HIGH_FREQ = 1200;  // 高音の周波数

// ブザーの音の種類を定義する列挙型
enum BuzzerTone { LO, MI, HI };

// 型と値を同期
const uint16_t BUZZ_FREQ[] = {
  BEEP_LOW_FREQ,  // LO に対応
  BEEP_MID_FREQ,  // MI に対応
  BEEP_HIGH_FREQ  // HI に対応
};

boolean buzzer_started = false;

// ブザー鳴動制御
void buzz(BuzzerTone tone_type, float duration = 0.0f) {
  // 初回実行時にピンモード指定
  if (!buzzer_started) {
    pinMode(BUZZER_PIN, OUTPUT);
    buzzer_started = true;
  }
  if (duration > 0.0f) {
    // 鳴動
    tone(BUZZER_PIN, BUZZ_FREQ[tone_type], (word) (duration * 1000.0f));
  } else {
    // 消音
    noTone(BUZZER_PIN);
  }
}

/*****************
 * サーボモーター *
 *****************/

Servo srv;
const byte SERVO_MIN = 6;
const byte SERVO_MAX = 161;
boolean servo_started = false;
void servo(uint16_t angle) {
  // 初回実行時にセットアップ
  if (!servo_started) {
    srv.attach(SERVO_PIN);
    servo_started = true;
  }
  srv.write(angle);
}

/*********
 * 7セグ *
 *********/

// 7セグ の列挙型
enum Segment { L1 = 0x01, L2 = 0x02, C1 = 0x04, C2 = 0x08, C3 = 0x10, R1 = 0x20, R2 = 0x40, POINT = 0x80 };

// int で直接できるように数字のみの配列を用意
const Segment num[] = {
  /* 0 */ L1 | L2 | C1 | C3 | R1 | R2,
  /* 1 */ R1 | R2,
  /* 2 */ L2 | C1 | C2 | C3 | R1,
  /* 3 */ C1 | C2 | C3 | R1 | R2,
  /* 4 */ L1 | C2 | R1 | R2,
  /* 5 */ L1 | C1 | C2 | C3 | R2,
  /* 6 */ L1 | L2 | C1 | C2 | C3 | R2,
  /* 7 */ L1 | C1 | R1 | R2,
  /* 8 */ L1 | L2 | C1 | C2 | C3 | R1 | R2,
  /* 9 */ L1 | C1 | C2 | C3 | R1 | R2
};

// アルファベット
const Segment SEG_A = L1 | L2 | C1 | C2 | R1 | R2;
const Segment SEG_B = L1 | L2 | C2 | C3 | R2;
const Segment SEG_C = L2 | C2 | C3;
const Segment SEG_D = L2 | C2 | C3 | R1 | R2;
const Segment SEG_E = L1 | L2 | C1 | C2 | C3;
const Segment SEG_F = L1 | L2 | C1 | C2;

boolean seg_started = false;

// セグメント実行
void seg(byte mask) {
  // 初回実行時にピンモード指定
  if (!seg_started) {
    pinMode(SEG_L1_PIN, OUTPUT);
    pinMode(SEG_L2_PIN, OUTPUT);
    pinMode(SEG_C1_PIN, OUTPUT);
    pinMode(SEG_C2_PIN, OUTPUT);
    pinMode(SEG_C3_PIN, OUTPUT);
    pinMode(SEG_R1_PIN, OUTPUT);
    pinMode(SEG_R2_PIN, OUTPUT);
    pinMode(SEG_POINT_PIN, OUTPUT);
    pinMode(SEG_MODE_PIN, OUTPUT);
    pinMode(MODE_PIN, OUTPUT);
    seg_started = true;
  }
  // 左上
  digitalWrite(SEG_L1_PIN, (mask & L1) ? HIGH : LOW);
  // 左下
  digitalWrite(SEG_L2_PIN, (mask & L2) ? HIGH : LOW);
  // 中央上
  digitalWrite(SEG_C1_PIN, (mask & C1) ? HIGH : LOW);
  // 中央真ん中
  digitalWrite(SEG_C2_PIN, (mask & C2) ? HIGH : LOW);
  // 中央下
  digitalWrite(SEG_C3_PIN, (mask & C3) ? HIGH : LOW);
  // 右上
  digitalWrite(SEG_R1_PIN, (mask & R1) ? HIGH : LOW);
  // 右下
  digitalWrite(SEG_R2_PIN, (mask & R2) ? HIGH : LOW);
  // 小数点
  digitalWrite(SEG_POINT_PIN, (mask & POINT) ? HIGH : LOW);
  // セグを点灯
  ren(SEG_MODE_PIN, HIGH);
  // 送信
  ren(MODE_PIN, LOW);
}

/*******************
 * LED マトリックス *
 *******************/

const byte MATRIX_0[8] = { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 };
const byte MATRIX_LEFT_1[8] = { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B11111111 };
const byte MATRIX_LEFT_2[8] = { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B11111111, B00000000 };
const byte MATRIX_LEFT_3[8] = { B00000000, B00000000, B00000000, B00000000, B00000000, B11111111, B00000000, B00000000 };
const byte MATRIX_LEFT_4[8] = { B00000000, B00000000, B00000000, B00000000, B11111111, B00000000, B00000000, B00000000 };
const byte MATRIX_LEFT_5[8] = { B00000000, B00000000, B00000000, B11111111, B00000000, B00000000, B00000000, B00000000 };
const byte MATRIX_LEFT_6[8] = { B00000000, B00000000, B11111111, B00000000, B00000000, B00000000, B00000000, B00000000 };
const byte MATRIX_LEFT_7[8] = { B00000000, B11111111, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 };
const byte MATRIX_LEFT_8[8] = { B11111111, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 };
const byte MATRIX_UP_1[8] = { B00000001, B00000001, B00000001, B00000001, B00000001, B00000001, B00000001, B00000001 };
const byte MATRIX_UP_2[8] = { B00000010, B00000010, B00000010, B00000010, B00000010, B00000010, B00000010, B00000010 };
const byte MATRIX_UP_3[8] = { B00000100, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100 };
const byte MATRIX_UP_4[8] = { B00001000, B00001000, B00001000, B00001000, B00001000, B00001000, B00001000, B00001000 };
const byte MATRIX_UP_5[8] = { B00010000, B00010000, B00010000, B00010000, B00010000, B00010000, B00010000, B00010000 };
const byte MATRIX_UP_6[8] = { B00100000, B00100000, B00100000, B00100000, B00100000, B00100000, B00100000, B00100000 };
const byte MATRIX_UP_7[8] = { B01000000, B01000000, B01000000, B01000000, B01000000, B01000000, B01000000, B01000000 };
const byte MATRIX_UP_8[8] = { B10000000, B10000000, B10000000, B10000000, B10000000, B10000000, B10000000, B10000000 };
const byte MATRIX_LEFT[8] = { B00011000, B00011000, B00011000, B00011000, B11111111, B01111110, B00111100, B00011000 };
const byte MATRIX_RIGHT[8] = { B00011000, B00111100, B01111110, B11111111, B00011000, B00011000, B00011000, B00011000 };
const byte MATRIX_UP[8] = { B00001000, B00001100, B00001110, B11111111, B11111111, B00001110, B00001100, B00001000 };
const byte MATRIX_DOWN[8] = { B00010000, B00110000, B01110000, B11111111, B11111111, B01110000, B00110000, B00010000 };

// 消灯用
inline void matrix_reset() {
  ren(RCLK_PIN, LOW);
  shiftOut(SER_PIN, SRCLK_PIN, MSBFIRST, B00000000); // 列
  shiftOut(SER_PIN, SRCLK_PIN, MSBFIRST, B00000000); // 行
  ren(RCLK_PIN, HIGH);
}

boolean matrix_started = false;

// 点灯
void matrix(const byte pattern[8], unsigned long duration = 100) {
  // 初回実行時にピンモード指定
  if (!matrix_started) {
    pinMode(SER_PIN, OUTPUT);
    pinMode(SRCLK_PIN, OUTPUT);
    pinMode(RCLK_PIN, OUTPUT);
    matrix_started = true;
  }
  unsigned long startTime = millis();
  // 指定された時間(ms)、パターンを表示
  while (millis() - startTime < duration) {
    // 1フレーム（8行分）を描画
    for (int row = 0; row < 8; row++) {
      // 残像防止のため、一旦非表示
      matrix_reset();
      // ラッチピンを下げて、データ送信を開始
      ren(RCLK_PIN, LOW);
      // 列
      shiftOut(SER_PIN, SRCLK_PIN, MSBFIRST, pattern[row]);
      // 行
      shiftOut(SER_PIN, SRCLK_PIN, MSBFIRST, 1 << row);
      // ラッチピンを上げて、シフトレジスタのデータに反映させる
      ren(RCLK_PIN, HIGH);
    }
  }
}

/************
 * LED バー *
 ************/

// 各線の列挙型
enum Line { P1 = 0x001, P2 = 0x002, P3 = 0x004, P4 = 0x008, P5 = 0x010, P6 = 0x020, P7 = 0x040, P8 = 0x080, P9 = 0x100, P10 = 0x200 };
// 各色の格納変数
const byte lineIndex[] = { P1, P2, P3, P4, P5, P6, P7, P8, P9, P10 };
// 各色の列挙型
enum Led { R = 0x1, G = 0x2, B = 0x4 };
// 白（ホワイト）
const Led W = R | G | B;
// 水色（シアン）
const Led C = G | B;
// 黄色（イエロー）
const Led Y = R | G;
// 紫（マゼンタ）
const Led M = R | B;
// 消灯（ブラック）
const Led K = 0;
// 各色の格納変数
const byte ledIndex[] = { R, G, B, W, C, Y, M, K };

boolean bar_started = false;

void bar(int line, int color = 0) {
  // 初回実行時にピンモード指定
  if (!bar_started) {
    pinMode(LED_BAR_1_PIN, OUTPUT);
    pinMode(LED_BAR_2_PIN, OUTPUT);
    pinMode(LED_BAR_3_PIN, OUTPUT);
    pinMode(LED_BAR_4_PIN, OUTPUT);
    pinMode(LED_BAR_5_PIN, OUTPUT);
    pinMode(LED_BAR_6_PIN, OUTPUT);
    pinMode(LED_BAR_7_PIN, OUTPUT);
    pinMode(LED_BAR_8_PIN, OUTPUT);
    pinMode(LED_BAR_9_PIN, OUTPUT);
    pinMode(LED_BAR_10_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_BLUE_PIN, OUTPUT);
  }
  digitalWrite(LED_BAR_1_PIN, (line & P1) ? HIGH : LOW);
  digitalWrite(LED_BAR_2_PIN, (line & P2) ? HIGH : LOW);
  digitalWrite(LED_BAR_3_PIN, (line & P3) ? HIGH : LOW);
  digitalWrite(LED_BAR_4_PIN, (line & P4) ? HIGH : LOW);
  digitalWrite(LED_BAR_5_PIN, (line & P5) ? HIGH : LOW);
  digitalWrite(LED_BAR_6_PIN, (line & P6) ? HIGH : LOW);
  digitalWrite(LED_BAR_7_PIN, (line & P7) ? HIGH : LOW);
  digitalWrite(LED_BAR_8_PIN, (line & P8) ? HIGH : LOW);
  digitalWrite(LED_BAR_9_PIN, (line & P9) ? HIGH : LOW);
  digitalWrite(LED_BAR_10_PIN, (line & P10) ? HIGH : LOW);
  digitalWrite(LED_RED_PIN, (color & R) ? LOW : HIGH);
  digitalWrite(LED_GREEN_PIN, (color & G) ? LOW : HIGH);
  digitalWrite(LED_BLUE_PIN, (color & B) ? LOW : HIGH);
}

/********************
 * フォトインタラプタ *
 ********************/

// フォトインタラプタが反応し続けている時は true
inline boolean isPhotoEnabled() {
  return digitalRead(PHOTO_INTERRUPTER_PIN) == LOW;
}

// フォトインタラプタの羽が指定回数通過した瞬間に true
boolean isPhotoPassed(byte rotation = 1) {
  // 瞬間検知のための状態保持フラグ
  static boolean photo_state = false;
  // 通過回数カウンター
  static byte photo_passed_count = 0;
  // 羽が1枚通過した瞬間かを判定
  boolean one_rotate = false;
  // 現在の遮光状態を一度だけ読み取る
  boolean currently_enabled = isPhotoEnabled();
  // 通過の瞬間を検知
  if (!photo_state && currently_enabled) {
    // 状態を検知済みに更新
    photo_state = true;
    // 1回通過したと判定
    one_rotate = true;
  }
  // 状態をリセット
  else if (!currently_enabled) {
    // 状態を未検知にリセット
    photo_state = false;
  }
  // 1回通過を検知した場合のみ回数判断へ
  if (!one_rotate) {
    return false;
  }
  // 1回通過が検知された場合
  if (rotation == 1) {
    // 目標が1回なら、そのまま true
    return true;
  } else {
    // 目標が複数回なら、カウンター処理を行う
    photo_passed_count++;
    if (photo_passed_count >= rotation) {
      photo_passed_count = 0;
      // 目標回数に到達した
      return true;
    }
  }
  // 目標回数に達していない場合は false
  return false;
}

/*****************
 * トグルスイッチ *
 *****************/

// トグルスイッチが奥側の時は true
inline boolean isToggleEnabled() {
  return digitalRead(TOGGLE_PIN) == HIGH;
}

// タクト・トグルチャタリング防止遅延 (マイクロ秒)
const byte CHATTER_DEBOUNCE_US = 60;
// トグルスイッチが上げられた時に true
boolean isTogglePulled() {
  // トグルの状態保持用
  static boolean toggle = true;
  // チャタリング防止
  delayMicroseconds(CHATTER_DEBOUNCE_US);
  boolean currently_enabled = isToggleEnabled();
  // トグルの状態を参照し更新
  if (currently_enabled && toggle) {
    // 上げられたので状態を更新
    toggle = false;
    return true;
  } else if (!currently_enabled) {
    // 下げられたので状態をリセット
    toggle = true;
    return false;
  } else {
    // 上げられているが無視
    return false;
  }
}

/*****************
 * タクトスイッチ *
 *****************/

// タクトスイッチの左右を識別する列挙型
enum TactSwitch { TL, TR, LL, LR, RL, RR };

// 指定された側のタクトスイッチが押され続けている時は true
boolean isTactEnabled(TactSwitch side) {
  static byte pin;
  switch (side) {
    case TL: pin = TACT_TEST_LEFT_PIN; break;
    case TR: pin = TACT_TEST_RIGHT_PIN; break;
    case LL: pin = TACT_LEFT_LEFT_PIN; break;
    case LR: pin = TACT_LEFT_RIGHT_PIN; break;
    case RL: pin = TACT_RIGHT_LEFT_PIN; break;
    case RR: pin = TACT_RIGHT_RIGHT_PIN; break;
  }
  return digitalRead(pin);
}

// 指定された側のタクトスイッチが１回押された時に true
boolean isTactPressed(TactSwitch side) {
  // スイッチの状態保持用
  static boolean tact_pressed_state[6] = { true, true, true, true, true, true };
  // チャタリング防止
  delayMicroseconds(CHATTER_DEBOUNCE_US);
  boolean currently_enabled = isTactEnabled(side);
  // 指定されたスイッチの状態を参照し更新
  if (currently_enabled && tact_pressed_state[side]) {
    // 押されたので状態を更新
    tact_pressed_state[side] = false;
    return true;
  } else if (!currently_enabled) {
    // 離されたので状態をリセット
    tact_pressed_state[side] = true;
    return false;
  } else {
    // 押され続けているが無視
    return false;
  }
}

/*************
 * 可変抵抗器 *
 *************/

// 可変抵抗器の値を 0 ~ 1023 で取得
inline uint16_t getPot() {
  return analogRead(POTENTIOMETER_PIN);
}

// 1023 -> 9
byte map_volume_value() {
  // アナログ値を取得
  uint16_t raw_value = getPot();
  // 変換
  byte scaled_value = (byte) (raw_value * 9 / 1023);
  // 戻す
  return scaled_value;
}

// 可変抵抗器と7セグを同期
void syncPot() {
  // ７セグに表示
  seg(num[map_volume_value()]);
}

/*******************
 * ジョイスティック *
 *******************/
// X軸の値を取得
inline uint16_t getJoyX() {
  return analogRead(JOYSTICK_X_PIN);
}
// Y軸の値を取得
inline uint16_t getJoyY() {
  return analogRead(JOYSTICK_Y_PIN);
}
// 可動域
const int THRESHOLD_LOW  = 350;
const int THRESHOLD_HIGH = 650;
// LED マトリックスと向きを同期
void syncArrow() {
  int xValue = getJoyX();
  int yValue = getJoyY();
  if (yValue < THRESHOLD_LOW) {
    matrix(MATRIX_UP);
  } else if (yValue > THRESHOLD_HIGH) {
    matrix(MATRIX_DOWN);
  } else if (xValue > THRESHOLD_HIGH) {
    matrix(MATRIX_RIGHT);
  } else if (xValue < THRESHOLD_LOW) {
    matrix(MATRIX_LEFT);
  } else {
    matrix(MATRIX_0);
  }
}

/***********
 * 実行準備 *
 ***********/

// 任意初期化
void start(void);

// 初期化
void setup() {
  // ボードレートを指定
  Serial.begin(9600);
  // 入力ピンの割り当て
  for (byte i = 0; i < sizeof(PIN_READ) / sizeof(PIN_READ[0]); i++) pinMode(PIN_READ[i], INPUT);
  // オプション関数
  start();
}

#endif // MONO2025_H
