// Martingale betting ///////////////////

/*
Doubles the stake following each losing bet until a winner occurs
With Martingale betting, you’re guaranteed to lose: a losing streak does not increase the odds of the next bet being a winner
No matter your initial position size, ...
... if you continue to double it with every loss, ...
 ... there’s some loss streak, N, that sends you bust
That loss streak depends only on the size of your initial bet
No one can go on increasing their bankroll infinitely: bank account or your broker’s willingness to extend you margin.
*/

void plotHistogram(string Name,var Val,var Step,var Weight,int Color)
{
    var Bucket = floor(Val/Step);
    plotBar(Name, Bucket, Step*Bucket, Weight, SUM+BARS+LBL2, Color);   
}

function run()
{
    setf(PlotMode, PL_FINE);
    set(PLOTNOW);

    StartDate = 2010;
    EndDate = 2011;
    Capital = 10000;
    BarPeriod = 60; // make it smaller to increase frequency of trades to show long horizon
    // NumTotalCycles = 5000; // Uncomment this and below to see how often the martingale fails

    if(Equity - MarginVal < Capital) Lots = 0;
    
    Stop = TakeProfit = ATR(100);
    Lots = pow(2, LossStreakTotal);  // Martingale position sizing
    
    if(NumOpenTotal == 0) {
        if(random() < 0) enterShort();     // random trading strategy 
        else enterLong();
    }
  	ColorUp = ColorDn = ColorDD = ColorWin = ColorLoss = 0; // don't plot a price curve
   	plot("Neg Streak",LossStreakTotal,0,RED);

    // if(is(EXITRUN)) 
    // {
    //     var finalValue = max(0, Equity);
    //     plotHistogram("Account Equity", finalValue, 500, 1, RED);   
    // }

}
