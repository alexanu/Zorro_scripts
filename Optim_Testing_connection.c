

int run() 
{
	BarPeriod = 1;
	LookBack = 0;


	// assetList("Single_Stock_CFD_FXCM");
    while(asset(loop(
		"AUD/USD","EUR/USD","EUR/CHF","GBP/USD","USD/CAD","USD/CHF","USD/JPY",
		"GER30","NAS100","SPX500","UK100","US30",
		"XAG/USD","XAU/USD"))) {
	// while(loop(Assets)) {

		printf("\n Latest closing price of %s is %.5f", Asset, priceClose());
	}

}
	

