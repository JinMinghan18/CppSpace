#include<fstream>
#include<iostream>
using namespace std;

struct stu{
	char name[50],index[50],date[50],order[50],sub[50],abstype[50];
};

int main()
{
	ifstream infile("example.txt",ios::in);
	stu a[100];
	int len = 1;
	while (infile>>a[len].name>>a[len].index>>a[len].date>>a[len].order>>a[len].sub>>a[len].abstype) len++;
	len--;
	for (int i = 1;i<=len;i++)
	{
		cout<<a[len].name<<a[len].index<<a[len].date<<a[len].order<<a[len].sub<<a[len].abstype<<endl;
	}
}
