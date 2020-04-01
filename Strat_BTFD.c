function run()
{
set(PARAMETERS|TESTNOW|LOGFILE);  // generate and use optimized parameters

TimeFrame = 1;

vars Price = series(price());
vars Trend = series(LowPass(Price,500)); // Like moving average but faster
Stop = optimize(4,2,10) * ATR(100);


vars MMI_Raw = series(MMI(Price,300)); // Is market trending or not? Market Meanness Index
vars MMI_Smooth = series(LowPass(MMI_Raw,500)); // smooth it with the LowPass filter

if(falling(MMI_Smooth)) { // smoothed MMI is falling => beginning of a trend
       if(valley(Trend)) enterLong();
       else if(peak(Trend)) enterShort();
       }
}