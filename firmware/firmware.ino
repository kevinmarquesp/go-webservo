#include "src/lib/PreciseServo/PreciseServo.h"

#include "src/helpers/serial/serial.h"
#include "src/helpers/servo/servo.h"

#include "src/header/user_config.h"

// setting up the global values that handle the servo objects
u8 pinarr[SERVO_NUM] = PIN_ARRAY;
u8 minarr[SERVO_NUM] = MIN_ARRAY;
u8 maxarr[SERVO_NUM] = MAX_ARRAY;
AdvancedServo Motor[SERVO_NUM];

void setup(void)
{
  String confstr = "gws_conf:";

  // that loop will construct the command string to send it after
  for (u8 i = 0; i < SERVO_NUM; ++i)
  {
    confstr.concat(String(minarr[i]) + "-");
    confstr.concat(i == SERVO_NUM - 1 ?
      String(maxarr[i]) : String(maxarr[i]) + ",");
  }

  Serial.begin(BAUDRATE);
  Serial.println(confstr);

  // and that loop will attach all servos and move them to the min value
  for (u8 i = 0; i < SERVO_NUM; ++i)
  {
    Motor[i].config(pinarr[i], minarr[i], maxarr[i]);
  }
}

void loop(void)
{
  if (not Serial.available())
    return;

  String data = readfromWebapp();

  executeMakemoviment(data, SERVO_NUM, [](u8 pos, u8 deg, u16 _){
    if (deg < Motor[pos].getMin())
      Motor[pos].write(Motor[pos].getMin());

    else if (deg > Motor[pos].getMax())
      Motor[pos].write(Motor[pos].getMax());

    else
      Motor[pos].write(deg);
  });

  executeParallelmoviment(data, SERVO_NUM, [](u8* degarr, u16 vel, u8 buffsize){
    String pastpos, nowpos;
    u8 doneCounter = 0;

    pastpos = getallServopos(Motor, buffsize);

    while (doneCounter <= buffsize)
    {
      for (u8 i = 0; i < buffsize; ++i)
      {
        u8 deg = degarr[i];

        Motor[i].move(Motor[i].is(0), deg, vel);

        if (isAlldone(Motor, buffsize))
          doneCounter++;
      }
    }

    nowpos = getallServopos(Motor, buffsize);
    resetallServo(Motor, buffsize);

    Serial.print("done:");
    Serial.println(String(pastpos + ">" + nowpos));
  });
}
