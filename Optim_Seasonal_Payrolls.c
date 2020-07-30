/* NFP DRIFT

NFP data is released first Friday of the month at 8:30 ET
If the first Friday is a holiday, NFP is released the following Friday

monthly NFP data typically causes large swings in the currency markets, ...
... even when the results are in line with estimates


*/

function run()
{
    set(PEEK|PLOTNOW); // PEEK enables the price() functions to access data from the future
	StartDate = 2009;
    EndDate = 2018;
    BarPeriod = 5;
    asset("EUR/USD");

    int StartSeason = 600; //time of day to commence season
    int EndSeason = 1100; //time of day to end season
    
    vars Closes = series(priceClose());
    vars Returns = series((Closes[0]-Closes[1])/Closes[1]);
    
    // set up cumulative returns series to track returns over the whole season
    vars CumReturns = series();
    CumReturns[0] = (Returns[0]+1)*(CumReturns[1]+1)-1;
    
    static int i;
    if(is(INITRUN)) i = 0;

    // at StartSeason, get first hour's return post NFP, and reset CumReturn to zero
    static var NFP_Return;

    // first Friday of the month
	if(ldow(ET) == 5 and day() <= 7 and ltod(ET) == StartSeason)
    {
        // calculate number of BarPeriods to use for future peeking post-NFP returns
        int timeDiff = 830 - StartSeason;
        var minutes = floor(timeDiff/100)*60 + timeDiff % 100;
        int offset = minutes/BarPeriod; //number of bars to NFP release
        
        // calculate post-NFP returns (1 hour)
        NFP_Return = (priceClose(-(offset+60/BarPeriod))-priceClose(-offset))/priceClose(-offset);
        CumReturns[0] = 0;
    }

    if(ldow(ET) == 5 and day() <= 7 and between(ltod(ET), StartSeason, EndSeason) and NFP_Return > 0)
    {
        plotBar("SD_CumRet", i, ltod(ET), CumReturns[0]*100, DEV|BARS|LBL2, LIGHTBLUE);
        plotBar("Avg_CumRet", i, ltod(ET), CumReturns[0]*100, AVG|BARS|LBL2, BLUE);
//      plotBar("SD (x4)", i, ltod(ET), Returns[0]*100/4, DEV|BARS|LBL2, LIGHTBLUE);
//      plotBar("Avg", i, ltod(ET), Returns[0]*100, AVG|BARS|LBL2, BLUE);
        i++;    
    }
       
    if(ltod(ET) > EndSeason) i = 0;  
}