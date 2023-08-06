#include "./routines.h"

#include "../../lib/PreciseServo/PreciseServo.h"
#include "../servo/servo.h"

extern AdvancedServo Motor[];

void livemovimentRoutine(u8 pos, u8 deg, u16 vel)
{
  if (deg < Motor[pos].getMin())
    Motor[pos].write(Motor[pos].getMin());

  else if (deg > Motor[pos].getMax())
    Motor[pos].write(Motor[pos].getMax());

  else
    Motor[pos].write(deg);
}

void parallelmovimentRoutine(u8* degarr, u16 vel, u8 buffsize)
{
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
}
