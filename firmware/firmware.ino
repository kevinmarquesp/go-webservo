#include "src/lib/PreciseServo/PreciseServo.h"

#include "src/helpers/serial/serial.h"
#include "src/helpers/routines/routines.h"

#include "src/header/user_config.h"

u8 pinarr[SERVO_NUM] = PIN_ARRAY;
u8 minarr[SERVO_NUM] = MIN_ARRAY;
u8 maxarr[SERVO_NUM] = MAX_ARRAY;

AdvancedServo Motor[SERVO_NUM];

void setup(void)
{
  Serial.begin(BAUDRATE);
  sendConfigdata(SERVO_NUM, minarr, maxarr);

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
