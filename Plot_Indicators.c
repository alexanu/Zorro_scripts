function run()
{
set(LOGFILE|PLOTNOW);
// NumYears = 1;
LookBack = 150;

StartDate = 20140101;
EndDate = 20140710;

BarPeriod = 60;

PlotBars = 400; // number of bars to plot in the chart. Default - all
// PlotStart = 20181231; // start of the chart


PlotScale = 8;
PlotWidth = 800;
// PlotHeight1 = 350; // Height of the main chart
// PlotHeight2 = 80; // Height of additional charts (plot with type=NEW)
PlotHeight1 = PlotHeight2;

assetList("AssetsSP500");
asset("A");
// vars Prices = series(price());
// plot("A Price",Prices,NEW,RED);

var ATR100 = ATR(100);
var ATRS100 = ATRS(100);
// plot("ATR (PIP)",ATR(100)/PIP,0+AXIS2,RED);
plot("ATR 100",ATR100,NEW,RED);
plot("ATRS 100",ATRS100,0,BLUE);


// plot("Doji",CDLDoji(),NEW+BARS,BLUE);
// plot("FractalDim",FractalDimension(Prices,30),NEW,RED);

// vars Closes = series(priceClose());
// plot("A Price",Closes,0,RED);
// plot("ConnorsRSI",ConnorsRSI(Closes,3,2,100),0+AXIS2,RED);


// plot("center",center(ATR100,100),0,GREEN);
// plot("compress",compress(ATR100-0.003,100),NEW,RED);
// plot("scale",scale(ATR100,100),NEW,RED);
// plot("normalize",normalize(ATR100,100),NEW,RED);
// plot("zscore",zscore(ATR100,100),NEW,RED);

}