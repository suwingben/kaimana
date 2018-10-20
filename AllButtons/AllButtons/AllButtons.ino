//  example.ino
//
//  Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com  
//  All rights reserved.  Use is subject to license terms.
//
//  Code is provided for entertainment purposes and use with the Kaimana controller.
//  Code may be copied, modified, resused with this Copyright notice.
//  No commercial use without written permission from Paradise Arcade Shop.
//
//  Paradise Arcade Shop Kaimana LED Driver Board
//  Initial Release October 15, 2013
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Kaimana example based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//


#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "kaimana.h"
#include "kaimana_custom.h"
#include "animations.h"


// local function declarations
int  pollSwitches(void);
void showStartup(void);
void setLEDRandomColor(int index);
int tourneypollSwitches(void);

boolean tournamentMode = false;
int holdTimeout = 0;
int p1_timer = 0;
int p2_timer = 0;
int p3_timer = 0;
int p4_timer = 0;
int k1_timer = 0;
int k2_timer = 0;
int k3_timer = 0;
int k4_timer = 0;

// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;


// the setup routine runs first and once each time power is applied to the Kaimana board
void setup() 
{                
  // light up all leds at boot to demonstrate everything is functional
	_STARTUP_ANIMATION
}




// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop() 
{
  unsigned long  ulTimeout;
  
    
  // initialize timeout value to now + some seconds
  ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
  

  // infinite loop of read switches, update LEDs and idle animation when necessary
  while(true)
  {
	  	if (tournamentMode != true)
		{
			// active -- poll switches and update leds
			if( pollSwitches() != 0 )
			{
				// some switches were active so reset idle timeout to now + some seconds
				ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
			}
			else
			{
				// no switches active so test for start of idle timeout  
				if( millis() > ulTimeout )
				{
					_IDLE_WALK_ANIMATION
				}  
			}
		}
	else
	{
		if( tourneypollSwitches() != 0 )
		{
			// some switches were active so reset idle timeout to now + some seconds
			ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
		}
	}    
    // delay a little to avoid flickering (yea, updates happens really, really fast!)
    //delay( MAIN_LOOP_DELAY );
  } 
}


// ==============================================================
//
//  local functions start here
//
// ==============================================================




// light up all leds at boot to demonstrate everything is functional
//

int pollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount;
  static int  i;  
  static int  j;  
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;
  static int  chargeunit;
  
  // reset LED status
  if (firsttime == 1)
  {
    for(i=0;i<LED_COUNT;++i)
    {
      iLED[i] = false;
      firsttime = 0;
    }
  }
  joystickDirection = ATTACK_NONE;
  // complex special case for joystick but it's worth the effort
  if(!digitalRead(PIN_RIGHT))
    joystickDirection |= ATTACK_RIGHT;
  if(!digitalRead(PIN_LEFT))
    joystickDirection |= ATTACK_LEFT;
  if(!digitalRead(PIN_DOWN))
    joystickDirection |= ATTACK_DOWN;
  if(!digitalRead(PIN_UP))
    joystickDirection |= ATTACK_UP;
  
  if(!digitalRead(PIN_RIGHT) || !digitalRead(PIN_LEFT)|| !digitalRead(PIN_DOWN) || !digitalRead(PIN_UP))
  {
    // switch is active
    if(iLED[LED_JOY] == true)
    {
      //maintain color while switch is active
      iLED[LED_JOY] = true;
	   
    }
    else
    {
      // select new color when switch is first activated
      setLEDRandomColor(LED_JOY);
      iLED[LED_JOY] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_JOY, BLACK);    
      iLED[LED_JOY] = false;
  }
  
  

  // clear results for switch activity
  switchActivity = ATTACK_NONE;
  
  // test switch and set LED based on result       // HOME = GUIDE
  if(!digitalRead(PIN_HOME))
  {
    // switch is active
    if(iLED[LED_HOME] == true)
    {
      //maintain color while switch is active
      iLED[LED_HOME] = true;
	    //Button hold to start tourneymode
    }
    else
    {
      // select new color when switch is first activated
      setLEDRandomColor(LED_HOME);
      iLED[LED_HOME] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_HOME, BLACK);    
      iLED[LED_HOME] = false;
	 // holdTimeout=0;
  }
  
  
  // test switch and set LED based on result
  if(!digitalRead(PIN_START))
  {    
    
    // switch is active
    if(iLED[LED_START] == true)
    {
      //maintain color while switch is active
      iLED[LED_START] = true;
	  	 //Button hold to start tourneymode
		holdTimeout += 1;
		if(holdTimeout == 2000)
		{
		tournamentMode = true;
		tourneyModeActivate();
		}	
    }
    else
    {
      // select new color when switch is first activated
      setLEDRandomColor(LED_START);
      iLED[LED_START] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_START, BLACK);    
      iLED[LED_START] = false;
	  holdTimeout=0;
  }
  
  
 // test switch and set LED based on result
  if(!digitalRead(PIN_SELECT))
  {
    
    
    // switch is active
    if(iLED[LED_SELECT] == true)
    {
	  chargeunit += 1;
	  
      //maintain color while switch is active
      iLED[LED_SELECT] = true;
    }
    else
    {
      // select new color when switch is first activated
      setLEDRandomColor(LED_SELECT);
      iLED[LED_SELECT] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_SELECT, BLACK);    
      iLED[LED_SELECT] = false;
	  chargeunit = 0;
  }


if(!digitalRead(PIN_P1))
  {
    switchActivity |= ATTACK_P1;    
    // switch is active
    if(iLED[LED_P1] == true){	  
	  megacharge(COLOR_RANDOM_8,p1_timer);
	  p1_timer++;
	}
    else
    {
      // select new color when switch is first activated
      //kaimana.setLED(LED_P1, COLOR_RANDOM_8); 
      iLED[LED_P1] = true;
	  p1_timer++;
  }
    }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P1, BLACK);    
      iLED[LED_P1] = false;
	  p1_timer=0;
  }


if(!digitalRead(PIN_P2))
  {
    switchActivity |= ATTACK_P2;
    
    // switch is active
    if(iLED[LED_P2] == true)
    {	  
	  megacharge(COLOR_RANDOM_4,p2_timer);
	  p2_timer++;
	}
    else
    {
      // select new color when switch is first activated
      //kaimana.setLED(LED_P1, COLOR_RANDOM_8); 
      iLED[LED_P2] = true;
	  p2_timer++;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P2, BLACK);    
      iLED[LED_P2] = false;
	  p2_timer=0;
  }
  

if(!digitalRead(PIN_P3))
  {
    switchActivity |= ATTACK_P3;
    
    // switch is active
    if(iLED[LED_P3] == true)
    {	  
	  float alpha = (pow(p3_timer, 1.7))/255;
      //maintain color while switch is active
      if(alpha >= 1){
		  float factor = millis()/1000.0;
		  float beta = 0.5* sin(factor*35)+0.5;
		  if(beta < 1){
    		  //kaimana.setLEDBrightness(LED_P3, COLOR_RANDOM_7,beta); 
			  kaimana.setALL(COLOR_RANDOM_5,beta);
		  }
		  delay(10);
	  }
	  else{
	  iLED[LED_P3] = true;
      //kaimana.setLEDBrightness( LED_P1,COLOR_RANDOM_8,alpha);
	  kaimana.setALL(COLOR_RANDOM_5,alpha); 
	  p3_timer++;
	  delay(50);		  
	  }

	}
    else
    {
      // select new color when switch is first activated
      //kaimana.setLED(LED_P1, COLOR_RANDOM_8); 
      iLED[LED_P3] = true;
	  p3_timer++;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P3, BLACK);    
      iLED[LED_P3] = false;
	  p3_timer=0;
  }
  


if(!digitalRead(PIN_P4))
  {
    switchActivity |= ATTACK_P4;
    
    // switch is active
    if(iLED[LED_P4] == true)
    {	  
	  float alpha = (pow(p4_timer, 1.7))/255;
      //maintain color while switch is active
      if(alpha >= 1){
		  float factor = millis()/1000.0;
		  float beta = 0.5* sin(factor*35)+0.5;
		  if(beta < 1){
    		  //kaimana.setLEDBrightness(LED_P4, COLOR_RANDOM_7,beta); 
			  kaimana.setALL(COLOR_RANDOM_3,beta);
		  }
		  delay(10);
	  }
	  else{
	  iLED[LED_P4] = true;
      //kaimana.setLEDBrightness( LED_P1,COLOR_RANDOM_8,alpha);
	  kaimana.setALL(COLOR_RANDOM_3,alpha); 
	  p4_timer++;
	  delay(50);		  
	  }

	}
    else
    {
      // select new color when switch is first activated
      //kaimana.setLED(LED_P1, COLOR_RANDOM_8); 
      iLED[LED_P4] = true;
	  p4_timer++;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P4, BLACK);    
      iLED[LED_P4] = false;
	  p4_timer=0;
  }


if(!digitalRead(PIN_K1))
  {
    switchActivity |= ATTACK_K1;
    
    // switch is active
    if(iLED[LED_K1] == true)
    {	  
	  float alpha = (pow(k1_timer, 1.7))/255;
      //maintain color while switch is active
      if(alpha >= 1){
		  float factor = millis()/1000.0;
		  float beta = 0.5* sin(factor*35)+0.5;
		  if(beta < 1){
    		  //kaimana.setLEDBrightness(LED_K1, COLOR_RANDOM_7,beta); 
			  kaimana.setALL(COLOR_RANDOM_1,beta);
		  }
		  delay(10);
	  }
	  else{
	  iLED[LED_K1] = true;
      //kaimana.setLEDBrightness( LED_P1,COLOR_RANDOM_8,alpha);
	  kaimana.setALL(COLOR_RANDOM_1,alpha); 
	  k1_timer++;
	  delay(50);		  
	  }

	}
    else
    {
      // select new color when switch is first activated
      //kaimana.setLED(LED_P1, COLOR_RANDOM_8); 
      iLED[LED_K1] = true;
	  k1_timer++;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K1, BLACK);    
      iLED[LED_K1] = false;
	  k1_timer=0;
  }

if(!digitalRead(PIN_K2))
  {
    switchActivity |= ATTACK_K2;
    
    // switch is active
    if(iLED[LED_K2] == true)
    {	  
	  float alpha = (pow(k2_timer, 1.7))/255;
      //maintain color while switch is active
      if(alpha >= 1){
		  float factor = millis()/1000.0;
		  float beta = 0.5* sin(factor*35)+0.5;
		  if(beta < 1){
    		  //kaimana.setLEDBrightness(LED_K2, COLOR_RANDOM_7,beta); 
			  kaimana.setALL(COLOR_RANDOM_6,beta);
		  }
		  delay(10);
	  }
	  else{
	  iLED[LED_K2] = true;
      //kaimana.setLEDBrightness( LED_P1,COLOR_RANDOM_8,alpha);
	  kaimana.setALL(COLOR_RANDOM_6,alpha); 
	  k2_timer++;
	  delay(50);		  
	  }

	}
    else
    {
      // select new color when switch is first activated
      //kaimana.setLED(LED_P1, COLOR_RANDOM_8); 
      iLED[LED_K2] = true;
	  k2_timer++;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K2, BLACK);    
      iLED[LED_K2] = false;
	  k2_timer=0;
  }
  
if(!digitalRead(PIN_K3))
  {
    switchActivity |= ATTACK_K3;
    
    // switch is active
    if(iLED[LED_K3] == true)
    {	  
	  float alpha = (pow(k3_timer, 1.7))/255;
      //maintain color while switch is active
      if(alpha >= 1){
		  float factor = millis()/1000.0;
		  float beta = 0.5* sin(factor*35)+0.5;
		  if(beta < 1){
    		  //kaimana.setLEDBrightness(LED_K3, COLOR_RANDOM_7,beta); 
			  kaimana.setALL(COLOR_RANDOM_7,beta);
		  }
		  delay(10);
	  }
	  else{
	  iLED[LED_K3] = true;
      //kaimana.setLEDBrightness( LED_P1,COLOR_RANDOM_8,alpha);
	  kaimana.setALL(COLOR_RANDOM_7,alpha); 
	  k3_timer++;
	  delay(50);		  
	  }

	}
    else
    {
      // select new color when switch is first activated
      //kaimana.setLED(LED_P1, COLOR_RANDOM_8); 
      iLED[LED_K3] = true;
	  k3_timer++;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K3, BLACK);    
      iLED[LED_K3] = false;
	  k3_timer=0;
  }
  // test switch and set LED based on result
if(!digitalRead(PIN_K4))
  {
    switchActivity |= ATTACK_K4;
    
    // switch is active
    if(iLED[LED_K4] == true)
    {	  
	  float alpha = (pow(k4_timer, 1.7))/255;
      //maintain color while switch is active
      if(alpha >= 1){
		  float factor = millis()/1000.0;
		  float beta = 0.5* sin(factor*35)+0.5;
		  if(beta < 1){
    		  //kaimana.setLEDBrightness(LED_K4, COLOR_RANDOM_7,beta); 
			  kaimana.setALL(COLOR_RANDOM_2,beta);
		  }
		  delay(10);
	  }
	  else{
	  iLED[LED_K4] = true;
      //kaimana.setLEDBrightness( LED_P1,COLOR_RANDOM_8,alpha);
	  kaimana.setALL(COLOR_RANDOM_2,alpha); 
	  k4_timer++;
	  delay(50);		  
	  }

	}
    else
    {
      // select new color when switch is first activated
      //kaimana.setLED(LED_P1, COLOR_RANDOM_8); 
      iLED[LED_K4] = true;
	  k4_timer++;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K4, BLACK);    
      iLED[LED_K4] = false;
	  k4_timer=0;
  }  



  // convert joystick, P1-P4, K1-K4 into a single unsigned int
  switchActivity = joystickDirection + switchActivity;
  kaimana.switchHistorySet(switchActivity);
  

  // test for combinations from most complext to least complex
  // test for switches in reverse order (newest to oldest)


  // combo #6
  // test for: Ultra 2 (Metsu Shoryuken)
  // combo is: DOWN, DOWN+RIGHT, RIGHT, DOWN, DOWN+RIGHT, RIGHT, RIGHT+K3
  if( kaimana.switchHistoryTest( COMBO_PATTERN_6A ) )
      animation_combo_6();

  // combo #5
  // test for: Ultra 1 (Metsu Hadouken)
  // combo is: DOWN, DOWN+RIGHT, RIGHT, <NONE>, DOWN, DOWN+RIGHT, RIGHT, RIGHT+P3
  if( kaimana.switchHistoryTest( COMBO_PATTERN_5A ) )
      animation_combo_5();

  // combo #4
  // test for: Super (Shinkuu Hadouken)
  // combo is: DOWN, DOWN+RIGHT, RIGHT, <NONE>, DOWN, DOWN+RIGHT, RIGHT, RIGHT+P1
  if( kaimana.switchHistoryTest( COMBO_PATTERN_4A ) )
      animation_combo_4();

  // combo #3
  // test for: Tatsumaki Senpukyaku (Hurricane Kick)
  // combo is: DOWN, DOWN+LEFT, LEFT, LEFT+K1 or LEFT+K2
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3A ) )
      animation_combo_3();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3B ) )
      animation_combo_3();

  // combo #2
  // test for: Ryu Shoryuken (Dragon Punch)
  // combo is: RIGHT, <NONE>, DOWN, DOWN+RIGHT, DOWN+RIGHT+P1 or DOWN+RIGHT+P2
  if( kaimana.switchHistoryTest( COMBO_PATTERN_2A ) )
      animation_combo_2();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_2B ) )
      animation_combo_2();

  // combo #1
  // test for: Ryu Hadouken (Fireball) 
  // combo is: DOWN, DOWN+RIGHT, RIGHT, RIGHT+P1 or RIGHT+P2  
  if( kaimana.switchHistoryTest( COMBO_PATTERN_1A ) )
      animation_combo_1();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_1B ) )
      animation_combo_1();


  // zero active switch counter (note: 4 way joystick counts as 1)
  iActiveSwitchCount = 0;
  
  // set LED color based on switch
  for(i=0;i<LED_COUNT;++i)
  {
    if(iLED[i] == true)
      ++iActiveSwitchCount;
  }  

  // update the leds with new/current colors in the array
  kaimana.updateALL();
  
  // return number of active switches
  return(iActiveSwitchCount);
}  

int tourneypollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount = 0;
  static int  i;
  static int  j;
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;

  // test switch and set LED based on result       // HOME = GUIDE
  if(!digitalRead(PIN_START))
  {
	  //Button hold to change idle animation
		holdTimeout += 1;
		//Button hold to start tourneymode		
		if(holdTimeout == 200)
		{
		tournamentMode = false;
		tourneyModeDeactivate();
		}
      ++iActiveSwitchCount;
	delay(10);	  
  }
  else
  {  	 
	holdTimeout=0;
  }
    return(iActiveSwitchCount);
}

 
