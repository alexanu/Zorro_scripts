#include <profile.c>

// plots intraday seasonality in local time. based on include/profile.c plotDay
void plotLocalDay(var value, int type, int timezone)
{
	int periods = 2*24;
	checkLookBack(periods);
	int m30 = 2*lhour(timezone, 0) + minute(0)/30;
	if(m30 > periods) return;
	plotSeason(m30, lhour(timezone, 0), ldow(timezone, 0), value, type);
}



function run()
{
	set(PLOTNOW);
  	StartDate = 2010;
  	BarPeriod = 60;
  	LookBack = 120;

	
	vars Close = series(priceClose());
	vars Return = series((Close[0] - Close[1])/Close[1]);
// "0" is cumulative evolution of the average and standard deviation over the time period of interest
// "1" is period-to-period changes, i.e. bar-to-bar changes

	// plotDay(Return[0], 0); // min BarPeriod is 30
				// Going lower, for example, trying to assess seasonality of say 15 minute periods, 
				// .. will cause the 15-minute periods within each 30-minute period to be averaged.
	// plotWeek(Return[0], 0); // min BarPeriod is 60
	plotMonth(Return[0], 1); // min BarPeriod is 1440; "1" is for ‘buy one day, sell another’
	plotYear(Return[0], 1); // min BarPeriod is 1440; "1" is for ‘buy one day, sell another’

	

/*
The Zorro functions for plotting seasonality call another Zorro function: plotBar. 
This function is used for making bar plots that aggregate a variable on some attribute of that variable.
In our case, we’re aggregating returns by the hour of the day and then taking their mean.
This is what we want to do, but unfortunately, we’re not getting the result we expect. 
And unfortunately, we don’t have access to the source code for this function.
*/

	int tz = ET;
	BarZone = ET;
	while(asset(loop("EUR/USD", "USD/JPY", "GBP/USD", "USD/CAD", "AUD/USD", "NZD/USD", "USD/CHF")))
	{ 
		vars Close = series(priceClose());
		vars Return = series((Close[0] - Close[1])/Close[1]);
		vars Trend = series(SMA(Close, 5));
		if(Close[0] < Trend[0]) plotLocalDay(Return[0], 0, tz); // long condition - price under short term MA
		if(Close[0] > Trend[0]) plotLocalDay(Return[0], 0, tz); // short condition - price over short term MA
	}

}