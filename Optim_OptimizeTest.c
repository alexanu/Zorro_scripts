// Parameter optimization Test ////////////////

#define METHOD	ASCENT
//#define METHOD	BRUTE
//#define METHOD	GENETIC

function run()
{
	set(PARAMETERS|TESTNOW);  // generate and use optimized parameters
	setf(TrainMode,METHOD);
	BarPeriod = 240;	// 4 hour bars
	LookBack = 500;
	StartDate = 2011;
	EndDate = 2019; 	// fixed simulation period
	NumWFOCycles = 5; // activate WFO
	NumCores = -1;	// multicore training
	
// measure the time
	static var Time = 0;
	if(Train && is(FIRSTINITRUN)) 
		Time = timer();
	if(Test && is(INITRUN) && is(TESTNOW)) 
		printf("\nTime for optimizing >>> %.3f sec <<<",(timer()-Time)/1000);

// portfolio loop
	while(asset(loop("EUR/USD","USD/JPY","GBP/USD"))) 
	{
// calculate the buy/sell signal
		vars Price = series(price());
		vars Filtered = series(BandPass(Price,optimize(30,20,40,5),0.5));
		vars Signal = series(FisherN(Filtered,500));
		var Threshold = optimize(1,0.6,1.4,0.2);

// buy and sell
		Stop = optimize(4,2,20,2) * ATR(100);
		Trail = optimize(4,2,20,2) * ATR(100);
		if(crossUnder(Signal,-Threshold))
			enterLong(); 
		else if(crossOver(Signal,Threshold))
			enterShort();
	}
} 