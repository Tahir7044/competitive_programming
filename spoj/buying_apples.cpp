#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;  // numbers of apples
		int k;	// amount of Apples(kgs) which he should buy.
		cin>>n>>k;
		vector<int> weight,value;
		for(int i=1;i<=k;i++)
		{
			int s;
			cin>>s;
			// the available ith apples whose price is known.
			if(s!=-1)
			{
				value.push_back(s); // price of ith apple.
				weight.push_back(i); // weight of ith apple.
			}
		}
		int len=weight.size();
		int dp[k+1];       // dp[i] say what is the minimum price to purchase i kgs of apples.
		// initialize with some max value since it is a minimization problem. 
		for(int i=1;i<=k;i++)
			dp[i]=1000000;

		dp[0]=0; //price of 0 kg apple is 0. 
		for(int i=0;i<len;i++)  // this loop choose the apples one by one [1,2,3...len].
		{
			for(int j=1;j<=k;j++) // this loop ckeck how the ith apple contributing to the j kgs of requirements. 
			{
				// here we check if the weight of ith apple is less then the j kgs of requirements then it can be contribute towards my ans.  
				if(j>=weight[i])
				{
					dp[j]=min(dp[j],dp[j-weight[i]]+value[i]); // here we checking if the price if j kgs is less than by adding ith apple then we add it.
				}
			}

		}
		// dp[k] is the price of k kgs of apples.
		if(dp[k]!=1000000) 
			cout<<dp[k]<<endl;
		else
			cout<<-1<<endl;

	}
}