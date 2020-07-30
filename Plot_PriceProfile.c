#include <profile.c>	
function run()	
{	
	vars Trend = series(LowPass(series(price()),500));	
	if(valley(Trend)) {	
		plotPriceProfile(40,0);	// type=0: plot price difference to the first bar
		enterLong();	
	} else if(peak(Trend)) {	
		plotPriceProfile(40,2);	// type=2: plot negative price difference to the first bar (for short trades)
		enterShort();	
		}	
}	

