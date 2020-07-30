function run()
{
	set(TICKS,PLOTNOW,LOGFILE);

	StartDate = 2015;
	LookBack = 0;
	BarPeriod = 5;	

	// asset("SPY");
	// asset("SPX500");  
	asset("US30");  

	LifeTime = 3;
	if(lhour(EST)==15 and minute() == 30) // Sunday 6:30pm Eastern (market has been open 90 minutes)
	enterLong();

}