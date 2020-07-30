// #define FULLY_OPTIM	
// #define STOP_OPTIM	
// #define SMA_OPTIM	
// #define SMA_AND_STOP_OPTIM	
// #define ONLY_REINV_OPTIM
#define NOT_OPTIM


function tradeOneNightStand()	
    {	
	#ifdef FULLY_OPTIM
        vars Price = series(price());	
        vars SMAShort = series(SMA(Price, optimize(10,5,20)));	
        vars SMALong = series(SMA(Price, optimize(40,30,80,5)));	
        
        Stop = optimize(100,100,500,10) * PIP;	
        var BuyStop = HH(10) + 1*PIP;	
        var SellStop = LL(10) - 1*PIP;	
        
        if(between(tow(),42355,50005)) {	// check the time interval around thursday midnight 
            if (SMAShort[0] > SMALong[0] && rising(SMAShort) && rising(SMALong) && NumOpenLong == 0 && NumPendingLong == 0) {	
                Margin = 0.1 * OptimalFLong * Capital * sqrt(1 + ProfitClosed/Capital);	
                enterLong(0,BuyStop);	
                }	
            else if (SMAShort[0] < SMALong[0] && falling(SMAShort) && falling(SMALong) && NumOpenShort == 0 && NumPendingShort == 0) {	
                Margin = 0.1 * OptimalFShort * Capital * sqrt(1 + ProfitClosed/Capital);	
                enterShort(0,SellStop);	
                }	
            }	    
    #endif

	#ifdef STOP_OPTIM
        vars Price = series(price());	
        vars SMAShort = series(SMA(Price, 10));	
        vars SMALong = series(SMA(Price, 40));	
        
        Stop = optimize(100,100,500,10) * PIP;	
        var BuyStop = HH(10) + 1*PIP;	
        var SellStop = LL(10) - 1*PIP;	
        
        if(between(tow(),42355,50005)) {	// check the time interval around thursday midnight 
            if (SMAShort[0] > SMALong[0] && rising(SMAShort) && rising(SMALong) && NumOpenLong == 0 && NumPendingLong == 0) {	
                enterLong(0,BuyStop);	
                }	
            else if (SMAShort[0] < SMALong[0] && falling(SMAShort) && falling(SMALong) && NumOpenShort == 0 && NumPendingShort == 0) {	
                enterShort(0,SellStop);	
                }	
            }	
    #endif

	#ifdef SMA_OPTIM
        vars Price = series(price());	
        vars SMAShort = series(SMA(Price, optimize(10,5,20)));	
        vars SMALong = series(SMA(Price, optimize(40,30,80,5)));	
        
        Stop = 100 * PIP;	
        var BuyStop = HH(10) + 1*PIP;	
        var SellStop = LL(10) - 1*PIP;	
        
        if(between(tow(),42355,50005)) {	// check the time interval around thursday midnight 
            if (SMAShort[0] > SMALong[0] && rising(SMAShort) && rising(SMALong) && NumOpenLong == 0 && NumPendingLong == 0) {	
                enterLong(0,BuyStop);	
                }	
            else if (SMAShort[0] < SMALong[0] && falling(SMAShort) && falling(SMALong) && NumOpenShort == 0 && NumPendingShort == 0) {	
                enterShort(0,SellStop);	
                }	
            }	
    #endif

	#ifdef SMA_AND_STOP_OPTIM
        vars Price = series(price());	
        vars SMAShort = series(SMA(Price, optimize(10,5,20)));	
        vars SMALong = series(SMA(Price, optimize(40,30,80,5)));	
        
        Stop = optimize(100,100,500,10) * PIP;	
        var BuyStop = HH(10) + 1*PIP;	
        var SellStop = LL(10) - 1*PIP;	
        
        if(between(tow(),42355,50005)) {	// check the time interval around thursday midnight 
            if (SMAShort[0] > SMALong[0] && rising(SMAShort) && rising(SMALong) && NumOpenLong == 0 && NumPendingLong == 0) {	
                enterLong(0,BuyStop);	
                }	
            else if (SMAShort[0] < SMALong[0] && falling(SMAShort) && falling(SMALong) && NumOpenShort == 0 && NumPendingShort == 0) {	
                enterShort(0,SellStop);	
                }	
            }	
    #endif

	#ifdef ONLY_REINV_OPTIM
        vars Price = series(price());	
        vars SMAShort = series(SMA(Price, 10));	
        vars SMALong = series(SMA(Price, 40));	
        
        Stop = 100 * PIP;	
        var BuyStop = HH(10) + 1*PIP;	
        var SellStop = LL(10) - 1*PIP;	
        
        if(between(tow(),42355,50005)) {	// check the time interval around thursday midnight 
            if (SMAShort[0] > SMALong[0] && rising(SMAShort) && rising(SMALong) && NumOpenLong == 0 && NumPendingLong == 0) {	
                Margin = 0.1 * OptimalFLong * Capital * sqrt(1 + ProfitClosed/Capital);	
                enterLong(0,BuyStop);	
                }	
            else if (SMAShort[0] < SMALong[0] && falling(SMAShort) && falling(SMALong) && NumOpenShort == 0 && NumPendingShort == 0) {	
                Margin = 0.1 * OptimalFShort * Capital * sqrt(1 + ProfitClosed/Capital);	
                enterShort(0,SellStop);	
                }	
            }	    
    #endif


	#ifdef NOT_OPTIM
        vars Price = series(price());	
        vars SMAShort = series(SMA(Price, 10));	
        vars SMALong = series(SMA(Price, 40));	
        
        Stop = 100 * PIP;	
        var BuyStop = HH(10) + 1*PIP;	
        var SellStop = LL(10) - 1*PIP;	
        
        if(between(tow(),42355,50005)) {	// check the time interval around thursday midnight 
            if (SMAShort[0] > SMALong[0] && rising(SMAShort) && rising(SMALong) && NumOpenLong == 0 && NumPendingLong == 0) {	
                enterLong(0,BuyStop);	
                }	
            else if (SMAShort[0] < SMALong[0] && falling(SMAShort) && falling(SMALong) && NumOpenShort == 0 && NumPendingShort == 0) {	
                enterShort(0,SellStop);	
                }	
            }	
    #endif

    if (dow() != 4 && dow() != 5 && dow() != 6)	// exit on Monday morning's open, or Tuesday morning's open, if Monday is a holiday
        {
        exitShort();	
        exitLong();	
        }	
}	
	
function run()	
    {	
	set(LOGFILE|PLOTNOW);
   	// set(PARAMETERS,FACTORS,LOGFILE,PLOTNOW);  // generate and use optimized parameters and factors

    BarPeriod = 15;	
    // while(asset(loop("EUR/USD","USD/CHF","GBP/USD","USD/JPY")))	
    asset("USD/CHF");
    tradeOneNightStand();	
}	