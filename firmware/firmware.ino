#define AMOUNT 3

const uint8_t minarr[AMOUNT] = {  0,   0,   0};
const uint8_t maxarr[AMOUNT] = {180, 180, 180};

void setup(void)
{
  String webconfig = "gws_conf:";

  for (uint8_t i = 0; i < AMOUNT; ++i)
  {
    webconfig.concat(String(minarr[i]) + String("-"));
    webconfig.concat(i == AMOUNT - 1 ?
      String(maxarr[i]) : String(maxarr[i]) + String(","));
  }

  Serial.begin(9600);
  Serial.println(webconfig);
}

void loop(void)
{
}
