// Mean Variance Optimization ////////////////////////	

//#define DAYS 252	// 1 year
#define DAYS 6*22	// 6 Months
//#define DAYS 4*22	// 4 Months
//#define DAYS 2*22	// 2 Months

#define WEIGHTCAP .25	// Cap 0.15 - 0.5 Range
#define NN 50	// max number of assets
#define LEVERAGE 4	// 1:4 leverage
	
function run()	
{	
	BarPeriod = 1440;	
	LookBack = DAYS;
	NumYears = 7;	
	set(PRELOAD);	// allow extremely long lookback period
	set(LOGFILE);	
	Verbose = 0;	
	set(watch);	

	// AssetList = "ETF2016-OK.csv";	
	AssetList = "AssetsZ8.csv";	

	string Names[NN];	
	string Symbols[NN];	// Store the ISIN Code
	vars Returns[NN];	
	var Means[NN];	
	var Covariances[NN][NN];	
	var Weights[NN];	

	static int OldLots[NN];	

	var TotalCapital = slider(1,1000,1000,50000,"Capital","Total capital to distribute");	
	var VFactor = slider(2, 10 ,0, 100,"Risk","Variance factor");	
	int N = 0;	
	while(Names[N] = loop(Assets))	
			{	
			if(is(INITRUN) && strstr(Names[N], "#")== NULL) {	
					assetHistory(Names[N], FROM_YAHOO);	
					Symbols[N] = Symbol; //	Store the isin code for quick referenze
					}	
			if(strstr(Names[N], "#")== NULL && is(RUNNING)) {	
					asset(Names[N]);	
					Returns[N] = series((priceClose(0)-priceClose(1))/priceClose(1));	
					}	
			if(strstr(Names[N], "#")!= NULL && is(RUNNING)) Returns[N] = series(0);	
			if(N++ >= NN) break;	
			}	

	if(tdm() == 1 && !is(LOOKBACK)){ // 1st trading day of the month
		int i,j;	
		for(i=0; i<N; i++) {	
			Means[i] = Moment(Returns[i],LookBack,1);	
			for(j=0; j<N; j++)	
				Covariances[N*i+j] = Covariance(Returns[i],Returns[j],LookBack);	
			}	
		var BestVariance = markowitz(Covariances, Means, N, WEIGHTCAP);	
		var MinVariance = markowitzReturn(0,0);	
		markowitzReturn(Weights,MinVariance+VFactor/100.*(BestVariance-MinVariance));	

		for(i=0; i<N; i++)	
			if (strstr(Names[i], "#")== NULL){	
				asset(Names[i]);	
				MarginCost = priceClose()/LEVERAGE;	
				int NewLots = TotalCapital*Weights[i]/MarginCost;	// change the portfolio composition according to new weights
				if(NewLots > OldLots[i]) enterLong(NewLots-OldLots[i]);	
				else if(NewLots < OldLots[i]) exitLong(0,0,OldLots[i]-NewLots);	
				OldLots[i] = NewLots;	
				}	
		}	
	}	