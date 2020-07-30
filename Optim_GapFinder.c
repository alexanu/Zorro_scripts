// Display gaps in historical data.
// Red lines = gap length in days. 

function run()
{
	StartDate = 2012;
	BarPeriod = 15;	
	LookBack = 0;

	// set(PLOTNOW);
	// var m = minutesAgo(1);
	// plot("Gap",m/(60*24),NEW,RED);

	string filename = "FXCM_GAPs.csv"; 

	if(is(INITRUN)) // specifying the header in the first run
	{
		char header[500];
		sprintf(header, "Asset, UTCDate, DoW, Time, Gap_Minutes, \n");
		file_delete(filename);
		file_append(filename, header);
	}

    while(asset(loop( // FXCM assets
		"AUD/USD","EUR/USD","EUR/CHF","GBP/USD","USD/CAD","USD/CHF","USD/JPY",
		"GER30","NAS100","SPX500","UK100","US30",
		"XAG/USD","XAU/USD"))) {

         var tdiff = (wdate() - wdate(1));	// time difference in days of the last consecutive bars
         if(tdiff > (BarPeriod/1440)*1.5 && dow() != 7) 
		// 1 day = 1440 minutes....	
		// search for time differences at 1.5 times longer than BarPeriod
		// skip gaps on Sundays
                  {	
 					char line[500];
					sprintf(line, "%s, %d-%02d-%02d, %i, %02d:%02d, %.0f, \n", 
					              Asset, year(), month(), day(), dow(), hour(), minute(),(wdate() - wdate(1))*1440);
					file_append(filename, line);
                  }	
         }	
}
