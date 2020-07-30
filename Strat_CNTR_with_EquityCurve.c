
function checkEquity() {	
        vars EquityCurve = series(EquityLong+EquityShort);	//	generate equity curve including phantom trades
        vars EquityLP = series(LowPass(EquityCurve,10));	
        if(EquityLP[0] < LowPass(EquityLP,100) && falling(EquityLP)) //	don't trade when the equity curve goes down & and is below its own lowpass filtered value
                setf(TradeMode,TR_PHANTOM);	//	drawdown -> phantom trades
        else	
                resf(TradeMode,TR_PHANTOM);	//	profitable -> normal trades
		}	

function tradeCounterTrend()
{
		
	BarPeriod = 240; 
// Counter trend trading is affected by market cycles and more sensitive to the bar period than trend trading
// Bar periods that are in sync with the worldwide markets - such as 4 or 8 hours - ...
// ... are especially profitable with this type of trading

	LookBack = 500;
	set(PARAMETERS);
	StartDate = 2005;

	NumWFOCycles = 10;

	vars Price = series(price());
	vars Filtered = series(BandPass(Price,optimize(30,20,40),0.5));
	// BandPass is similar to LowPass + it dampens short cycles => curve with medium-period peaks and valleys

	vars Signal = series(FisherN(Filtered,500)); // Normalisation in order to compare with threshold

	var Threshold = optimize(1,0.5,1.5,0.1);

	checkEquity(); // equity curve trading 

	// buy and sell
	Stop = optimize(4,2,10) * ATR(100);
	Trail = 4*ATR(100); // 4 average candles away from the current price
// Trailing often - not always - improves the profit of a strategy, ...
// but is almost always better than placing a profit target

	if(crossUnder(Signal,-Threshold)) enterLong(); // price is supposedly close to the bottom of the main cycle
	else if(crossOver(Signal,Threshold)) enterShort(); // price is closed to peak
}