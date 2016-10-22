#include "arrows.h"
#include <stdlib.h>
#include <time.h>
#include "key.h"
#include "../pre_emptive_os/api/osapi.h"

void reflex()
{
	srand(time(NULL));
	int arrowNr;
	tU8 key = KEY_NOTHING;
	tu8 keyList [] = {KEY_NOTHING, KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT, KEY_CENTER};
	
	do
	{
		lcdColor(0,0);
		lcdClrscr();
		
		arrowNr=rand()%4;
		switch(arrowNr)
		{
			case 1:
				lcdIcon(36, 4, 57, 102, _arrow_up_57x102[2], _arrow_up_57x102[3], &_arrow_up_57x102[4]);
				break;
			case 2:
				lcdIcon(14, 26, 102, 57, _arrow_right_102x57[2], _arrow_right_102x57[3], &_arrow_right_102x57[4]);
				break;
			case 3:
				lcdIcon(36, 4, 57, 102, _arrow_down_57x102[2], _arrow_down_57x102[3], &_arrow_down_57x102[4]);
				break;
			case 4:
				lcdIcon(14, 26, 102, 57, _arrow_left_102x57[2], _arrow_left_102x57[3], &_arrow_left_102x57[4]);
				break;
			default:
				break;
		}
		key=checkKey();
		lcdGotoxy(20,115);
		lcdColor(0,0);
		if (key == keyList[arrowNr])
		{
			lcdPuts("AWESOME!");
			osSleep(10);
		}
		else if (key != KEY_CENTER)
		{
			lcdPuts("TRY AGAIN");
			osSleep(10);
		}
	} while (key != KEY_CENTER)
}