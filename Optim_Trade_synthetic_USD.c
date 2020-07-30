var priceUSD()	
// generate a synthetic asset "USD"…
//…combined from the USD value of EUR, GBP, and AUD
{	
	var p = 0;	
	asset("GBP/USD"); p += price();	
	asset("AUD/USD"); p += price();	
	asset("EUR/USD"); p += price();	
	return p;	
}	
	
int tradeUSD(var StopUSD) // basket trade function with stop limit
{	
	// exit the trade
	if((TradeIsLong && priceUSD() <= StopUSD) or (TradeIsShort && priceUSD() >= StopUSD)) return 1;	
	else return 0;	// continue the trade
}	
	
void enterLongUSD(var StopDistUSD)	// open a trade with the synthetic asset and a stop loss
{	
	var StopUSD = priceUSD()-StopDistUSD;	
	asset("GBP/USD"); enterLong(tradeUSD,StopUSD);	
	asset("AUD/USD"); enterLong(tradeUSD,StopUSD);	
	asset("EUR/USD"); enterLong(tradeUSD,StopUSD);	
}	
	
void enterShortUSD(var StopDistUSD)	
{	
	var StopUSD = priceUSD()+StopDistUSD;	
	asset("GBP/USD"); enterShort(tradeUSD,StopUSD);	
	asset("AUD/USD"); enterShort(tradeUSD,StopUSD);	
	asset("EUR/USD"); enterShort(tradeUSD,StopUSD);	
}	
	
function run()	
{	
	set(PLOTNOW);	
	plot("USD",priceUSD(),0,RED);	// plot a price curve of the synthetic asset …
	// … the plot command is linked to the last used asset - so "EUR/USD" must be selected in the scrollbox
}