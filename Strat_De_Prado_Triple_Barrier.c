// Tripple Barrier
// Source: https://github.com/mg64ve/TripleBarrier/blob/master/TripleBarrier.c

#define DO_SIGNALS  // generate sample set in Train mode
#define OFFSET 8
#define BARRIER 10

///////////////////////////////////////////////////////////////////////
#include <r.h>

var change(int n, int os)
{
	return scale((priceClose(os) - priceClose(n+os))/priceClose(os),100)/100;
}

var range(int n, int os)
{
	return scale((HH(n+os) - LL(n+os))/priceClose(os),100)/100;
}

///////////////////////////////////////////////////////////////////////

function run()
{
	NumCores = -1;
	StartDate = 20150101;
	EndDate = 20160531;
	BarPeriod = 5;	// 1 hour
	LookBack = 300;
	int i,Offset;

	WFOPeriod = 252*24*12; // 1 year
	DataSplit = 90;

	asset("EUR/USD");
	set(RULES); 
	Spread = RollLong = RollShort = Commission = Slippage = 0;
	if(Train) { 
	   Hedge = 2;
	   Offset = OFFSET;
	}
	LifeTime = OFFSET;
	
	var Threshold = BARRIER * PIP;
	TakeProfit = BARRIER * PIP;
	//Stop = 5 * PIP;

	vars CloseTS = series(priceClose());
	vars OpenTS = series(priceOpen());	

	var ret = CloseTS[0]-OpenTS[0];
	vars rets = series(ret);

	var profit = 0;
	for(i=Offset-1; i--; i>=0) {
		profit += rets[i];
		if(profit>Threshold) { profit=1; break; }
		if(profit<-Threshold) { profit=-1; break; }
	}
	
	var vPred;
///////////////////////////////////////////////////////////	
#ifdef DO_SIGNALS
	SelectWFO = -1; // use the last WFO cycle for calibrating the neural net
	if((vPred = adviseLong(SIGNALS,profit,
#else
	set(LOGFILE|PLOTNOW);
	if((vPred = adviseLong(NEURAL,profit,
#endif
		change(1,Offset),change(2,Offset),change(3,Offset),change(4,Offset),change(8,Offset),change(16,Offset),change(32,Offset),change(64,Offset),change(128,Offset),change(256,Offset),
		range(1,Offset),range(2,Offset),range(3,Offset),range(4,Offset),range(8,Offset),range(16,Offset),range(32,Offset),range(64,Offset),range(128,Offset),range(256,Offset))) >= 1)	
		enterShort();
#ifndef DO_SIGNALS
	else if(vPred <= -1) enterLong();
            else { 
			      for(open_trades)
					  exitTrade(ThisTrade);
			}
#endif
	PlotWidth = 800;
	PlotHeight1 = 340;
}
