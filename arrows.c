#include "arrows.h"
#include <stdlib.h>
#include "key.h"
#include "../pre_emptive_os/api/osapi.h"
#include "../pre_emptive_os/api/general.h"

extern tU32 ms;

void reflex()
{
  srand(ms);
  tU8 arrowToShow;
  tU8 key = KEY_NOTHING;
  tU8 keyList [] = {KEY_NOTHING, KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT, KEY_CENTER};
  tS32 t = 0;
  lcdClrscr();
  char myTime [20];
  do
  {
    key = KEY_NOTHING;
	lcdGotoxy(60,60);
    lcdColor(0x00,0xfd);
	lcdPuts("3");
	osSleep(100);
	lcdClrscr();
	
	lcdGotoxy(60,60);
	lcdPuts("2");
	osSleep(100);
	lcdClrscr();
	
	lcdGotoxy(60,60);
	lcdPuts("1");
	osSleep(100);
	
	lcdGotoxy(0,0);
	lcdColor(0xff,0xfd);
    lcdClrscr();
    arrowToShow = rand()%4 + 1;
    switch(arrowToShow)
    {
      case 1: lcdIcon(36, 4, 57, 102, _arrow_up_57x102[2], _arrow_up_57x102[3], &_arrow_up_57x102[4]);
              break;
      case 2: lcdIcon(14, 26, 102, 57, _arrow_right_102x57[2], _arrow_right_102x57[3], &_arrow_right_102x57[4]);
              break;
      case 3: lcdIcon(36, 4, 57, 102, _arrow_down_57x102[2], _arrow_down_57x102[3], &_arrow_down_57x102[4]);
              break;
      case 4: lcdIcon(14, 26, 102, 57, _arrow_left_102x57[2], _arrow_left_102x57[3], &_arrow_left_102x57[4]);
              break;
      default: break;
    }
    t = ms;
    while(key == KEY_NOTHING)
    {
      key = checkKey();
    }
    t = ms - t;
    lcdGotoxy(20,60);
    lcdColor(0x00,0xfd);
	lcdClrscr();
    if (key == keyList[arrowToShow])
    {
      lcdPuts("AWESOME!");
	  sprintf(myTime,"%d",t);
	  lcdPuts(myTime);
    }
    else if (key != KEY_CENTER)
    {
      lcdPuts("TRY AGAIN");
    }
  } while (key != KEY_CENTER);
}
