// Detrending and shuffling ///////////////////////
// Used for removing bias from parameters, trades, indicators & verifying the robustness of a strategy

// Black - original prices
// Blue - detrended prices
// Red - inverted prices
// Grey - shuffled prices

function run()
{
	set(PLOTNOW|LEAN|PRELOAD); // reload prices after any cycle, LEAN flag must be set for Detrend=SHUFFLE
	StartDate = 2012; 
	BarPeriod = 1440;
	LookBack = 0;
	NumTotalCycles = 10;


	if(TotalCycle == 1) {
		Detrend = CURVE; // Detrend the historical price data on loading
		plot("Detrend",priceClose(),MAIN|LINE,BLUE);		
	} else if(TotalCycle == 2) {
		Detrend = INVERT; // used for a reality check of a symmetric system 
		plot("Invert",priceClose(),MAIN|LINE,RED);		
	} else if(TotalCycle <= NumTotalCycles-1) {
		Detrend = SHUFFLE; //|PEAK|VALLEY; Randomize the price curve by shuffling the price ticks
		plot(strf("Shuffle%d", TotalCycle),priceClose(),MAIN,GREY); //color(100*TotalCycle/NumTotalCycles,BLUE,RED,GREEN));
	}

	Detrend = SHUFFLE;
	plot(strf("#Cycle_%d", TotalCycle), priceClose(), MAIN, color(100*TotalCycle/NumTotalCycles, BLUE, RED, GREEN));	
}
