#include "stdafx.h"
#include "Clipboard.h"


Clipboard::Clipboard()
{
}


Clipboard::~Clipboard()
{
}


void Clipboard::SetClipBoardData(char* StrData)
{
	//�� OpenClipboard �����Ĳ���ָ��Ϊ NULL������Ϊ��ǰ���̴򿪼�����
	if (OpenClipboard(NULL))
	{
		char * pDataBuf;

		//ȫ���ڴ����
		HGLOBAL hGlobalClip;

		//��ȫ���ڴ�������ȫ���ڴ�
		hGlobalClip = GlobalAlloc(GHND, strlen(StrData) + 1);
		//ͨ����ȫ���ڴ���������ö�ȫ���ڴ�������
		pDataBuf = (char *)GlobalLock(hGlobalClip);
		memcpy(pDataBuf, StrData, sizeof(StrData));
		//ʹ����ȫ���ڴ�����Ҫ��ȫ���ڴ�����
		GlobalUnlock(hGlobalClip);

		//��ռ�����
		EmptyClipboard();
		//���ü��������ݣ�����ֱ�ӽ����ݷŵ��˼������У���û��ʹ���ӳ��ύ����
		SetClipboardData(CF_TEXT, hGlobalClip);
		//�رռ�����
		CloseClipboard();
	}
}

void Clipboard::GetClipBoardData(char **DataBuf)
{
	if (OpenClipboard(NULL))
	{
		
		//�жϼ������е����ݸ�ʽ�Ƿ�Ϊ CF_TEXT
		if (IsClipboardFormatAvailable(CF_TEXT))
		{
			
			HGLOBAL            hGlobalClip;

			//�Ӽ������л�ȡ��ʽΪ CF_TEXT ������
			hGlobalClip = GetClipboardData(CF_TEXT);
			GlobalLock(hGlobalClip);
			 
			//memcpy(DataBuf, szBuffer, sizeof(szBuffer));
			*DataBuf = (char *)GlobalLock(hGlobalClip);
			GlobalUnlock(hGlobalClip);
		}
		CloseClipboard();
	}
}