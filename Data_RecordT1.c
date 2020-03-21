// Record ticks to .t1 files ////////////////////////////////////////

void tick()
{
	T1* Ask = dataAppendRow(1,2);
	Ask->time = wdate();
	Ask->fVal = priceClose();
	T1* Bid = dataAppendRow(1,2);
	Bid->time = wdate();
	Bid->fVal = -(priceClose()-Spread);
}

void click()
{
	dataSort(1);
	dataSave(1,strf("History\\%srec.t1",strx(Asset,"/","")));
	quit("Done!");
}

void run()
{
	if(!Live) { quit("Start in [Trade] mode!"); return; }
	BarPeriod = 1;
	TickTime = 100;
	LookBack = 0;
	panelSet(-1,-1,"Save");
}

