// Indicator implementation example //////////////////////////////////
// Formula: Out[0] = (a-a^2/4) * In[0] + a^2/2 * In[1] - (a-3a^2/4) * In[2] + (2-2a) * Out[1] - (1-a)^2 * Out[2]

var lowpass(vars In,int Period)
{
	var a = 1./(1+Period);
	vars Out = series(In[0],3);
	return Out[0] = (a-0.25*a*a)*In[0]
		+ 0.5*a*a*In[1]
		- (a-0.75*a*a)*In[2]
		+ (2-2*a)*Out[1]
		- (1-a)*(1-a)*Out[2];
}

function run() // for testing
{
	set(PLOTNOW);
	plot("lowpass",lowpass(series(price()),10),LINE,RED);
}