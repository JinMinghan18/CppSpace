#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include<iostream>
#include <algorithm>
using namespace std;

bool cmp(int a,int b)
{
	return a>b;
} 
int main() 
{
	int T;
	cin>>T;
	while(T--)
	{
		int a[5],k,sum1=0,sum2=0,final,temp;
		cin>>temp;
		int temp2 = temp;
		cin>>k;
		a[4] = temp%10;temp/=10;
		a[3] = temp%10;temp/=10;
		a[2] = temp%10;temp/=10;
		a[1] = temp; 		
		if(k == 0)	cout<<temp2<<endl;
		else
		{	
			while(k--)
			{
				sum1 = 0;sum2 = 0;
				sort(a+1,a+5);
				for(int i=4;i>0;i--)
					sum1 = sum1*10+a[i],sum2 = sum2*10+a[5-i];	
				final = abs(sum2-sum1);
				a[4] = final%10;final/=10;
				a[3] = final%10;final/=10;
				a[2] = final%10;final/=10;
				a[1] = final; 		
			}
			cout<<abs(sum1-sum2)<<endl;
		}
	}
		
	return 0;
}
