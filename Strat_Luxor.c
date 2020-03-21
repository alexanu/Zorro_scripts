// Luxor system by Jaeckle/Tomasini /////////////
// Make a system profitable by creative selection
// of start and end date 

function run()
{
	StartDate = 2004;
	EndDate = 2010;
	BarPeriod = 30;
	LookBack = 30;
	asset("GBP/USD");

// no trade costs...	
	Spread = 0;
	Slippage = 0;
	RollLong = RollShort = 0; 
	
	vars Price = series(priceClose()),
		Fast = series(SMA(Price,3)),
		Slow = series(SMA(Price,30));
	
	static var BuyLimit,SellLimit,BuyStop,SellStop;
	
	if(crossOver(Fast,Slow)) {
		BuyStop = priceHigh() + 1*PIP;
		BuyLimit = priceHigh() + 5*PIP;
	}
	if(crossUnder(Fast,Slow)) {
		SellStop = priceLow() - 1*PIP;
		SellLimit = priceLow() - 5*PIP;
	}
		
	if(!NumOpenLong && Fast[0] > Slow[0] && Price[0] < BuyLimit)
		enterLong(1,BuyStop);
	if(!NumOpenShort && Fast[0] < Slow[0] && Price[0] > SellLimit)
		enterShort(1,SellStop);

	PlotWidth = 1000;
	set(PLOTNOW);
}