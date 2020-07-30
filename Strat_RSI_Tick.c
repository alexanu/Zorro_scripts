function run()
{
	set(PLOTNOW, PARAMETERS);
	BarPeriod = 60;
	NumYears = 10;
	LookBack = 160;
	assetList("AssetsFix");
	asset("EUR/USD");
	
	// RSI: Ratio of the recent upwards data movement to the total data movement; range 0..100
	vars Prices = series(priceClose());
	vars RSI12 = series(RSI(Prices,12)); 

	int overbought = optimize(70, 60, 90,5);
	int oversold = optimize(30, 10, 40, 5);

	Stop = 4*ATR(100);
	TakeProfit = 2*ATR(100);
	MaxLong = MaxShort = 1;

	//set up trend filter
		TimeFrame = 4;	// 4-hourly trade filter
		vars PriceH4 = series(price());	
		int filtPeriod = optimize(5, 3, 10, 1)*24;
		vars filter = series(LowPass(PriceH4, 200));	


	if(crossOver(RSI12,overbought) and Prices[0] > filter[0] and NumOpenLong == 0) enterLong(); // if rsi crosses over buy level, exit short and enter long
	if(crossUnder(RSI12,oversold) and Prices[0] < filter[0] and NumOpenShort == 0) enterShort(); // if rsi crosses below sell level, exit long and enter short

	if(crossOver(RSI12,0) && crossUnder(RSI12,0))
		{exitLong();
		exitShort();
		}

	//plots
		PlotBars = 250; //plot first 250 bars only for better viewing
		PlotHeight1 = 400;
		PlotHeight2 = 125;
		PlotWidth = 1200;
		ColorEquity = ColorDD = 0;
		plot("rsi", RSI12, NEW, BLUE);
		plot("overbought", overbought, 0, BLACK);
		plot("oversold", oversold, 0, BLACK);

}