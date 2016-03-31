// LEDS blink on randomly
void starryStartup(void)	
{
	static int i;
	static int trackled[]= {1,2,3,4,5,6,7,8};
	int delay_val;
	
	kaimana.setALL( BLACK ); //set everything to OFF | this is for when you are calling from a button combination the buttons pressed do not remain on
	
	for (i = 0; i < 8; ++i) //randomizing the array
    {     
      int rand = random(1,8);
	  int temp = trackled[i];
	  trackled[i] = trackled[rand];
	  trackled[rand] = temp;
    }
	
	for (i = 0; i < 8; ++i) //managing delay separately so we can simplify usage
    {     
		if (i != 7)
		{
			delay_val = BOOT_COLOR_DELAY;
		}
		else
		{
			delay_val = BOOT_COMPLETE_DELAY;
		}
	  
		switch(trackled[i])
		{
			case 1:
			kaimana.setLED(LED_P4, MAGENTA);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 2:
			kaimana.setLED(LED_P3, MAGENTA);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 3:
			kaimana.setLED(LED_P2, MAGENTA);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 4:
			kaimana.setLED(LED_P1, MAGENTA);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 5:
			kaimana.setLED(LED_K1, MAGENTA);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 6:
			kaimana.setLED(LED_K2, MAGENTA);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 7:
			kaimana.setLED(LED_K3, MAGENTA);
			kaimana.updateALL();
			delay( delay_val );
			break;
			case 8:
			kaimana.setLED(LED_K4, MAGENTA);
			kaimana.updateALL();
			delay( delay_val );
			break;
			default:   // any undefined value so discard data and set led to BLACK
			kaimana.setALL( BLACK );    
			kaimana.updateALL();
			delay( delay_val );
			break;
		}
		
	}
}