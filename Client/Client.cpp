// Client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MailslotClient.h"
#include "NamedPipeClient.h"
int main()
{
	//CMailslotClient v1;
	//v1.OnSend("hello yifi ");
	CNamedPipeClient v1;
	v1.OpenNamedPipeInClient();

	//���շ���˷���������
	v1.NamedPipeReadInClient();

	//�������ܵ���д������
	v1.NamedPipeWriteInClient("Sukang");
	getchar();
	getchar();
    return 0;
}

