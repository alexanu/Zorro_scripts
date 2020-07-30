// Update Assets.csv and/or download price history of a certain asset (or all)
// Select the account (Demo/Real) before.
// See remarks in the manual under "History".

#define MAX_GAP	3
#define VERBOSE	3
//#define DO_OVERRIDE	// enforce download even if history is up to date
//#define ASSETLIST	"AssetsFXCM"
//#define ASSET	"ES-FUTX-20181221-ES-GLOBEX-USD"
//#define ASSET	"IUSQ-STK-SMART-EUR"

BOOL Loading = FALSE;

int Download()
{
/*	if(!is(TRADEMODE)) {
		printf("\nClick [Trade] to download assets!");
		quit();
		return 0;
	}*/
	
	int Mode = 1;
	if(panelGet(4,0) == "Stooq")
		Mode = FROM_STOOQ;
	else if(panelGet(4,0) == "Yahoo")
		Mode = FROM_YAHOO;
	else if(panelGet(4,0) == "AlphaVantage")
		Mode = FROM_AV;
	else if(panelGet(2,0) == "Tick")
		Mode = 0;
	else if(panelGet(2,0) == "EOD")
		Mode = 3;
	if(Mode > 1 && panelGet(3,0) == "Unadjusted")
		Mode |= UNADJUSTED; 
#ifdef DO_OVERRIDE
	Mode |= OVERRIDE;
#endif
	if(panelGet(3,0) == "Trades")
		brokerCommand(SET_PRICETYPE,2);
	else
		brokerCommand(SET_PRICETYPE,1);
	if(panelGet(3,0) == "Assetlist")
		NumYears = -1;
	else
		NumYears = 0;
	
	string Years = panelGet(1,0);
	if(!strstr(Years,"-")) // single date only
		StartDate = EndDate = atoi(Years);
	else {
		if(2 != sscanf(Years,"%4i-%4i",&StartDate,&EndDate)) {
			printf("\nSyntax error!"); return 0; }
	}
	if(StartDate > EndDate) {
		printf("\nWrong dates!"); return 0; }

	string Name = panelGet(0,0);
	printf("\nDownload...");
	Loading = TRUE;
	if(strstr(Name,"Assets") || strstr(Name,".csv")) {
		assetList(Name);
		for(listed_assets)
			assetHistory(0,Mode);
	} else
		assetHistory(Name,Mode);
	
	Loading = FALSE;
	return 1; // date ok	
}

void click(int row,int col)
{
	if(Loading || !is(RUNNING)) return; // don't click while downloading data
	sound("click.wav");	
	string Text = panelGet(row,col);
	
	if(Text == "M1") panelSet(row,col,"Tick",0,0,0); 
	else if(Text == "Tick") panelSet(row,col,"EOD",0,0,0); 
	else if(Text == "EOD") panelSet(row,col,"M1",0,0,0); 
	
	else if(Text == "Ask/Bid") panelSet(row,col,"Trades",0,0,0); 
	else if(Text == "Trades") panelSet(row,col,"Unadjusted",0,0,0); 
	else if(Text == "Unadjusted") panelSet(row,col,"Assetlist",0,0,0); 
	else if(Text == "Assetlist") panelSet(row,col,"Ask/Bid",0,0,0); 
	
	else if(Text == "Broker") panelSet(row,col,"Stooq",0,0,0); 
	else if(Text == "Stooq") panelSet(row,col,"Yahoo",0,0,0); 
	else if(Text == "Yahoo") panelSet(row,col,"AlphaVantage",0,0,0); 
	else if(Text == "AlphaVantage") panelSet(row,col,"Broker",0,0,0); 
	
	else if(Text == "Download!") 
		if(Download() && Live) quit("Done");
}


void main()
{
	LookBack = 0;
	StartDate = EndDate = year(NOW);
	GapDays = MAX_GAP;	// detect gaps
	Verbose = VERBOSE;
	set(NOLOCK);	// allow API access to other Zorros
	
	panel(6,1,GREY,90);
	print(TO_PANEL,"Download");
	int n = 0; // 1=Asset oder Liste,2=Year
#ifdef ASSETLIST
	assetList(ASSETLIST);
#endif
#ifdef ASSET
	assetAdd(ASSET);
	panelSet(n++,0,ASSET,ColorPanel[2],1,2);
#else
	panelSet(n++,0,Asset,ColorPanel[2],1,2);
#endif
	panelSet(n++,0,strf("%i-%i",StartDate,EndDate),ColorPanel[2],1,2);
	panelSet(n++,0,"M1",ColorPanel[3],1,4); // M1 - Tick - EOD
	panelSet(n++,0,"Ask/Bid",ColorPanel[3],1,4); // Ask/Bid - Trades - Unadjusted - Assetlist 
	panelSet(n++,0,"Broker",ColorPanel[3],1,4); // Broker - STOOQ - AV
	panelSet(n++,0,"Download!",ColorPanel[3],1,4);

	while(wait(100)); // wait for panel entry
	panel(0,0,0,0); // remove panel
}