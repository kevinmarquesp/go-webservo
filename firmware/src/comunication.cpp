#include "comunication.h"

String readfromWebapp(void)
{
  return Serial.readStringUntil('\n');
}

void validateCommandstring(String raw, String expected, Command* cmdbuf)
{
  if (raw.indexOf(expected) == -1)
  {
    cmdbuf->error = true;
    return;
  }

  cmdbuf->arg = raw.substring(expected.length(), raw.length());
  cmdbuf->error = false;
}

void splitarrayDegstring(String data, char dlmr, void run(u8 pos, u8 val))
{
  data.replace(" ", "");
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
        run(j, elm.toInt());

      s = i;
      ++j;
    }
  }
}

void executeMakemoviment(String raw, void run(u8 pos, u8 val))
{
  Command cmd;

  validateCommandstring(raw, "mv:", &cmd);

  if (cmd.error)
    return;

  splitarrayDegstring(cmd.arg, ',', run);
}
