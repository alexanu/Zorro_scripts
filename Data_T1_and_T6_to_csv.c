// Source: https://gitlab.com/snippets/34036

function run()
{
	Weekend = 0;
	History=".t1";
	set(TICKS);
	BarPeriod = 0.1/60.0;
	UnstablePeriod = 0;
	LookBack = 0;
	StartDate = 2015;
	EndDate = 2015;

	string format = "\n%04i.%02i.%02i %02i:%02i:%.2g,%f";
	char fileName[40];
	sprintf(fileName, "History\\%s.csv", strx(Asset,"/","")); // remove slash from forex pairs
	
	if(is(INITRUN))
		file_write(fileName, "Date,Price", 0);
	else
		file_append(fileName, strf(format,
			year(),month(),day(),hour(),minute(),second(),
			price()));
}

//----------------------------------------------------------------------------------

string Source = "..\\Zorro\\History\\AAPL.t6";
string Target = "History\\Export1.csv";

function main()
{
     file_delete(Target);
     if(strstr(Source,".t6")) {
          T6 *Ticks = file_content(Source);
          int nTicks = file_length(Source)/sizeof(T6);
          while(nTicks--)
               {
               T6 *t = Ticks+nTicks;
               file_append(Target,strf("%s,%.5f,%.5f,%.5f,%.5f\n",
                                        strdate("%Y/%m/%d %H:%M:%S", t->time),
                                        (var)t->fOpen, (var)t->fHigh, (var)t->fLow, (var)t->fClose));
               }
     } else if(strstr(Source,".t1")) {
          T1 *Ticks = file_content(Source);
          int nTicks = file_length(Source)/sizeof(T1);
          while(nTicks--)
               {
               T1 *t = Ticks+nTicks;
               file_append(Target,strf("%s,%.5f\n",
                                        strdate("%Y/%m/%d %H:%M:%S", t->time),
                                        (var)t->fVal));
               }
          }
     printf("\nDone!");
}

// ------------------------------------------------------------------------------------------

// Export historic price data to a .csv file 
// f.i. "31/12/12 00:00, 1.32205, 1.32341, 1.32157, 1.32278"
string Format = "%02i/%02i/%02i %02i:%02i, %.5f, %.5f, %.5f, %.5f\n"

function run()	
     {	
     BarPeriod = 1440;	
     StartDate = 2008;	
     EndDate = 2012;	
     LookBack = 0;	
     string line = strf(Format,	
                    day(),month(),year()%100,hour(),minute(),	
                    priceOpen(),priceHigh(),priceLow(),priceClose());	
     if(is(INITRUN))	
          file_delete("Data\\export.csv");	
     else	
          file_append("Data\\export.csv",line);	
}	


// ------------------------------------------------------------------------------------------


