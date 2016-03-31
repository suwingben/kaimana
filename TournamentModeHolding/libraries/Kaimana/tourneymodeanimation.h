// tourneymode animation

void tourneyMode(void)
{
	#define  T_DELAY      500    // value in miliseconds
	kaimana.setALL(RED);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K4, BLACK);
	kaimana.setLED(LED_P4, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );	
	
	kaimana.setLED(LED_K3, BLACK);
	kaimana.setLED(LED_P3, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K2, BLACK);
	kaimana.setLED(LED_P2, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
	
	kaimana.setLED(LED_K1, BLACK);
	kaimana.setLED(LED_P1, BLACK);
	kaimana.updateALL();
	delay( T_DELAY );
}