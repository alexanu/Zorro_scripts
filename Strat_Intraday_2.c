void run() {	
        set(LOGFILE); // could print the hour and lhour to the log for checking

		BarPeriod = 15;
		StartDate = 2010;
		EndDate = 2019;
		asset("USD/JPY");

		int timezone = JST;	
		if(lhour(timezone) == 10 && minute() == 00) enterShort();
		if(lhour(timezone) == 12 && minute() == 30) exitShort();

        BarZone = JST;
        if(hour() == 10 && minute() == 00) enterShort();
        if(hour() == 12 && minute() == 30) exitShort();
	}	