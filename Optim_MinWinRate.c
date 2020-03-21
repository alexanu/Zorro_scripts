// Required win rate vs. trade length /////////////////////

function run()
{
	StartDate = 2015;
	BarPeriod = 1;
	LookBack = 1440;
	PlotScale = 15;	
	Commission = 0.6;
	Spread = 0.3*PIP;

	int length = 1, i = 0;
	if(is(LOOKBACK) || (Bar%200)) return; // use every 200th bar
	while(length <= 1440)
	{ 	
		var Win = abs(priceClose(length)-priceClose(0))*PIPCost/PIP;
		var Cost = Commission*LotAmount/10000. + Spread*PIPCost/PIP;
// Breakeven:
// Profit = Cost = Rate * Win - (1.-Rate) * Win; 
// => Cost = (Rate - 0.5) * 2 * Win; 
		
		var Rate = ifelse(Win>Cost, Cost/(2*Win) + 0.5, 1.);
		plotBar("Min win rate",i,length,100*Rate,AVG+BARS,BLACK+TRANSP);	
		
		if(length < 10) length += 1;
		else if(length < 60) length += 5;
		else if(length < 180) length += 30;
		else length += 60;
		i++;
	}
}