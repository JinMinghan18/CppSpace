#include <cmath>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define maxn 50010
#define ll long long 
using namespace std;

int main() 
{ 
	int  n,a[maxn];
	scanf("%lld",&n);
	for(int i=1;i<= n;i++)
	{
		scanf("%lld",&a[i]);
	}
	ll ans=INF;
	ll temp = 0;
	for(int i=1;i<=n;i++)
	{
		temp += a[i];
		if(temp <= ans )
		{
			ans = temp;
		} 
	}
	printf("%lld\n",-ans);
	return 0;
}
