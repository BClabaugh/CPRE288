/*
 * functions.c
 *
 *  Created on: Feb 6, 2024
 *      Author: clab22
 */


#include "functions.h"
#include "open_interface.h"
//#include "cyBot_Scan.h"
#include "cyBot_uart.h"


void sendBytes(char* message, double data){
  int i;
  char final_mes[100];

  if (data != -10000) {
    sprintf(final_mes, "%s %.3f", message, data);
  } else {
    strcpy(final_mes, message);
  }
//  sprintf(final_mes,"%s", final_mes);
  for(i = 0; i < strlen(final_mes); i++){
    //printf("%c\n", final_mes[i]);
    cyBot_sendByte(final_mes[i]);
  }

}

cyBOT_Scan_t *scan_alloc()
{
	return calloc(1, sizeof(cyBOT_Scan_t));
}

void scan_free(cyBOT_Scan_t *self)
{
    free(self);
}

void lcd_rotatingBanner(char* message)
{
    int i;
    char* spaces = "                   ";
    char final_mes[100];
    sprintf(final_mes,"%s%s", spaces,message);
    while(1){
        for(i=0;i<=strlen(final_mes);i++){
            lcd_printf("%.20s\n",final_mes+i);
            timer_waitMillis(300);
        }
    }
}





