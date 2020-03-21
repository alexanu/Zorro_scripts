// Spectral Analysis ///////////////////

//#define FILTER

function run()
{
	BarPeriod = 60;
	StartDate = 20151101;
	EndDate = StartDate + 0100; // 1 month
	LookBack = 2000;
	asset("EUR/USD");
	
	vars Price = series(price());
#ifdef FILTER
	plot("Filtered",BandPass(Price,24,0.1),NEW,BLACK);
	set(PLOTNOW+PLOTLONG);
#else	
	int Cycle;
	for(Cycle = 10; Cycle < 200; Cycle += 1)
		plotBar("Spectrum",Cycle,Cycle,Spectrum(Price,Cycle,4*Cycle),
		BARS+AVG+LBL2,BLUE);
#endif
	PlotHeight1 = 320;
}
