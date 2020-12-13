#include<iostream>
#include<iomanip>
#include<string.h>
#include<bits/stdc++.h>
#define maxN 100
using namespace std;

char str[maxN][maxN];//存储文法 
int grammer_lines;//存储文法行数 
int generated_items=0;//存储生成项的个数 
char charR[20][10];//存储分析表的float值 
int Rvalue[20][10];//存储分析表的int值 
struct DFA{
	int OrderNum;//记录生成项的序号 
	int  childloc[10];//存储该项的上一项位置 
	int father;//记录父项目 
	char grammer[10][10];//存储该项的文法 
	int cnt;//记录该项的文法行数 
	int dotloc;//存储第一行字符串'.'的位置 
}LR[maxN];

//初始化，输入上下文无关文法，以#号结尾 
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



//为文法添加小数点 
void AddDot(int LRnum,int row){//为LR[a]的ss第b行字符串添加'.' 
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

//添加移进项目的文法 
void AddGrammer(int LRnum,char s){//把str文法中左部非终结符与s相同的文法，添加进LR[a]中 
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

//将文法小圆点向后移一位 
void addAStep(int LRnum,int j){
	int i,k;
	char temp;
	for(i=0;i<strlen(LR[LRnum].grammer[j]);i++){
		LR[generated_items].grammer[0][i]=LR[LRnum].grammer[j][i];
		if(LR[LRnum].grammer[j][i]=='.')
		k=i;//记录小圆点的位置 
	}
	LR[LRnum].childloc[j]=generated_items;//记录该条文法的跳转（子）项数 
	LR[generated_items].father=LRnum;//记录跳转项数的来源（父代） 
	LR[generated_items].cnt++;
	temp=LR[generated_items].grammer[0][k+1];//小圆点向后移一位 
	LR[generated_items].grammer[0][k+1]=LR[generated_items].grammer[0][k];
	LR[generated_items].grammer[0][k]=temp;
	LR[generated_items].dotloc=k+1;//记录小圆点的位置 
}

//更新某一项的来源（父代）和每一句文法的跳转项（子代） 
void update(int a,int LRnum){
	int i,j,k;
	k=LR[LRnum].father;//父代 
	for(i=0;i<LR[k].cnt;i++)
	if(LR[k].childloc[i]==LRnum)
	LR[k].childloc[i]=a;//子代 
}

//比较，删除相同的内容 
void CmpAndDel(int LRnum){
	int i,j,k;
	for(i=0;i<LRnum;i++){
		for(j=i+1;j<=LRnum;j++){
			if(strcmp(LR[i].grammer[0],LR[j].grammer[0])==0){//若相同 
				update(i,j);
				memset(LR[j].grammer,0,sizeof(LR[j].grammer));//靠后的文法内容清空 
				LR[j].cnt=0;
			}
		}
	}	
}

//LR(0)规范集的构建
void Create_LR0(){
	int i,j,k,p;
	for(i=0;i<20;i++){
		LR[i].OrderNum=i;//Ii
		if(i==0){//第一个，赋予文法的初始符Z->E 
			for(k=0;k<strlen(str[0]);k++)
			LR[0].grammer[0][k]=str[0][k];
			AddDot(0,LR[0].cnt);//添加小圆点 Z->.E 
			LR[0].dotloc=3;//小圆点的位置 
			LR[0].cnt++;//文法数目+1		
	    	if(LR[i].grammer[0][4]>='A'&&LR[i].grammer[0][4]<'Z') 
	    	AddGrammer(i,LR[i].grammer[0][4]);//添加移进项目的文法E->aA E->bB
	    	generated_items++;
            //为每一个文法进行向外扩散 I1、I2、I3 
	    	for(j=0;j<LR[0].cnt;j++){
	    		p=strlen(LR[0].grammer[j]);
		    	if(LR[0].grammer[j][p-1]!='.'){
		    		addAStep(0,j);//将向外扩散的文法小圆点向后移一位 
		    		generated_items++;
		    	}
	    	}
		}
    	else{//除I0以外的生成项 
    		p=strlen(LR[i].grammer[0]);//Ii第一句文法的长度 
    		if(LR[i].cnt==1&&LR[i].grammer[0][p-1]=='.'){//若小圆点再最后则不进行处理 
    	    }
    		else{
	        	p=LR[i].dotloc;//小圆点的位置 
	        	if(LR[i].grammer[0][p+1]>='A'&&LR[i].grammer[0][p+1]<'Z')
	        	AddGrammer(i,LR[i].grammer[0][p+1]);//添加移进项目的文法
	            //为每一个文法进行向外扩散 
	        	for(j=0;j<LR[i].cnt;j++){
	        		addAStep(i,j);//将待向外扩散的文法小圆点向后移一位 
	        		generated_items++;
	            }
	            
	        }
            CmpAndDel(i);//对所有已生成的项进行比较，若有重复的则删除i值靠后的 
		}
	}
    //将生成的项进行整理，补齐有缺的部分（删除重复的之后可能会有内容为空，从后面补齐） 
    for(i=0;i<20;i++){
    	for(j=i+1;j<20;j++){
    		if(LR[i].cnt==0&&LR[j].cnt!=0&&LR[i].OrderNum<LR[j].OrderNum){
    			update(i,j);
    			LR[i]=LR[j];
    			LR[j].cnt=0;    			
			}
		}
	}
	//对当前的生成项进行编号 
	for(i=0;LR[i].cnt!=0;)
	i++;
	generated_items=i;
	//输出当前生成项及各项的文法 
	cout<<"各项的序号和文法内容："<<endl;
	for(i=0;i<generated_items;i++){
    	cout<<i<<":"<<endl;
    	for(j=0;j<LR[i].cnt;j++)
    	cout<<LR[i].grammer[j]<<endl;
        cout<<endl;
    }  
} 

 
//分析表根据第一行进行匹配处理 
void match(int LRnum,int row){
	int i,j;
	char k;
	if(row==0&&LR[LRnum].cnt==1&&strlen(LR[LRnum].grammer[row])-1==LR[LRnum].dotloc){//若是终结文法 （即小圆点在最后） 
		if(LR[LRnum].grammer[row][0]=='Z')//且是初始符终结 
    	strcpy(charR[LRnum+1],"acc");
    	else
		for(i=0;i<5;i++)//Action都输出r 
		charR[LRnum+1][i]='r';
	}
    else{//不是终结文法，k储存小圆点后一个字符，进行比较判断 
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
 
//进行分析表的构建和输出 
void print(){
	int i,j,k,temp;
	strcpy(charR[0],"abcd#EAB");//分析表的第一行 
	cout<<"LR0分析表："<<endl;
	cout<<setw(20)<<"Action"<<setw(18)<<"Goto"<<endl; 
	//分析表根据第一行进行匹配 
    for(i=0;i<generated_items;i++){
    	for(j=0;j<LR[i].cnt;j++)
    	match(i,j);//进行匹配处理 
	}
	//进行分析表输出形式的处理 
	for(i=0;i<generated_items+1;i++){
		temp=0;
		//保证输出对其 
		if(i==0)
		cout<<"   ";
        if(i>0&&i<=10)
    	cout<<" "<<i-1<<":";
    	if(i>10)
    	cout<<i-1<<":";
    	if(strcmp(charR[i],"acc")==0)
    	cout<<setw(24);
    	//先输出Action部分 
		for(j=0;j<5;j++){
		    if(charR[i][j]=='r'){//输出终结文法 
    	    	cout<<setw(4)<<charR[i][j]<<k;
    	    	temp=1;
    	    }
    	    else if(strcmp(charR[i],"acc")==0)//输出起始符的终结欸文法 
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
	    k++;//进行对r1、r2、r3等下标的处理 
	    //再输出Goto部分 
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
	strcpy(charR[0],"abcd#EAB");//分析表的第一行 
	out<<"LR0分析表："<<endl;
	out<<setw(20)<<"Action"<<setw(18)<<"Goto"<<endl; 
	//分析表根据第一行进行匹配 
    for(i=0;i<generated_items;i++){
    	for(j=0;j<LR[i].cnt;j++)
    	match(i,j);//进行匹配处理 
	}
	//进行分析表输出形式的处理 
	for(i=0;i<generated_items+1;i++){
		temp=0;
		//保证输出对其 
		if(i==0)
		out<<"   ";
        if(i>0&&i<=10)
    	out<<" "<<i-1<<":";
    	if(i>10)
    	out<<i-1<<":";
    	if(strcmp(charR[i],"acc")==0)
    	out<<setw(24);
    	//先输出Action部分 
		for(j=0;j<5;j++){
		    if(charR[i][j]=='r'){//输出终结文法 
    	    	out<<setw(4)<<charR[i][j]<<k;
    	    	temp=1;
    	    }
    	    else if(strcmp(charR[i],"acc")==0)//输出起始符的终结欸文法 
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
	    k++;//进行对r1、r2、r3等下标的处理 
	    //再输出Goto部分 
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
//主函数 
int main(){
	Init();//输入上下文无关文法 
	Create_LR0();//规范集的构建 
    print();//输出分析表 
    output();
    
} 
