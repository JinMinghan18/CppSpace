#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
char A[maxn],B[maxn];//A为主串 B为模式串
int len1,len2;//len1为A的长度 同理
int next[maxn];
int ans;
//得到next 数组
void get_next()
{
    next[0] =-1;
    for(int i=1; i<len2 ;i++)
    {
        int j=next[i-1];
        while (B[j+1] != B[i] && j>=0)//不等就不断缩小长度 否则增加长度
            j = next[j];
        if(B[j+1] == B[i])
            next[i] =j+1;
        else
            next[i] =-1;
    }
}
//利用next数组寻找匹配，这里我们是每找到一个匹配就输出其开始的位置
int kmp()
{
    int i=0,j=0;
    while (i < len1)
    {
        if(A[i] == B[j])
        {
            i++;j++;
            if(j == len2)
            {
                printf("%d\n",i-len2);
                j=next[j-1]+1;
            }
        }
        else
        {
            if(j ==0)
                i++;
            else
                j= next[j-1]+1;
        }
    }
}

int main ()
{
    cin>>A>>B;
    len1=strlen(A),len2=strlen(B);
    get_next();
    kmp();
    //cout<< A[ans]<<endl;
}
