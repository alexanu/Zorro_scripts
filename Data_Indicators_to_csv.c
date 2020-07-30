
// script to export values of various parameters
 
void export_variables(int zone, int barPeriod)
{
	vars Close = series(priceClose());
	vars Returns = series((Close[0]-Close[1])/Close[1]);
	vars filterFast = series(LowPass(Close, 50));
	vars filterSlow = series(LowPass(Close, 200));
	vars filterDiff = series(filterFast[0] - filterSlow[0]);
		
	//custom daily bars 
	AssetZone = zone;
	FrameOffset = (60/barPeriod) * 8; //calculate at 8am
	TimeFrame = AssetFrame;
	
	vars closeDaily = series(priceClose());
	vars priceDaily = series(price());
	vars ReturnsDaily = series((closeDaily[0]-closeDaily[1])/closeDaily[1]);
	
	vars filterFastDaily = series(LowPass(closeDaily, 50));
	vars filterSlowDaily = series(LowPass(closeDaily, 200));
	vars filterDiffDaily = series(filterFastDaily[0] - filterSlowDaily[0]);
		
	TimeFrame = 1; //return to base time frame
	
	//EXPORT VARIABLES
	string filename = "variables.csv"; // If we don’t specify a path, the file will be saved in the root Zorro directory
	
	if(is(INITRUN)) // specifying the header in the first run
	{
		char header[500];
		sprintf(header, "Asset, TimeZone, UTCDateTime, LocalTime, LocalDoW, Close, DailyClose, FilterDiff, FilterDiffDaily, \n");
		file_delete(filename);
		file_append(filename, header);
	}
		
	char line[500];
	sprintf(line, "%s, %d, %02i/%02i/%02i %04i, %04i, %01i, %.5f, %.5f, %.5f,%.5f\n", Asset, zone, day(),month(),year(), tod(), ltod(zone), ldow(zone), Close[0], closeDaily[0], filterDiff[0], filterDiffDaily[0]);
	file_append("variables.csv", line);
 
}
 
function set_parameter(string parameter)
{
	switch (Asset)
	{
		case "EUR/USD":
		switch (parameter)
		{
			case "TimeZone" : return WET;
	
		}
		case "GBP/USD":
		switch (parameter)
		{
			case "TimeZone" : return WET;
	
		}
		case "AUD/USD":
		switch (parameter)
		{
			case "TimeZone" : return AEST;
	
		}
	}
}
 
function run()
{
	StartDate = 20160101;
	EndDate = 20161231;
	BarPeriod = 60;
	while(asset(loop("EUR/USD", "GBP/USD", "AUD/USD")))
	{
		int start_zone = set_parameter("TimeZone"); //switch time zone to local time of asset
		export_variables(start_zone, BarPeriod);
	}	
}
 
/* OUTPUT
Asset,TimeZone,UTCDateTime,LocalTime,LocalDoW,Close,DailyClose,FilterDiff,FilterDiffDaily
EUR/USD,0,28/12/2015,1300,1300,1,1.09738,1.09886,-0.00004,0
GBP/USD,0,28/12/2015,1300,1300,1,1.49085,1.49079,0,0
AUD/USD,10,28/12/2015,1300,2300,1,0.72673,0.72608,0.00002,0
EUR/USD,0,28/12/2015,1400,1400,1,1.09749,1.09886,-0.00012,0
GBP/USD,0,28/12/2015,1400,1400,1,1.49063,1.49079,0,0
*/