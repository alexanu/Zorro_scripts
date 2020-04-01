// Dual Momemntum (Gary Antonacci)


#define NUMBEROFASSETS 100 // space for up to 100 assets

var assetWeight[NUMBEROFASSETS]; // hold index and performance stat of up to 1000 assets
int assetSorted[NUMBEROFASSETS]; // hold index of assetWeight sorted in decreasing order of performance
var myAssetType[NUMBEROFASSETS]; // whether asset in assetWeight is stock =1 or bond =0
vars Price[NUMBEROFASSETS]; // price history for each asset
int assetNum; // number of assets
int assetPlusNum; // number of assets with positive return

function bubbleSort() // sorts assetSorted to contain assetWeight indices in decreasing weight order
{
int i,s,tmp;
s=assetNum-1;
while(s>0){
        for(i=0;i<s;i++){
                if(assetWeight[assetSorted[i]]*pow(100,myAssetType[assetSorted[i]]) <
                assetWeight[assetSorted[i+1]]*pow(100,myAssetType[assetSorted[i+1]])){ 
				// stocks weigh "100 times" more while sorting, since they grow better than bonds
                        tmp=assetSorted[i];
                        assetSorted[i]=assetSorted[i+1];
                        assetSorted[i+1]=tmp;
                        }
                }
        s--;
        }
}

function run()
{
	set(LOGFILE+PRELOAD);

	BarPeriod = 1440;
	LookBack = 24*20; // 2Y
	StartDate = 2010;
	Capital = slider(1, 5000, 0, 7000, "Capital", "How much money you start trading with.");
	int myLookBack = 12; // for calculating return - 12 months
	int myDaysUpdate = 15; // after how many days to update trades

	if(is(INITRUN)) {
			assetList("History\\AssetsZ9.csv");
			}

	// Implement absolute momentum:
	assetNum=0;assetPlusNum=0;
	while(loop(Assets)) // portfolio loop to determine performance of each asset
			{
			asset(Loop1);
			assetHistory(Loop1, FROM_STOOQ);
			// assetHistory(Loop1, FROM_AV);
			Price[assetNum]=series(price());
			myAssetType[assetNum] = 1-AssetVar[0];

			// Baltas and Kosowski (2012): linear regression is the best momentum indicator
			assetWeight[assetNum]=LinearRegSlope(Price[assetNum],myLookBack*20)/ // 20 days per month
													Moment(Price[assetNum],myLookBack*20,1);
			if(assetWeight[assetNum]>0) // count up a wanted asset
					{ assetPlusNum++; }
			assetSorted[assetNum]=assetNum;
			assetNum++;
			}

	// Implement relative momentum:
	bubbleSort(); // sort AssetSorted to contain assetWeight indices in decreasing weight order

	static int dayspast=0;dayspast++; // increment days count until trade adjustment
	int i,enterNum=min((assetNum)/2,assetPlusNum); // Participate in at most 1/2 of winning assets

	if(dayspast>myDaysUpdate){ // update trades only once a time period myDaysUpdate
			for(i=enterNum;i<assetNum;i++){
						asset(Assets[assetSorted[i]]);
						exitLong(); // exit unwanted assets
						}
			var totalSlope=0;
			for(i=0;i<enterNum;i++){
						totalSlope=totalSlope+assetWeight[assetSorted[i]]; // determine the overall weight of wanted assets
						}
			for(i=0;i<enterNum;i++){ //
						asset(Assets[assetSorted[i]]);
						Stop=3*ATR(24*20);
						Lots=Capital*sqrt(1 + (WinTotal-LossTotal)/Capital)*Leverage/(4*enterNum*price()*LotAmount);
						if(NumOpenLong < 3 && (Equity - MarginVal)/(Capital+WinTotal-LossTotal) >0.33 )
						enterLong(); // enter wanted assets, each at the appropriate weight
						}
			dayspast=0; // reset the day counter after the trades
			}
	asset(Assets[0]);

	PlotWidth = 600;
	PlotHeight1 = 300; PlotHeight2 = 300;
	plot("$ Balance",Balance,NEW,BLUE);
	plot("Equity",Equity,0,GREEN);
	plot("BalanceInTrades",MarginVal,0,RED);

}