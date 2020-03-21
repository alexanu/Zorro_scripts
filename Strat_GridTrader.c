// Grid trader
 
// find all trades at a grid line
bool findTrade(var Price,var Grid,bool IsShort)
{
	int result = false;
	for(open_trades)
		if((TradeIsShort == IsShort)
			and between(TradeEntryLimit,Price-Grid/2,Price+Grid/2)) {
				result = true;
				break_trades;
			}
	return result;
}

int run() 
{
	BarPeriod = 1440;
	Hedge = 2;	// allow long & short trades at the same time
	
	EntryTime = LifeTime = 250; // close trades after 1 year
	var Price, Grid = 200*PIP; // set grid distance to 200 pips
	var Close = priceClose();
	
// place pending trades at 5 grid lines 
// above and below the current price
	for(Price = 0; Price < Close+5*Grid; Price += Grid)
	{
// find the lowest grid line
		if(Price < Close-5*Grid) continue;
// place not more than 200 trades		
		if(NumOpenTotal + NumPendingTotal > 200) break;
// place short trades below the current price
		if(Price < Close and !findTrade(Price,Grid,true))
			enterShort(1,Price,20*Grid,Grid);  		
// place long trades above the current price
		else if(Price > Close and !findTrade(Price,Grid,false))
			enterLong(1,Price,20*Grid,Grid);
	}
}
	

