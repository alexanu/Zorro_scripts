/* AUTOCORRELATION OF A MEAN REVERTING SPREAD  

mean-reverting spread is a combination of two instruments into a portfolio ...
                    ... such that the value of the portfolio is stationary =>
					deviation from its mean value will be followed by 
					a subsequent reversion towards the mean


*/
 
#include <profile.c>

function run()
{
	set(PLOTNOW);
  	StartDate = 2016;
  	EndDate = 2017;
  	BarPeriod = 1440;
  	LookBack = 201;
  	
  	// get ETF data
	string Name;
	vars Closes[2];
	int n = 0;
	while(Name = loop("GLD", "GDX"))
	{
		if(is(INITRUN)) assetHistory(Name,FROM_AV);
		asset(Name);
		Closes[n] = series(priceClose());
		n++;
	}
	
	// go long GLD and short GDX
	// For every share of GLD we buy, we sell short 2.5 shares of GLD in an attempt to create a stationary spread. 
	var beta = 0.3; 
	vars spread = series((Closes[0])[0] - beta*(Closes[1])[0]);
	
  	plotCorrelogram(spread[0], 150);

	// The value of the spread is anti-correlated with itself over longer periods, ...
	// ... most strongly over a period of approximately 120 days. 
	//  That is, the value of the spread 120 days ago tells us something about its value tomorrow
}