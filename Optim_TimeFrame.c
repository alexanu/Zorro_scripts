function run()
{
	set(PLOTNOW);
	StartDate = 20160901;
	EndDate = 20160902;
	BarPeriod = 5;
	LookBack = 0;

	// Zorro always uses UTC time in its plots

	//////////////////////////////////////////////////

	vars Close5 = series(priceClose());
	vars Filt5 = series(LowPass(Close5, 100));
	
	TimeFrame = 12; //aggregate every 12 bars - hourly
	
	vars Close60 = series(priceClose());
	vars Filt60 = series(LowPass(Close60, 100));
	
	TimeFrame = 1; //back to 5 minutely
 
	PlotBars = 250;
	plot("Filt5", Filt5, MAIN, BLUE);
	plot("Filt60", Filt60, 0, RED);
	plot("Close60", Close60, 0|DOT, GREEN);

	///////////////////////////////////////////////////
	
	TimeFrame = 24;
//	TimeFrame = frameSync(24); // uncomment and compare with previous
	
	vars Close = series(priceClose());
	TimeFrame = 1;
	plot("DayClose", Close, MAIN|DOT, RED);


	////////////////////////////////////////////////////

	// set up daily bars for the AUD/USD exchange rate aligned to 9am Sydney time

	BarPeriod = 1440;
	BarZone = AEST;
	BarOffset = 9*60; //minutes from midnight
	asset("AUD/USD");
	
	PlotScale = 30;
	printf("\nLocal time: %d UTC time: %d", lhour(AEST), hour());
	

	////////////////////////////////////////////////////

	// aggregate the hourly bars into daily bars that change at 9am AEST
	asset("AUD/USD");
	FrameOffset = 9; // multiple of BarPeriod  after which the daily boundary occurs
	AssetZone = AEST; // time zone to which we wish to sync our asset’s data
	TimeFrame = AssetFrame; // creates daily bars aligned to the AssetZone
	
	vars Close = series(priceClose());
	
	TimeFrame = 1;
 	plot("Close", Close, MAIN|DOT, BLUE);

	////////////////////////////////////////////////////

	// align daily bars differently for the various assets
	
	while(asset(loop("AUD/USD", "USD/JPY", "EUR/USD")))
	{
		if(Asset == "AUD/USD")
		{
			FrameOffset = 9;
			AssetZone = AEST;
		}
		else if(Asset == "USD/JPY")
		{
			FrameOffset = 10;
			AssetZone = JST;
		}
		else if(Asset == "EUR/USD")
		{
			FrameOffset = 8;
			AssetZone = WET;
		}
		
		TimeFrame = AssetFrame;
		
		vars Close = series(priceClose());
		
		TimeFrame = 1;
		PlotBars = 200;
		plot("Close", Close, MAIN|DOT, BLUE);
	}



}