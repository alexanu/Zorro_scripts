////////////////////////////////////////////////
// Convert price history from .csv to .t6
// The Format string determines the CSV format (see examples)
////////////////////////////////////////////////

#define SPLIT_YEARS	// split into separate years
#define FIX_ZONE	5 // add a time zone difference, f.i. original is in EST, we need UTC
// #define REMOVE_SPACES // was used for txt files



// string InName = "DAT_ASCII_USDZAR_M1_2015.csv";  // name of a single year CSV file
// string OutName = "USDZAR.t6";

// string InName = ".\\sierra_csv\\continuous\\ESM19-BarData.txt";
// string OutName = "ES_continuous.t6";

//string InName = "D:\\History\\VIX_2013_2016.stk";
//string OutName = "VIX"; // for separate years, f.i. VIX_2016.t6, VIX_2015.t6 etc.


string InName ="D:\\Data\\A.txt";
string OutName = "A.t6";
// line format OHLC Vol
string Format = "+0%Y%m%d,%H:%M,f3,f1,f2,f4,f6"; // unadjusted


// HISTDATA line format: "20100103 170000;1.430100;1.430400;1.430100;1.430400;0"
// string Format = "+%Y%m%d %H%M%S;f3;f1;f2;f4;f6;f";

// YAHOO line format "2015-05-29,43.45,43.59,42.81,42.94,10901500,42.94"
//string Format = "%Y-%m-%d,f3,f1,f2,f4,f6,f5"; // unadjusted

// TRADESTATION line format "06/30/2016,17:00:00,2086.50,2086.50,2086.50,2086.50,319,0"
//string Format = "+%m/%d/%Y,%H:%M:%S,f3,f1,f2,f4,f6,f5";

// STK line format "12/23/2016,2300.00,SPY, 225.63, 225.68, 225.72, 225.62,1148991"
//string Format = "+-%m/%d/%Y,%H%M,,f3,f4,f1,f2,f6,f";

function main()
{
	#ifdef REMOVE_SPACES
         {
         string original = file_content(InName);
         if(!original){
                  printf("\nError, cannot read original file!");
                  return;
                  }
         string output;
         int i;
         int j;
         int len = strlen(original);
         output = malloc(len);
         if(!output){
                  printf("\nMalloc failed!");
                  return;
                  }
         memset(output,0,len);
         for(i=0; i< len; i++){
                  char ch = original[i];
                  switch(ch){
                           case ' ':
                                    break;
                           default:
                                    output[j] = ch;
                                    j++;
                           }
                  }
         file_write(InName, output, strlen(output));
         }
#endif // REMOVE_SPACES


	int Records = dataParse(1,Format,InName);
	printf("\n%d lines read",Records);

#ifdef FIX_ZONE
	int i;
	for(i=0; i<Records; i++)
		dataSet(1,i,0,dataVar(1,i,0)+FIX_ZONE/24.);
#endif

#ifndef SPLIT_YEARS
	if(Records) dataSave(1,OutName);
#else
	int i, Start = 0, Year, LastYear = 0;
	for(i=0; i<Records; i++) {
		Year = atoi(strdate("%Y",dataVar(1,i,0)));
		if(!LastYear) LastYear = Year;
		if(i == Records-1) { // end of file
			LastYear = Year; Year = 0;
		}
		if(Year != LastYear) {
			string NewName = strf("%s_%4i.t6",strxc(OutName,'.',0),LastYear);
			printf("\n%s",NewName);		
			dataSave(1,NewName,Start,i-Start);
			Start = i;
			LastYear = Year;
		}
	}
#endif
}