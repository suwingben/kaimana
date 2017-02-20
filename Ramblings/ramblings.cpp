
/*	
void buttonDetect(Button button)
{
    switchActivity |= ATTACK_K1;digitalWrite(PIN_START, LOW);
    // switch is active
    if(iLED[button.led] == true)
    {
		//maintain color while switch is active
		iLED[button.led] = true;		
    }
    else
    {
      // select new color when switch is first activated
	  setLEDRandomColor(button.led);
      iLED[button.led] = true;
    }
 	
}

if(!digitalRead(K1.pin))
	{
		buttonDetect(K1);
	}		
	  else
	{
      // switch is inactive
	  
      kaimana.setLED(K1.led, BLACK);          
	  iLED[K1.led] = false;
	}*/
	
int pollSwitches(void)
{
	for
}

  for(i=0;i<LED_COUNT;++i)
  {
    if(iLED[i] == true)
	{
		++iActiveSwitchCount;
		mySerial.print(1);		
	}
  }

int checkbutton()
{
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
      setLEDRandomColor(LED_HOME);
      iLED[LED_HOME] = true;
    }
  }
  else
  {
      // switch is inactive
      kaimana.setLED(LED_HOME, BLACK);
      iLED[LED_HOME] = false;
  }
}