#define SYMBOLS "AUD/USD","USD/JPY","USD/CAD","GBP/USD","EUR/USD"


function run()
{
//StartDate = 2004;
// set(PARAMETERS+FACTORS);
NumYears = 2;
BarPeriod = 15;
LookBack = 80*4*24;
Capital = 50000;
//Margin = OptimalF * (Capital + sqrt(ProfitClosed));
// Margin = 0.02*(Capital + sqrt(ProfitClosed));
Margin = 0.02*Capital;


while(asset(loop(SYMBOLS)))
while(algo(loop("H1","H4")))
       {
       if(is(INITRUN)){
              AlgoVar[0]=0;
              AlgoVar[1]=0;
              AlgoVar[2]=0;
              AlgoVar[3]=0;
              }
       TimeFrame = 1;
       if(Algo == "H1") TimeFrame = 4;
       else if(Algo == "H4") TimeFrame = 4*4;
       
       vars Price = series(priceClose());
       var dFast=2;//optimize(2,1,10);
       var dSlow=18;//optimize(18,18,60);
       var dMulF=2;//optimize(2,1,10);
       var dMulS=5;//optimize(4,4,16);
       var dSignal=19;//optimize(9,9,27);
       vars Fast = series(MACD(Price,dFast,dFast*dMulF,dSignal));
       vars Slow = series(MACD(Price,dSlow,dSlow*dMulS,dSignal));

       var BuyLimit=AlgoVar[0], SellLimit=AlgoVar[1], BuyStop=AlgoVar[2], SellStop=AlgoVar[3];
       
       var dStop=2;//optimize(1.5,1,5);
       var dLimit=3;//optimize(3,2,10);

       if(crossOver(Fast,Slow)) {
              BuyStop = priceHigh() + 1*PIP;
            //   BuyStop = priceHigh() + dStop*ATRS(9);
              BuyLimit = priceHigh() + 5*PIP;
            //   BuyLimit = priceHigh() + dLimit*ATRS(27);
              }
       if(crossUnder(Fast,Slow)) {
              SellStop = priceLow() - 1*PIP;
            //   SellStop = priceLow() - dStop*ATRS(9);
              SellLimit = priceLow() - 5*PIP;
            //   SellLimit = priceLow() - dLimit*ATRS(27);
              }
       
       TakeProfit = ATRS(90); // *optimize(3,3,10)
       Stop = ATRS(60); // *optimize(3,3,10)
       
       if(!NumOpenLong && Fast[0] > Slow[0] && Price[0] < BuyLimit )
              enterLong(0,BuyStop);
       if(!NumOpenShort && Fast[0] < Slow[0] && Price[0] > SellLimit )
              enterShort(0,SellStop);
       
       AlgoVar[0]=BuyLimit;
       AlgoVar[1]=SellLimit;
       AlgoVar[2]=BuyStop;
       AlgoVar[3]=SellStop;
       }
//PlotWidth = 1000;
//set(PLOTNOW);
}