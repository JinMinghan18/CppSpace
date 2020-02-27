#include<iostream>
#include <cstring>
using namespace std;
int main()
{
	string a;
	cin>>a;
	bool flag = true;
	if(a.length()%2 != 0) cout<<"NO"<<endl;
	else if(a.length() %2 == 0)
	{
		for(int i=0;i<=a.length()/2-1 ;i++)
		{
			if(a[i] != a[i+a.length()/2])
			{flag = false;break;}
		}
		if(flag == false) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
}
