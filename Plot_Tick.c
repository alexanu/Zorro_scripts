function run()	
{
    set(TICKS);
    History=".t1";	
    TickTime=1000;
    BarPeriod = 5./60.;	// 1 second bars
    LookBack = 50;
    StartDate =20180105;
    EndDate =StartDate+20;	// fixed simulation period
    assetList("HistoryAssetsTest.csv");
    asset(Assets[0]);

    plot("price",price(),0,BLUE);
    plot("priceOpen",priceOpen(),0,RED);
    plot("priceHigh-1",priceHigh()-1,0,GREEN);
    plot("priceLow+1",priceLow()+1,0,CYAN);
    PlotWidth = 600;
    PlotHeight1 = 900;
    PlotHeight2 = 900;
    set(PLOTNOW);
}	