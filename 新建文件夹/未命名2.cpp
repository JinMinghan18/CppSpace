#include <iostream>
#include <fstream> //�ļ����������
using namespace std;
int main()
{
    fstream fileOut("aa.txt",ios::out);   
    if(!fileOut)
    {
       cout<<"error !";
    }
    else
    {
    	string a;
    	cin>>a;
        fileOut<<a;
 		ifstream in;
		 
        fileOut.close();
    
	}
    
    return 0;
}
