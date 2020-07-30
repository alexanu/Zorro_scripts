function run()
{
	set(PLOTNOW);
	StartDate = 20161201;
	EndDate = 20161231;
	BarPeriod = 60;
	LookBack = 0;
	while(asset(loop("EUR/USD", "GBP/USD", "USD/JPY", "AUD/USD")))
			{
			FrameOffset = 9;
			switch(Asset)
				{
				case "EUR/USD" : AssetZone = WET; break;
				case "GBP/USD" : AssetZone = WET; break;
				case "USD/JPY" : AssetZone = ET; break;
				case "AUD/USD" : AssetZone = AEST; break;
				default : quit("No alignment defined for selected asset!");
				}
			TimeFrame = AssetFrame;
			if(lhour(AssetZone) == FrameOffset) plot("Open", priceHigh(), DOT, BLUE);
			PlotScale = 10;
			}
	}