#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
char A[maxn],B[maxn];//AΪ���� BΪģʽ��
int len1,len2;//len1ΪA�ĳ��� ͬ��
int next[maxn];
int ans;
//�õ�next ����
void get_next()
{
    next[0] =-1;
    for(int i=1; i<len2 ;i++)
    {
        int j=next[i-1];
        while (B[j+1] != B[i] && j>=0)//���ȾͲ�����С���� �������ӳ���
            j = next[j];
        if(B[j+1] == B[i])
            next[i] =j+1;
        else
            next[i] =-1;
    }
}
//����next����Ѱ��ƥ�䣬����������ÿ�ҵ�һ��ƥ�������俪ʼ��λ��
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
