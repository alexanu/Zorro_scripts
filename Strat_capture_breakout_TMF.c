/* 
capture an expected breakout of the hour prior to London open

a buy stop limit above the current price and a sell stop below the current price
a sell limit above the current price and a buy limit below the current price
one-cancels-the-other orders, or OCO orders

*/
 
#define HIGH AssetVar[0]
#define LOW AssetVar[1]
#define CANCELPENDING AssetVar[2]
 
int ocoTMF() // one-cancels-the-other orders
{
  // When a pending order is executed, the other order is cancelled
	if(CANCELPENDING == 1 and TradeIsPending) return 1; //exit the pending trade
	if(TradeIsEntry) CANCELPENDING = 1; //trigger cancel pending
 
        return 0;		
}

int oco_sarTMF() // stop-and-reverse order enters an opposite order at market if a trade is stopped out
{
	if(CANCELPENDING == 1 and TradeIsPending) return 1; //exit the pending trade
	if(TradeIsEntry) CANCELPENDING = 1; //trigger cancel pending
	
	if(TradeIsStop)
	{
		if(TradeIsLong) enterShort(oco_sarTMF);
		else if(TradeIsShort) enterLong(oco_sarTMF);
	}
	return 0;
  // we we don’t need to run our TMF at every tick ...
  // – only when a trade hits its stop loss – ...
  // ... so we can use 16 as the return value, which results in a slight increase in simulation speed

		
}

function run()
{
	set(TICKS);
	set(PLOTNOW);
 
	BarPeriod = 5;
	StartDate = 20190101;
		
	if(is(INITRUN)) CANCELPENDING = 0;
	
	// price series
	vars highs = series(priceHigh());
	vars lows = series(priceLow());
	vars Price = series(price());
	
	// get the highest high and the lowest low of pre-open
	int openHour = 8;
	if (lhour(WET) == openHour and minute() == 0) 
	{
 		HIGH = MaxVal(highs, 12); 
		LOW = MinVal(lows, 12); 
		CANCELPENDING = 0; //reset CANCELPENDING each day => script is limited to only one trade per day
	}
 
	if (lhour(WET) >= openHour)
	{
		if (between(priceClose(0), LOW, HIGH)) 
		{
			// Trail = 3*ATR(40); // Somehow with trail the profit is smaller
			Entry = HIGH; Stop = LOW; // places pending buy and sell stops at these levels
			if (NumOpenLong == 0) enterLong(ocoTMF); // enterLong(oco_sarTMF);

			Entry = LOW; Stop = HIGH;
			if (NumOpenShort == 0) enterShort(ocoTMF); // enterShort(oco_sarTMF);
 
		}
	}

 
	if (lhour(WET) >= 20) // UTC = WET, but WET has summer time
		{
		exitLong("*"); exitShort("*");
		}
 
	// PlotBars = 800; // 	PlotBars = 200;
	// PlotDate = 20170105;
	PlotHeight1 = 400;
	PlotWidth = 1200;
	ColorEquity = ColorDD = 0;
	plot("High", HIGH, MAIN|DOT, BLUE);
	plot("Low", LOW, MAIN|DOT, RED);

}


////////////////////////////////////////////////////////////////////////////////////////////////////


