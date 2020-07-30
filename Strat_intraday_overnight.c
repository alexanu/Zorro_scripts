/* OVERNIGHT EFFECT */
 
// define sessions
int timezone = JST;
int sessionStart = 8; // corresponds to 18 in ET
int sessionEnd = 18; // corresponds to 5 in ET

 
function run()
{
	set(PLOTNOW);
	setf(PlotMode, PL_FINE);
	StartDate = 2009;
	EndDate = 2018;
	BarPeriod = 60;
	MaxShort = 1;
	asset("USD/JPY");
	// Spread = Commission = Slippage = RollLong = RollShort = 0;
	
	if(lhour(timezone) == sessionStart)	enterShort();
	if(lhour(timezone) == sessionEnd) exitShort();

}