int ReverseAtStop()	
{	
	if(TradeIsStop && NumOpenLong+NumOpenShort < 5) { // When Stop-loss hit, …
			if(TradeIsShort) enterLong(ReverseAtStop); // … enter opposite trade
			else enterShort(ReverseAtStop);	
			}	
	if(TradeIsProfit && NumOpenLong+NumOpenShort < 5) {	// when profit target is reached …
			if(TradeIsShort) enterShort(ReverseAtStop); // … enter same trade again
			else enterLong(ReverseAtStop);	
			}	
	// call the TMF only at events: 
		// entering or exiting due to Entry,Stop, or TakeProfit, 
		// and after the trade was closed
	return 16;	
}	
	
function run()	
{	
	// set(TICKS);	// normally needed for TMF
    set(PLOTNOW);

    StartDate = 2015;
    EndDate = 2016;
	BarPeriod =15;

	Stop = TakeProfit = ATR(300);
	if(Bar == LookBack)	enterLong(ReverseAtStop); // enter the first trade directly at the first bar
	plot("Open trades",NumOpenLong+NumOpenShort,0,RED);
}	