#include <cmath>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#define maxn 10010
using namespace std;

int main() 
{ 
	int n,m,w[maxn],order = 1;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
	}
	sort(w+1,w+n+1);
	int minn = 1,maxx = n;
	int ans = 0;
	while(1)
	{
		if(maxx == minn)
		{
			ans ++;
			break;
		} 
		else if(maxx < minn)
		break;
		else if(w[maxx] + w[minn]<=m)
			minn++,maxx--,ans++;
		else maxx--,ans++;
	}
	printf("%d\n",ans); 
	return 0;
}

