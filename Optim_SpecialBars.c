// Special bars example //////////////////////////////

//#define MULTI_ASSET

var BarRange = 0.0030; // 0.3 cents bar range

// Range Bars
int Range(vars Open,vars High,vars Low,vars Close)
{
  if(Open[0] != Close[1]) {
    High[0] = max(Open[0],Close[1]);
    Low[0] = min(Open[0],Close[1]);
    Open[0] = Close[1];
  }
  if(High[0]-Low[0] >= BarRange)
    return 1;
  return 4;
}

// Renko Bars, variant 1 
int Renko1(vars Open,vars High,vars Low,vars Close)
{
  Open[0] = round(Close[1],BarRange);
  if(Close[0]-Open[0] >= BarRange) {
    Close[0] = Open[0]+BarRange;
    High[0] = Close[0];
    Low[0] = Open[0];
    return 1;
  }
  if(Open[0]-Close[0] >= BarRange) {
    Close[0] = Open[0]-BarRange;
    High[0] = Open[0];
    Low[0] = Close[0];
    return 1;
  }
  return 4;
}

// Renko Bars, variant 2 
int Renko2(vars Open, vars High, vars Low, vars Close)
{
  var OpenDiff = abs(Close[0]-Open[1]);
  var CloseDiff = abs(Close[0]-Close[1]);
  if(OpenDiff < CloseDiff) // we have a valley or peak
     Open[0] = Open[1];
  else  // we are moving with the trend
     Open[0] = round(Close[1],BarRange);
  if(Close[0]-Open[0] >= BarRange) {  // going up
    Close[0] = Open[0]+BarRange;
    High[0] = Close[0];
    Low[0] = Open[0];
    return 1;
  }
  if(Open[0]-Close[0] >= BarRange) { // going down
    Close[0] = Open[0]-BarRange;
    High[0] = Open[0];
    Low[0] = Close[0];
    return 1;
  }
  return 4;
}

// Mean Renko Bars
int Renko3(vars Open, vars High, vars Low, vars Close)
{
  Open[0] = 0.5*(Close[1]+Open[1]);
  if(Close[0] <= Open[0] - BarRange) {
    Close[0] = Open[0] - BarRange;
    return 1;
  } else if(Close[0] >= Open[0] + BarRange) {
    Close[0] = Open[0] + BarRange;
    return 1;
  }
  return 4;
}

// Haiken Ashi Bars
int HA(vars Open,vars High,vars Low,vars Close)
{
  Close[0] = (Open[0]+High[0]+Low[0]+Close[0])/4;
  Open[0] = (Open[1]+Close[1])/2;
  High[0] = max(High[0],max(Open[0],Close[0]));
  Low[0] = min(Low[0],min(Open[0],Close[0]));
  return 8;
}

// Point-and-Figure Bars
int PAF(vars Open,vars High,vars Low,vars Close)
{
  static int direction = 0;
  if(direction == 1 && High[0]-Close[0] >= BarRange) {
    Open[0] = round(Low[0],BarRange);
    Close[0] = round(High[0],BarRange);
    Low[0] = Open[0];
    High[0] = Close[0];
    direction = 0;
    return 1;
  }
  if(direction == 0 && Close[0]-Low[0] >= BarRange) {
    Open[0] = round(High[0],BarRange);
    Close[0] = round(Low[0],BarRange);
    High[0] = Open[0];
    Low[0] = Close[0];
    direction = 1;
    return 1;
  }
  return 4;
}

#ifndef MULTI_ASSET // single asset user bars ////////////////////

int bar() {} // dummy function to be set to the real bar function

void run()
{
	bar = Renko1;
	BarPeriod = 15; // determines only the number of allocated bars, not the bar period
	StartDate = 20180601;
	EndDate = 20180901;
	LookBack = 0;
	set(PLOTNOW);
	// ... perform the algorithm.
}

#else // multi asset user bars ///////////////////////////////////

int _bar(vars Open,vars High,vars Low,vars Close); // prototype

int nextBar(vars Open,vars High,vars Low,vars Close)
{
	var O[2],H[2],L[2],C[2]; // parameters for the bar function 
	O[0] = priceOpen(0); O[1] = Open[1];
	H[0] = priceHigh(0); H[1] = High[1];
	L[0] = priceLow(0); L[1] = Low[1];
	C[0] = priceClose(0); C[1] = Close[1];
	if(_bar(O,H,L,C) == 1) {
		shift(Open,O[0],LookBack);
		shift(High,H[0],LookBack);
		shift(Low,L[0],LookBack);
		shift(Close,C[0],LookBack);
		return 1;
	} else return 0;
}

void run()
{
	BarPeriod = 1; // determines here the time resolution of the bar
	StartDate = 20180601;
	EndDate = 20180901;
	LookBack = 0;
	set(PLOTNOW);
		
	while(asset(loop("EUR/USD","GBP/USD"))) 
	{
		_bar = Renko1;	
		vars O = series(priceOpen(),-LookBack), // series must be static here
			H = series(priceHigh(),-LookBack),
			L = series(priceLow(),-LookBack),
			C = series(priceClose(),-LookBack);
		if(nextBar(O,H,L,C)) {
			// ... perform the algorithm. Shift other series.
			printf("#\nNew Bar");
		}
		plot("Renko",C,LINE,RED);
	}
}
#endif