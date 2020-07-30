#include <profile.c>

function run()
{
	set(PLOTNOW);
  	StartDate = 2015;
  	EndDate = 2018;
  	BarPeriod = 15;
  	LookBack = 120;
  	// Weekend = 1; // Weekend variable has been replaced
 
 

	vars Price = series(price());
	vars Trend = series(LowPass(series(price()),100));	
	Stop = 100*PIP;	
	Trail = 4*ATR(10);

	if (crossOver(Price, Trend)) enterLong();	
	else if (crossUnder(Price, Trend)) enterShort();	

	// plotWeek(Equity,1);	// Weekly return analysis …
	plotWeekProfit();	// … or quarterly profit/loss
	// plotMAEGraph(50);
	// plotTradeProfile(50);	
	// plotPriceProfile();
}