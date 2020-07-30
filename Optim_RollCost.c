// FX strategy with some multi-week hold periods	

// significantly impact by the swap (cost of financing the position) ...
// ... typically derived from the central bank interest rate differential of the two currencies 
// ... in the exchange rate being traded, plus some additional fee for your broker. 	

// Most brokers apply it on a daily basis, 
// ... and typically apply three times the regular amount on a Wednesday to account for the weekend	
// Zorro’s default swap calculation relies on a constant derived from the Assets List used in the simulation...	
// ... might lead to unrealistic results when the hold period is very long.	
	
#include <contract.c>	

// Calculates Zorro roll long / short in units of quote currency
var calculate_roll_long(var base_ir, var quote_ir, var broker_fee)
	{
	var ird = (base_ir - quote_ir)/100;
	return 10000*ird/365 - broker_fee;	// interest per day per 10000 units traded, in account currency
	}
var calculate_roll_short(var base_ir, var quote_ir, var broker_fee)
	{	
	var ird = (quote_ir - base_ir)/100;	
	return 10000*ird/365 - broker_fee;	
	}	
	

function run()	
	{	
	set(PLOTNOW);	
	PlotWidth = 800;	
	PlotHeight1 = 400;	
	PlotHeight2 = 250;	
	StartDate = 20100101;	
	EndDate = 20180630;	

	// daily policy rates of major central banks, from BIS via Quandl
	var usd_ir = dataFromQuandl(1, "%Y-%m-%d,f", "BIS/PD_DUS", 1);
	var jpy_ir = dataFromQuandl(2, "%Y-%m-%d,f", "BIS/PD_DJP", 1);
	var aud_ir = dataFromQuandl(3, "%Y-%m-%d,f", "BIS/PD_DAU", 1);
	var eur_ir = dataFromQuandl(4, "%Y-%m-%d,f", "BIS/PD_DXM", 1);
	var cad_ir = dataFromQuandl(5, "%Y-%m-%d,f", "BIS/PD_DCA", 1);
	var chf_ir = dataFromQuandl(6, "%Y-%m-%d,f", "BIS/PD_DCH", 1);
	var nzd_ir = dataFromQuandl(7, "%Y-%m-%d,f", "BIS/PD_DNZ", 1);
	var gbp_ir = dataFromQuandl(8, "%Y-%m-%d,f", "BIS/PD_DGB", 1);

	// What the broker takes in addition to the interest rate differential. 
	// Will vary by broker, by pair, and even by direction! 
	// Make a conservative assumption.
	var broker_fee = 0.5;	

	asset("EUR/USD");	// EUR/USD roll in AUD example
	var rl = calculate_roll_long(eur_ir, usd_ir, broker_fee); // calculate roll long in units of quote currency

// convert to units of account currency - here the account currency is AUD	
// not required if account currency is the same as the quote currency	
	string current_asset = Asset; // store name of currently selected asset
	asset("AUD/USD"); // switch to ACCT_CCY/QUOTE_CCY
	var p = priceClose();	
	asset(current_asset); // switch back to original asset
	RollLong = rl/p; // adjust roll long calculation and set Zorro's RollLong variable
	
	var rs = calculate_roll_short(eur_ir, usd_ir, broker_fee);	
	RollShort = rs/p;	// adjust roll short calculation and set Zorro's RollShort variable

	plot("Roll Long", RollLong, NEW, BLUE);	// plot roll in units of account currency
	plot("Roll Short", RollShort, 0, RED);	
	}	