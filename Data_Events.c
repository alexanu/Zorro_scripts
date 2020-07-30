////////////////////////////////////////////////
// Trading Iniial Jobless Claims
////////////////////////////////////////////////

#define FIX_ZONE	5 // add a time zone difference, f.i. original is in EST, we need UTC


string FileName = "Data\\IJC_test.csv"; // Iniial Jobless Claims


//DateTime;TimestampMillis;Currency;Country;Name;ImpactFactor;Previous;Consensus;Actual
//07.01.2010 13:30;1.26287E+12;USD;United_States;Initial_Jobless_Claims;2;433;449;433
string Format = "+0%d.%m.%Y %H:%M;;s;s;s;i;;f;f;f"

int N,Row,Record,Records;	


Records = dataParse(1,Format,FileName);	// read BBO data
printf("\n%d rows read",Records);	
if(!Records) return;


#ifdef FIX_ZONE
	int i;
	for(i=0; i<Records; i++)
		dataSet(1,i,0,dataVar(1,i,0)+FIX_ZONE/24.);
#endif




for(Record = 0,Row = 0; Record < Records; Record++)	{
    float Price = 0.01 * dataInt(1,Record,3);	// price in cents
    string AskBid = dataStr(1,Record,2);	
    time = dataVar(1,Record,0) + 1./24.; // add 1 hour Chicago-NY time difference
 		O->fStrike = dataVar(1,i,2);
		O->fAsk = dataVar(1,i,5);
		O->fBid = dataVar(1,i,6);
		O->fVol = dataVar(1,i,7);


    Row++;	

}