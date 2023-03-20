#include "tm4c123gh6pm.h"
#include <stdbool.h>

void stopwatchinit(void);
void enableStopwatch();
void disableTimer();
void displayTime(int sec, int min, int hour);
bool getOvrFlwFlg();
