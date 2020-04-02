// Returns the price move within a given time horizon in %, 
// ... based on the given percentile of all such price moves in the Data series

var move(vars Data,int Length,int Horizon,var Percent)
{
	if(Length <= Horizon) return 0;
	checkLookBack(Length);
	vars Moves = series(0,0);
	for(int i=0; i<Length-Horizon; i++)
		Moves[i] = 100.*(Data[i]-Data[i+Horizon])/Data[i+Horizon];
	var Result =Percentile (Moves,Length-Horizon,Percent);
	return Result;
}