// Client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MailslotClient.h"
#include "NamedPipeClient.h"
#include "LPCClient.h"
#include <iostream>
#include <Windows.h>
#include "..\\xmlrpc\\src\\XmlRpc.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
VOID TestNamedPipe();
VOID TestRPCClient();
int TestLPCClient();
int main()
{
	TestRPCClient();
	//TestLPCClient();
	getchar();
	getchar();
    return 0;
}
int TestLPCClient()
{
	BOOL bIsWow64Process = FALSE;
	if (IsWow64Process(GetCurrentProcess(), &bIsWow64Process) && bIsWow64Process)
	{
		cout << "32λ����32λϵͳ������" << endl;
		return 0;
	}
	WCHAR BufferData[LPC_MESSAGE_LENGTH] = { 0 };
	CLPCClient Client;
	ULONG MsgType = 0;
	Client.ConnectServer(L"\\LPCServer");
	while (TRUE)
	{
		cout << "Input the Msg Type:";
		cin >> MsgType;
		if (MsgType < 0 || MsgType > 3)
		{
			continue;
		}
		cout << "Input the Message: ";
		wcin >> BufferData;
		if (!Client.LPCSendMessage(BufferData, MsgType))
			break;
		if (MsgType == 2)
		{
			break;
		}
	}
	printf("Bye\r\n");
	return 0;
}
VOID TestNamedPipe()
{
	//CMailslotClient v1;
	//v1.OnSend("hello yifi ");
	CNamedPipeClient v1;
	v1.OpenNamedPipeInClient();

	//���շ���˷���������
	v1.NamedPipeReadInClient();

	//�������ܵ���д������
	v1.NamedPipeWriteInClient("Sukang");
}

VOID TestRPCClient()
{
	using namespace XmlRpc;
	int port = 2356;
	XmlRpcClient client("localhost", 2356);
	XmlRpcValue noArgs;
	XmlRpcValue result;

	if (client.execute("Hello", noArgs, result))
	{
		std::cout << result << std::endl;
	}
	return;
}