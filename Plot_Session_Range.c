function run(){	
	set(PLOTNOW);
    LookBack = 0;
	StartDate = 20160901;	
	EndDate = 20160910;	
	BarPeriod = 15;	
	//BarZone = 6;	

	asset("SPX500");	
	StartMarket=0830;	
	EndMarket=1515;	
	vars PriceHigh = series(priceHigh());	
	vars PriceLow = series(priceLow());	
	var session_low = dayLow(ET,1); // calculate the range of the US session
	var session_high = dayHigh(ET,1); // calculate the range of the US session
	plot("US Session High Price", session_high,MAIN, RED);	
	plot("US Session Low Price", session_low, MAIN, GREEN);	

	var USRange = session_high - session_low;	// calculate the range of the US session
	plot("USRange", USRange, NEW, BLUE);	

}