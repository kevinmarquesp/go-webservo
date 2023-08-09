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
  u8 bspos = 0, doneCounter = 0, lenarr[buffsize];
  u16 total, velarr[buffsize];

  // get the length of each movement
  for (u8 i = 0; i < buffsize; ++i)
    lenarr[i] = abs(Motor[i].read() - degarr[i]);

  // select the slowest movement and calc the total
  for (u8 i = 0; i < buffsize; ++i)
    bspos = lenarr[i] > lenarr[bspos] ? i : bspos;

  total = lenarr[bspos] * vel;

  // use the total value to calc the movement for each servo
  for (u8 i = 0; i < buffsize; ++i)
    velarr[i] = total / lenarr[i];

  pastpos = getallServopos(Motor, buffsize);

  // stop the program execution to move the servos
  while (doneCounter <= buffsize)
  {
    for (u8 i = 0; i < buffsize; ++i)
      Motor[i].move(Motor[i].is(0), degarr[i], velarr[i]);

    if (isAlldone(Motor, buffsize))
      doneCounter++;
  }

  nowpos = getallServopos(Motor, buffsize);
  resetallServo(Motor, buffsize);

  Serial.print("done:");
  Serial.println(String(pastpos + ">" + nowpos));
}
