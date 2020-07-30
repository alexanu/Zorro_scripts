#include <profile.c>	

#define METHOD	ASCENT
//#define METHOD	BRUTE
//#define METHOD	GENETIC

// trailing stop moves closer and closer to recent price as new highs are made

function run()	
	{	

	set(PARAMETERS,LOGFILE,PLOTNOW);  // generate and use optimized parameters
	setf(TrainMode,METHOD);
	StartDate = 2015;	
	LookBack = 500 + UnstablePeriod; // for optimizing time periods, LookBack = max possible value (here, TimeCycle 100 * TimeFactor 5)	

	var AtrLen = 3;	
	var AtrMult = 2;	
	var AccelInit = 0.02;	
	var AccelStep = 0.02;	
	var AccelMax = 0.2;	
	var Stp;	

	static var Accel;	
	static var Hihi, Lolo;	

	vars Price = series(price());	
	// When parameters affect each other ...
	// ... for instance, two time periods for a crossover of two moving averages ...
		// optimize only one time period, and …
		// … optimize a multiplication factor for the other.
	int fastPeriod = optimize(50, 10, 100, 10);	//set up moving averages
	int slowPeriod = optimize(2, 1.5, 5, 0.5)*fastPeriod;	
	vars FastMA = series(EMA(Price, fastPeriod));	
	vars SlowMA = series(EMA(Price, slowPeriod));	
	vars mmi = series(MMI(Price, slowPeriod));	//set up Market Meanness Index

	StartDate = 20140801;	

	if (is(INITRUN)) Accel = AccelInit;	

	if (NumOpenLong + NumPendingLong + NumOpenShort + NumPendingShort == 0) {	
			if (crossOver(FastMA, SlowMA) and falling(mmi)) {	
				exitShort();	
				// Initial stop is at low of entry bar minus ATR multiple (e.g. 2)
				enterLong(0,  0, priceLow()  - AtrMult*ATR(AtrLen));	
				Accel = AccelInit;	
				Hihi = priceHigh();	
				}	
			if (crossUnder(FastMA, SlowMA) and falling(mmi)) {	
				exitLong();	
				// Initial stop is at low of entry bar minus ATR multiple (e.g. 2)
				enterShort(0, 0, priceHigh() + AtrMult*ATR(AtrLen));	
				Accel = AccelInit;	
				Lolo = priceLow();	
				}	
			}	

	for(open_trades) {	
			Stp = 0;	
			if (TradeIsLong) {	
				TradeStopLimit = min(priceLow(), TradeStopLimit +  Accel*(Hihi-TradeStopLimit));
				// With every new bar, stop is moved up ...
				// ... by acceleration times distance between highest_high_since_entry and the old stop level, 
				// ... but not beyond last low.
				Stp = TradeStopLimit;	// for painting
				if (priceHigh() > Hihi) {	
					Hihi = priceHigh();	// Every time a new highest_high_since_entry is reached, ...
					// .... acceleration is increased by one step (e.g. 0.02), limited by some maximal value (e.g. 0.2)
					Accel = min(AccelMax, Accel+AccelStep);	
					}	
			} else if (TradeIsShort) {	
				// With every new bar, stop is moved up ...
				// ... by acceleration times distance between highest_high_since_entry and the old stop level, 
				// ... but not beyond last low.
				TradeStopLimit = max(priceHigh(), TradeStopLimit - Accel*(TradeStopLimit-Lolo));	
				Stp = TradeStopLimit;	// for painting
				if (priceLow() < Lolo) {	
					Lolo = priceLow();	
					Accel = min(AccelMax, Accel+AccelStep);	// acceleration is increased
					}	
				}	
			}	

	PlotDate = 20140829;
	PlotWidth = 4096;	
	PlotHeight1 = 800;	
	ColorEquity = ColorDD = 0;	
	ColorUp = ColorDn = 0x00AAAAAA;	
	plot("FastMA",FastMA[0],0,BLACK);	
	plot("SlowMA",SlowMA[0],0,RED);	
	if (Stp!=0) {plot("Stp",Stp,DOT,BLUE);}	
	set(PLOTNOW);	
	}	