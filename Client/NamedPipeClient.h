#pragma once
#include <Windows.h>
class CNamedPipeClient
{
public:
	CNamedPipeClient();
	~CNamedPipeClient();


	HANDLE            hNamedPipe;

	 
	const char * pPipeName = "\\\\.\\pipe\\yifiPipe";
	//�������ܵ�
	void OpenNamedPipeInClient();

	//�ͻ��˴������ܵ��ж�ȡ����
	void NamedPipeReadInClient();

	//�ͻ����������ܵ���д������
	void NamedPipeWriteInClient(char* BufferData);
};

