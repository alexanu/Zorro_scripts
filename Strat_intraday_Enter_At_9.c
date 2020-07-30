function run()
{
	StartDate = 2010;
	LookBack = 0;
	BarPeriod = 60;	
	FrameOffset = 9;	// trade both assets at 9:00 of their local time
	while(asset(loop("EUR/USD","USD/JPY")))	// trade two assets with different time zones
		{	
		if(strstr(Asset,"EUR"))	// Substring
		AssetZone= WET;	
		else if(strstr(Asset,"JPY"))	
		AssetZone= JST;	
		TimeFrame=AssetFrame;	// use a daily time frame changing at 9:00 local time
		LifeTime = 8;
		enterLong();
		}
}	












}