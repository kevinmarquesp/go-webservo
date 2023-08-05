#include "comunication.h"

String readfromWebapp(void)
{
  String data = Serial.readStringUntil('\n');

  data.replace(" ", "");
  return data;
}

void validateCommandstring(String raw, String expected, Command* cmdbuf)
{
  if (raw.indexOf(expected) != 0)
  {
    cmdbuf->error = true;
    return;
  }

  cmdbuf->arg = raw.substring(expected.length(), raw.length());
  cmdbuf->error = false;
}

void converttoDegstring(String data, char dlmr, u8* degarr)
{
  data.concat(',');

  u8 j = 0, s = 0;

  for (u8 i = 0; i < data.length(); ++i)
  {
    if (data.charAt(i) == dlmr or i == data.length() + 1)
    {
      String elm = data.substring(s, i);
      i8 matchdlmr = data.indexOf(dlmr);

      // remove the dlmr string if it is present on this instance
      if (matchdlmr != -1)
        data.remove(matchdlmr, 1);

      // only execute if the element is not an empty string
      if (elm.length() > 0)
        degarr[j] = elm.toInt();

      s = i;
      ++j;
    }
  }
}

void splitString(String data, char dlmr, Strsplit* buff)
{
  u8 matchdlmr = data.indexOf(dlmr);

  if (matchdlmr == -1)
  {
    buff->error = true;
    return;
  }

  buff->left = data.substring(0, matchdlmr);
  buff->rigth = data.substring(matchdlmr + 1, data.length());
  buff->error = false;
}

void executeMakemoviment(String raw, u8 buffsize, void run(u8, u8, u16))
{
  Command cmd;
  u8 degarr[buffsize];

  validateCommandstring(raw, "mv:", &cmd);

  if (cmd.error)
    return;

  converttoDegstring(cmd.arg, ',', arr);

  for (u8 i = 0; i < buffsize; ++i)
    run(i, degarr[i], 0);
}

void executeParallelmoviment(String raw, u8 buffsize, void run(u8, u8, u16))
{
  Command cmd;
  Strsplit split;

  validateCommandstring(raw, "pmv:", &cmd);

  if (cmd.error)
    return;

  splitString(cmd.arg, '/', &split);

  if (split.error or split.left.length() == 0 or split.rigth.length() == 0)
    return;

  /* converttoDegstring(split.rigth, ',', run, split.left.toInt()); */
}
