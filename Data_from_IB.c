#define ASSET_LIST "AssetsPairsIBSTK"

function run() 
{
	//Verbose = 7|DIAG;
	
	NumYears = 1;
	GapDays = 3;
	assetList(strf("%s.csv", ASSET_LIST)); 
	brokerCommand(SET_PRICETYPE, 2); // Last trade mode
	
	while(loop(Assets))
	{
		assetHistory(Loop1,1);
	}
	quit();
}