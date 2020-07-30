
// Volume Bars

static int vol = 0;
int bar(vars Open, vars High, vars Low, vars Close)
	{
	//printf("nVol %i", vol);
	vol += marketVol();
	if (vol >= 500) {
			vol = 0;
			return 1;
			}
	return 4;
	}

function run() 
	{
	set(TICKS);
	StartDate = 20150101;
	EndDate = 20150115;
	set(PLOTNOW);          
	BarPeriod = 10;
	vars Close = series(priceClose());
	plot("Vol",marketVol(),NEW,RED);
	}