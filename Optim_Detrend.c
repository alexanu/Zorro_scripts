// Detrending and shuffling ///////////////////////
// Black - original prices
// Blue - detrended prices
// Red - inverted prices
// Grey - shuffled prices

function run()
{
	set(PLOTNOW|LEAN|PRELOAD); // reload prices after any cycle
	StartDate = 2012; 
	BarPeriod = 1440;
	LookBack = 0;
	NumTotalCycles = 10;

	if(TotalCycle == 1) {
		Detrend = CURVE; 
		plot("Detrend",priceClose(),MAIN|LINE,BLUE);		
	} else if(TotalCycle == 2) {
		Detrend = INVERT; 
		plot("Invert",priceClose(),MAIN|LINE,RED);		
	} else if(TotalCycle <= NumTotalCycles-1) {
		Detrend = SHUFFLE; //|PEAK|VALLEY; 
		plot(strf("Shuffle%d", TotalCycle),priceClose(),MAIN,GREY); //color(100*TotalCycle/NumTotalCycles,BLUE,RED,GREEN));
	}
}
