// Calculates trade costs through the spread/volatility ratio

function run()
{
	BarPeriod = 1440;
	StartDate = EndDate = 2014;
	if(is(EXITRUN))
		printf("\nTrade costs in percent of volatility - - - - - -");

	int n = 0;
	static var Cost[20];
	
	while(asset(loop(
		"AUD/USD","EUR/USD","EUR/CHF","GBP/USD","USD/CAD","USD/CHF","USD/JPY",
		"GER30","NAS100","SPX500","UK100","US30",
		"XAG/USD","XAU/USD")))
	{
		if(is(INITRUN))
			Cost[n] = 0;
		else
			Cost[n] += Spread/max(1*PIP,ATR(5));
		if(is(EXITRUN))
			printf("\n%s - %.1f%%",Asset,100*Cost[n]/Bar);
		n++;
	}
}