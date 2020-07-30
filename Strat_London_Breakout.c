function run()	
{	
	StartDate = 20170101;	
	EndDate = 20181231;	
	BarPeriod = 10;	
	LookBack = 100;	
		
	asset("EUR/USD");	
		
	vars Price = series(price());	
	vars Highs = series(priceHigh());	
	vars Lows = series(priceLow());	
		
	int fracTime = 7;	//short term ... 
	var fHigh = FractalHigh(Highs, fracTime); // ... highs and ... 
	var fLow = FractalLow(Lows, fracTime);	// ... lows	
	
	static var longEntry, shortEntry;	// Static is important
	if(fHigh != 0 or fLow != 0)	
           {	
           shortEntry = Lows[0];	
           longEntry = Highs[0];	
           }	

	MaxLong = MaxShort = 1;	
	Spread = Commission = Slippage = RollLong = RollShort = 0;	
	EntryTime = 3;	
	ExitTime = 12;	
	Stop = 4*ATR(40);	
	Trail = Stop;	
	
	static var fHighCurrent, fLowCurrent;	// Static is important
	if(fHigh != 0) fHighCurrent = fHigh;	
	if(fLow != 0) fLowCurrent = fLow;	

	vars trendFilter = series(LowPass(Price, 100));	

	if(lhour(WET) >= 8 and lhour(WET) <= 17  // London Session
		and between(priceClose(0), fLowCurrent, fHighCurrent))	
           {	
           if (Price[0] > trendFilter[0])	
				{	
				Entry = longEntry; // go long on recent high
				enterLong();	
				}	
           if (Price[0] < trendFilter[0])	
				{	
				Entry = shortEntry;	
				enterShort();	
				}	
           }	

	set(PLOTNOW);	
	setf(PlotMode, PL_FINE);	
	PlotBars = 400; // number of bars to plot in the chart. Default - all

	ColorDD = ColorEquity = 0; // don't plot Equty and drawdowns

	plot("Recent High", fHighCurrent, MAIN|DOT, BLUE);	
	plot("Recent Low", fLowCurrent, MAIN|DOT, RED);	
	plot("LowPass", trendFilter, MAIN, GREEN);	
}	