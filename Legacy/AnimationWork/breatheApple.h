//breatheApple.h


//Simulates the Apple power LED breathing pattern as described in http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/

void breatheApple(int iR, int iG, int iB)
{
	int index;
	
	while(true)
	{
	int breatheSpeed= 1;
	float factor = millis()/1000.0;

		int alpha = 127.0 + 127 * sin((factor*.50)* PI );
		//STROOOBE int alpha = 127.0 + 127 * sin((factor*3)* PI );
		// set all leds in the array to the RGB color passed to this function
		if (alpha != 0 ){
		for(index=0;index<LED_COUNT;++index)
		{
			kaimana.setLEDBrightness( index, iR, iG, iB,alpha );
		}
		
		// update the leds with new/current colors in the array
		kaimana.updateALL();
		Serial.print(alpha);
	Serial.print("\n");}
		//delay(100);
		
	}
  }