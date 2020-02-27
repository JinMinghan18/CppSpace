#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
int main(){
 
	vector<double> v;
	for(int i=2;i<=5;i++) v.push_back(2.2*i);
	vector<double>::iterator it,it1,it2;
	for(it=v.begin();it!=v.end();it++) cout<<(*it)<<"   ";
	cout<<endl;
	it1=v.begin(),it2=v.end();
	*it1=1.1;
	*(it2-1)=9.9;
	for(it=v.begin();it!=v.end();it++) cout<<(*it)<<"   ";
	cout<<endl;
	it1+=3;
	it2-=3;
	cout<<(*it1)<<"   "<<(*it2)<<endl;
	it1--;
	++it2;
	cout<<(*it1)<<"   "<<(*it2)<<endl;
	cout<<it1[1]<<"   "<<it2[-1]<<endl;
	} 
