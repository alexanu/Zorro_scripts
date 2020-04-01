#define SYMBOLS "AUD/USD","USD/JPY","USD/CAD","GBP/USD","EUR/USD"

#define FORMAT_FX_LONG "\n%04i-%02i-%02i %02i:%02i, %.5f, %.5f, %.5f, %.5f, %s" // OHLC and name of Asset in last column
#define FORMAT_NOT_FX_LONG "\n%04i-%02i-%02i %02i:%02i, %.1f, %.1f, %.1f, %.1f, %s" // OHLC and name of Asset in last column


function write_to_csv()
{
	string Format = ifelse(assetType(Asset) == FOREX,FORMAT_FX_LONG,FORMAT_NOT_FX_LONG);
	char FileName[40];
	// sprintf(FileName,"History\\%s.csv",strx(Asset,"/","")); // separate file for every asset
	sprintf(FileName,"History\\Test.csv"); // one file for all assets

	char My_Name[40];
	strcat(My_Name,Asset);
	
	if(is(INITRUN))
	file_write(FileName,"Date,Open,High,Low,Close",0);
	// file_delete("Data\\export.csv");
	else
	file_append(FileName,strf(Format,
                                        year(),month(),day(),hour(),minute(),
                                        round(priceOpen(),0.1*PIP),
                                        round(priceHigh(),0.1*PIP),
                                        round(priceLow(),0.1*PIP),
                                        round(priceClose(),0.1*PIP),
				  	My_Name));
}


function run() 
{
	BarPeriod = 120;  //2 hours
	StartDate = EndDate = 20190107;
	LookBack = 0;
	
	while(asset(loop(SYMBOLS)))	write_to_csv();
}

# ----------------------------------------------------------------------------------------------------------------------------

#define FORMAT_FX_SHORT "\n%04i-%02i-%02i %02i:%02i, %.5f, %.5f" // only 1 value
#define FORMAT_NOT_FX_SHORT "\n%04i-%02i-%02i %02i:%02i, %.1f, %.1f" // only 1 value

function run() 
{
	BarPeriod = 1440; // 1 day
	StartDate = 2008;
	EndDate = 2012;	

	LookBack = 0;
	
	asset("EUR/CHF");
	var PriceCHF = price();
	asset("EUR/USD");
	var PriceUSD = price();

	string Format = FORMAT_FX_SHORT;
	
	if(is(INITRUN))
	file_write("History\\Test1.csv","Date,USD,CHF",0);
	else
	file_append("History\\Test1.csv",strf(Format,
                                         year(),month(),day(),hour(),minute(),
                                         PriceCHF,PriceUSD));
}

