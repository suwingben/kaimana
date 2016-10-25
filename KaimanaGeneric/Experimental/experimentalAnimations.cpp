void blinkMultiExperimental(int index)
{
	int iR = random(1,256);
	int iG = random(1,256);
	int iB = random(1,256);
	
	int variance = abs(iR-iG-iB);
	if(variance <100)
	{
		kaimana.setLED(index, iR,iG,iB);
		delay( FAST_COLOR_DELAY );
		kaimana.updateALL();
		kaimana.setLED(index, BLACK);		
	}
}