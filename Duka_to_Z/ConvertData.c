#define SPREAD
//#define TCK
#include <default.c>
#include <stdio.h>

// already should contain ticks in reversed order
string basePath = "C:\\Data\\";
int start = 2015;
int end = 2016;

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
} SYSTEMTIME;

API(SystemTimeToVariantTime,oleaut32)
int _stdcall SystemTimeToVariantTime(SYSTEMTIME* lpSystemTime, double* pvtime);

DATE ConvertTime(int yr, int mth, int d, int hr, int mnt, int sec, int ms)
{
	SYSTEMTIME time;
	memset(&time, 0, sizeof(SYSTEMTIME));

	time.wYear = yr;
	time.wMonth = mth;
	time.wDay = d;
	time.wHour = hr;
	time.wMinute = mnt;
	time.wSecond = sec;
	
	DATE vTime;
	SystemTimeToVariantTime(&time, &vTime);
	
	// Add milliseconds
	vTime += (double) ms / 1000000 / 60 / 60 / 24;
	return vTime;
}

string readT1(string content, T1* ask, T1* bid)
{
	// Tokenize a single line	
	char* line = strtok(content,"\n");
	int yr, mth, d, hr, mnt, sec, ms = 0;
	float fBid = 0, fAsk = 0, fBidVol = 0, fAskVol = 0; 
  
   // Line format: "2010.01.03 17:00:00.123000,1.43010,1.43040,20.12,28.73"
	if(9 != sscanf(line,"%4d.%2d.%2d %2d:%2d:%2d.%6d,%f,%f",
		&yr, &mth, &d, &hr, &mnt, &sec, &ms, &fBid, &fAsk)) {
		printf("\nWrong line format!");
		return 0;
	}

	ask->fVal = fAsk;
	ask->time = ConvertTime(yr, mth, d, hr, mnt, sec, ms);
	
	if(bid != NULL)
	{
		bid->fVal = fBid;
		bid->time = ask->time;
	}
	// Return pointer to next line
	return line+strlen(line)+1;
}

string readT6(string content,T6* candle)
{
	// Tokenize a single line	
	char* line = strtok(content,"\n");
	if(!line) return 0;

	int yr, mth, d, hr, mnt, sec = 0; 
	float fVol;
	
	// Line format: 2016.10.21 21:59,0.76055,0.76073,0.76043,0.76055,0.00033

	if(10 != sscanf(line,"%4d.%2d.%2d %2d:%2d,%f,%f,%f,%f,%f",
		&yr, &mth, &d, &hr, &mnt,
		&candle->fOpen, &candle->fHigh, &candle->fLow, &candle->fClose, &candle->fVal)) 
		return 0;
	
	// Store the time in DATE format
	candle->time = ConvertTime(yr, mth, d, hr, mnt, 0, 0);
	// Return pointer to next line
	return line+strlen(line)+1;
}

int convertTickFiles(int startYear, int endYear, string smbl)
{
	FILE *fr;
	int y1;
	for(y1 = startYear; y1 <= endYear; y1++)
	{
		printf("\nProcessing year %d...", y1);
		char inName[256];
		char outNameAsk[256];
		char outNameBid[256];
		sprintf(inName, "%s%s_%d.csv", basePath, smbl, y1);
		sprintf(outNameAsk, "%s%s_%d.t1", basePath, smbl, y1);
		sprintf(outNameBid, "%s!%s_%d.t1", basePath, smbl, y1);
		file_delete(outNameAsk);
		file_delete(outNameBid);		
		printf("\nIn File: %s", inName);
		printf("\nOut Ask: %s", outNameAsk);
		printf("\nOut Bid: %s", outNameBid);
		
		if(!file_length(inName)) {
			printf("File %s not found, skipping.", inName);
			continue;
		}

		int i = 0;
		int maxticks = 60*24*365; 
		T1* asks = malloc(maxticks * sizeof(T1));
		T1* ask = asks;
		
		#ifdef SPREAD
			T1* bids = malloc(maxticks * sizeof(T1));
			T1* bid = bids;
		#endif

		fr = fopen(inName, "r");	
		char line[128];

		while(fgets(line, 128, fr)) 
		{
			++i;
			
			#ifdef SPREAD
				readT1(line, ask++, bid++);
			#else
				readT1(line, ask++, NULL);
			#endif

			if(i == maxticks)
			{	
				printf("\nSplit: %.5f / %.5f", (var)(ask-1)->time, (var)(ask-1)->fVal);			
				int size = (int)(ask)-(int)(asks);
				file_append(outNameAsk, asks, size);
				free(asks);
				asks = malloc(maxticks*sizeof(T1));
				ask = asks;
				
				#ifdef SPREAD
					file_append(outNameBid, bids, size);
					free(bids);
					bids = malloc(maxticks*sizeof(T1));
					bid = bids;
				#endif
				i = 0;
			}
		} // end while
	
		if(i > 0)
		{
			int size = (int)(ask)-(int)(asks);	
			
			#ifdef SPREAD
				file_append(outNameBid, bids, size);
				free(bids);
			#endif
			
			file_append(outNameAsk, asks, size);
			free(asks);
		} // end if(i > 0)
		fclose(fr);
	} // end for
}

int convertOhlcFiles(int startYear, int endYear, string smbl)
{
	int y1;
	for(y1 = start; y1 <= end; y1++)
	{
		printf("\nProcessing year %d...", y1);
		char inName[256];
		char outName[256];

		sprintf(inName, "%s%s_%d.csv", basePath, smbl, y1);
		sprintf(outName, "%s%s_%d.t6", basePath, smbl, y1);
		file_delete(outName);
		
		printf("\nIn File: %s", inName);
		printf("\nOut File: %s", outName);
		
		if(!file_length(inName)) {
			printf("File %s not found, skipping.", inName);
			continue;
		}
		
		string content = file_content(inName);
		printf("\nContent length: %d", strlen(content));
			
		// Allocate T6 array		
		int maxcandles = 60*24*365; 
		T6* candles = malloc(maxcandles*sizeof(T6));
	
		// Already contains ticks in reverse order	
		T6* candle = candles; 
		while(content) {
			content = readT6(content,candle++);
		}
		// Store the ticks
		int size = (int)(candle-1)-(int)(candles);
		file_write(outName, candles, size);	
	
		free(candles);
		printf("\nRead %d candles", size/sizeof(T6));
		free(content);
	}
}


function main()
{
	if(Command[0] > 1900) {
		start = Command[0];
	}
	if(Command[1] > 1900) {
		end = Command[1];
	}
	
	string smbl = strx(Asset, "/", "");
	
	#ifdef TCK
		convertTickFiles(start, end, smbl);
	#else
		convertOhlcFiles(start, end, smbl);
	#endif
	
}