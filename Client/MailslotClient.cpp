#include "stdafx.h"
#include "MailslotClient.h"


CMailslotClient::CMailslotClient()
{
}


CMailslotClient::~CMailslotClient()
{
}

void CMailslotClient::OnSend(char* szBuffer)
{
	HANDLE				SendMailSlotHandle;
	DWORD				dwWrite;

	//���ɷ���˴������ʼ���
	SendMailSlotHandle = CreateFile(TEXT("\\\\.\\mailslot\\YIFIMailSlot"),
		GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == SendMailSlotHandle)
	{
		MessageBox(NULL,TEXT("���ʲ�ʧ�� ..."), TEXT("��ʾ"), MB_ICONERROR);
		return;
	}
	//ͨ���ʼ��������˷�������
	if (!WriteFile(SendMailSlotHandle, szBuffer, strlen(szBuffer), &dwWrite, NULL))
	{
		MessageBox(NULL,TEXT("д������ʧ�� ..."), TEXT("��ʾ"), MB_ICONERROR);

		CloseHandle(SendMailSlotHandle);
		return;
	}
	MessageBox(NULL,TEXT("д�����ݳɹ� ..."), TEXT("��ʾ"), MB_ICONINFORMATION);

 
	 
}
