#include "./servo.h"

String getallServopos(AdvancedServo* Servoarr, u8 buffsize)
{
  String res = "";

  for (u8 i = 0; i < buffsize; ++i)
    res.concat(i == buffsize - 1 ?
      Servoarr[i].read() : String(Servoarr[i].read()) + ",");

  return res;
}

bool isAlldone(AdvancedServo* Servoarr, u8 buffsize)
{
  for (u8 i = 0; i < buffsize; ++i)
  {
    if (not Servoarr[i].isDone())
      return false;
  }

  return true;
}

void resetallServo(AdvancedServo* Servoarr, u8 buffsize)
{
  for (u8 i = 0; i < buffsize; ++i)
    Servoarr[i].reset();
}

