
function run()
{
	set(PLOTNOW);
	StartDate = 20180401; 
	EndDate = 20180408;   
	History = ".t1";
	BarPeriod = 1;
	
	asset("EUR/USD");
	vars closes = series(priceClose());
	if(between(ltod(ET), 700, 1100)) plot("Open NY", closes, 0, RED);

	// volatility of one-minute returns
	int stddev_period = 60;
	vars returns = series(ROCP(closes, 1));
	vars volatility = series(100*sqrt(Moment(returns, stddev_period, 2)));
	
	// plot dots above price bars for the first hour of London trading
	// if(lhour(WET) == 7) plot("London Open", priceHigh(), MAIN|DOT, MAGENTA);

	// // plot an orange line through the mean price of each bar from half an hour before to half an hour after the NY open
	// if(between(ltod(ET), 630, 730)) plot("NY Open", price(), MAIN, ORANGE);

	// plot("volatility", volatility, 0+AXIS2, BLUE);
	// if(between(ltod(ET), 700, 1100)) plot("#volatility", volatility, 0+AXIS2, RED);
}