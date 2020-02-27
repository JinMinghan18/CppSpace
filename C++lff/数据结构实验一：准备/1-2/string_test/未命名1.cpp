#include<iostream>
using namespace std;
string array = "agctagcagctagctg";
void prefixArray(int prefix[],int n){
	for(int i=2;i<n;i++){
		int k = prefix[i-1]; 
		while(array[i] != array[k]){
		k = prefix[k-1]; 
		if(k == 0) break;
		}
		if(k == 0 && array[i] != array[k])
		prefix[i] = 0;
		else prefix[i] = k+1;
			
	}
}
int main(){
	
	int prefix[10000]={};
	prefixArray(prefix,array.length());
	for(int i=0;i<array.length();i++){
		cout<<prefix[i]	;
	} 
}
int StringType::KpmFind(const StringType& pattern){
	int lenMin = pattern.length();
	int lenMax = myStorage.length();
	prefixArray(prefix,lenMin);
	int i = 0,j = 0,count= 0;
	while(i<lenMax-lenMin+1){
		if(myStorage[i] == pattern[j]){
			i++,j++;
			if(j == lenMin){
				count++;
			}
		}
		else{
			if(j == 0){
				i++;	
			}
			else j = prefix[j-1];
		}
	}
	if(count == 0) return 0;
	else return 1;
} 
