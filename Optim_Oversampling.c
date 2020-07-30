// #define FULLY_OPTIM	
// #define STOP_OPTIM_NO_TAKEPROFIT	
// #define STOP_TAKEPROFIT_OPTIM	
// #define INDIC_OPTIM	
#define NOT_OPTIM


void tradeRSI()
{
	TimeFrame = 4; 	// 4-hourly trade filter
	vars PriceH4 = series(price());


#ifdef FULLY_OPTIM
	vars Filter = series(LowPass(PriceH4, 200));
	
	TimeFrame = 1; 	//Entries/Exits on 1-hourly 
	vars PriceH1 = series(price());
	vars rsi = series(RSI(PriceH1, 14));
	int overbought = optimize(70,60, 90,5);
	int oversold = optimize(30, 10, 40, 5);
	
	Stop = optimize(4, 1, 12, 1)*ATR(100);
	Trail = Stop;
	TakeProfit = optimize(4, 1, 12, 1)*ATR(100);
	
	if(crossOver(rsi, overbought) and PriceH1[0] < Filter[0] and NumOpenShort == 0) enterShort();
	if(crossUnder(rsi, oversold) and PriceH1[0] > Filter[0] and NumOpenLong == 0) enterLong(); 	
#endif

#ifdef STOP_OPTIM_NO_TAKEPROFIT
	vars Filter = series(LowPass(PriceH4, 200));
	
	TimeFrame = 1; 	//Entries/Exits on 1-hourly 
	vars PriceH1 = series(price());
	vars rsi = series(RSI(PriceH1, 14));
	int overbought = 70;
	int oversold = 70;
	
	Stop = Trail = optimize(4, 1, 12, 1)*ATR(100);
	
	if(crossOver(rsi, overbought) and PriceH1[0] < Filter[0] and NumOpenShort == 0) enterShort();
	if(crossUnder(rsi, oversold) and PriceH1[0] > Filter[0] and NumOpenLong == 0) enterLong(); 	
#endif

#ifdef STOP_TAKEPROFIT_OPTIM
	vars Filter = series(LowPass(PriceH4, 200));
	
	TimeFrame = 1; 	//Entries/Exits on 1-hourly 
	vars PriceH1 = series(price());
	vars rsi = series(RSI(PriceH1, 14));
	int overbought = 70;
	int oversold = 70;
	
	Stop = optimize(4, 1, 12, 1)*ATR(100);
	Trail = Stop;
	TakeProfit = optimize(4, 1, 12, 1)*ATR(100);

	if(crossOver(rsi, overbought) and PriceH1[0] < Filter[0] and NumOpenShort == 0) enterShort();
	if(crossUnder(rsi, oversold) and PriceH1[0] > Filter[0] and NumOpenLong == 0) enterLong(); 	
#endif

#ifdef INDIC_OPTIM
	vars Filter = series(LowPass(PriceH4, 200));
	
	TimeFrame = 1; 	//Entries/Exits on 1-hourly 
	vars PriceH1 = series(price());
	vars rsi = series(RSI(PriceH1, 14));
	int overbought = optimize(70,60, 90,5);
	int oversold = optimize(30, 10, 40, 5);
	
	Stop = TakeProfit = 4*ATR(100);
	Trail = Stop;

	if(crossOver(rsi, overbought) and PriceH1[0] < Filter[0] and NumOpenShort == 0) enterShort();
	if(crossUnder(rsi, oversold) and PriceH1[0] > Filter[0] and NumOpenLong == 0) enterLong(); 	
#endif

#ifdef NOT_OPTIM
	vars Filter = series(LowPass(PriceH4, 200));
	
	TimeFrame = 1; 	//Entries/Exits on 1-hourly 
	vars PriceH1 = series(price());
	vars rsi = series(RSI(PriceH1, 14));
	int overbought = 70;
	int oversold = 30;
	
	Stop = TakeProfit = 4*ATR(100);
	Trail = Stop;

	if(crossOver(rsi, overbought) and PriceH1[0] < Filter[0] and NumOpenShort == 0) enterShort();
	if(crossUnder(rsi, oversold) and PriceH1[0] > Filter[0] and NumOpenLong == 0) enterLong(); 	
#endif

}
 
void tradeDigi()
{
	vars Price = series(price());
	vars filter = series(Roof(Price, 50, 100));
	
	Stop = optimize(3, 1, 6, 0.5)*ATR(100);
	Trail = 0.5*Stop;
	TrailLock = 10;
	TrailSpeed = 200;
	
	if(valley(filter)) reverseLong(1);
	if(peak(filter)) reverseShort(1);

}
 
function run()
{
	set(TESTNOW|PLOTNOW|PARAMETERS|FACTORS|ALLCYCLES);
	StartDate= 2010;
	NumWFOCycles = 10;
	BarPeriod = 60;
	LookBack = 150;
	// NumSampleCycles = 4;
	

	while(asset(loop("EUR/USD", "AUD/USD")))//, "NZD/USD")))
	while(algo("rsi"))
	// while(algo(loop("rsi", "digi")))
	{
		if(Algo == "rsi") tradeRSI();
		else if(Algo == "digi") tradeDigi();		
	}
	
}