#include "./serial.h"

void sendConfigdata(u8 servonum, u8* minarr, u8* maxarr)
{
  String confstr = "conf:";

  for (u8 i = 0; i < servonum; ++i)
  {
    confstr.concat(String(minarr[i]) + "-");

    confstr.concat(i == servonum - 1 ?
      String(maxarr[i]) : String(maxarr[i]) + ",");
  }

  Serial.println(confstr);
}

String readfromWebapp(void)
{
  String data = Serial.readStringUntil('\n');

  data.replace(" ", "");
  return data;
}
