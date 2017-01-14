#include "stdafx.h"
#include "NamedPipeClient.h"
#include <iostream>

using namespace std;


CNamedPipeClient::CNamedPipeClient()
{
}


CNamedPipeClient::~CNamedPipeClient()
{
}


void CNamedPipeClient::OpenNamedPipeInClient()
{
    //�ȴ����������ܵ�
	WaitNamedPipeA(pPipeName, NMPWAIT_WAIT_FOREVER);
	int a = GetLastError();
  /*  {
        cout<<"�����ܵ�ʵ�������� ..."<<endl<<endl;
        return;
    }*/
 
    //�������ܵ�
    hNamedPipe = CreateFileA(pPipeName, GENERIC_READ | GENERIC_WRITE, 
        0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(INVALID_HANDLE_VALUE == hNamedPipe)
    {
        cout<<"�������ܵ�ʧ�� ..."<<endl<<endl;
        return;
    }
}
 
 
void CNamedPipeClient::NamedPipeReadInClient()
{
    char				pReadBuf[1000];
	DWORD				dwRead;
	char				BufferData[1000];
    //�������ܵ��ж�ȡ����
    if(!ReadFile(hNamedPipe, pReadBuf,4  , &dwRead, NULL))
    {
        delete []pReadBuf;
 
        cout<<"��ȡ����ʧ�� ..."<<endl<<endl;
        return;
    }
}
 
 
void CNamedPipeClient::NamedPipeWriteInClient(char* BufferData)
{
    DWORD                dwWrite;
 
    //�������ܵ���д������
    if(!WriteFile(hNamedPipe, BufferData, strlen(BufferData), &dwWrite, NULL))
    {
        cout<<"д������ʧ�� ..."<<endl<<endl;
        return;
    }
    cout<<"д�����ݳɹ���    "<< BufferData <<endl<<endl;
}