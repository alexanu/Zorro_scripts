// optimizing objective based on PRR: Pessimistic Return Ratio (PRR)
// Profit Factor adjusted for the biggest wins and losses

var objective()
{
	if(NumWinTotal < 2 || NumWinTotal+NumLossTotal < 5) return 0.;	// needs at least 5 trades
	var wFac = 1./sqrt(1.+NumWinTotal); 
	var lFac = 1./sqrt(1.+NumLossTotal);
	var Win = WinTotal, Loss = LossTotal;

// remove possible outlier wins/losses
	if(NumLossTotal > 1) {
		Loss -= (NumLossTotal-1)*LossMaxTotal/NumLossTotal;
		Win -= (NumWinTotal-1)*WinMaxTotal/NumWinTotal;
	}
	return (1.-wFac)/(1.+lFac)*(1.+Win)/(1.+Loss); // return PRR

}
