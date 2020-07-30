
// https://papers.ssrn.com/sol3/papers.cfm?abstract_id=2613592

#define LONG 0	
#define SHORT 1	

bool Reinvest = false;	
bool UseOptimalF = false;	

var CalculateMargin(int side)	
        {	
        var value = 0.1 * Capital;	
        if (Reinvest) value *= sqrt(Balance / Capital);	//value *= sqrt(1 + max(0, ProfitClosed/Capital));	
        if (UseOptimalF) value *= ifelse(side == LONG, OptimalFLong, OptimalFShort);	
        return value;	
        }	

int hoursLookup[300]; // lookup table stores startHour - endHour combinations (300 combinations per day)	
function Initialize()	
        {	
        int count = 0;	
        int startHour, endHour;	
        for (startHour = 0; startHour <= 23; ++startHour)	
        for (endHour = startHour + 1; endHour <= 24; ++endHour)				
	        hoursLookup[count++] = (endHour % 24) * 24 + startHour;	
        }	

int NumOpenTrades(int side)	
        {	
        string currentAsset = Asset;	
        string currentAlgo = Algo;	
        int count = 0;	
        for (open_trades)	
                {	
                if (strcmp(TradeAsset, currentAsset) != 0 || strcmp(TradeAlgo, currentAlgo) != 0) continue;	
                if ((TradeIsLong && side == LONG) || (TradeIsShort && side == SHORT)) count++;	
                }	
        return count;	
        }

TRADE* EnterTrade(int side)	
        {	
        if (side == LONG) return enterLong();	
        else return enterShort();	
        }	

void ExitTrade(int side)	
        {	
        if (side == LONG) exitLong();	
        else exitShort();	
        }	

function TradeIS(int side)	
        {	
        int index = (int)(optimize(0, 0, 254, 1) / 254 * 299);        	
		// The optimize function computes an index into a lookup table. .
		// It can only handle 255 steps, that is why it looks for a value between 0 and 254 
		// ... and than scales that to [0, 299].

        int startHour = hoursLookup[index] % 24;	
        int endHour = hoursLookup[index] / 24;	
	
        if (dow() == FRIDAY && hour() >= 21) // Exit over the weekend
                {	
                exitLong();	
                exitShort();	
                }	

        Stop = 55 * PIP;	
        Trail = 10 * PIP;	
	
        if (startHour == endHour) return;	// Don't trade from 00:00 to 00:00
	
        if (dow() >= 1 && dow() <= 5) // Trade during the week
                {	
                Margin = CalculateMargin(side);	
                int numOpen = NumOpenTrades(side);	
                if (numOpen == 0 && hour() == startHour) EnterTrade(side);	
                if (numOpen > 0 && hour() == endHour) ExitTrade(side);	
                }	
        }	

#define METHOD	ASCENT
//#define METHOD	BRUTE
//#define METHOD	GENETIC

function run()	
        {	
        set(PARAMETERS + FACTORS);
        setf(TrainMode,METHOD);
	
        StartDate = 2010;	
        // EndDate = 2016;	
        BarPeriod = 60;	
        Capital = 10000;	
        DataSplit = 80;	// 80% training, 20% test period
        WFOPeriod = (312 * 24) * DataSplit / (100 - DataSplit); // 718848 min => 500 days
        
        if (is(INITRUN)) 
                {
                Initialize();	
                NumCores = -1;
                }

	// asset("EUR/USD");
        while (asset(loop("AUD/USD", "EUR/USD", "GBP/USD", "NZD/USD", "USD/CAD",  "USD/CHF", "USD/JPY")))	
        while (algo(loop("ISL", "ISS")))	
                {	
                if (Algo == "ISL") TradeIS(LONG);	
                else if (Algo == "ISS") TradeIS(SHORT);	
                }	
        }	