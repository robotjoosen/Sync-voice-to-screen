#include "SSD1306Wire.h"

SSD1306Wire  display(0x3c, 18, 19);

const unsigned int MAX_INPUT = 50;
unsigned int blink_timer = 0;
unsigned int blink_speed = 400;
unsigned int tweek_timer = 0;
unsigned int tweek_speed = 1250;

void setup() {
  Serial.begin(115200);
  display.init();
  draw_face(0,0,0);
}

void loop() {
  while (Serial.available() > 0) {
    processIncomingByte (Serial.read ());
  }
}

void process_data(String input_data)
{
  display.clear();
  blinkEyes();
  tweekEye();
  talk(input_data.toFloat());
  display.display();
}

void blinkEyes()
{
  if(blink_timer < blink_speed) {
    drawLeftEye(0);
    drawRightEye(0);
  } else if(blink_timer < (blink_speed+5)) {
    drawLeftEye(1);
    drawRightEye(2);
  } else if(blink_timer < (blink_speed+10)) {
    drawLeftEye(3);
    drawRightEye(3);
  } else {
    drawLeftEye(0);
    drawRightEye(0);
    blink_timer = 0;
  }
  blink_timer++;
}

void tweekEye()
{
  if(tweek_timer < tweek_speed) {
    // Nothing
  } else if(tweek_timer < (tweek_speed+5)) {
    display.clear();
    drawLeftEye(1);
    drawRightEye(0);
  } else if(tweek_timer < (tweek_speed+10)) {
    display.clear();
    drawLeftEye(2);
    drawRightEye(0);
  } else if(tweek_timer < (tweek_speed+15)) {
    display.clear();
    drawLeftEye(0);
    drawRightEye(0);
    tweek_timer = 0;
  }
  tweek_timer++;
}

void talk(float level)
{
  if(level > 15) {
    drawMouth(3);
  } else if(level > 10) {
    drawMouth(2);
  } else if(level > 5) {
    drawMouth(1);
  } else {
    drawMouth(0);
  }
}

void processIncomingByte (const byte inByte)
{
  static char input_line [MAX_INPUT];
  static unsigned int input_pos = 0;

  switch (inByte) {
    case '\n':   // end of text
      input_line [input_pos] = 0;  // terminating null byte
      process_data(input_line);
      input_pos = 0;  
      break;
    case '\r':   // discard carriage return
      break;
    default:
      if (input_pos < (MAX_INPUT - 1))
        input_line [input_pos++] = inByte;
      break;
  }
}

void screenDemo()
{
  face_blink(2);
  face_open_eyes();
  face_close_eyes();
  face_cry(10);
  face_open_eyes();
  face_close_eyes();
  face_sleep(10);
  face_open_eyes();
  face_close_eyes();
  face_uncomfort();
  delay(1000);
  face_open_eyes();
  face_close_eyes();
  face_sad();
  delay(1000);
}

//ANIMATION
void face_cry(int duration)
{
  for(int i = 0; i<duration; i++)
  {
    face_cry_0();
    delay(200);
    face_cry_1();
    delay(200);
    face_cry_2();
    delay(200);
  }
}
void face_sleep(int duration)
{
  for(int i = 0; i<duration; i++)
  {
    face_sleep_0();
    delay(200);
    face_sleep_1();
    delay(200);
    face_sleep_2();
    delay(200);
  }
}
void face_blink(int duration)
{
  for(int i = 0; i<duration; i++)
  {
    face_normal();
    delay(100);
    face_closing();
    delay(50);
    face_closed();
    delay(200);
    face_closing();
    delay(50);
  }
}
void face_close_eyes()
{
  face_normal();
  delay(100);
  face_closing();
  delay(100);
  face_closed();
  delay(200);
}
void face_open_eyes()
{
  face_closed();
  delay(100);
  face_closing();
  delay(100);
  face_normal();
  delay(200);
}


//BASIC
void face_normal()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_normal);
  display.display();
}
void face_closing()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_closing);
  display.display();
}
void face_closed()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_closed);
  display.display();
}
void face_sad()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_sad);
  display.display();
}
void face_uncomfort()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_uncomfort);
  display.display();
}

//CRY
void face_cry_0()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_cry_0);
  display.display();
}
void face_cry_1()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_cry_1);
  display.display();
}
void face_cry_2()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_cry_2);
  display.display();
}

//SLEEP
void face_sleep_0()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_sleep_0);
  display.display();
}
void face_sleep_1()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_sleep_1);
  display.display();
}
void face_sleep_2()
{
  display.clear();
  display.drawFastImage(0, 0, 128, 64, graphic_sleep_2);
  display.display();
}

//Face builder
/**
 * @param int mouth
 * @param int left_eye
 * @param int right_eye
 */
void draw_face(int mouth, int left_eye, int right_eye)
{
  display.clear();
  drawLeftEye(left_eye);
  drawRightEye(right_eye);
  drawMouth(mouth);
  display.display();
}

void drawLeftEye(int state)
{
  int image_width = 41;
  int image_height = 41;
  int position_x = 4;
  int position_y = 12;
  switch(state) {
    case 0 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_eye_open); break;
    case 1 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_eye_bottom); break;
    case 2 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_eye_squint); break;
    case 3 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_eye_closed); break;
  }
}

void drawRightEye(int state)
{
  int image_width = 41;
  int image_height = 41;
  int position_x = 83;
  int position_y = 12;
  switch(state) {
    case 0 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_eye_open); break;
    case 1 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_eye_bottom); break;
    case 2 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_eye_squint); break;
    case 3 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_eye_closed); break;
  }
}

void drawMouth(int state)
{
  int image_width = 30;
  int image_height = 30;
  int position_x = 49;
  int position_y = 32;
  switch(state) {
    case 0 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_mouth_normal); break;
    case 1 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_mouth_mid); break;
    case 2 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_mouth_open); break;
    case 3 : display.drawXbm(position_x, position_y, image_width, image_height, graphic_mouth_wide); break;
  }
}
