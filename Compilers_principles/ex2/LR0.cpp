#include<iostream>
#include<iomanip>
#include<string.h>
#include<bits/stdc++.h>
#define maxN 100
using namespace std;

char str[maxN][maxN];//�洢�ķ� 
int grammer_lines;//�洢�ķ����� 
int generated_items=0;//�洢������ĸ��� 
char charR[20][10];//�洢�������floatֵ 
int Rvalue[20][10];//�洢�������intֵ 
struct DFA{
	int OrderNum;//��¼���������� 
	int  childloc[10];//�洢�������һ��λ�� 
	int father;//��¼����Ŀ 
	char grammer[10][10];//�洢������ķ� 
	int cnt;//��¼������ķ����� 
	int dotloc;//�洢��һ���ַ���'.'��λ�� 
}LR[maxN];

//��ʼ���������������޹��ķ�����#�Ž�β 
void Init(){

	ifstream in("input.txt",ios::in);
	int i=0;
    for(i =0;;i++){
    	in >> str[i];
    	if(str[i] != "")
    		cout<<str[i]<<endl;
    	if(str[i][0] == '#')
    		break;
	}
    in.close(); 
//    strcat(str[0],"S->");
    str[0][3] = str[1][0];
    grammer_lines=i+1;
}



//Ϊ�ķ����С���� 
void AddDot(int LRnum,int row){//ΪLR[a]��ss��b���ַ������'.' 
	int i,j=0;
	char c[10];
	for(i=0;i<3;i++)
	c[j++]=LR[LRnum].grammer[row][i];
	c[3]='.';
	j++;
	for(i=3;i<strlen(LR[LRnum].grammer[row]);i++)
	c[j++]=LR[LRnum].grammer[row][i];
	memset(LR[LRnum].grammer[row],0,sizeof(LR[LRnum].grammer[row]));
	for(i=0;i<j;i++)
	LR[LRnum].grammer[row][i]=c[i];
}

//����ƽ���Ŀ���ķ� 
void AddGrammer(int LRnum,char s){//��str�ķ����󲿷��ս����s��ͬ���ķ�����ӽ�LR[a]�� 
	int i,j,k;
	for(i=0;i<grammer_lines;i++){
		if(str[i][0]==s){
			for(j=0;j<strlen(str[i]);j++)
			LR[LRnum].grammer[LR[LRnum].cnt][j]=str[i][j];
			AddDot(LRnum,LR[LRnum].cnt); 
			LR[LRnum].cnt++;
		}
	}
}

//���ķ�СԲ�������һλ 
void addAStep(int LRnum,int j){
	int i,k;
	char temp;
	for(i=0;i<strlen(LR[LRnum].grammer[j]);i++){
		LR[generated_items].grammer[0][i]=LR[LRnum].grammer[j][i];
		if(LR[LRnum].grammer[j][i]=='.')
		k=i;//��¼СԲ���λ�� 
	}
	LR[LRnum].childloc[j]=generated_items;//��¼�����ķ�����ת���ӣ����� 
	LR[generated_items].father=LRnum;//��¼��ת��������Դ�������� 
	LR[generated_items].cnt++;
	temp=LR[generated_items].grammer[0][k+1];//СԲ�������һλ 
	LR[generated_items].grammer[0][k+1]=LR[generated_items].grammer[0][k];
	LR[generated_items].grammer[0][k]=temp;
	LR[generated_items].dotloc=k+1;//��¼СԲ���λ�� 
}

//����ĳһ�����Դ����������ÿһ���ķ�����ת��Ӵ��� 
void update(int a,int LRnum){
	int i,j,k;
	k=LR[LRnum].father;//���� 
	for(i=0;i<LR[k].cnt;i++)
	if(LR[k].childloc[i]==LRnum)
	LR[k].childloc[i]=a;//�Ӵ� 
}

//�Ƚϣ�ɾ����ͬ������ 
void CmpAndDel(int LRnum){
	int i,j,k;
	for(i=0;i<LRnum;i++){
		for(j=i+1;j<=LRnum;j++){
			if(strcmp(LR[i].grammer[0],LR[j].grammer[0])==0){//����ͬ 
				update(i,j);
				memset(LR[j].grammer,0,sizeof(LR[j].grammer));//������ķ�������� 
				LR[j].cnt=0;
			}
		}
	}	
}

//LR(0)�淶���Ĺ���
void Create_LR0(){
	int i,j,k,p;
	for(i=0;i<20;i++){
		LR[i].OrderNum=i;//Ii
		if(i==0){//��һ���������ķ��ĳ�ʼ��Z->E 
			for(k=0;k<strlen(str[0]);k++)
			LR[0].grammer[0][k]=str[0][k];
			AddDot(0,LR[0].cnt);//���СԲ�� Z->.E 
			LR[0].dotloc=3;//СԲ���λ�� 
			LR[0].cnt++;//�ķ���Ŀ+1		
	    	if(LR[i].grammer[0][4]>='A'&&LR[i].grammer[0][4]<'Z') 
	    	AddGrammer(i,LR[i].grammer[0][4]);//����ƽ���Ŀ���ķ�E->aA E->bB
	    	generated_items++;
            //Ϊÿһ���ķ�����������ɢ I1��I2��I3 
	    	for(j=0;j<LR[0].cnt;j++){
	    		p=strlen(LR[0].grammer[j]);
		    	if(LR[0].grammer[j][p-1]!='.'){
		    		addAStep(0,j);//��������ɢ���ķ�СԲ�������һλ 
		    		generated_items++;
		    	}
	    	}
		}
    	else{//��I0����������� 
    		p=strlen(LR[i].grammer[0]);//Ii��һ���ķ��ĳ��� 
    		if(LR[i].cnt==1&&LR[i].grammer[0][p-1]=='.'){//��СԲ��������򲻽��д��� 
    	    }
    		else{
	        	p=LR[i].dotloc;//СԲ���λ�� 
	        	if(LR[i].grammer[0][p+1]>='A'&&LR[i].grammer[0][p+1]<'Z')
	        	AddGrammer(i,LR[i].grammer[0][p+1]);//����ƽ���Ŀ���ķ�
	            //Ϊÿһ���ķ�����������ɢ 
	        	for(j=0;j<LR[i].cnt;j++){
	        		addAStep(i,j);//����������ɢ���ķ�СԲ�������һλ 
	        		generated_items++;
	            }
	            
	        }
            CmpAndDel(i);//�����������ɵ�����бȽϣ������ظ�����ɾ��iֵ����� 
		}
	}
    //�����ɵ����������������ȱ�Ĳ��֣�ɾ���ظ���֮����ܻ�������Ϊ�գ��Ӻ��油�룩 
    for(i=0;i<20;i++){
    	for(j=i+1;j<20;j++){
    		if(LR[i].cnt==0&&LR[j].cnt!=0&&LR[i].OrderNum<LR[j].OrderNum){
    			update(i,j);
    			LR[i]=LR[j];
    			LR[j].cnt=0;    			
			}
		}
	}
	//�Ե�ǰ����������б�� 
	for(i=0;LR[i].cnt!=0;)
	i++;
	generated_items=i;
	//�����ǰ�����������ķ� 
	cout<<"�������ź��ķ����ݣ�"<<endl;
	for(i=0;i<generated_items;i++){
    	cout<<i<<":"<<endl;
    	for(j=0;j<LR[i].cnt;j++)
    	cout<<LR[i].grammer[j]<<endl;
        cout<<endl;
    }  
} 

 
//��������ݵ�һ�н���ƥ�䴦�� 
void match(int LRnum,int row){
	int i,j;
	char k;
	if(row==0&&LR[LRnum].cnt==1&&strlen(LR[LRnum].grammer[row])-1==LR[LRnum].dotloc){//�����ս��ķ� ����СԲ������� 
		if(LR[LRnum].grammer[row][0]=='Z')//���ǳ�ʼ���ս� 
    	strcpy(charR[LRnum+1],"acc");
    	else
		for(i=0;i<5;i++)//Action�����r 
		charR[LRnum+1][i]='r';
	}
    else{//�����ս��ķ���k����СԲ���һ���ַ������бȽ��ж� 
    	if(row==0)
    	k=LR[LRnum].grammer[row][LR[LRnum].dotloc+1];
    	else
    	k=LR[LRnum].grammer[row][4];
    	for(i=0;i<strlen(charR[0]);i++){
    		if(charR[0][i]==k)
    		Rvalue[LRnum+1][i]=LR[LRnum].childloc[row]; 
    	}
	}
}
 
//���з�����Ĺ�������� 
void print(){
	int i,j,k,temp;
	strcpy(charR[0],"abcd#EAB");//������ĵ�һ�� 
	cout<<"LR0������"<<endl;
	cout<<setw(20)<<"Action"<<setw(18)<<"Goto"<<endl; 
	//��������ݵ�һ�н���ƥ�� 
    for(i=0;i<generated_items;i++){
    	for(j=0;j<LR[i].cnt;j++)
    	match(i,j);//����ƥ�䴦�� 
	}
	//���з����������ʽ�Ĵ��� 
	for(i=0;i<generated_items+1;i++){
		temp=0;
		//��֤������� 
		if(i==0)
		cout<<"   ";
        if(i>0&&i<=10)
    	cout<<" "<<i-1<<":";
    	if(i>10)
    	cout<<i-1<<":";
    	if(strcmp(charR[i],"acc")==0)
    	cout<<setw(24);
    	//�����Action���� 
		for(j=0;j<5;j++){
		    if(charR[i][j]=='r'){//����ս��ķ� 
    	    	cout<<setw(4)<<charR[i][j]<<k;
    	    	temp=1;
    	    }
    	    else if(strcmp(charR[i],"acc")==0)//�����ʼ�����ս�G�ķ� 
    	    cout<<charR[i][j];
	    	else{ 
	    		if(i==0)
    	    	cout<<setw(5)<<charR[i][j];
    	    	else if(Rvalue[i][j]==0)
    	    	cout<<setw(5)<<" ";
    	    	else
    	    	cout<<setw(4)<<"S"<<Rvalue[i][j];
    	    }
	    }
	    if(temp==1)
	    k++;//���ж�r1��r2��r3���±�Ĵ��� 
	    //�����Goto���� 
		for(j=5;j<strlen(charR[0]);j++){
			if(i==0)
    	    cout<<setw(5)<<charR[i][j];
    	    else if(Rvalue[i][j]==0)
    	    cout<<setw(5)<<" ";
    	    else
    	    cout<<setw(5)<<Rvalue[i][j];
		}
		cout<<endl;
	}
}
void output(){
	int i,j,k,temp;
	ofstream out("output.txt",ios::out);
	for(i=0;i<generated_items;i++){
    	out<<i<<":"<<endl;
    	for(j=0;j<LR[i].cnt;j++)
    	out<<LR[i].grammer[j]<<endl;
        out<<endl;
    } 
	strcpy(charR[0],"abcd#EAB");//������ĵ�һ�� 
	out<<"LR0������"<<endl;
	out<<setw(20)<<"Action"<<setw(18)<<"Goto"<<endl; 
	//��������ݵ�һ�н���ƥ�� 
    for(i=0;i<generated_items;i++){
    	for(j=0;j<LR[i].cnt;j++)
    	match(i,j);//����ƥ�䴦�� 
	}
	//���з����������ʽ�Ĵ��� 
	for(i=0;i<generated_items+1;i++){
		temp=0;
		//��֤������� 
		if(i==0)
		out<<"   ";
        if(i>0&&i<=10)
    	out<<" "<<i-1<<":";
    	if(i>10)
    	out<<i-1<<":";
    	if(strcmp(charR[i],"acc")==0)
    	out<<setw(24);
    	//�����Action���� 
		for(j=0;j<5;j++){
		    if(charR[i][j]=='r'){//����ս��ķ� 
    	    	out<<setw(4)<<charR[i][j]<<k;
    	    	temp=1;
    	    }
    	    else if(strcmp(charR[i],"acc")==0)//�����ʼ�����ս�G�ķ� 
    	    out<<charR[i][j];
	    	else{ 
	    		if(i==0)
    	    	out<<setw(5)<<charR[i][j];
    	    	else if(Rvalue[i][j]==0)
    	    	out<<setw(5)<<" ";
    	    	else
    	    	out<<setw(4)<<"S"<<Rvalue[i][j];
    	    }
	    }
	    if(temp==1)
	    k++;//���ж�r1��r2��r3���±�Ĵ��� 
	    //�����Goto���� 
		for(j=5;j<strlen(charR[0]);j++){
			if(i==0)
    	    out<<setw(5)<<charR[i][j];
    	    else if(Rvalue[i][j]==0)
    	    out<<setw(5)<<" ";
    	    else
    	    out<<setw(5)<<Rvalue[i][j];
		}
		out<<endl;
	}
}
//������ 
int main(){
	Init();//�����������޹��ķ� 
	Create_LR0();//�淶���Ĺ��� 
    print();//��������� 
    output();
    
} 
