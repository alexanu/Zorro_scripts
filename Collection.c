#define DATE  20110501	// some historical date
#define ASSET_A "EURUSD_A"



#ifndef DATE	
	if(!Live || Broker != "IB") {
		printf("\nStart in Trade mode with IB TWS!");
		return;
	}
	StartDate = NOW;
#else
	StartDate = DATE;
#endif

	StartDate = 20120101;
	EndDate = 20181231;
    EndDate = StartDate + 0100; // 1 month
	StartDate = 2010;
	EndDate = 2018;
    StartDate = EndDate = 2014;
	StartDate = EndDate = year(NOW);
	EndDate = 20171231; // fixed simulation period 
	NumYears = 1;

	string Years = panelGet(1,0);
	if(!strstr(Years,"-")) // single date only
		StartDate = EndDate = atoi(Years);
	else {
		if(2 != sscanf(Years,"%4i-%4i",&StartDate,&EndDate)) {






	BarPeriod = 1440; // 1 day
	BarPeriod = 60;	// 1 hour bars
    
    LookBack = 0;



	BarZone = WET; // Western European midnight
	BarMode = BR_LEISURE;	// allows weekend bars, but don't trade on them



	set(PARAMETERS,FACTORS,LOGFILE);  // generate and use optimized parameters and factors
    set(PLOTNOW,LOGFILE);
	set(LOGFILE|PLOTNOW);
	set(PLOTNOW|LEAN|PRELOAD); // reload prices after any cycle
	set(TICKS,FAST);






	assetList("AssetsIB");
	asset("SPY");
	asset("SPX500");  
    asset("EUR/USD");
    while(asset(loop("EUR/USD","USD/JPY"))) {
	while(asset(loop("EUR/USD","AUD/USD","GBP/USD")))
	

	while(algo(loop("TRND","CNTR")))
    while(asset(loop(
		"AUD/USD","EUR/USD","EUR/CHF","GBP/USD","USD/CAD","USD/CHF","USD/JPY",
		"GER30","NAS100","SPX500","UK100","US30",
		"XAG/USD","XAU/USD"))) {

	if(is(INITRUN)) {
		assetAdd(ASSET);
		assetHistory(ASSET,FROM_AV);
		asset(ASSET);
	}

	asset("EUR/CHF");
	var PriceCHF = price();
	asset("EUR/USD");
	var PriceUSD = price();



	TimeFrame = 4;




	vars Price = series(price());
	var High = dayHigh(ET,1);
	vars MMI_Raws = series(MMI(Prices,300));
    var LP30 = LowPass(Price,30);
	var LP100 = LowPass(Price,100);
    vars R = series(LP30);
	vars Osc = series(StochEhlers(series(price()),10,20,10));




	Commission = 0.6;
	Spread = 0.3*PIP;
	Spread = RollLong = RollShort = Commission = Slippage = 0;
	var Cost = Commission*LotAmount/10000. + Spread*PIPCost/PIP;

	asset(ASSET_A);
	var SpreadA = Spread, PriceA = priceClose(), 
		CommissionA = Commission*LotAmount/10000*PIP/PIPCost; // convert commission to price difference	



	LifeTime = 3; 
	EntryTime = LifeTime = 250; // close trades after 1 year
	MaxLong = MaxShort = 1;
	Stop = optimize(10,2,30) * ATR(100);
	Trail = 4*ATR(100);
	Trail = 0; // for trading trend
	Stop = TakeProfit = ATR(100);



	if(NumOpenTotal == 0) {
	if(NumOpenTotal + NumPendingTotal > 200) break; // place not more than 200 trades		


	if(NumOpenLong == 0) {
		if((tom(0) ==tdm(0)) &&hour()>= 12) // If it is UTC midday at the last day of the month…
		enterLong();
	} else if(tdm(0) >= 2)
		exitLong();


	BuyStop = priceHigh() + 1*PIP;
	BuyLimit = priceHigh() + 5*PIP;
	if(!NumOpenLong && Fast[0] > Slow[0] && Price[0] < BuyLimit)
		enterLong(1,BuyStop);


	if(High > 0 && Low > 0 && Close > 0 
		&& timeOffset(ET,0,9,30) == 0) 	// enter a trade at the 9:30 bar when the NYSE opens 










    printf("\nDownloading %s chain.. ",Asset);
    printf("\nCall %i %.2f: Ask %.2f Bid %.2f",
        ContractExpiry,ContractStrike,ContractAsk,ContractBid);
	if(is(EXITRUN))
		printf("\nTrade costs in percent of volatility - - - - - -");


// plot signals and thresholds
	plot("Filtered",Filtered,NEW,BLUE);
	plot("Signal",Signal,NEW,RED);
	plot("Threshold1",1,0,BLACK);
	plot("Threshold2",-1,0,BLACK);

    plot("Filtered",BandPass(Price,24,0.1),NEW,BLACK);

	plot("MMI_Raw",MMI_Raws,NEW,GREY);
