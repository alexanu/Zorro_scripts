function run()	// simple mean reversion system
{	
set(PLOTNOW);
// PlotBars = 800; // number of bars to plot in the chart. Default - all
vars Price = series(price());	

// highpass filter dampens all cycles above 30 bars …
// ... and thus removes the trend from the price curve
vars Filtered = series(HighPass(Price,30));	
vars Signal = series(FisherN(Filtered,500)); // normalized by the Fisher transformation …
// This allows us to determine fixed thresholds at 1 and -1 for separating the tails from the resulting bell curve
var Threshold = 1.0;	
	
Stop = ATR(100);

if(Hurst(Price,500) < 0.5 ) {	// Above 0.5 begins momentum regime and below 0.5 mean reversion regime.
	if(crossUnder(Signal,-Threshold)) // If the price enters a tail in any direction, …
			enterLong(1);	// … anticipation that it will soon return into the bell’s belly.
	else if(crossOver(Signal,Threshold)) enterShort(1); 
	}	

// plot("Price",Price,1,RED);
// plot("No trend",Filtered,1,BLUE);
// plot("Normalized",Signal,1,GREEN);
// plot("Mean rev",Hurst(Price,500),1,BLACK);

}	