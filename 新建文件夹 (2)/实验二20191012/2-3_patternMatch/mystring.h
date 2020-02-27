#ifndef	mystring_H
#define mystring_H

#include <iostream>
#include <cassert>
using namespace std;

class mystring {
private: 
    char  *buffer; //存放字符串的空间的起始位置
    unsigned buflen;  //空间大小
public: 
     //初始化
     mystring();    //空串
     mystring(unsigned); //指定长度串（无值）
     mystring(char); //给定值的串-字符
     mystring(const char *); //给定值的串-c/c++类型的字符串
     mystring(const mystring&); //给定值的串-mystring类型的字符串
     ~mystring();  //  析构

     void operator = (const mystring& right); //赋值
     int compare(const mystring& right) const; //比较
     char& operator[](unsigned index) const;//下标访问
     unsigned length( ) const;  //求串长
	 char* getBuffer() const; //取字符串的存储空间首地址
     istream& Getline(istream&); //按行读入
     operator const char* ( ) const; //转换成C/C++表示的字符串  
     //friend ostream& operator<<(ostream& out,const mystring& str);
};

unsigned cstrLen( const char str[]);//求串长
istream& operator>>(istream& in,mystring& str);//输入流重载
ostream& operator<<(ostream& out,const mystring& str);//输出流重载
int operator<=(const mystring& left,const mystring& right);//关系运算符重载系列
int operator<(const mystring& left,const mystring& right);
int operator>(const mystring& left,const mystring& right);
int operator>=(const mystring& left,const mystring& right);
int operator==(const mystring& left,const mystring& right);
int operator!=(const mystring& left,const mystring& right);

#endif
