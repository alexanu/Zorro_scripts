// Download EOD data from any online source to a .t6 history file /////////////////

// the symbol that you want to download
string Ticker = "AAPL.US";
// the API url of the online source ("%s" is replaced with the symbol name)
string URL = "https://stooq.pl/q/d/l/?s=%s&i=d";
// the CSV format string (for details see manual about "dataParse")
string Format = "+%Y-%m-%d,f3,f1,f2,f4,f6";

void main()
{
	string Api = strf(URL,Ticker);
	string Content = http_transfer(Api,0);
	if(!Content) {
		printf("Can't access %s",Api);
		return;
	}
	string TempFile = "History\\history.csv";
	file_write(TempFile,Content,0);
// convert the CSV to .t8
	int N = dataParse(1,Format,TempFile);
	if(!N) {
		printf("%s invalid content",TempFile);
		return;
	}
// replace '.','/' in ticker name with '-'
	dataSave(1,strf("History\\%s.t6",strxc(strxc(Ticker,'.','-'),'/','-')));
	printf("%i %s records read",N,Ticker);
}