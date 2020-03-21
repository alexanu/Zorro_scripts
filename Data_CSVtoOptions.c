// Example script for converting CSV EOD options data to .t8:
// Format: underlying symbol, exchange, date MMDDYYYY, adj close, option symbol, expiry MMDDYYYY, strike, Call/Put, American/European, ask, bid, volume, open interest, unadj close
// Sample: "TLT,NYSEArca,04/10/2015,129.62,TLT   150410C00112500,04/10/2015,112.5,C,A,17.3,16.2,0,0,129.62"

int Year = 2018;
string Ticker = "TLT"; // File name: TLT_2018.csv
string Format = ",,%m/%d/%Y,,,i,f,s,s,f,f,f,f,f"; // from the sample above

void main() 
{
// first step: parse the CSV file into a dataset
	int Records = dataParse(1,Format,strf("History\\%s_%i.csv",Ticker,Year));
	printf("\n%d %s Records parsed",Records,Ticker);
	if(!Records) return;
// second step: convert the raw data to the final CONTRACT format
	int i;
	for(i=0; i<Records; i++) {
		CONTRACT* O = dataAppendRow(2,9);
		O->time = dataVar(1,i,0);
		string PC = dataStr(1,i,3);
		string EA = dataStr(1,i,4);
		O->Type = ifelse(*PC == 'P',PUT,CALL) + ifelse(*EA == 'E',EUROPEAN,0);
		int Expiry = dataInt(1,i,1); 
		O->Expiry = 10000*(Expiry%10000) + Expiry/10000; // MMDDYYYY -> YYYYMMDD
		O->fStrike = dataVar(1,i,2);
		O->fAsk = dataVar(1,i,5);
		O->fBid = dataVar(1,i,6);
		O->fVol = dataVar(1,i,7);
		O->fVal = dataVar(1,i,8); // open interest
		O->fUnl = dataVar(1,i,9);
		if(!progress(100*i/Records,0)) break; // show a progress bar
	}
	dataSort(2);
	dataSave(2,strf("History\\%s_%1.t8",Ticker,Year));
}