// Trade Test for Broker API Verification ///////////////////

#define PERCENTSTOP	// stop in percent of price
//#define BY_MARGIN		// Margin instead of lots
#define MAXLOTS	50		// slider endpoint
#define MAXLIMIT	0.5	// OrderLimit in multiples of spread
//#define USE_LOOKBACK	80
#define VERBOSE	3
//#define LOG_ACCOUNT
#define LOG_TRADES
#define LOG_VOL		// log volume, spread, margin cost
//#define LOG_BOOK
//#define RESUME			// resume open trades in next session
//#define TYPE_TRADES	// last trade price instead of current ask/bid
//#define DIAGNOSTICS	2
//#define ROLLSTART	(1<<23)
//#define ORDERTEXT	"MOC/" // special order types for IB
//#define EXCHANGE	"BTRX"
//#define RECORD			// store asset prices
#define ROUND_LIMIT	// round order limit to 1 pip (needed for IB)
//#define ASSETLIST	"AssetsSP30"
//#define ASSET "DAX-FUT-20171215-FDAX-DTB-EUR"
//#define ASSET "ES-FUT-20200320-ES-GLOBEX"
//#define ASSET "EUR-FUT-20181015-6E-GLOBEX-USD"
//#define MAXREQUESTS	10./60	// 10 requests per minute

///////////////////////////////////////////////////////////
int AutoTrade = 0;
int OrderMode = 0;

int tradeAdapt(var Step)
{
	if(!TradeIsOpen) { // entry limit
		if(TradeIsLong) {
			if(OrderLimit > TradePriceOpen) 
				return 0; 	// try no more
			OrderLimit += Step;	// adapt limit
		} else { // short
			if(OrderLimit < TradePriceOpen-Spread) 
				return 0; 	
			OrderLimit -= Step;
		}
	} else { // exit limit
		if(TradeIsLong)
			OrderLimit -= Step;
		else
			OrderLimit += Step;
	}
	OrderLimit = roundto(OrderLimit,PIP/2);
	return 1;
}

// TMF with adaptive entry/exit algorithm
int tmf()
{
//	printf("\nTMF: %f/%f\\%f/%f",priceOpen(),priceHigh(),priceLow(),priceClose());
// adapt limit of FOK/IOC trades
	if(TradeIsMissed && OrderMode >= 2) 
	{
		var Step = max(0.333*Spread,0.333*PIP);
		if(OrderMode == 2) // FOK order
			OrderDelay = 30;	// try again in 30 seconds
		else // GTC order, no delay needed
			OrderDelay = 0;
		if(!tradeAdapt(Step)) 
			return 1; // cancel trade
		else {
			printf("\n%s Limit %s",strtr(ThisTrade),sftoa(OrderLimit,5));
			return ifelse(TradeIsOpen,1+16,2+16); // repeat order, and trigger tmf at next event
		} 
	}
	return 16;
}

void setLimit(var Factor)
{
	OrderLimit = OrderDelay = OrderDuration = 0;
	resf(TradeMode,TR_GTC);
	if(OrderMode == 1) {
		OrderLimit = priceClose() + Factor*Spread; 
		printf(" Limit %s",sftoa(OrderLimit,5));
	} else if(OrderMode == 2) {
		OrderLimit = priceClose() + ifelse(Factor<0,-Spread,0.);
		printf(" Adaptive %s",sftoa(OrderLimit,5));
	} else if(OrderMode == 3) {
		OrderLimit = priceClose() + Factor*Spread;
		OrderDuration = 30;
		setf(TradeMode,TR_GTC);
		printf(" GTC %s",sftoa(OrderLimit,5));
	}
#ifdef ROUND_LIMIT
	OrderLimit = roundto(OrderLimit,PIP);
	printf("\nRounded Limit: %.4f",OrderLimit);
#endif
#ifdef ROLLSTART
	setf(AssetMode,ROLLSTART);
	RollLong = RollShort = -0.5;
#endif
}

void doTrade(int What,var Factor)
{
#ifdef BY_MARGIN
	Margin = slider(1);
#else
	Lots = slider(1);	// get current slider position
#endif
#ifdef PERCENTSTOP
	if(slider(2) > 0)
		Stop = Trail = roundto(0.01*priceClose()*slider(2),PIP);
	else
		Stop = 0;
#else
	Stop = Trail = PIP*slider(2);
#endif
	//if(OrderMode) TradeMode &= ~TR_MAIN; //else TradeMode |= TR_MAIN;
#ifdef ORDERTEXT
	brokerCommand(SET_ORDERTEXT,ORDERTEXT);
#endif
	setLimit(Factor);
	if(What == 1)
		enterLong(tmf);
	else if(What == 2)
		enterShort(tmf);
	else if(What == 3) {
#ifdef BY_MARGIN
		exitLong();
#else
		exitLong(0,0,Lots);
#endif
	} else if(What == 4) {
#ifdef BY_MARGIN
		exitShort();
#else
		exitShort(0,0,Lots);
#endif
	}
}

void click(int row,int col)
{
	if(!is(RUNNING)) return; // only clickable when session is active
	sound("click.wav");	
	
	if(row == -3) { // Asset Box
		panelSet(4,0,AssetBox);
		asset(AssetBox);
		return;
	}
	
	string Text = panelGet(row,col);
	if(Text == "Auto Off") {
		panelSet(row,col,"Auto On",0,0,0); 
		AutoTrade = 1;
	}
	else if(Text == "Auto On") {
		panelSet(row,col,"Auto Off",0,0,0); 
		AutoTrade = 0;
	}
	else if(Text == "NFA Off") {
		panelSet(row,col,"NFA On",0,0,0); 
		set(NFA);
	}
	else if(Text == "NFA On") {
		panelSet(row,col,"NFA Off",0,0,0); 
		set(NFA|OFF);
	}
	else if(Text == "Hedge 0") {
		panelSet(row,col,"Hedge 2",0,0,0); 
		Hedge = 2;
	}
	else if(Text == "Hedge 2") {
		panelSet(row,col,"Hedge 4",0,0,0); 
		Hedge = 4;
	}
	else if(Text == "Hedge 4") {
		panelSet(row,col,"Hedge 5",0,0,0); 
		Hedge = 5;
	}
	else if(Text == "Hedge 5") {
		panelSet(row,col,"Hedge 0",0,0,0); 
		Hedge = 1;
	}
	else if(Text == "MKT Order") {
		panelSet(row,col,"LMT Order",0,0,0); 
		OrderMode = 1;
	}
	else if(Text == "LMT Order") {
		panelSet(row,col,"Adaptive",0,0,0); 
		OrderMode = 2;
	}
	else if(Text == "Adaptive") {
		panelSet(row,col,"GTC Order",0,0,0); 
		OrderMode = 3;
	}
	else if(Text == "GTC Order") {
		panelSet(row,col,"MKT Order",0,0,0); 
		OrderMode = 0;
	} else if(row == 4) { // new asset name
		char Name[NAMESIZE2];
		strcpy(Name,strmid(Text,0,NAMESIZE2-1));
		assetAdd(Name,Text); 
		asset(Name);
	} else {
		printf("\n%s %s",Text,Asset);
		if(Text == "Buy Long")
			call(1,doTrade,1,-MAXLIMIT);
		else if(Text == "Buy Short")
			call(1,doTrade,2,MAXLIMIT);
		else if(Text == "Close Long")
			call(1,doTrade,3,MAXLIMIT);
		else if(Text == "Close Short")
			call(1,doTrade,4,-MAXLIMIT);
		else if(Text == "Update Stop") {
			exitShort(0,priceClose()+Stop);	
			exitLong(0,priceClose()-Stop);	
		}
		OrderLimit = 0;
	}
}

function run()
{
	if(is(TESTMODE)) {
		quit("Click [Trade]!");
		return;
	}
	if(is(INITRUN))
		AutoTrade = OrderMode = 0;
	
	BarPeriod = 1;
	PlotPeriod = 5;
	NumYears = 1;
	LookBack = 0;
	TradesPerBar = 1;
#ifdef USE_LOOKBACK
	LookBack = USE_LOOKBACK;
#endif
	Verbose = VERBOSE;

	Weekend = 0;	
#ifndef RESUME
	SaveMode = 0;
#endif
	TickTime = 1000;
	set(LOGFILE);
	//set(SAV_STATS);
	
#ifdef ASSETLIST
	assetList(ASSETLIST);
#endif
#ifdef EXCHANGE
	if(is(INITRUN)) brokerCommand(SET_BROKER,EXCHANGE);
#endif
#ifdef ASSET
	assetAdd(ASSET);
	asset(ASSET);
#else
	asset(Asset);
#endif

#ifdef BY_MARGIN
	Margin = slider(1,100,0,100*MAXLOTS,"Margin",0);
#else
	Lots = slider(1,MAXLOTS/4,0,MAXLOTS,"Lots",0);
#endif
#ifdef PERCENTSTOP	
	Stop = Trail = 0.01*priceClose()*slider(2,0,0,40,"Stop %",0);
#else
	Stop = Trail = PIP*slider(2,0,0,50,"Stop",0);
#endif

	if(is(INITRUN)) brokerCommand(SET_ORDERTEXT,"TradeTest");
#ifdef DIAGNOSTICS
	if(is(INITRUN)) brokerCommand(SET_DIAGNOSTICS,DIAGNOSTICS);
#endif
#ifdef TYPE_TRADES
	if(is(INITRUN)) brokerCommand(SET_PRICETYPE,2);
	if(is(INITRUN)) brokerCommand(SET_VOLTYPE,4);
#else
	if(is(INITRUN)) brokerCommand(SET_PRICETYPE,1);
#endif

	if(is(INITRUN)) {
		AutoTrade = 0;
		Hedge = 2;
		panel(9,1,GREY,80);
		int n = 0;
		panelSet(n++,0,"Auto Off",ColorPanel[2],1,4);
		if(mode(NFA)) 
			panelSet(n++,0,"NFA On",ColorPanel[2],1,4);
		else
			panelSet(n++,0,"NFA Off",ColorPanel[2],1,4);
		panelSet(n++,0,"Hedge 2",ColorPanel[2],1,4);
		panelSet(n++,0,"MKT Order",ColorPanel[2],1,4);
		panelSet(n++,0,Asset,ColorPanel[2],1,2);
		panelSet(n++,0,"Buy Long",ColorPanel[3],1,4);
		panelSet(n++,0,"Buy Short",ColorPanel[3],1,4);
		panelSet(n++,0,"Close Long",ColorPanel[3],1,4);
		panelSet(n++,0,"Close Short",ColorPanel[3],1,4);
		panelSet(n++,0,"Update Stop",ColorPanel[3],1,4);

#ifdef MAXREQUESTS
		MaxRequests = MAXREQUESTS;
#endif
		if(MaxRequests > 0) printf("\nMax Requests: %.1f / sec",MaxRequests);
	}
	
	if(AutoTrade) {	
		asset(panelGet(4,0));
		if(NumOpenTotal >= 3) {
			exitLong();
			exitShort();
		} else {
			if(price(0) > price(1)) enterLong();
			else if(price(0) < price(1)) enterShort();
		}
	}
	if(!is(LOOKBACK)) {
#ifdef LOG_ACCOUNT
_POS(10);
		printf("\nN %i H %i  B %s Eq %s M %s  Px %s",
			ifelse(is(NFA),1,0),Hedge,
			sftoa(Balance,2),sftoa(Equity,2),sftoa(MarginVal,2),
			sftoa(priceClose(0),5));
_POS(20);
		var Pos = brokerCommand(GET_POSITION,Symbol);
		if(Pos != 0) printf(" T %.2f",Pos);
#endif
#ifdef LOG_TRADES		
		for(open_trades) {
			if(TradeIsPending) printf("\n%s still pending",strtr(ThisTrade));
			else printf("\n%s Lots: %i Target: %i",strtr(ThisTrade),TradeLots,TradeLotsTarget);
		}
#endif
		int x=1;
	}
#ifdef LOG_VOL
	if(!is(LOOKBACK)) 
		printf("\nVol %s  Spr %s  MCost %s",sftoa(marketVol(),2),sftoa(Spread,2),sftoa(MarginCost,2));
#endif
#ifdef LOG_BOOK
	static T2 Quotes[MAX_QUOTES];
	brokerCommand(SET_SYMBOL,Symbol);
	int N = brokerCommand(GET_BOOK,Quotes);
	printf("\nOrderbook: %i quotes",N);
#endif
#ifdef RECORD
	History = "rec.t6";
	priceRecord();
#endif
}