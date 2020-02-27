#include <bits/stdc++.h>
#define maxn 10010
#define INF 0x3f3f3f3f
using namespace std;
int n,k;
struct node
{
	int order,num;
}m[maxn];
bool cmp1(node a,node b)
{
	return a.num < b.num;
}
bool cmp2(node a,node b)
{
	return a.order<b.order;
}
int main()
{
	scanf("%d%d"&n,&k);
	for(int i =1;i<=n;i++)
	{
		scanf("%d",&m[i].num);
		m[i].order = i;
	}
	sort(m+1,m+n+1,cmp);
	int sum = INF,temp = 0; 
	if(k%2 == 0)
	{
		for(int i=k;i<=n;i++)
		{
			for(int j=i-k+1;j<=i;j++)
			{
				temp+=(m[j].num-m[i-k/2].num);
			} 
			sum = min(temp,sum); 
		}
	} 
	else if(k%2 ==1)
	{
		for(int i=k;i<=n;i++)
		{
			for(int j=i-k+1;j<=i;j++)
			{
				temp+=(m[j].num-m[i-k/2].num);
			} 
			sum = min(temp,sum); 
		}
	}
	
}
