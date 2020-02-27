#include <bits/stdc++.h>
using namespace std;
int N,C,X,lowsum[60],maxsum[60]; 
struct node 
{
	int l,h;
}m[60];
bool cmp1(node a,node b)
{
	return a.l<b.l; 
}
bool cmp2(node a,node b)
{
	return a.h<b.h;
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int i;
		scanf("%d%d%d",&N,&C,&X);
		for(int i=1;i<=N;i++)
		{
			scanf("%d%d",&m[i].l,&m[i].h);
		}
		sort(m+1,m+N+1,cmp1);
		lowsum[0] = maxsum[0] = 0;
		int ans = N;
		for( i=1;i<=N;i++)
		{
			lowsum[i] = lowsum[i-1] + m[i].l;
			maxsum[i] = maxsum[i-1] + m[i].h;
		}
		for( i =N;i>=1;i--)
		{
			if(lowsum[N]-lowsum[i-1]>=X)
				break;
		} 
		ans = min(ans,N+1-i);
		sort(m+1,m+N+1,cmp2);
		for( i=1;i<=N;i++)
		{
			lowsum[i] = lowsum[i-1] + m[i].l;
			maxsum[i] = maxsum[i-1] + m[i].h;
		}
		for( i=N;i>=1;i--)
		{
			if(C-maxsum[i-1]>=X)
				break;
		}
		ans = min(ans,N-i+1);
		printf("%d\n",ans);
	}
	
}
