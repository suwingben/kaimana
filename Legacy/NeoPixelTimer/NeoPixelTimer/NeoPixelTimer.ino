//  NeoPixel.ino
//	
//  Authored:  August   5, 2016	  info // mightyjrmods.com -- 
// Code based on the Kaimana LED source provided by Paradise Arcade Shop www.paradisearcade.com
#define __PROG_TYPES_COMPAT__ 
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "kaimana.h"
#include "kaimana_custom.h"
#include "animations.h"

// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;
int delayer=1000;
int sec =0;
int min=0;
int hour=0;
int leds=LED_COUNT;
int place=0;	
int mode=0;
int cycle=0;
bool holding=false;
int lightup=0;
struct Position{
	int position;
	int level = 0;
	bool state;
	int currentR,currentG,currentB;
	int prevR, prevG, prevB;
};

//testing aggregate initializers
Position positions[12]{ 0,0,false,BLACK,BLACK };

void resetStatus(){
	for(int j = 0; j<LED_COUNT;j++){
		positions[j].position = j;
	}
}

void setup() 
{                
	kaimana.setALL(BLUE);
	resetStatus();
	delay(10);
}


void loop() 
{
	switch(mode){
	case 0: {
		if (sec == 12) {
			sec = 0;
			positions[min].state = true;
			min++;
		}
		if (min == 12) {
			min = 0;
			resetStatus();
			positions[hour].level++;
			hour++;
		}
		if (hour == 12) {
			hour = 0;
		}

		//keep track of lights
		for (int i = 0;i < LED_COUNT;i++) {
			int switchLevel = positions[i].level;
			if (positions[i].state == true) {
				if (switchLevel == 0) {
					turnOn(positions[i].position, WHITE);
				}
				if (switchLevel == 1) {
					turnOn(positions[i].position, GREEN);
				}
			}
		}
		blink(positions[sec].position, RED);
		sec++;
		break;
	}
		default:
			mode = 0;
			sec = 0;
			min = 0;
			hour = 0;
			break;
	}
	
	if(!digitalRead(PIN_HOME)){
		kaimana.setALL(BLACK);
		resetStatus();
		sec = 0;
		if(!holding){
		holding=true;
		mode++;			
		}
	}
	else{
		holding =false;
	}

	delay(100);
}