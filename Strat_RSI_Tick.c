function run()
{
	set(TICKS,FAST);
	BarPeriod = 60;
	NumYears = 10;
	assetList("AssetsFix");
	asset("EUR/USD");
	
// get the RSI series. RSI: Ratio of the recent upwards data movement to the total data movement; range 0..100
	vars Prices = series(priceClose());
	vars RSI12 = series(RSI(Prices,12));
 
// set up stop / profit levels
	Stop = 200*PIP;
	TakeProfit = 200*PIP;
	MaxLong = MaxShort = 1;
 
// if rsi crosses over buy level, exit short and enter long
	if(crossOver(RSI12,75))
		enterLong();
// if rsi crosses below sell level, exit long and enter short
	if(crossUnder(RSI12,25))
		enterShort();

// measure the time
	static var Time = 0;
	if(is(INITRUN)) Time = timer();
	if(is(EXITRUN)) printf("\nTime needed: >>> %.3f sec <<<",(timer()-Time)/1000);


	set(TICKS|FAST);
	BarPeriod = 60;
	NumYears = 10;
	assetList("AssetsFix");
	asset("EUR/USD");

	vars Close = series(priceClose());
	vars Rsi12 = series(RSI(Close,12));

	Stop = 200*PIP;
	TakeProfit = 200*PIP;
	MaxLong = MaxShort = 1;

	if(crossOver(Rsi12,75))
	reverseLong(1);
	if(crossUnder(Rsi12,25))
	reverseShort(1);
}







}