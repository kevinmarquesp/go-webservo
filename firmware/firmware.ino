#include "src/lib/PreciseServo/PreciseServo.h"

#include "src/helpers/serial/serial.h"
#include "src/helpers/routines/routines.h"

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
    Motor[i].config(pinarr[i], minarr[i], maxarr[i]);
}

void loop(void)
{
  if (Serial.available())
  {
    String input = readfromWebapp();

    executeMakemoviment(input, SERVO_NUM, &livemovimentRoutine);
    executeParallelmoviment(input, SERVO_NUM, &parallelmovimentRoutine);
  }
}
