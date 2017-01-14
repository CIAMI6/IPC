#include <cstdio>
#include "Mailslot.h"

char* StrRecvData;
CMailslot::CMailslot()
{
	StrRecvData = new char[maxDataLen];
	memset(StrRecvData, 0, maxDataLen);
}


CMailslot::~CMailslot()
{
}

//���հ�ť����Ϣ����
void CMailslot::OnRecv()
{
	DWORD                ReadLength;

	//�����������ݵ��̣߳����ʲ۾�����ݸ��߳�
	CreateRecvThread((LPVOID)MailslotHandle, 0, NULL);
}
//�̴߳�����
DWORD WINAPI RecvThreadProc(LPVOID lpPrameter)
{
	HANDLE                hRecvMailSlot;
	DWORD                dwRead;

	hRecvMailSlot = (HANDLE)lpPrameter;

	//���ô��������ʲ۾�������վ�,�������ݴ�ŵ� pStrRecvData ��
	ReadFile(hRecvMailSlot, StrRecvData, maxDataLen, &dwRead, NULL);
	
	int a = GetLastError();

	printf("%s   %d\r\n", StrRecvData,a);
	//�ر��ʲ�
	CloseHandle(hRecvMailSlot);

	return NULL;
}

void CMailslot::OnCreate()
{
	//������Ϊ ZacharyMailSlot ���ʲ�
	MailslotHandle = CreateMailslot(TEXT("\\\\.\\mailslot\\YIFIMailSlot"), 0,MAILSLOT_WAIT_FOREVER, NULL);

	if (INVALID_HANDLE_VALUE == this->MailslotHandle)
	{
		MessageBox(NULL,TEXT("�����ʲ�ʧ�� ..."), TEXT("��ʾ"), MB_ICONERROR);
		return;
	}
}

HANDLE CMailslot::CreateRecvThread(LPVOID lpParameter, DWORD threadFlag, LPDWORD lpThreadID)
{
	//����һ���߳�
	return CreateThread(NULL, 0, RecvThreadProc, lpParameter, threadFlag, lpThreadID);
}