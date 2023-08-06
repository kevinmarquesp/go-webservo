#include "./string.h"

void convstrtoNumarray(String data, char dlmr, u8* degarr)
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
