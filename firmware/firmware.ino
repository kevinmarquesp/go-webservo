#include <Servo.h>

#define AMOUNT 3

const uint8_t pinarr[AMOUNT] = {  7,   6,   5};
const uint8_t minarr[AMOUNT] = {  0,  30,  10};
const uint8_t maxarr[AMOUNT] = {180, 150,  90};

Servo actor[AMOUNT];

void setup(void)
{
  String webconfig = "gws_conf:";

  for (uint8_t i = 0; i < AMOUNT; ++i)
  {
    webconfig.concat(String(minarr[i]) + String("-"));
    webconfig.concat(i == AMOUNT - 1 ?
      String(maxarr[i]) : String(maxarr[i]) + String(","));

    actor[i].attach(pinarr[i]);
    actor[i].write(minarr[i]);
  }

  Serial.begin(9600);
  Serial.println(webconfig);
}

void loop(void)
{
  if (not Serial.available())
    return;

  String rawData = Serial.readStringUntil('\n');
  String strData[AMOUNT];
  uint8_t j = 0, s = 0;

  for (uint8_t i = 0; i < rawData.length(); ++i)
  {
    if (rawData.charAt(i) == ' ' or i == rawData.length() - 1)
    {
      strData[j] = rawData.substring(s, i + 1);
      s = i;
      j++;
    }
  }

  for (uint8_t i = 0; i < AMOUNT; ++i)
  {
    actor[i].write(strData[i].toInt());
  }
}
