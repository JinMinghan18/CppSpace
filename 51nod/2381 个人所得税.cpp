#include <iostream>
using namespace std;
int main()
{
	int a;
	cin>>a;
	if(a-8000<=0 && a-5000>= 0) cout<<a-(a-5000)*0.03<<endl;
	else if(a-8000>0 && a-17000<=0) cout<<a-90-(a-8000)*0.1<<endl;
	else if(a-17000>0 && a-30000 <=0) cout<<a-990-(a-17000)*0.2<<endl;
	else if(a-30000>0 && a-40000<=0) cout<<a-3590-(a-30000)*0.25<<endl;
	else if(a-40000>0 && a-60000<=0) cout<<a-6090-(a-40000)*0.30<<endl;
	else if(a-60000>0 && a-85000<=0) cout<<a-12090-(a-60000)*0.35<<endl;
	else if(a-85000>0) cout<<a-20840-(a-85000)*0.45<<endl;
	else if(a<5000) cout<<a<<endl;
}
