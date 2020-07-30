// Source: https://github.com/AndrewAMD/zorro_snippets/blob/master/zorro_folder/Strategy/alphavantage_downloader.c


#include <default.c>


// AlphaVantage downloader
string AVParseFormat = "%Y-%m-%d,f3,f1,f2,f4,f7,f6,f8"; // We need f7/f4 for adjustments
const char* can_get_av_key();
const char* get_av_daily_adj_csv(const char* symbol, bool compact);
void do_download_eod_av(string asset_list);
#define AV_RATE_LIMITING // if defined, will do rate limiting with AlphaVantage, 5 per minute
void filter_data(void);

void filter_data(void){
	printf("\nLaunching data filter...");
	for(listed_assets){
		asset(Asset);
		const char* file_in = strf(".\\History\\%s.t6",Asset);
		const char* file_out = strf(".\\History\\%s.t6",Asset);
		int h = 1;
		int n = dataLoad(h,file_in,7); //t6 file
		if(!n){
			printf("\ndataLoad failure!");
			continue;
		}
		int i;
		for(i=0;i<n;i++){
			dataSet(h,i,1,roundto(dataVar(h,i,1),PIP));
			dataSet(h,i,2,roundto(dataVar(h,i,2),PIP));
			dataSet(h,i,3,roundto(dataVar(h,i,3),PIP));
			dataSet(h,i,4,roundto(dataVar(h,i,4),PIP));
		}
		dataSave(h,file_out);
	}
	printf("\nData filtration complete.");
}



// ******** ALPHAVANTAGE DOWNLOADER ********  
void do_download_eod_av(string asset_list){
	printf("\nBeginning AV download...");
	if(!can_get_av_key()){
		return;
	}
	
	
	assetList(asset_list);
	for(listed_assets){
		if(!wait(1)) return;
		
		string Content;
		bool pass = false;
		int i, numtries=5;
		for(i=1;i<=numtries;i++){
			Content = get_av_daily_adj_csv(Asset,false);
			if(Content){
				pass = true;
				break;
			}
			else{
				printf("\nDownload %s attempt %d of %d failed.",Asset,i,numtries);
				if(i<numtries){
					printf("\npause one minute...");
					if(!wait(60000)){
						printf("\naborted!");
						return;
					}
				}
			}
		}
		if(!pass){
			printf("\nSkipping Asset: %s",Asset);
			continue;
		}
		
		string TempFile = strf("History\\%s_av_adj.csv",Asset);
		file_write(TempFile,Content,0);
		// convert the CSV to .t8
		dataNew(1,0,0);
		int N = dataParse(1,AVParseFormat,TempFile);
		if(!N) {
			printf("%s invalid content",TempFile);
			return;
		}
		//dataSave(1,strf("History\\%s_unadjusted.t8",Asset)); //diagnostic only
		printf("\n%s: %i records read",Asset,N);
		
		dataNew(2,N,7); // t6 file
		int i;
		for(i=0;i<N;i++){
			var da,op,hi,lo,cl,vo,cl_adj;
			da = dataVar(1,i,0);
			op = dataVar(1,i,3);
			hi = dataVar(1,i,1);
			lo = dataVar(1,i,2);
			cl = dataVar(1,i,4);
			vo = dataVar(1,i,6);
			cl_adj = dataVar(1,i,7);
			var ra = cl_adj/cl;
			dataSet(2,i,0,(var)da);
			dataSet(2,i,3,(var)(op * ra));
			dataSet(2,i,1,(var)(hi * ra));
			dataSet(2,i,2,(var)(lo * ra));
			dataSet(2,i,4,(var)(cl * ra));
			dataSet(2,i,6,(var)vo);
		}
		dataSave(2,strf("History\\%s.t6",Asset));

		#ifdef AV_RATE_LIMITING
		static int i = 0;
		i++;
		if(i==5){
			printf("\nRate limiting. Pause one minute...");
			if(!wait(60000)) return;
			i=0;
		}
		#endif
	}
	filter_data();
}

// returns AV key string
const char* can_get_av_key(){
	static char out[128];
	static bool ready = false;
	if(ready) return &out[0]; // no need to repeat
	memset(out,0,128);
	
	// read zorro.ini file
	char* ini = file_content("Zorro.ini");
	if(!strlen(ini)){printf("\nZorro.ini failed to load"); return NULL;}
	// parse for av key
	
	char* output = strtext(ini, "AVApiKey", "");
	// check for bad outcome, if so return false
	if(!strlen(output)){printf("\nini parse came up empty!"); return NULL;}
		
	// output av key return true
	strcpy(out,output);
	ready = true;
	return &out[0];
}


const char* get_av_daily_adj_csv(const char* symbol, bool compact){
	static char* out = 0;
	if(out) {
		//free(out);
		out = 0;
	}
	
	const char* fn = "TIME_SERIES_DAILY_ADJUSTED";
	char* outputsize = 0;
	if(compact) outputsize = "compact";
	else outputsize = "full";
	
	const char* datatype = "csv";
	const char* apikey = can_get_av_key();
	if(!apikey){
		printf("\nCannot load AlphaVantage Key! Check Zorro.ini");
		return NULL;
	}
	
	char url[512];
	sprintf(
		url,
		"https://www.alphavantage.co/query?function=%s&symbol=%s&outputsize=%s&apikey=%s&datatype=%s",
		fn,
		symbol,
		outputsize,
		apikey,
		datatype);
	//printf("\nurl: %s", url);
	
	int h = http_send(url,0,0);
	int bytes = 0;
	while(1){
		bytes = http_status(h);
		if(bytes==0) // still in progress
		{
			if(!wait(100))  // pause 100ms, abort if necessary
			{
				http_free(h);
				return NULL;
			}
		} 
		else if ((bytes == -1) || (bytes == -2)) // failed or invalid
		{
			http_free(h);
			return NULL;
		}
		else // transfer completed
			break;
	}
	
	printf("\nbytes: %d",bytes);
	//get the string
	out = zalloc(bytes+1);
	//memset(out,0,bytes);
	http_result(h,out,bytes);

	//free the handle
	http_free(h);
	
	//check for html failure
	if(out[0]=='<'){
		printf("\nError: HTML detected!");
		printf("\n%s",out);
		//free(out);
		out = 0;
	}
	
	//check for json message
	if(out[0]=='{'){
		printf("\nError: JSON detected!");
		printf("\n%s",out);
		//free(out);
		out = 0;
	}
		
	return out;
}
