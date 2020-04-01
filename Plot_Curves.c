function run()
{
set(LOGFILE|PLOTNOW);
NumYears = 1;
BarPeriod = 240;

PlotBars = 400; // number of bars to plot in the chart. Default - all

PlotScale = 8;
PlotWidth = 800;
PlotHeight1 = PlotHeight2;

vars Price[3];
int N=0;
string names[3];
while(asset(loop("AUD/USD","EUR/USD","GBP/USD")))
            {
            names[N] = Asset;
            Price[N] = series(price());
            N++;
            }
for(N=0; N<3; N++)
            {
            plot(strf("price_%s",names[N]), Price[N], NEW, BLACK);
            }
}