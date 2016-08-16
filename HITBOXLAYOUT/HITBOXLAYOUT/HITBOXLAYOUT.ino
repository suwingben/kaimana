//  holdingTournamentMode.ino
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
//	Revised:  March	   7, 2016	  info // mightyjrmods.com -- Added startup animations

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
boolean tournamentMode = false;
int holdTimeout = 0;

// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;


// the setup routine runs first and once each time power is applied to the Kaimana board
void setup() 
{                
  // light up all leds at boot to demonstrate everything is functional
  defaultStartup();
 
}



// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop() 
{
  unsigned long  ulTimeout;
  
    
  // initialize timeout value to now + some seconds
  ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
  
 // infinite loop of read switches, update LEDs and idle animation when necessary
  while( true)
  {
    // active -- poll switches and update leds
	
	if (tournamentMode != true)
	{
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
			animation_idle();
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
  }
    // delay a little to avoid flickering (yea, updates happens really, really fast!)
    delay( MAIN_LOOP_DELAY );
 
}


// ==============================================================
//
//  local functions start here
//
// ==============================================================


// light up all leds at boot to demonstrate everything is functional
//

// set LED to one of 8 predefined colors selected at random
//
void setLEDRandomColor(int index)
{
  switch(random(1,7))    // pick a random color between 1 and 7
  {
    case 1:
      kaimana.setLED(index, COLOR_RANDOM_1);
      break;
    case 2:
      kaimana.setLED(index, COLOR_RANDOM_2);
      break;
    case 3:
      kaimana.setLED(index, COLOR_RANDOM_3);
      break;
    case 4:
      kaimana.setLED(index, COLOR_RANDOM_4);
      break;
    case 5:
      kaimana.setLED(index, COLOR_RANDOM_5);
      break;
    case 6:
      kaimana.setLED(index, COLOR_RANDOM_6);
      break;
    case 7:
      kaimana.setLED(index, COLOR_RANDOM_7);
      break;
   
    default:   // any undefined value so discard data and set led to BLACK
      kaimana.setLED(index, BLACK);    
      break;
  }  
}



int pollSwitches(void)
{
  static int  iLED[LED_COUNT];
  static int  iActiveSwitchCount;
  static int  i;  
  static int  j;  
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;

  // reset LED status
  if (firsttime == 1)
  {
    for(i=0;i<LED_COUNT;++i)
    {
      iLED[i] = false;
      firsttime = 0;
    }
  }

  // read arduino pins and save results in the mapped LED if button is pressed (pin grounded)

  // complex special case for joystick but it's worth the effort
  joystickDirection = ATTACK_NONE;

  if(!digitalRead(PIN_RIGHT))    
    joystickDirection |= ATTACK_RIGHT;
  if(!digitalRead(PIN_LEFT))
    joystickDirection |= ATTACK_LEFT;
  if(!digitalRead(PIN_DOWN))
    joystickDirection |= ATTACK_DOWN;
  if(!digitalRead(PIN_UP))
    joystickDirection |= ATTACK_UP;

  switch(joystickDirection)
  {
    case ATTACK_RIGHT:    // right
      kaimana.setLED(LED_RIGHT, PURPLE); 
      iLED[LED_RIGHT] = true;
      break;
    case ATTACK_LEFT:    // left
      kaimana.setLED(LED_LEFT, PURPLE); 
      iLED[LED_LEFT] = true;
      break;
    case ATTACK_DOWN:    // down
      kaimana.setLED(LED_DOWN, PURPLE);
      iLED[LED_DOWN] = true;
      break;
    case ATTACK_DOWN + ATTACK_RIGHT:    // down + right
      kaimana.setLED(LED_DOWN, PURPLE); 
      iLED[LED_DOWN] = true;
      break;
    case ATTACK_DOWN + ATTACK_LEFT:    // down + left
      kaimana.setLED(LED_DOWN, PURPLE); 
      iLED[LED_DOWN] = true;
      break;
    case ATTACK_UP:    // up
      kaimana.setLED(LED_UP, PURPLE); 
      iLED[LED_UP] = true;
      break;
    case ATTACK_UP + ATTACK_RIGHT:    // up + right
      kaimana.setLED(LED_UP, PURPLE); 
      iLED[LED_UP] = true;
      break;
    case ATTACK_UP + ATTACK_LEFT:   // up + left
      kaimana.setLED(LED_UP, PURPLE); 
      iLED[LED_UP] = true;
      break;
    default:   // zero or any undefined value on an 8 way stick like UP+DOWN which is not happening on my watch
  
   
      break;
  }  
  
  

  // clear results for switch activity
  switchActivity = ATTACK_NONE;
  
  // test switch and set LED based on result       // HOME = GUIDE
  if(!digitalRead(PIN_LEFT))
  {
    // switch is active
    if(iLED[LED_LEFT] == true)
    {
      //maintain color while switch is active
      iLED[LED_LEFT] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_LEFT, PURPLE);
      iLED[LED_LEFT] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_LEFT, RED);    
      iLED[LED_LEFT] = false;
  }


  // test switch and set LED based on result    
  if(!digitalRead(PIN_DOWN))
  {
    // switch is active
    if(iLED[LED_DOWN] == true)
    {
      //maintain color while switch is active
      iLED[LED_DOWN] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_DOWN, PURPLE);
      iLED[LED_DOWN] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_DOWN,RED);    
      iLED[LED_DOWN] = false;
  }

    // test switch and set LED based on result   
  if(!digitalRead(PIN_RIGHT))
  {
    // switch is active
    if(iLED[LED_RIGHT] == true)
    {
      //maintain color while switch is active
      iLED[LED_RIGHT] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_RIGHT,PURPLE);
      iLED[LED_RIGHT] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_RIGHT,RED);    
      iLED[LED_RIGHT] = false;
  }

if(!digitalRead(PIN_UP))
  {
    switchActivity |= ATTACK_UP;
    // switch is active
    if(iLED[LED_UP] == true)
    {
    //maintain color while switch is active
    iLED[LED_UP] = true;
    
    }
    else
    {
      // select new color when switch is first activated
      
   kaimana.setLED(LED_UP, PURPLE);
      iLED[LED_UP] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_UP, RED);    
      
    iLED[LED_UP] = false;
  }

  // test switch and set LED based on result
  if(!digitalRead(PIN_START))
  {
  //Button hold to start tourneymode
	holdTimeout += 1;
	if(holdTimeout == 2000)
	{
	  tournamentMode = true;
	  tourneyModeActivate();
	}
    // switch is active
    if(iLED[LED_START] == true)
    {
      //maintain color while switch is active
      iLED[LED_START] = true;
	  
    }
    else
    {
      // select new color when switch is first activated
      holdTimeout = 0;
      setLEDRandomColor(LED_START);
      iLED[LED_START] = true;
	  
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_START, BLACK);    
      iLED[LED_START] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P1))
  {
    switchActivity |= ATTACK_P1;
    // switch is active
    if(iLED[LED_P1] == true)
    {
		//maintain color while switch is active
		iLED[LED_P1] = true;
		
    }
    else
    {
      // select new color when switch is first activated
      
	  kaimana.setLED(LED_P1, PURPLE);
      iLED[LED_P1] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P1, RED);    
      
	  iLED[LED_P1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P2))
  {
    switchActivity |= ATTACK_P2;
    
    // switch is active
    if(iLED[LED_P2] == true)
    {
      //maintain color while switch is active
      iLED[LED_P2] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P2, PURPLE);
      iLED[LED_P2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P2, RED);    
      iLED[LED_P2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P3))
  {
    switchActivity |= ATTACK_P3;
    
    // switch is active
    if(iLED[LED_P3] == true)
    {
      //maintain color while switch is active
      iLED[LED_P3] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P3, PURPLE);
      iLED[LED_P3] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P3, RED);    
      iLED[LED_P3] = false;
  }
  

  // test switch and set LED based on result
  if(!digitalRead(PIN_P4))
  {
    switchActivity |= ATTACK_P4;
    
    // switch is active
    if(iLED[LED_P4] == true)
    {
      //maintain color while switch is active
      iLED[LED_P4] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_P4, PURPLE);
	  
      iLED[LED_P4] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_P4, RED);    
      iLED[LED_P4] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K1))
  {
    switchActivity |= ATTACK_K1;
    
    // switch is active
    if(iLED[LED_K1] == true)
    {
      //maintain color while switch is active
      iLED[LED_K1] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K1, PURPLE);
      iLED[LED_K1] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K1, RED);    
      iLED[LED_K1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K2))
  {
    switchActivity |= ATTACK_K2;
    
    // switch is active
    if(iLED[LED_K2] == true)
    {
      //maintain color while switch is active
      iLED[LED_K2] = true;
    }
    else
    {
      // select new color when switch is first activated
     kaimana.setLED(LED_K2, PURPLE);
      iLED[LED_K2] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K2, RED);    
      iLED[LED_K2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K3))
  {
    switchActivity |= ATTACK_K3;
    
    // switch is active
    if(iLED[LED_K3] == true)
    {
      //maintain color while switch is active
      iLED[LED_K3] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K3, PURPLE);
      iLED[LED_K3] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K3, RED);    
      iLED[LED_K3] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K4))
  {
    switchActivity |= ATTACK_K4;
    
    // switch is active
    if(iLED[LED_K4] == true)
    {
      //maintain color while switch is active
      iLED[LED_K4] = true;
    }
    else
    {
      // select new color when switch is first activated
      kaimana.setLED(LED_K4, PURPLE);
      iLED[LED_K4] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_K4, RED);    
      iLED[LED_K4] = false;
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
  if( kaimana.switchHistoryTest( COMBO_PATTERN_4B ) )
      animation_combo_4();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_4C ) )
      animation_combo_4();

  // combo #3
  // test for: Tatsumaki Senpukyaku (Hurricane Kick)
  // combo is: DOWN, DOWN+LEFT, LEFT, LEFT+K1 or LEFT+K2
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3A ) )
      animation_combo_3();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3B ) )
      animation_combo_3();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3C ) )
      animation_combo_3();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3D ) )
      animation_combo_3();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3E ) )
      animation_combo_3();
  if( kaimana.switchHistoryTest( COMBO_PATTERN_3F ) )
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
  if( kaimana.switchHistoryTest( COMBO_PATTERN_1C ) )
      animation_combo_1();
	 if( kaimana.switchHistoryTest( COMBO_PATTERN_1D ) )
      animation_combo_1();
   if( kaimana.switchHistoryTest( COMBO_PATTERN_1E ) )
      animation_combo_1();
   if( kaimana.switchHistoryTest( COMBO_PATTERN_1F ) )
      animation_combo_1();
  
	  //Tournament mode
/*   if( kaimana.switchHistoryTest( TOURNAMENT_MODE ) )
  {
	  if (tournamentMode != true)
	  {
		  tournamentMode = true;
		  tourneyMode
	  }
	  else
	  {
		  
		  tournamentMode = false;
	  }
  } */
  

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
  static int  iActiveSwitchCount;
  static int  i;  
  static int  j;  
  static int  firsttime;
  static uint16_t  joystickDirection;
  static uint16_t  switchActivity;

  // reset LED status
  if (firsttime == 1)
  {
    for(i=0;i<LED_COUNT;++i)
    {
      iLED[i] = false;
      firsttime = 0;
    }
  }

  // read arduino pins and save results in the mapped LED if button is pressed (pin grounded)

  // complex special case for joystick but it's worth the effort
  joystickDirection = ATTACK_NONE;

  if(!digitalRead(PIN_RIGHT))    
    joystickDirection |= ATTACK_RIGHT;
  if(!digitalRead(PIN_LEFT))
    joystickDirection |= ATTACK_LEFT;
  if(!digitalRead(PIN_DOWN))
    joystickDirection |= ATTACK_DOWN;
  if(!digitalRead(PIN_UP))
    joystickDirection |= ATTACK_UP;

  switch(joystickDirection)
  {
    case ATTACK_RIGHT:    // right
    
      iLED[LED_RIGHT, RED] = true;
      break;
    case ATTACK_LEFT:    // left
      iLED[LED_LEFT, RED] = true;
      break;
    case ATTACK_DOWN:    // down
      iLED[LED_DOWN, RED] = true;
      break;
    case ATTACK_DOWN + ATTACK_RIGHT:    // down + right
      iLED[LED_DOWN, RED] = true;
      break;
    case ATTACK_DOWN + ATTACK_LEFT:    // down + left
      iLED[LED_DOWN, RED] = true;
      break;
    case ATTACK_UP:    // up
      iLED[LED_UP, RED] = true;
      break;
    case ATTACK_UP + ATTACK_RIGHT:    // up + right
      iLED[LED_UP, RED] = true;
      break;
    case ATTACK_UP + ATTACK_LEFT:   // up + left
      iLED[LED_UP, RED] = true;
      break;
    default:   // zero or any undefined value on an 8 way stick like UP+DOWN which is not happening on my watch
      
      break;
  }  

//DIRECTIONAL LEDS
  
   kaimana.setLED(LED_DOWN,RED);
   kaimana.setLED(LED_UP,RED);
   kaimana.setLED(LED_LEFT,RED);      
   kaimana.setLED(LED_RIGHT ,RED);  
  
  
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
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_HOME] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_HOME] = false;
  }


  // test switch and set LED based on result    // SELECT = BACK 
  if(!digitalRead(PIN_SELECT))
  {
    // switch is active
    if(iLED[LED_SELECT] == true)
    {
      //maintain color while switch is active
      iLED[LED_SELECT] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_SELECT] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_SELECT] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_START))
  {
  
    // switch is active
	//Button hold to stop tourneymode
	holdTimeout += 1;
	if(holdTimeout == 2000)
	{
	  tournamentMode = false;
	  tourneyModeDeactivate();
	}
    if(iLED[LED_START] == true)
    {
      //maintain color while switch is active
      iLED[LED_START] = true;
    }
    else
    {
      // select new color when switch is first activated
      holdTimeout = 0;
      iLED[LED_START] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_START] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P1))
  {
    switchActivity |= ATTACK_P1;
    
    // switch is active
    if(iLED[LED_P1] == true)
    {		
		
	  iLED[LED_P1] = true;
    }
    else
    {    
	iLED[LED_P1] = true;
    
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_P1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P2))
  {
    switchActivity |= ATTACK_P2;
    
    // switch is active
    if(iLED[LED_P2] == true)
    {
      //maintain color while switch is active
      iLED[LED_P2] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_P2] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_P2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_P3))
  {
    switchActivity |= ATTACK_P3;
    
    // switch is active
    if(iLED[LED_P3] == true)
    {
      //maintain color while switch is active
      iLED[LED_P3] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_P3] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_P3] = false;
  }
  

  // test switch and set LED based on result
  if(!digitalRead(PIN_P4))
  {
    switchActivity |= ATTACK_P4;
    
    // switch is active
    if(iLED[LED_P4] == true)
    {
      //maintain color while switch is active
      iLED[LED_P4] = true;
    }
    else
    {
      // select new color when switch is first activated
	  
      iLED[LED_P4] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_P4] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K1))
  {
    switchActivity |= ATTACK_K1;
    
    // switch is active
    if(iLED[LED_K1] == true)
    {
      //maintain color while switch is active
      iLED[LED_K1] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K1] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_K1] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K2))
  {
    switchActivity |= ATTACK_K2;
    
    // switch is active
    if(iLED[LED_K2] == true)
    {
      //maintain color while switch is active
      iLED[LED_K2] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K2] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_K2] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K3))
  {
    switchActivity |= ATTACK_K3;
    
    // switch is active
    if(iLED[LED_K3] == true)
    {
      //maintain color while switch is active
      iLED[LED_K3] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K3] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_K3] = false;
  }


  // test switch and set LED based on result
  if(!digitalRead(PIN_K4))
  {
    switchActivity |= ATTACK_K4;
    
    // switch is active
    if(iLED[LED_K4] == true)
    {
      //maintain color while switch is active
      iLED[LED_K4] = true;
    }
    else
    {
      // select new color when switch is first activated
      iLED[LED_K4] = true;
    }
  }
  else
  {
      // switch is inactive
      iLED[LED_K4] = false;
  }



  // convert joystick, P1-P4, K1-K4 into a single unsigned int

  

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
	
	//Tournament mode
	// Adding a custom animation when pressing buttons


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



