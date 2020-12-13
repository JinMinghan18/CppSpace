#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;

char str[10][10];//�洢�ķ� 
int n;//�洢�ķ����� 
int v=0;//�洢������ĸ��� 
char r[20][10];//�洢�������floatֵ 
int rr[20][10];//�洢�������intֵ 
struct DFA{
	int num;//��¼���������� 
	int  c[10];//�洢�������һ��λ�� 
	int f;//��¼ 
	char ss[10][10];//�洢������ķ� 
	int count;//��¼������ķ����� 
	int l;//�洢��һ���ַ���'.'��λ�� 
}LR[20];

//��ʼ���������������޹��ķ�����#�Ž�β 
void Init(){
	int i,j;
	cout<<"�����������޹��ķ���"<<endl;
	for(i=1;;i++){
		cin>>str[i];
		if(str[i][0]=='#')
		break;
	}
	strcat(str[0],"Z->");
	str[0][3]=str[1][0]; 
	n=i+1;
}

//��һ��ʼ���ʱ���ȸ����ķ�������ÿ�β����ظ����� 
void input(){
	int i,j;
	strcat(str[0],"Z->E");
	strcat(str[1],"E->aA");
	strcat(str[2],"E->bB");
	strcat(str[3],"A->cA");
	strcat(str[4],"A->d");
	strcat(str[5],"B->cB");
	strcat(str[6],"B->d");
	n=7;
	for(i=0;i<n;i++)
	cout<<str[i]<<endl;
	cout<<"***************************"<<endl;
}

//Ϊ�ķ����С���� 
void AddD(int a,int b){//ΪLR[a]��ss��b���ַ������'.' 
	int i,j=0;
	char c[10];
	for(i=0;i<3;i++)
	c[j++]=LR[a].ss[b][i];
	c[3]='.';
	j++;
	for(i=3;i<strlen(LR[a].ss[b]);i++)
	c[j++]=LR[a].ss[b][i];
	memset(LR[a].ss[b],0,sizeof(LR[a].ss[b]));
	for(i=0;i<j;i++)
	LR[a].ss[b][i]=c[i];
}

//����ƽ���Ŀ���ķ� 
void AddG(int a,char s){//��str�ķ����󲿷��ս����s��ͬ���ķ�����ӽ�LR[a]�� 
	int i,j,k;
	for(i=0;i<n;i++){
		if(str[i][0]==s){
			for(j=0;j<strlen(str[i]);j++)
			LR[a].ss[LR[a].count][j]=str[i][j];
			AddD(a,LR[a].count); 
			LR[a].count++;
		}
	}
}

//���ķ�СԲ�������һλ 
void add(int a,int j){
	int i,k;
	char temp;
	for(i=0;i<strlen(LR[a].ss[j]);i++){
		LR[v].ss[0][i]=LR[a].ss[j][i];
		if(LR[a].ss[j][i]=='.')
		k=i;//��¼СԲ���λ�� 
	}
	LR[a].c[j]=v;//��¼�����ķ�����ת���ӣ����� 
	LR[v].f=a;//��¼��ת��������Դ�������� 
	LR[v].count++;
	temp=LR[v].ss[0][k+1];//СԲ�������һλ 
	LR[v].ss[0][k+1]=LR[v].ss[0][k];
	LR[v].ss[0][k]=temp;
	LR[v].l=k+1;//��¼СԲ���λ�� 
}

//����ĳһ�����Դ����������ÿһ���ķ�����ת��Ӵ��� 
void fix(int a,int b){
	int i,j,k;
	k=LR[b].f;//���� 
	for(i=0;i<LR[k].count;i++)
	if(LR[k].c[i]==b)
	LR[k].c[i]=a;//�Ӵ� 
}

//�Ƚϣ�ɾ����ͬ������ 
void Compare(int a){
	int i,j,k;
	for(i=0;i<a;i++){
		for(j=i+1;j<=a;j++){
			if(strcmp(LR[i].ss[0],LR[j].ss[0])==0){//����ͬ 
				fix(i,j);
				memset(LR[j].ss,0,sizeof(LR[j].ss));//������ķ�������� 
				LR[j].count=0;
			}
		}
	}	
}

//LR(0)�淶���Ĺ���
void gfj(){
	int i,j,k,p;
	for(i=0;i<20;i++){
		LR[i].num=i;//Ii
		if(i==0){//��һ���������ķ��ĳ�ʼ��Z->E 
			for(k=0;k<strlen(str[0]);k++)
			LR[0].ss[0][k]=str[0][k];
			AddD(0,LR[0].count);//���СԲ�� Z->.E 
			LR[0].l=3;//СԲ���λ�� 
			LR[0].count++;//�ķ���Ŀ+1		
	    	if(LR[i].ss[0][4]>='A'&&LR[i].ss[0][4]<'Z') 
	    	AddG(i,LR[i].ss[0][4]);//����ƽ���Ŀ���ķ�E->aA E->bB
	    	v++;
            //Ϊÿһ���ķ�����������ɢ I1��I2��I3 
	    	for(j=0;j<LR[0].count;j++){
	    		p=strlen(LR[0].ss[j]);
		    	if(LR[0].ss[j][p-1]!='.'){
		    		add(0,j);//��������ɢ���ķ�СԲ�������һλ 
		    		v++;
		    	}
	    	}
		}
    	else{//��I0����������� 
    		p=strlen(LR[i].ss[0]);//Ii��һ���ķ��ĳ��� 
    		if(LR[i].count==1&&LR[i].ss[0][p-1]=='.'){//��СԲ��������򲻽��д��� 
    	    }
    		else{
	        	p=LR[i].l;//СԲ���λ�� 
	        	if(LR[i].ss[0][p+1]>='A'&&LR[i].ss[0][p+1]<'Z')
	        	AddG(i,LR[i].ss[0][p+1]);//����ƽ���Ŀ���ķ�
	            //Ϊÿһ���ķ�����������ɢ 
	        	for(j=0;j<LR[i].count;j++){
	        		add(i,j);//����������ɢ���ķ�СԲ�������һλ 
	        		v++;
	            }
	            
	        }
            Compare(i);//�����������ɵ�����бȽϣ������ظ�����ɾ��iֵ����� 
		}
	}
    //�����ɵ����������������ȱ�Ĳ��֣�ɾ���ظ���֮����ܻ�������Ϊ�գ��Ӻ��油�룩 
    for(i=0;i<20;i++){
    	for(j=i+1;j<20;j++){
    		if(LR[i].count==0&&LR[j].count!=0&&LR[i].num<LR[j].num){
    			fix(i,j);
    			LR[i]=LR[j];
    			LR[j].count=0;    			
			}
		}
	}
	//�Ե�ǰ����������б�� 
	for(i=0;LR[i].count!=0;)
	i++;
	v=i;
	//�����ǰ�����������ķ� 
	cout<<"�������ź��ķ����ݣ�"<<endl;
	for(i=0;i<v;i++){
    	cout<<i<<":"<<endl;
    	for(j=0;j<LR[i].count;j++)
    	cout<<LR[i].ss[j]<<endl;
        cout<<endl;
    }  
} 

 
//��������ݵ�һ�н���ƥ�䴦�� 
void match(int a,int b){
	int i,j;
	char k;
	if(b==0&&LR[a].count==1&&strlen(LR[a].ss[b])-1==LR[a].l){//�����ս��ķ� ����СԲ������� 
		if(LR[a].ss[b][0]=='Z')//���ǳ�ʼ���ս� 
    	strcpy(r[a+1],"acc");
    	else
		for(i=0;i<5;i++)//Action�����r 
		r[a+1][i]='r';
	}
    else{//�����ս��ķ���k����СԲ���һ���ַ������бȽ��ж� 
    	if(b==0)
    	k=LR[a].ss[b][LR[a].l+1];
    	else
    	k=LR[a].ss[b][4];
    	for(i=0;i<strlen(r[0]);i++){
    		if(r[0][i]==k)
    		rr[a+1][i]=LR[a].c[b];
    	}
	}
}
 
//���з�����Ĺ�������� 
void Output(){
	int i,j,k,temp;
	strcpy(r[0],"abcd#EAB");//������ĵ�һ�� 
	cout<<"LR0������"<<endl;
	cout<<setw(20)<<"Action"<<setw(18)<<"Goto"<<endl; 
	//��������ݵ�һ�н���ƥ�� 
    for(i=0;i<v;i++){
    	for(j=0;j<LR[i].count;j++)
    	match(i,j);//����ƥ�䴦�� 
	}
	//���з����������ʽ�Ĵ��� 
	for(i=0;i<v+1;i++){
		temp=0;
		//��֤������� 
		if(i==0)
		cout<<"   ";
        if(i>0&&i<=10)
    	cout<<" "<<i-1<<":";
    	if(i>10)
    	cout<<i-1<<":";
    	if(strcmp(r[i],"acc")==0)
    	cout<<setw(24);
    	//�����Action���� 
		for(j=0;j<5;j++){
		    if(r[i][j]=='r'){//����ս��ķ� 
    	    	cout<<setw(4)<<r[i][j]<<k;
    	    	temp=1;
    	    }
    	    else if(strcmp(r[i],"acc")==0)//�����ʼ�����ս�G�ķ� 
    	    cout<<r[i][j];
	    	else{ 
	    		if(i==0)
    	    	cout<<setw(5)<<r[i][j];
    	    	else if(rr[i][j]==0)
    	    	cout<<setw(5)<<" ";
    	    	else
    	    	cout<<setw(4)<<"S"<<rr[i][j];
    	    }
	    }
	    if(temp==1)
	    k++;//���ж�r1��r2��r3���±�Ĵ��� 
	    //�����Goto���� 
		for(j=5;j<strlen(r[0]);j++){
			if(i==0)
    	    cout<<setw(5)<<r[i][j];
    	    else if(rr[i][j]==0)
    	    cout<<setw(5)<<" ";
    	    else
    	    cout<<setw(5)<<rr[i][j];
		}
		cout<<endl;
	}
}

//������ 
int main(){
	int i,j;
//	Init();
	input();//�����������޹��ķ� 
	gfj();//�淶���Ĺ��� 
	//Excels();
    Output();//��������� 
} 
