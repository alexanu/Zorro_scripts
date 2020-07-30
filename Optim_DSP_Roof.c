// #define METHOD	ASCENT
#define METHOD	BRUTE
//#define METHOD	GENETIC


function run()
{
	set(PLOTNOW,PARAMETERS);
	setf(TrainMode,METHOD);

	// PlotBars = 400;
	NumWFOCycles = 5;
	StartDate= 2010;
	BarPeriod = 60;
	LookBack = 150;
	// NumSampleCycles = 4;
	
	asset("EUR/USD");

	int CutoffLow = optimize(10,10,30,5);
	int CutoffHigh = optimize(2, 1.5, 5, 0.5)*CutoffLow;
	vars filter = series(Roof(series(price()), CutoffLow, CutoffHigh));

	Stop = Trail = 3*ATR(100);
	TrailSlope = 50;

	if(NumOpenTotal == 0 && valley(filter)) enterLong();
	if(NumOpenTotal == 0 && peak(filter)) enterShort();
	
	// plot("Stp",TradeStopLimit,DOT,BLUE);
	plot("Trades",NumWinTotal+NumLossTotal,1,RED);



	// plot("Roof", filter, NEW, RED);
	// plot("Roof2", series(Roof(series(price()), 50, 100)), 0, YELLOW);

}