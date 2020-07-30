// Source: https://financial-hacker.com/petra-on-programming-the-correlation-cycle-indicator/

// Correlation Cycle Indicator
// ... measures the price curve correlation with a sine wave


var correlY(var Phase); // function pointer
var cosFunc(var Phase) { return cos(2*PI*Phase); }
var sinFunc(var Phase) { return -sin(2*PI*Phase); }


// correlation of the Data series with an arbitrary curve given by the Func function
var correl(vars Data, int Length, function Func)
{
   correlY = Func; 
   var Sx = 0, Sy = 0, Sxx = 0, Sxy = 0, Syy = 0;
   int count;
   for(count = 0; count < Length; count++) {
      var X = Data[count];
      var Y = correlY((var)count/Length);
      Sx += X; Sy += Y;
      Sxx += X*X; Sxy += X*Y; Syy += Y*Y;
   }
   if(Length*Sxx-Sx*Sx > 0 && Length*Syy-Sy*Sy > 0)
      return (Length*Sxy-Sx*Sy)/sqrt((Length*Sxx-Sx*Sx)*(Length*Syy-Sy*Sy));
   else return 0;
}

var CCY(vars Data, int Length) { return correl(Data,Length,cosFunc); } // correlation with cosine
var CCYROC(vars Data, int Length) { return correl(Data,Length,sinFunc); } // rate of change


function run()
{
   BarPeriod = 1440;
   LookBack = 40;
   StartDate = 20190101;

   assetAdd("SPY","STOOQ:SPY.US"); // load price history from Stooq
   asset("SPY");

   vars Prices = series(priceClose());
   plot("CCY(14)",CCY(Prices,14),NEW|LINE,RED);
   plot("ROC(14)",CCYROC(Prices,14),LINE,GREEN);
 }

// peaks or valleys could be used for trade signals
// CCY is no good for trade signals
// The phase angle of the CCY and CCYROC reflects the market state. 
//        1 for a rising trend, 
//       -1 for a falling trend, 
//    and 0 for cycle regime.

var CCYState(vars Data,int Length,var Threshold)
{
   vars Angles = series(0,2);
   var Real = correl(Data,Length,cosFunc);
   var Imag = correl(Data,Length,sinFunc);
// compute the angle as an arctangent function and resolve ambiguity
   if(Imag != 0) Angles[0] = 90 + 180/PI*atan(Real/Imag);
   if(Imag > 0) Angles[0] -= 180;

// do not allow the rate change of angle to go negative
   if(Angles[1]-Angles[0] < 270 && Angles[0] < Angles[1])
      Angles[0] = Angles[1];
   //return Angles[0];
// compute market state
   if(abs(Angles[0]-Angles[1]) < Threshold)
      return ifelse(Angles[0] < 0,-1,1);
   else return 0;
}

function run() 
{
   set(PARAMETERS);
   BarPeriod = 1440;
   LookBack = 40;
   NumYears = 8;

   assetAdd("SPY","STOOQ:SPY.US"); // load price history from Stooq
   asset("SPY");
   
   NumWFOCycles = 4;
   int Cutoff = optimize(10,5,30,5);

   vars Prices = series(priceClose());
   vars Signals = series(LowPass(Prices,Cutoff));
   if(valley(Signals)) enterLong();
   else if(peak(Signals)) enterShort();
}

// Let’s see if the CCYState indicator can help to improve the above LowPass trades
function run() 
{
   set(PARAMETERS);
   BarPeriod = 1440;
   LookBack = 40;
   NumYears = 8;

   assetAdd("SPY","STOOQ:SPY.US"); // load price history from Stooq
   asset("SPY");
   
   NumWFOCycles = 4;
   int Cutoff = optimize(10,5,30,5);
   int Period = optimize(14,10,25,1);
   var Threshold = optimize(9,5,15,1);

   vars Prices = series(priceClose());

   var State = CCYState(Prices,Period,Threshold);
   plot("State",State*0.9,NEW|LINE,BLUE);
   vars Signals = series(LowPass(Prices,Cutoff));
   
   if(State != 0) { // system trades only when the market state is 1 or -1, indicating trend regime
      if(valley(Signals)) enterLong();
      else if(peak(Signals)) enterShort();
   }
   else { // goes out of the market when the market state is 0
      exitLong(); 
      exitShort();
   }
}

