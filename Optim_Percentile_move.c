// Returns the price move within a given time horizon in %, 
// ... based on the given percentile of all such price moves in the Data series

var move(vars Data,int Length,int Horizon,var Percent)
{
	if(Length <= Horizon) return 0;
	checkLookBack(Length);
	vars Moves = series(0,0);
	int i;
	for(i=0;i<Length-Horizon;i++) 
		Moves[i] = 100.*(Data[i]-Data[i+Horizon])/Data[i+Horizon];
	var Result =Percentile(Moves,Length-Horizon,Percent);
	return Result;
}

function run()
{
	set(PLOTNOW);
	StartDate = 2016; 
	BarPeriod = 15;
	LookBack=160;
	
	asset("EUR/USD");
	vars mos = series(move(series(priceClose()),BarPeriod*10,BarPeriod,10));
	plot("Percent", mos,NEW|BARS,RED);
}
