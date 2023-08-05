#include <Servo.h>

#include "src/comunication.h"
#include "config.h"

// setting up the global values that handle the servo objects
u8 pinarr[SERVO_NUM] = PIN_ARRAY;
u8 minarr[SERVO_NUM] = MIN_ARRAY;
u8 maxarr[SERVO_NUM] = MAX_ARRAY;
Servo Motor[SERVO_NUM];

void setup(void)
{
  String confstr = "gws_conf:";

  // that loop will construct the command string to send it after
  for (u8 i = 0; i < SERVO_NUM; ++i)
  {
    confstr.concat(minarr[i]);
    confstr.concat('-');
    confstr.concat(maxarr[i]);

    if (i == SERVO_NUM - 1)
      confstr.concat(',')
  }

  Serial.begin(BAUDRATE);
  Serial.println(confstr);

  // and that loop will attach all servos and move them to the min value
  for (u8 i = 0; i < SERVO_NUM; ++i)
  {
    Motor[i].attach(pinarr[i]);
    Motor[i].write(minarr[i]);
  }
}

void loop(void)
{
  if (not Serial.available())
    return;

  String data = readfromWebapp();

  executeMakemoviment(data, [](u8 pos, u8 val){
    if (pos < SERVO_NUM)
      Motor[pos].write(val);
  });
}
