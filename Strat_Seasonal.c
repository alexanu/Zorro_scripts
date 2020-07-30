/*
var predictSeason(vars Prices,int LookBack=252,int LifeTime=1,int Mode)
{
	var Val = 0.; // initial and final value
	int i, Samples, Count = 0;
	Samples = 252/(6*DAYBARS); break; // 42

	var D = wdate(0); 
	for(i=LifeTime; i<LookBack-1; i++) { // from 1 to 251
		if(D >= wdate(i+1)) { 
			if(LifeTime) Val += Prices[i-LifeTime] - Prices[i]; // sample the difference only
			else Val += Prices[i];
			if(++Count >= Samples) break;
			D -= 7.; break; // same day previous week
			}
		}
	return Val/Count;
}
*/

function tradeSeason()
{
	vars Prices = series(price());
	if(!is(LOOKBACK)) {
		LifeTime = 1;
		var Season = predictSeason(Prices,LookBack,LifeTime,2);
		if(Season > 0) enterLong();
		else if(Season < 0) enterShort();
		}
}

function run()	
    {	
   	set(LOGFILE);  // generate and use optimized parameters and factors

	StartDate = 2013;
	EndDate=2018;
	BarPeriod = 1440;
	LookBack = 252;
    
	while(loop(Assets)) {
		asset(Loop1);
		tradeSeason();
	}
}	