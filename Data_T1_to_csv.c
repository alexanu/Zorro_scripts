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
