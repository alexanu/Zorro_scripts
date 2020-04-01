// simple gap trading system, 
// from a book by David Bean 
function run()
{
  set(LOGFILE|PLOTNOW);
  BarPeriod = 30;
  StartDate = EndDate = 2014;

  // LookBack = 100*1440/BarPeriod; // 100 days lookback 

  asset("SPX500");  
  Stop = 200*PIP;
  MaxLong = MaxShort = -1;
  StartMarket = 930;
  EndMarket = 1600;

  vars Prices = series(priceClose());  
  var High = dayHigh(ET,1);
  var Low = dayLow(ET,1); 
  var Close = dayClose(ET,1); // returns yesterday's closing price of the current asset at NYSE
  var Avg = SMA(Prices,LookBack);


  if(High > 0 && Low > 0 && Close > 0 
    && timeOffset(ET,0,9,30) == 0) // enter a trade at the 9:30 bar when the NYSE opens 
  {
    if(Prices[0] > Close 
      && Prices[0] < High
      && Prices[0] < Avg)
      enterShort();
          
    if(Prices[0] < Close 
      && Prices[0] > Low
      && Prices[0] > Avg)
      enterLong();
  }
  	plot("SMA",Avg,0,BLACK);

}