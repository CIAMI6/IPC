#pragma once
#include <Windows.h>
//���������ʲ۷��ͺͽ��յ���������ֽ���
const int        maxDataLen = 424;
class CMailslot
{
public:

	HANDLE MailslotHandle;
	CMailslot();
	~CMailslot();

	
	void OnRecv();
	void OnCreate();
	 
	//����һ�����������̵߳ĳ�Ա����
	HANDLE    CreateRecvThread(LPVOID lpParameter, DWORD threadFlag, LPDWORD lpThreadID);
};

