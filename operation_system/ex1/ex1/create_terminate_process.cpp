# include <iostream> 
#include <windows.h>
#include <stdio.h>
#include<TCHAR.h>
void RunExe()
{
	STARTUPINFO si; //����startupinfo�ṹ��
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);//cb����ṹ��С
	

	PROCESS_INFORMATION pi; //������Ϣ�����ṹ�������½��̵�������Ϣ
	memset(&pi, 0, sizeof(pi));
	TCHAR exePath[] = _T("C:\\Program Files\\Internet Explorer\\iexplore.exe");//ϵͳ����.exe��ִ���ļ�
	TCHAR CmdLine[] = _T(" http://baidu.com");   //lpCommandLine�������п�ͷ��Ҫһ���ո񣬲�Ȼ�ͺ�lpApplicationName����һ��ȥ��

	try
	{
		bool createProcess = ::CreateProcess(
			exePath,//lpApplicationName,Ҫִ�е�ģ�飬����exe�ļ�·��
			CmdLine,//lpCommandLine,
			NULL,//lpprocessattributes
			NULL,//lpthreadattributes ͬ�϶�Ϊָ��SECURITY_ATTRIBUTES�ṹ��ָ��
			false,//���ɼ̳д����߽���
			CREATE_DEFAULT_ERROR_MODE,
			//dwCreationFlags��ʶ��Ӱ���½��̴����ı�־
			//CREATE_NEW_CONSOLE��ʾʹ���µĿ���̨
			//CREATE_DEFAULT_ERROR_MODE���̳е��ý��̵Ĵ���ģʽ
			//CREATE_NEW_PROCESS_GROUPʹ��һ���������ĸ�����
			//https://blog.csdn.net/pxm2525/article/details/39828865
			NULL,//ָ���µĻ�����
			NULL,//�ӽ��̵�ǰ��������Ŀ¼
			&si,//ָ��STARTUPINFO�ṹ���
			&pi//ָ�������Ϣ�����ṹ
		);



		if (createProcess)
		{
			std::cout << "���̴����ɹ�" << std::endl;
			std::cout << "����pidΪ" << pi.dwProcessId << "\n�߳�idΪ" << pi.dwThreadId << std::endl;
			//�ȴ�7s��رս���
			std::cout << "��ȴ�7s���Զ��رճ���" << std::endl;
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
			//�����������ʧ�ܣ��鿴������
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