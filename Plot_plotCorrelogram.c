#include <profile.c>

function run()
{
	set(PLOTNOW);
  	StartDate = 2009;
  	EndDate = 2018;
  	BarPeriod = 60;
  	LookBack = 150;
 
  	// vars Close = series(priceClose());
  	// vars Return = series((Close[0] - Close[1])/Close[1]);
  	// plotCorrelogram(Return[0], 24*5); // lags of up to 5 days

	var range = priceHigh() - priceLow();
	plotCorrelogram(range, 24*5);	  

	// heteroskedasticity: tendency of the volatility of financial time series to cluster.
	// This plot tells a vastly different story to the returns correlogram.
	// We can see that volatility is highly correlated with itself, 
	// ... with peaks in the correlation coefficient at 24-hour intervals. 
	// The range of the current bar is highly correlated with the range of the previous bar.
}