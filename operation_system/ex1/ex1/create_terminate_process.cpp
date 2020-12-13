# include <iostream> 
#include <windows.h>
#include <stdio.h>
#include<TCHAR.h>
void RunExe()
{
	STARTUPINFO si; //定义startupinfo结构，
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);//cb定义结构大小
	

	PROCESS_INFORMATION pi; //进程信息描述结构，接受新进程的描述信息
	memset(&pi, 0, sizeof(pi));
	TCHAR exePath[] = _T("C:\\Program Files\\Internet Explorer\\iexplore.exe");//系统进程.exe可执行文件
	TCHAR CmdLine[] = _T(" http://baidu.com");   //lpCommandLine的内容中开头需要一个空格，不然就和lpApplicationName连在一起去了

	try
	{
		bool createProcess = ::CreateProcess(
			exePath,//lpApplicationName,要执行的模块，包括exe文件路径
			CmdLine,//lpCommandLine,
			NULL,//lpprocessattributes
			NULL,//lpthreadattributes 同上都为指向SECURITY_ATTRIBUTES结构的指针
			false,//不可继承创建者进程
			CREATE_DEFAULT_ERROR_MODE,
			//dwCreationFlags标识了影响新进程创建的标志
			//CREATE_NEW_CONSOLE表示使用新的控制台
			//CREATE_DEFAULT_ERROR_MODE不继承调用进程的错误模式
			//CREATE_NEW_PROCESS_GROUP使用一个进程树的根进程
			//https://blog.csdn.net/pxm2525/article/details/39828865
			NULL,//指向新的环境块
			NULL,//子进程当前驱动器和目录
			&si,//指向STARTUPINFO结构框架
			&pi//指向进程信息描述结构
		);



		if (createProcess)
		{
			std::cout << "进程创建成功" << std::endl;
			std::cout << "进程pid为" << pi.dwProcessId << "\n线程id为" << pi.dwThreadId << std::endl;
			//等待7s后关闭进程
			std::cout << "请等待7s后自动关闭程序" << std::endl;
			WaitForSingleObject(pi.hProcess, 7000L);
			/*::CloseHandle(pi.hProcess);
			::CloseHandle(pi.hThread);
			pi.hProcess = NULL;
			pi.hThread = NULL;
			pi.dwProcessId = 0;
			pi.dwThreadId = 0;*/
			TerminateProcess(pi.hProcess, pi.dwProcessId);
		}
		else
		{
			//如果创建进程失败，查看错误码
			DWORD dwErrCode = GetLastError();
			printf_s("ErrCode : %d\n", dwErrCode);
		}
	}
	catch (...)
	{
	}
}
int main()
{
	RunExe();
	return 0;
}