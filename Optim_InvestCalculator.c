// Investment calculator ///////////////////////////////////

void main()
{
	slider(1,10000,1,20000,"Capital","Initial capital");
	slider(2,10000,0,20000,"Profit","Profit so far");
	slider(3,2000,1000,2000,".Root","Nth root"); // 1.000 = linear, 2.000 = square root
	while(wait(100))
		print(TO_INFO,"Investment: $%.0f",
			slider(1)*pow(1+slider(2)/slider(1),1./(0.001*slider(3))));
}