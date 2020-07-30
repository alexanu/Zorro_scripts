function run()
{
    setf(PlotMode, PL_ALL);
    set(PLOTNOW,LOGFILE);
	StartDate = 20130101;
    BarPeriod = 10;
   	// ColorUp = ColorDn = 0; // don't plot a price curve

	// while(asset(loop(Assets))) 
    while(asset(loop("AUD/USD","EUR/USD","GBP/USD"))) 
        // plot(Asset, series(diff(price())), 0+BARS, color(random(100),BLUE,RED,YELLOW));
        {
        if(ldow(ET)==7 and lhour(ET)==17 and minute() == 10) // 10 mins after open on Sunday 5pm eastern
			{	
			int barsAgo = timeOffset(ET, 2, 13, 0);	// Friday 1pm eastern
			vars gap_returns = series((priceOpen() - priceClose(barsAgo))/priceClose(barsAgo));	
	        plot(Asset, gap_returns, NEW, BLACK);
            // printf("\n%s Gap Return: %.3f%%", Asset, gap_returns[idx[i]]*100);		
            }
        }
}