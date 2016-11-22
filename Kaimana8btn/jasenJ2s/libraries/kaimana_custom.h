
//  kaimana_custom.h Generated from jasensCustoms.com Kaimana Khameleon Code Generator
//  KK Code Generator: http://brightstick.freecade.org
//  Code is provided for entertainment purposes and use with the Kaimana Khameleon and Panzer Fight Stick 2.
//  Code may be copied, modified, resused with this Copyright notice.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Based on code originally released by ParadiseArcadeShop.com
//  Generator Created:  November 4, 2015    jasenhicks // jasenscustoms.com -- Cavalier Mannitude Encouragement
//
// THIS FILE GENERATED ON: Friday 26th of August 2016 09:44:40 PM


#ifndef __kaimana_local_h__
#define __kaimana_local_h__
#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana.h"

//ON BUTTON STATE
#define LED_JOY_COLOR_ON 255,0,0
#define LED_P1_COLOR_ON 0,220,220
#define LED_P2_COLOR_ON 0,220,220
#define LED_P3_COLOR_ON 0,220,220
#define LED_P4_COLOR_ON 0,220,220
#define LED_K1_COLOR_ON 0,220,220
#define LED_K2_COLOR_ON 0,220,220
#define LED_K3_COLOR_ON 0,220,220
#define LED_K4_COLOR_ON 0,220,220
#define LED_SELECT_COLOR_ON 127,0,220
#define LED_HOME_COLOR_ON 127,0,220
#define LED_START_COLOR_ON 127,0,220


//OFF BUTTON STATE 
#define LED_JOY_COLOR_OFF 255,0,0
#define LED_P1_COLOR_OFF 127,0,220
#define LED_P2_COLOR_OFF 127,0,220
#define LED_P3_COLOR_OFF 127,0,220
#define LED_P4_COLOR_OFF 127,0,220
#define LED_K1_COLOR_OFF 255,0,0
#define LED_K2_COLOR_OFF 255,0,0
#define LED_K3_COLOR_OFF 255,0,0
#define LED_K4_COLOR_OFF 255,0,0
#define LED_SELECT_COLOR_OFF 255,0,0
#define LED_HOME_COLOR_OFF 255,0,0
#define LED_START_COLOR_OFF 255,0,0


//RANDOM COLORS SET
#define COLOR_RANDOM_1 255,0,0
#define COLOR_RANDOM_2 255,255,0
#define COLOR_RANDOM_3 255,255,255
#define COLOR_RANDOM_4 0,0,255
#define COLOR_RANDOM_5 0,255,255
#define COLOR_RANDOM_6 255,0,255
#define COLOR_RANDOM_7 127,255,0
#define COLOR_RANDOM_8 255,0,127
  
//BOOT AND IDLE SEQUENCE TIMING
#define  BOOT_COLOR_DELAY         250
#define  BOOT_COMPLETE_DELAY      500
#define  MAIN_LOOP_DELAY           50
#define IDLE_TIMEOUT_SECONDS       5
#define IDLE_ANIMATION_DELAY       6
#define BRIGHTNESS                 1

//LED INDEX
#define  LED_P4         15
#define  LED_P4_B       16
#define  LED_P3         13
#define  LED_P3_B       14
#define  LED_P2         11    
#define  LED_P2_B       12
#define  LED_P1         9
#define  LED_P1_B       10
#define  LED_JOY        0xFF    
#define  LED_K4         0        
#define  LED_K4_B       1
#define  LED_K3         2 
#define  LED_K3_B       3
#define  LED_K2         4
#define  LED_K2_B       5
#define  LED_K1         6
#define  LED_K1_B       7
#define  LED_SELECT     17
#define  LED_SELECT_B   18
#define  LED_HOME       19
#define  LED_HOME_B     20
#define  LED_START      21
#define  LED_START_B    22
#define  LED_COUNT      23

#endif