function run()
{
set(LOGFILE|PLOTNOW);

StartDate = EndDate = 2020;
BarPeriod = 240;
LookBack = 0;

// if(is(INITRUN)) assetHistory("SPY", FROM_AV);
assetHistory("SPY", FROM_AV);
asset("SPY");
vars Closes = series((priceClose()));
plot("SPY AV",Closes,NEW,BLUE);



// string Name;
// int n = 0;
// int i, j;
// while(Name = loop("SPY", "CWI", "CSJ", "HYG", "TLT"))
//           {
//           if(is(INITRUN)) assetHistory(Name,FROM_AV);
//           asset(Name);
//           Returns[n] = series((priceClose(0)-priceClose(1))/priceClose(1));
//           n++;
//           }
// if(!is(LOOKBACK))
//           {
//           // plot returns
//           plot("SPY Returns", Returns[0], NEW|BARS, BLUE);
//           plot("CWI Returns", Returns[1], NEW|BARS, BLUE);
//           plot("CSJ Returns", Returns[2], NEW|BARS, BLUE);
//           plot("HYG Returns", Returns[3], NEW|BARS, BLUE);
//           plot("TLT Returns", Returns[4], NEW|BARS, BLUE);
//           }
}