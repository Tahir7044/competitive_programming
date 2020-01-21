#include<bits/stdc++.h>
using namespace std;
#define ll long long int
set<string> insignificant_words;
std::vector<string> significant_words;
std::vector<int> significant_word_length,acronym;
string s,st,abbriviation;
int n_,m;
ll dp[150][150];
ll solve(int word_pos,int abbriviation_pos,int cur_pos)
{
	/*
		base case if abbriation_pos which is poiting to char of abbriviation is equal to the length of abbriviation
		then check if word_pos which is pointing to the number of words used for abbriviation.if word_pos==n_(total number of words) then 
		we can say we make one combinition by using all given significant words so return 1. if not all the words contibuting then return 0  
	*/
	if(abbriviation_pos==m) 
	{
		if(word_pos==n_)
			return 1;
		return 0;
	}

	if(word_pos==n_) return 0; //no such words remain to use.
	ll &temp=dp[abbriviation_pos][acronym[word_pos]+cur_pos]; // dp state.Here cur_pos pointing to the char of current word
	if(temp!=-1) return temp;
	temp=0;
	for(int i=significant_word_length[word_pos]-1;i>=cur_pos;i--) // processing the current significant word in reverse order.
	{
		//if the abbriviation char match with current significant_word char
		if(significant_words[word_pos][i]==abbriviation[abbriviation_pos]) 
		{
			/* if char of significant word is not the end char then we just increament the char position for
			 abbriviation and significant word. else we also increament significant word.
			*/
			if(i!=significant_word_length[word_pos]-1) 
				temp+=solve(word_pos,abbriviation_pos +1,i+1);
			temp+=solve(word_pos+1,abbriviation_pos +1,0);
		}
	}
	return temp;
}
int main()
{
	while(1)
	{
		int n;
		cin>>n;
		if(!n)break; // if n=-1 then break the loop.
		insignificant_words.clear(); // clear the global variables
		for(int i=0;i<n;i++)
		{
			cin>>s;
			insignificant_words.insert(s);
		}
		getline(cin,s); // taking one extra input for extra newline.
		while(1)
		{
			getline(cin,s); // taking input.
			istringstream iss(s); // it will break your input sentances in wordstream in variable "iss" 
			iss>>abbriviation>>st; // taking first two words from variable "iss" to abbriviation ans st.
			if(abbriviation=="LAST"&&st=="CASE") break; 
			cout<<abbriviation; // printing value as per output format.
			transform(abbriviation.begin(), abbriviation.end(), abbriviation.begin(), ::tolower); //convert to lower case			
			/*
			st(holding the second word of input sentance) is not present in the set of insignificant words 
			then add it to vector of significant words as well adding the length of significant words.
			*/ 

			if(insignificant_words.find(st)==insignificant_words.end()) 
				significant_words.push_back(st),significant_word_length.push_back(st.size());
			
			// processing from third word and doing same as previous.
			while(iss>>st)
			{
				if(insignificant_words.find(st)==insignificant_words.end())
					significant_words.push_back(st),significant_word_length.push_back(st.size());
			}	

			n_=significant_words.size();
			m=abbriviation.size();
			
			/*
				prefix sum the length of significant word and store it in acronym
			*/

			for(int i=0;i<n;i++)
			{
				if(!i)
					acronym.push_back(0);
				else
					acronym.push_back(acronym[i-1]+significant_word_length[i-1]);
			}	
			
			memset(dp,-1,sizeof(dp)); // initialization

			ll ans=solve(0,0,0);

            if(ans>0) cout<<" can be formed in "<<ans<<" ways"<<endl;
            else cout<<" is not a valid abbreviation"<<endl;	
            significant_words.clear();
            significant_word_length.clear();
            acronym.clear();
		}
	}
}