function trade_Ehlers()
{
// simplier than in the Excel

TimeFrame = 2;

vars Price = series(price());
vars Smoothed = series(LowPass(Price,optimize(100,50,200,25)));
vars Trendline = series(HTTrendline(Price));
vars Trendmode = series(HTTrendMode(Price));

MaxLong = MaxShort = 1;

Stop = optimize(30,3,21,3) * ATR(30);

if(Trendmode == 1) {
          if(crossOver(Smoothed, Trendline)) enterLong();
          else if(crossUnder(Smoothed, Trendline)) enterShort();
                    }
else if(Trendmode == 0){
          if(Smoothed[0] > Trendline[0]) enterLong();
          else if(Smoothed[0] < Trendline[0]) enterShort();
                    }
}