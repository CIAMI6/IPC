
#include "NamedPipeServer.h"
#include <iostream>


using namespace std;

CNamedPipeServer::CNamedPipeServer()
{
}


CNamedPipeServer::~CNamedPipeServer()
{
}


void CNamedPipeServer::CreateNamedPipeInServer()
{
	HANDLE                    hEvent;
	OVERLAPPED                ovlpd;

	//������Ҫ���������ܵ�
	//���ﴴ������˫��ģʽ��ʹ���ص�ģʽ�������ܵ�
	hNamedPipe = CreateNamedPipeA(pPipeName,
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		0, 1, 1024, 1024, 0, NULL);
	cout << "���������ܵ��ɹ� ..." << endl << endl;
	if (INVALID_HANDLE_VALUE == hNamedPipe)
	{
		hNamedPipe = NULL;
		cout << "���������ܵ�ʧ�� ..." << endl << endl;
		return;
	}

	//����¼��Եȴ��ͻ������������ܵ�
	//���¼�Ϊ�ֶ������¼����ҳ�ʼ��״̬Ϊ���ź�״̬
	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!hEvent)
	{
		cout << "�����¼�ʧ�� ..." << endl << endl;
		return;
	}

	memset(&ovlpd, 0, sizeof(OVERLAPPED));

	//���ֶ������¼����ݸ� ovlap ����
	ovlpd.hEvent = hEvent;

	//�ȴ��ͻ�������
	if (!ConnectNamedPipe(hNamedPipe, &ovlpd))
	{
		if (ERROR_IO_PENDING != GetLastError())
		{
			CloseHandle(hNamedPipe);
			CloseHandle(hEvent);

			cout << "�ȴ��ͻ�������ʧ�� ..." << endl << endl;
			return;
		}
	}

	//�ȴ��¼� hEvent ʧ��
	if (WAIT_FAILED == WaitForSingleObject(hEvent, INFINITE))
	{
		CloseHandle(hNamedPipe);
		CloseHandle(hEvent);

		cout << "�ȴ�����ʧ�� ..." << endl << endl;
		return;
	}

	CloseHandle(hEvent);
}


void CNamedPipeServer::NamedPipeReadInServer()
{
	char *            pReadBuf;
	DWORD            dwRead;

	pReadBuf = new char[strlen(pStr) + 1];
	memset(pReadBuf, 0, strlen(pStr) + 1);

	//�������ܵ��ж�ȡ����
	if (!ReadFile(hNamedPipe, pReadBuf, strlen(pStr), &dwRead, NULL))
	{
		delete[]pReadBuf;

		cout << "��ȡ����ʧ�� ..." << endl << endl;
		return;
	}
	cout << "��ȡ���ݳɹ���    " << pReadBuf << endl << endl;
}


void CNamedPipeServer::NamedPipeWriteInServer(char* szBuffer)
{
	DWORD            dwWrite;

	//�������ܵ���д������
	if (!WriteFile(hNamedPipe, szBuffer, strlen(szBuffer), &dwWrite, NULL))
	{
		cout << "д������ʧ�� ..." << endl << endl;
		return;
	}
	cout << "д�����ݳɹ���    " << szBuffer << endl << endl;
}