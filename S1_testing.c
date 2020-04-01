

int run() 
{
	BarPeriod = 240;
	StartDate = 20120101;
	set(PLOTNOW,LOGFILE);
	LookBack = 200;

    asset("USD/JPY");


	// while(asset(loop("EUR/USD","AUD/USD","GBP/USD"))) {
		vars Close = series(priceClose());
		vars Trend = series(LowPass(Close, 100)); // Like moving average but faster
		Stop = ATR(80);
		Trail = ATR(120);
		if(crossOver(Close, Trend)) enterLong();	
		plot("LowPass",Trend,0,BLUE);

	// }


}
	

