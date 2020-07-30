
/*
Just to summarize, our strategy now does the following:
1) Pre-processes the raw price series using Ehlers’ Roofing Filter
2) Calculates the period of the dominant cycle of the pre-processed price series
3) Tunes a Band-Pass filter centred on a period slightly lower than the dominant cycle, 
		but with a bandwidth that incorporates the dominant cycle.
4) Calculates a trigger line based on 90% of the one-bar lagged Band-Pass filter output.
We simply reverse long and short when the trigger line crosses under and over the Band-Pass output respectively.
*/


function run()
{
	set(PLOTNOW);
	StartDate = 2007;
	EndDate = 2016;
	BarPeriod = 60;
	LookBack = 200*24;
	
	while(asset(loop("EUR/USD", "USD/JPY", "SPX500")))
	while(algo(loop("H1", "H4", "D1")))
	{
		if(Algo == "H1") TimeFrame = 60/BarPeriod;
		else if(Algo == "H4") TimeFrame = 240/BarPeriod;
		else if(Algo == "D1") TimeFrame = 1440/BarPeriod;
	
		Spread = Commission = Slippage = RollLong = RollShort = 0;
		
		vars Price = series(price());
		vars HP = series(Roof(Price, 10, 70)); // prepares series for further computation by removing trend and noise
		
		// Set up filter parameters
		var DomPeriod = DominantPeriod(HP, 30); // cannot detect any cycles longer than 60 bars
		var Delta = 0.3;
		var BP_Cutoff = (1 - 2/3*(0.5 * Delta)) * DomPeriod; //tune to a shorter period
		vars BP = series(BandPass(HP, BP_Cutoff, Delta)); // Band-Pass filter
		vars Trigger = series(0.9*BP[1]); // Trigger: another High-Pass filter


		int Bandwidth = ceil(BP_Cutoff*Delta);	
		int UpperBP_Cutoff = ceil(BP_Cutoff + Bandwidth/2); 
		int LowerBP_Cutoff = floor(BP_Cutoff - Bandwidth/2); 
				
		// Trade logic
		if(DomPeriod < 45) // any currently open trade will stay open ...
		                   // ... until DominantPeriod() detects a shorter cycle, ...
						   // ... hopefully exploiting any cycles that turn into trends
		{
			if(crossOver(Trigger, BP)) enterLong();
			if(crossUnder(Trigger, BP)) enterShort();
		}

		PlotHeight1 = 400;
		PlotWidth = 800;
		plot("BP", BP, NEW, BLUE);
		plot("Trigger", Trigger, 0, RED);
		plot("DomCyclePeriod", DomPeriod, NEW, BLACK);
		plot("UpperCutoff", UpperBP_Cutoff, 0, RED);
		plot("LowerCutoff", LowerBP_Cutoff, 0, RED);
	}
}