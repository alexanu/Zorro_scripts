
#include <profile.c> // for e.g. plotPriceProfile



#ifdef FULLY_OPTIM
#endif

#ifdef STOP_OPTIM
#endif

#ifdef SMA_OPTIM
#endif

#ifdef SMA_AND_STOP_OPTIM
#endif

#ifdef ONLY_REINV_OPTIM
#endif

#ifdef NOT_OPTIM
#endif





#define DATE  20110501	// some historical date

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
	MaxBars = 210; // Maximum number of bars of the simulation. Equivalent of Enddate

	//out of sample data
	//StartDate = 20170101;
	//EndDate = 20171231;
    
	//in-sample data
	StartDate = 20120101;
	EndDate = 20161231;


	NumYears = 1;

	string Years = panelGet(1,0);
	if(!strstr(Years,"-")) // single date only
		StartDate = EndDate = atoi(Years);
	else {
		if(2 != sscanf(Years,"%4i-%4i",&StartDate,&EndDate)) {





	BarPeriod = 1440; // 1 day
	BarPeriod = 60;	// 1 hour bars
	BarPeriod = 240; 
		// Counter trend trading is affected by market cycles and more sensitive to the bar period than trend trading
		// Bar periods that are in sync with the worldwide markets - such as 4 or 8 hours - ...
		// ... are especially profitable with this type of trading
	BarPeriod = 1;



	BarZone = WET; // Western European midnight
	BarMode = BR_LEISURE;	// allows weekend bars, but don't trade on them

	TimeFrame = 4;
	while(algo(loop("H1","H4"))) TimeFrame = 1;
    if(Algo == "H1") TimeFrame = 4;
    else if(Algo == "H4") TimeFrame = 4*4;




// Assets -----------------------------------------------------------------------------------------------

function Assets()
{
	#define SYMBOLS "AUD/USD","USD/JPY","USD/CAD","GBP/USD","EUR/USD"
	while(asset(loop(SYMBOLS)))

	#define ASSETLOOP”EUR/USD” , ”GBP/USD” , ”USD/CAD” , ”AUD/USD” , ”USD/JPY” , ”XAU/USD” , ”XAG/USD” // No Stock
	// #define ASSETLOOP ”USD/CHF” , ”EUR/USD” , ”GBP/USD” , ”USD/CAD” , ”AUD/USD” , ”USD/JPY” ,”XAU/USD” , ”XAG/USD” , ”NAS100” , ”SPX500” ,”GER30” , ”US30” , ”UK100”
	// #define ASSETLOOP ”USD/CHF” , ”EUR/USD” , ”USD/JPY” , ”XAU/USD” , ”SPX500”//MIN FOREX SET
	// #define ASSETLOOP ”EUR/USD” // test asset
	while(asset(loop(ASSETLOOP)))

	assetList("AssetsIB");
	asset("SPY");
	asset("SPX500");  
    asset("EUR/USD");


	AssetList = "AssetsZ8.csv";	
	int N = 0;	
	while(Names[N] = loop(Assets)) { ...	}


	while(asset(loop("EUR/USD","AUD/USD","GBP/USD","USD/JPY"))) {}
	while(algo(loop("TRND","CNTR")))
    while(asset(loop( // FXCM assets
		"AUD/USD","EUR/USD","EUR/CHF","GBP/USD","USD/CAD","USD/CHF","USD/JPY",
		"GER30","NAS100","SPX500","UK100","US30",
		"XAG/USD","XAU/USD"))) {}


	while(Name = loop("AAPL", "MSFT", "GOOGL", "IBM", "MMM", "AMZN", "CAT", "CL"))
		{
		assetHistory(Name, FROM_AV);
		asset(Name);
		}

	if(is(INITRUN)) {
		assetAdd(ASSET);
		assetHistory(ASSET,FROM_AV);
		asset(ASSET);
	}


	if(is(INITRUN))
		{
		assetList("History\\AssetsDM.csv");
		string Name;
		while(Name = loop(Assets)) assetHistory(Name, FROM_AV);
		}


	while(loop(Assets))
	{
		asset(Loop1);
		...
	}




   StartDate = 20190101;
   assetAdd("SPY","STOOQ:SPY.US"); // load price history from Stooq
   asset("SPY");
   vars Prices = series(priceClose());


	History = ".t1";
	History = "*a.t6";	// reads price history from AAPL_2015a.t6
	History = "History\\Temp\\*.t1";	// reads tick data history from History\Temp\AAPL_2015.t1
	History = "D:\\Data\\Options\\*.t8";	// reads price history from option chains in D:\Data\Options\AAPL.t8

    LookBack = 0;



	if(strstr(Algo,"TRND") and strstr(Asset,"EUR/USD")) tradeTrend();



	if(!isForex(g->asset)) return;

	asset("EUR/CHF");
	var PriceCHF = price();
	asset("EUR/USD");
	var PriceUSD = price();


	// exclude USD/NOK and USD/SEK before 2008-04-07 because of data inconsistencies
		if (ymd(wdate(0)) < 20080403 && (Asset == "USD/NOK" || Asset == "USD/SEK")) prices[0] = 0;


	while(asset(loop("EUR/USD","AUD/USD","GBP/USD","USD/JPY"))) 
	while(algo(loop("ATRS", "ATR", "IS","PIP")))
		{
			if(Algo == "ATRS") After_Lunch_ATR_S();	
			else if(Algo == "ATR") After_Lunch_ATR();
			else if(Algo == "PIP") After_Lunch_PIP();
			else if(Algo == "IS") tradeIS();	
		}

}


// Indicators -----------------------------------------------------------------------------------------------

function Indicators()

{

	set(PARAMETERS|TESTNOW);  // generate and use optimized parameters
	#define METHOD	ASCENT
	//#define METHOD	BRUTE
	//#define METHOD	GENETIC
	set(PARAMETERS,TESTNOW,PLOTNOW);  // generate and use optimized parameters
	setf(TrainMode,METHOD);



	vars Price = series(price());
	vars CloseTS = series(priceClose());
	vars OpenTS = series(priceOpen());	

	var High = dayHigh(ET,1);

	diff(log(x)) // log return of x , since log(a/b) = log(a) - log(b)
	vars returns = series(ROCP(CloseTS, 1));

	vars Changes = series(diff(priceClose()));	
	vars volatility = series(100*sqrt(Moment(returns, 60, 2))); // int stddev_period = 60;


	vars MMI_Raw = series(MMI(Price,300)); // Is market trending or not? Market Meanness Index
	vars MMI_Smooth = series(LowPass(MMI_Raw,500)); // smooth it with the LowPass filter
	if(falling(MMI_Smooth)) {} // smoothed MMI is falling => beginning of a trend


	vars Trend = series(LowPass(Price, optimize(500,300,800))); // Like moving average but faster
	vars Trend = series(LowPass(series(price()),500));
	vars Osc = series(StochEhlers(series(price()),10,20,10));

	vars Filtered = series(BandPass(Price,optimize(30,20,40),0.5));
	// BandPass is similar to LowPass + it dampens short cycles => curve with medium-period peaks and valleys
	vars Signal = series(FisherN(Filtered,500)); // Normalisation in order to compare with threshold


	int days=22;
	vars prices = series(price());
	vars long_sma = series(SMA(prices, days));
	vars short_sma = series(SMA(prices, (int)(days * 0.1)));
	vars sma_factor = short_sma/long_sma - 1;
	vars price_to_sma_factor = prices / long_sma - 1;
	vars sma_slope_factor = short_sma/short_sma[1]



	#define VOL TradeVar[0]	// meaningful name for the element of the TradeVar
	int recordVol(var volatility)	
	{	
		VOL = volatility;	
		return 16;	// run the TMF only when the position is entered and exited
	}	
	function run()
	{...
		var vol = Moment(series(ROCP(close, 1)), 50, 2);	rolling 50-period standard deviation of returns
		enterLong(recordVol, vol);	Pass the TMF and the variable
		plot("volatility", vol, NEW, BLUE);
		...}


		
}


// Costs -----------------------------------------------------------------------------------------------

function costs()
{

	Commission = 0.6; // round turn commission of 60 cents per 10,000 contracts (avg of a Forex trade)
	Spread = 0.3*PIP;
	Spread = RollLong = RollShort = Commission = Slippage = 0;


	// PIPCost/PIP is the conversion factor from a price difference to a win or loss on the account
	var Cost = Commission*LotAmount/10000. + Spread*PIPCost/PIP;

	asset(ASSET_A);
	var SpreadA = Spread, PriceA = priceClose(), 
		CommissionA = Commission*LotAmount/10000*PIP/PIPCost; // convert commission to price difference	


	int n = 0;
	static var Cost[20];
	while(asset(loop("AUD/USD","EUR/USD","EUR/CHF","GBP/USD","USD/CAD","USD/CHF")))
	{
		if(is(INITRUN)) Cost[n] = 0;
		else Cost[n] += Spread/max(1*PIP,ATR(5));
		if(is(EXITRUN))	printf("\n%s - %.1f%%",Asset,100*Cost[n]/Bar);
		n++;
	}

	// If we’re trading soon after the FX market opens for the week (Sunday 5pm ET) ...
	// ... there’s a lot less liquidity than in normal trading hours. 
	// This means that spreads are much wider than normal: ...
	// ... e.g. for AUD/USD normal is 0.00009 (0.9 pips), after openning on Sunday, it is 4x times wider
	// Look on avg profit per trade - around 3 pips
	Spread = 3.5*PIP; 


}


// Capitals + hedging + profits ------------------------------------------------------------------------------------

function Capital()

{
	set(PARAMETERS,FACTORS,LOGFILE);  // generate and use optimized parameters and factors
	

	if(IsTrading && Equity-MarginVal < 1000))	// when there's not enough money in the acount …
	Lots = 0;	// … then stop trading
	else Lots = 1;	

    if(Equity - MarginVal < Capital) Lots = 0;


	if(LossStreakShort>= 4 ||LossStreakLong>= 4) // suspend trading after 4 losses in a row
	Lots = -1;	// phantom trades
	else Lots = 1;	

    Lots = pow(2, LossStreakTotal);  // Martingale position sizing

    Capital = 10000;



	int myCapital = 0; // Global Variable	
	var myMargin = 0; // Global Variable	
	var comp = 0; // Global Variable	
	myCapital = slider (1,2500,0,25000,"Capital", "Initial Capital");
	myMargin = slider (2,50,0,500, "Margin", "Initial Margin");
	comp = slider (3, 0, 0, 1, "Comp.", "0 = Fixed margin 1 = Comp Margin");

	function FSLong()	
        if (comp==1 && !is(TRAINMODE) {	// If compounding ...
                Margin = OptimalFLong * myMargin * sqrt (1 + max(0, (WinLong-LossLong)/myCapital)):	
                enterLong();	
        } else {	
                Margin = myMargin;	
                enterLong();	
        }	




	bool Reinvest = false;	
	bool UseOptimalF = true;	
	var CalculateMargin(int side)	
        {	
        var value = 0.1 * Capital;	
        if (Reinvest) value *= sqrt(Balance / Capital);	//value *= sqrt(1 + max(0, ProfitClosed/Capital));	
        if (UseOptimalF) value *= ifelse(side == LONG, OptimalFLong, OptimalFShort);	
        return value;	
        }	



	char name[40];	// string of maximal 39 characters
	strcpy(name,Asset);	
	strcat(name,":");	// Adds to the end
	strcat(name,Algo);	
	var equity = EquityShort+EquityLong;	// Plot equity curves of single assets
	if(equity != 0) plot(name,equity,NEW|AVG,BLUE);	



	char name[40];
	strcpy(name,Symbol);
	var equity = EquityShort+EquityLong;
	plot(name,equity,MAIN,color(random(100), RED, BLACK, BLUE, YELLOW));	




	// Profit -----------------------------------------

		// sum up open profits of all assets and the current algo
		var ProfitSum = 0;
		for(used_assets) {
			asset(Asset); // select the current component
			ProfitSum += ProfitOpen;
			}

		// sum up the profit/loss of all open trades with the current asset
		var val = 0;
		string CurrentAsset = Asset;
		for(open_trades)
		if(strstr(Asset,CurrentAsset) && TradeIsOpen && !TradeIsPhantom)
			val += TradeProfit;


	
		var Profit_Factor = WinTotal/max(1,LossTotal);


		vars Price = series(price());
		int num =NumRiseFall (Price,20);
		int pos = 3*num;
		plotBar("Price",pos,num,1,SUM+BARS,RED);


		for(open_trades) printf("\n%s profit %.2f",Asset,(var)TradeProfit);	// print profit of every trade

		plot("Neg Streak",LossStreakTotal,0,RED);



}

// Limits -----------------------------------------------------------------------------------------------

function Limits()
{
	LifeTime = 3; 
	LifeTime = optimize(25,1,200,10);
	EntryTime = LifeTime = 250; // close trades after 1 year


	MaxLong = MaxShort = 1;

	Stop = optimize(10,2,30) * ATR(100);
	Stop = optimize(5,1,10)*ATR(30);
	Stop = ATR(10) * optimize(3,1,10,0.5,-3); // allow 3% tolerance for preferring low stop distances
	Trail = 4*ATR(100);
	Trail = 0; // for trading trend
	Trail = 4*ATR(100); // 4 average candles away from the current price
		// Trailing often - not always - improves the profit of a strategy, ...
		// but is almost always better than placing a profit target
	TrailLock = 10;

	Stop = TakeProfit = ATR(100);
	TakeProfit = optimize(4, 1, 12, 1)*ATR(100);

	exitLong(0,NewStop); // Change stops of all open long trades with the current algo and asset
	exitLong(0,-NewTakeProfit);	// Change profit targets of all open long trades with the current algo and asset

	Entry = -(priceLow()-10*PIP);	// buy at 10 pips below the current Low
	enterLong(5, priceHigh(0) + 10*PIP); // buy 5 lots if price reaches 10 points above the previous high	


	// if the trade goes into profit, ...
	// ... move the stop loss to the lowest low of the previous 5 periods, ...
	// ... if that value exceeds the existing stop loss:
	if (TradeProfit > 0) TradeStopLimit = max(TradeStopLimit, LL(5));


	BuyStop = priceHigh() + 1*PIP;
	BuyLimit = priceHigh() + 5*PIP;
	if(!NumOpenLong && Fast[0] > Slow[0] && Price[0] < BuyLimit)
		enterLong(1,BuyStop);


	// lock 80% profit of all winning trades
		for(open_trades) 
		{
			if(TradeIsOpen && !TradeIsPool && TradeProfit > 0) 
			{
				TradeTrailLock = 0.80;
				if(TradeIsShort) TradeTrailLimit = max(TradeTrailLimit,TradePriceClose);
				else TradeTrailLimit = min(TradeTrailLimit,TradePriceClose);
			}
		}

	// increase the stop of all winning trades slowly over time
		for(open_trades) 
		{  
			if(TradeProfit > 0 && !TradeIsPool)    
				TradeStopLimit -= 0.02 * TradeStopDiff;
		}



	// used as a trailing Stop Loss,...
	// ... for keeping trades in a trend and ...
	// ... preventing an early exit as long as the trend continues
		int Chandelier(var TimePeriod,var Multiplier)	
			{	
			if(TradeIsLong) TradeStopLimit = max(TradeStopLimit,ChandelierLong(TimePeriod,Multiplier));
		  								// = (highest price of TimePeriod) - ATR() * Multiplier
			else TradeStopLimit = min(TradeStopLimit,ChandelierShort(TimePeriod,Multiplier));	
			return 8; // from TMF: only update once per bar
			}	
		...	
		if(LongSignal) {	
				Stop = ChandelierLong(22,3);	
				enterLong(Chandelier,22,3);	
			}	


	// Call this function before entering a trade for not entering trades at the same time
	void setDelay(var Seconds)	
		{	
		static int PrevBar = 0;	
		static var Delay = 0;	
		if(Bar != PrevBar) {	// reset delay at any new bar
			Delay = 0;	
			PrevBar = Bar;	
			}	
		Delay += Seconds;	// increase delay within the bar
		OrderDelay = Delay;	
		Entry= -0.2*PIP * sqrt(Delay);	// entry limit for additional profit
		}	



	plot("Stp",TradeStopLimit,DOT,RED);
	plot("Prft",TradeProfitLimit,DOT,BLUE);

}


// Time conditions -----------------------------------------------------------------------------------------------

function Time_Condition()
{
/* 
Limit a strategy’s entry rules to only one or two conditions. 
Any more than this invites curve-fitting and leads to poor out-of-sample performance.
*/

	if(NumOpenLong == 0) {
		if((tom(0) ==tdm(0)) &&hour()>= 12) enterLong();// If it is UTC midday at the last day of the month…
		} else if(tdm(0) >= 2)	exitLong();


	if(High > 0 && Low > 0 && Close > 0 
		&& timeOffset(ET,0,9,30) == 0) 	// enter a trade at the 9:30 bar when the NYSE opens 


	if(ldow(EST)==7 and lhour(EST)==18 and minute() == 30) // Sunday 6:30pm Eastern (market has been open 90 minutes)
	if(between(lhour(CET),9,13))	// European business hours


	if(dow()== FRIDAY && hour()>= 18) { // On Friday afternoon GMT
		exitLong("*"); // exit all open trades
		exitShort("*");
		}


	// Weekend change
		// Option 1:
		if(dow() == SUNDAY &&lhour(ET) == 5) {	// wait until Sunday 5pm ET (use 1-hour bars)…
			int FridayBar = timeOffset(ET,SUNDAY-FRIDAY,5,0); // … then get the price change from Friday 5pm ET
			var PriceChange = priceClose(0) - priceClose(FridayBar);	
			}
		// Option 2:
		static var gap_returns[NUM_ASSETS];
		int i, barsAgo;
		if(ldow(ET)==7 and lhour(ET)==17 and minute() == 10) // 10 mins after open on Sunday 5pm eastern
		{
			for(i=0; Assets[i]; i++)
			{
				asset(Assets[i]);
				barsAgo = timeOffset(ET, 2, 17, 0);  // Friday 5pm eastern
				gap_returns[i] = (priceOpen() - priceClose(barsAgo))/priceClose(barsAgo);  
			} 
		}



	if(between(ltod(ET), 700, 1100)) plot("Open NY", closes, 0, RED); // highlighting with different color



	var session1TZ = WET; // JST
	var session1Start = 8; // 9
	var session1End = 16; // 16
	var session2TZ = ET;
	var session2Start = 11; // 11 equals 16 WET, 9 = 16 JST
	var session2End = 17;
	...
	if (dow()>= 1 && dow()<= 5) {	
        if (NumOpenShort == 0 && lhour(session1TZ) == session1Start) enterShort();	
        if (NumOpenShort > 0 && lhour(session1TZ) == session1End) exitShort();	
        if (NumOpenLong == 0 && lhour(session2TZ) == session2Start) enterLong();	
        if (NumOpenLong > 0 && lhour(session2TZ) == session2End) exitLong();	
        }	




	BarPeriod = 60;
	while(asset(loop("EUR/USD", "USD/JPY", "SPX500")))
	while(algo(loop("H1", "H4", "D1")))
	{
		if(Algo == "H1") TimeFrame = 60/BarPeriod;
		else if(Algo == "H4") TimeFrame = 240/BarPeriod;
		else if(Algo == "D1") TimeFrame = 1440/BarPeriod;
		vars Price = series(price());
		...
	}

	// exclude USD/NOK and USD/SEK before 2008-04-07 because of data inconsistencies
	if (ymd(wdate(0)) < 20080403 && (Asset == "USD/NOK" || Asset == "USD/SEK")) prices[0] = 0;
			
}

// Other conditions -----------------------------------------------------------------------------------------------

function Trade_Condition()
{
/* 
Limit a strategy’s entry rules to only one or two conditions. 
Any more than this invites curve-fitting and leads to poor out-of-sample performance.
*/


	BuyStop = priceHigh() + 1*PIP;
	BuyLimit = priceHigh() + 5*PIP;
	if(!NumOpenLong && Fast[0] > Slow[0] && Price[0] < BuyLimit) enterLong(1,BuyStop);

	if(falling(MMI_Smooth)) {} // smoothed MMI is falling => beginning of a trend


	var dayL = optimize(40,10,80);
	var dayS = optimize(40,10,80);
	if (priceHigh() >= HH(dayL)) enterLong();
	else if(priceLow() <= LL(dayS)) enterShort();


	if(price(0) > price(1)) enterLong();
	else if(price(0) < price(1)) enterShort();


	vars Close = series(priceClose());
	vars Open = series(priceOpen());
	if(Close[0] > Open[0]) enterLong();


	vars Price = series(price());
	vars Trend = series(LowPass(series(price()),100));	
	if (crossOver(Price, Trend)) enterLong();	
	else if (crossUnder(Price, Trend)) enterShort();	



	if(NumOpenTotal == 0) {}
	if(NumOpenTotal + NumPendingTotal > 200) break; // place not more than 200 trades		
	if(NumOpenLong< 3) enterlong();


	// suspend trading after 4 losses in a row
	if(LossStreakShort>= 4 ||LossStreakLong>= 4) Lots = -1;	phantom trades
	else Lots = 1;	



	if(strstr(Algo,"TRND") and strstr(Asset,"EUR/USD")) tradeTrend();

	if (tradeLong == true)
		{
		exitShort("*");
		enterLong();
		tradeShort = false;
		}

	// eturns nonzero when Condition became true the first time in a session or simulation cycle
	if(once(!is(LOOKBACK))) printf("\nEnd of lookback reached!");
}

// Print -----------------------------------------------------------------------------------------------

function Printing()
{
    printf("\nDownloading %s chain.. ",Asset);
    printf("\nCall %i %.2f: Ask %.2f Bid %.2f",ContractExpiry,ContractStrike,ContractAsk,ContractBid);
	if(is(EXITRUN))	printf("\nTrade costs in percent of volatility - - - - - -");

	for(open_trades) printf("\n%s profit %.2f",Asset,(var)TradeProfit);	// print profit of every trade

	printf("Yesterday's closing price: \%.5f", priceClose(0));	//print the previous closing price:


	printf("n ##### priceClose %.5f, myATR %.5f, Spread %.5f, EntryLong %.5f, EntryShort %.5f", 
			priceClose(0), myATR, Spread, myEntryPriceLong, myEntryPriceShort);

	printf("\n[%s.%.0f]  A %.5f  B %.5f", strdate(HMS,0),1000.*modf(second(),0),PriceA,PriceB);


	printf("\nH %i  B %s Eq %s M %s  Px %s",
			Hedge,
			sftoa(Balance,2),
			sftoa(Equity,2),
			sftoa(MarginVal,2),
			sftoa(priceClose(0),5));


	while(asset(loop("AUD/USD","EUR/USD","EUR/CHF","GBP/USD","USD/CAD","USD/CHF")))
	{
		if(is(INITRUN)) Cost[n] = 0;
		else Cost[n] += Spread/max(1*PIP,ATR(5));
		if(is(EXITRUN))	printf("\n%s - %.1f%%",Asset,100*Cost[n]/Bar);
		n++;
	}



	for(open_trades) {
		if(TradeIsPending) printf("\n%s still pending",strtr(ThisTrade));
		else printf("\n%s Lots: %i Target: %i",strtr(ThisTrade),TradeLots,TradeLotsTarget);
	}



	if(is(EXITRUN))
         {
         int count = 0;
         char line[100];
         string filename = "Log\\vol.csv";
         sprintf(line, "Asset, EntryDate, TradeReturn");
         file_append(filename, line);
         for(closed_trades)
                  {
                  sprintf(line, "\n%s, %i, %.6f", 
				  					Asset, 
									ymd(TradeDate), 
									(-2*TradeIsShort+1)*(TradePriceClose-TradePriceOpen)/TradePriceOpen);
                  file_append(filename, line);
                  count++;
                  }
         printf("\nTrades: %i", count);
		 }
}

// Ploting ----------------------------------------------------------------------------------

function Plotting ()

{

    setf(PlotMode, PL_ALL);
    set(PLOTNOW,LOGFILE);

	PlotBars = 400; // number of bars to plot in the chart. Default - all
	// PlotStart = 20181231; // start of the chart


	PlotScale = 8; // bigger symbols
	PlotWidth = 800;
	// PlotHeight1 = 350; // Height of the main chart
	// PlotHeight2 = 80; // Height of additional charts (plot with type=NEW)
	PlotHeight1 = PlotHeight2;

	plot("Filtered",Filtered,NEW,BLUE);
	plot("Signal",Signal,NEW,RED);
	plot("Threshold1",1,0,BLACK);
	plot("Threshold2",-1,0,BLACK);


	asset(""); // dummy asset
	
	ColorWin = ColorLoss = 0; // don't plot trades
	ColorDD = ColorEquity = 0; // don't plot Equty and drawdowns
	ColorUp = ColorDn = 0; // don't plot a price curve, but plot Equty and trades

	plot("lowpass",lowpass(series(price()),30),LINE,RED);


	asset("EUR/USD");
	vars closes = series(priceClose());
	if(between(ltod(ET), 700, 1100)) plot("Open NY", closes, 0, RED); // highlighting with different color


	plot("Neg Streak",LossStreakTotal,0,RED);
	plot("Trades",NumOpenTotal,0+AXIS2,BLUE);


	plot("Stp",TradeStopLimit,DOT,RED);
	plot("Prft",TradeProfitLimit,DOT,BLUE);


	char name[40];	// string of maximal 39 characters
	strcpy(name,Asset);	
	strcat(name,":");	// Adds to the end
	strcat(name,Algo);	
	var equity = EquityShort+EquityLong;	// Plot equity curves of single assets
	if(equity != 0) plot(name,equity,NEW|AVG,BLUE);	



	var equity;
	int i;
	string Name;
	for(i=0; Name=Assets[i]; i++)
	{
		asset(Name);
		equity += EquityShort+EquityLong;
	}
	plot(Algo,equity,NEW|AVG|BARS,color);


	char name[40];
	strcpy(name,Symbol);
	var equity = EquityShort+EquityLong;
	plot(name,equity,MAIN,color(random(100), RED, BLACK, BLUE, YELLOW));	



	vars Price = series(price());
	int num =NumRiseFall (Price,20);
	int pos = 3*num;
	plotBar("Price",pos,num,1,SUM+BARS,RED);



}
