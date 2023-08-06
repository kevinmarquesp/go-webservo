#include "./serial.h"

#include "../../utils/string/string.h"

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


String readfromWebapp(void)
{
  String data = Serial.readStringUntil('\n');

  data.replace(" ", "");
  return data;
}

void executeMakemoviment(String raw, u8 buffsize, void run(u8, u8, u16))
{
  Command cmd;
  u8 degarr[buffsize];

  validateCommandstring(raw, "mv:", &cmd);

  if (cmd.error)
    return;

  convstrtoNumarray(cmd.arg, ',', degarr);

  for (u8 i = 0; i < buffsize; ++i)
    run(i, degarr[i], 0);
}

void executeParallelmoviment(String raw, u8 buffsize, void run(u8*, u16, u8))
{
  Command cmd;
  Strsplit split;
  u8 degarr[buffsize];
  u16 vel;

  validateCommandstring(raw, "pmv:", &cmd);

  if (cmd.error)
    return;

  splitString(cmd.arg, '/', &split);

  if (split.error or split.left.length() == 0 or split.rigth.length() == 0)
    return;

  vel = split.left.toInt();
  convstrtoNumarray(split.rigth, ',', degarr);

  run(degarr, vel, buffsize);
}
