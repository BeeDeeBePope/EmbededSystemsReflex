#include "../pre_emptive_os/api/osapi.h"
#include "../pre_emptive_os/api/general.h"
#include <printf_P.h>
#include <ea_init.h>
#include <stdlib.h>

#include "lcd.h"
#include "key.h"
#include "hw.h"
#include "version.h"

#define INIT_STACK_SIZE  600
static tU8 initStack[INIT_STACK_SIZE];
static void initProc(void* arg);

#define PROC1_STACK_SIZE 800
static tU8 pid1;
static tU8 proc1Stack[PROC1_STACK_SIZE];
static void proc1(void* arg);

#define LED_PROC_STACK_SIZE 200
static tU8 ledProcStack[LED_PROC_STACK_SIZE];
static tU8 pid2;
static void ledProc(void* arg);

volatile tU32 ms;

static tU8 contrast = 56;
static tU8 cursor   = 0;

static void drawMenuCursor(tU8 cursor);
void errorFun();
void appTick(tU32 elapsedTime);

int
main(void)
{
  tU8 error;
  tU8 pid;
  
  osInit();

  //immediate initilaizeation of hardware I/O pins
  immediateIoInit();
  
  osCreateProcess(initProc, initStack, INIT_STACK_SIZE, &pid, 1, NULL, &error);
  osStartProcess(pid, &error);
  
  osStart();
  return error;
}

static void drawMenu(void) {
  lcdColor(0,0); // main BG
  lcdClrscr();

  lcdRect(14, 0, 102, 128, 0x6d); // menu title BG
  lcdRect(15, 17, 100, 110, 0); //inner menu BG

  lcdGotoxy(31,1);// position of title
  lcdColor(0x6d,0);
  lcdPuts("MAIN MENU"); // menu title
  drawMenuCursor(cursor);
}

static void initProc(void* arg) {
  tU8 error;

  eaInit();

  printf("EmbedeSystems Reflex game.\n"
		  "TEST\n");

  osCreateProcess(proc1, proc1Stack, PROC1_STACK_SIZE, &pid1, 3, NULL, &error);
  osStartProcess(pid1, &error);

  if(error != OS_OK) {
	  errorFun("There was an error with proc1 process.");
  }

  osCreateProcess(ledProc, ledProcStack, LED_PROC_STACK_SIZE, &pid2, 3, NULL, &error);
  osStartProcess(pid2, &error);

  if(error != OS_OK) {
  	  errorFun("There was an error with ledProc process.");
    }

  initKeyProc();

  osDeleteProcess();
}

static void proc1(void* arg) {
  //shortly bleep with the buzzer and flash with the LEDs
  tU8 i,j;

  for(i=0; i<3; i++)
  {
    for(j=0; j<3; j++)
    {
      setBuzzer(TRUE);
      setLED(LED_GREEN, FALSE);
      setLED(LED_RED,   TRUE);
      osSleep(1);
      setLED(LED_RED,   TRUE);
      osSleep(1);
      setLED(LED_RED,   FALSE);
      osSleep(3);
      setLED(LED_RED,   TRUE);
      osSleep(1);
      setLED(LED_RED,   FALSE);
      osSleep(2);
      setLED(LED_RED,   TRUE);
      osSleep(1);
      setLED(LED_RED,   FALSE);
      osSleep(5);
      setLED(LED_RED,   TRUE);
      osSleep(1);

      setBuzzer(FALSE);
      setLED(LED_GREEN, TRUE);
      setLED(LED_RED,   FALSE);
      osSleep(1);
    }
    osSleep(10);
  }
  setLED(LED_GREEN, FALSE);
  setLED(LED_RED,   FALSE);

  resetLCD();
  lcdInit();

  drawMenu();
  
  while(TRUE)
  {
    tU8 anyKey;
    static tU8 i = 0;

    anyKey = checkKey();
    if (anyKey != KEY_NOTHING)
    {
      //select specific function
      if (anyKey == KEY_CENTER)
      {
        switch(cursor)
        {
          case 0: 
            reflex();
			
			
			
			
            break;
          default: 
        	break;
        }
        drawMenu();
      }
      
      //adjust contrast
      else if (anyKey == KEY_RIGHT)
      {
        contrast++;
        if (contrast > 127)
          contrast = 127;
        lcdContrast(contrast);
      }
      else if (anyKey == KEY_LEFT)
      {
        if (contrast > 0)
          contrast--;
        lcdContrast(contrast);
      }
    }

    osSleep(20);
  }
}

static void ledProc(void* arg) {
	while(TRUE){
		setLED(LED_GREEN, TRUE);
		osSleep(10);
		setLED(LED_RED, TRUE);
		osSleep(20);
		setLED(LED_GREEN, FALSE);
		osSleep(20);
		setLED(LED_RED, FALSE);
		osSleep(10);
	}
}

static void drawMenuCursor(tU8 cursor) {
  tU32 row;

  for(row=0; row<4; row++)
  {
    lcdGotoxy(18,20+(14*row));
    if(row == cursor)
      lcdColor(0xd4,0xe0);
    else
      lcdColor(0x00,0xfd);

    switch(row)
    {
      case 0: lcdPuts("play Reflex");
			  break;

      default:
      break;
    }
  }
}

void errorFun(char *message) {
	lcdColor(0,0xff); // main BG
	lcdClrscr();

	lcdGotoxy(30,50);
	lcdPuts("ERROR"); // menu title
	printf(message);
}
//seems useless
void appTick(tU32 elapsedTime) {
  ms += elapsedTime;
}
