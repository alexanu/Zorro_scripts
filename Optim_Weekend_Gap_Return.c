#define SYMBOLS "USD/CHF","USD/JPY","USD/CAD","GBP/USD","EUR/USD"
#define NUM_ASSETS 5


function run()
	{
	set(PLOTNOW);
	BarMode = BR_FLAT;

	StartDate = 20130101;
	EndDate = 20191230;
	BarPeriod = 10;	
	LookBack=300;

	int i=1; 
	int barsAgo;
	static var gap_returns[NUM_ASSETS];
	static var abs_gap_returns[NUM_ASSETS];

	if(ldow(ET)==7 and lhour(ET)==17 and minute() == 10) // 10 mins after open on Sunday 5pm eastern
		{	
		printf("\nCalculating Gap....");	
		while(asset(loop(SYMBOLS)))
			{	
			barsAgo = timeOffset(ET, 2, 17, 0);	// Friday 5pm eastern
			gap_returns[i] = (priceOpen() - priceClose(barsAgo))/priceClose(barsAgo);	
			abs_gap_returns[i] = abs(gap_returns[i]);	
			printf("\n%s %.5f", Asset, gap_returns[i]);	

			// PlotScale = 12;	
			plot("close", priceClose(barsAgo), MAIN|TRIANGLE, ORANGE);	
			plot("open", priceOpen(), MAIN|TRIANGLE4, MAROON);	
			i++;
			}	
		printf("\nDone calculating gap......");	
		}	
	}	