// Price Distribution Chart /////////////////////

function run()
{
	StartDate = 20110920; // First day of the CHF price cap
	EndDate = 20150114; // Last day of the CHF price cap

	asset("EUR/CHF");
	var PriceCHF = price();
	asset("EUR/USD");
	var PriceUSD = price();
// plot distributions separately (otherwise only the selected asset is plotted)	
	if(PriceCHF > 1.2020) // suppress the border peak at ~1.2010
		plotBar("EUR/CHF",250*PriceCHF,PriceCHF,1,SUM+BARS+LBL2,BLACK);	
	if(PriceUSD > 0.)
		plotBar("EUR/USD",250*PriceUSD,PriceUSD,1,SUM+BARS+LBL2,GREY+TRANSP);
//	vars Random = series(1.3);
//		Random[0] = Random[1] + 0.005*random();
//	plotBar("Random",500*(Random[0]-1.20),Random[0],1,SUM+BARS+LBL2,BLUE+TRANSP);
}