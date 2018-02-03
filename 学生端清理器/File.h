#include "stdafx.h"

BOOL IsDirectory(const char *pDir)
{
	char szCurPath[500];
	ZeroMemory(szCurPath, 500);
	sprintf_s(szCurPath, 500, "%s//*", pDir);
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));

	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData); /**< find first file by given path. */

	if (hFile == INVALID_HANDLE_VALUE)
	{
		FindClose(hFile);
		return FALSE; /** ��������ҵ���һ���ļ�����ôû��Ŀ¼ */
	}
	else
	{
		FindClose(hFile);
		return TRUE;
	}

}

BOOL DeleteDirectory(const char * DirName)
{
	char szCurPath[MAX_PATH];        //���ڶ���������ʽ
	_snprintf(szCurPath, MAX_PATH, "%s//*.*", DirName);    //ƥ���ʽΪ*.*,����Ŀ¼�µ������ļ�
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData);
	BOOL IsFinded = TRUE;
	while (IsFinded)
	{
		IsFinded = FindNextFileA(hFile, &FindFileData);    //�ݹ������������ļ�
		if (strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, "..")) //�������"." ".."Ŀ¼
		{
			std::string strFileName = "";
			strFileName = strFileName + DirName + "//" + FindFileData.cFileName;
			std::string strTemp;
			strTemp = strFileName;
			if (IsDirectory(strFileName.c_str())) //�����Ŀ¼����ݹ�ص���
			{
				printf("Ŀ¼Ϊ:%s\n", strFileName.c_str());
				DeleteDirectory(strTemp.c_str());
			}
			else
			{
				DeleteFileA(strTemp.c_str());
			}
		}
	}
	FindClose(hFile);

	BOOL bRet = RemoveDirectoryA(DirName);
	if (bRet == 0) //ɾ��Ŀ¼
	{
		printf("ɾ��%sĿ¼ʧ�ܣ�\n", DirName);
		if (GetLastError() == 2) printf("ԭ��Ŀ¼������,�Ѿ���ɾ��\n\n");
		return FALSE;
	}
	return TRUE;
}


void copy(char* src, char* dst)
{
	ifstream in(src, ios::binary);
	ofstream out(dst, ios::binary);
	if (!in.is_open()) {
		cout << "error open file " << src << endl;
		exit(EXIT_FAILURE);
	}
	if (!out.is_open()) {
		cout << "error open file " << dst << endl;
		exit(EXIT_FAILURE);
	}
	if (src == dst) {
		cout << "the src file can't be same with dst file" << endl;
		exit(EXIT_FAILURE);
	}
	char buf[2048];
	long long totalBytes = 0;
	while (in)
	{
		//read��in���ж�ȡ2048�ֽڣ�����buf�����У�ͬʱ�ļ�ָ������ƶ�2048�ֽ�
		//������2048�ֽ������ļ���β������ʵ����ȡ�ֽڶ�ȡ��
		in.read(buf, 2048);
		//gcount()������ȡ��ȡ���ֽ�����write��buf�е�����д��out����
		out.write(buf, in.gcount());
		totalBytes += in.gcount();
	}
	in.close();
	out.close();
}


void Tranfile(char* pszFileCopee, char* pszFileCoper)
{
	fstream fsCopee(pszFileCopee, ios::binary | ios::in);
	fstream fsCoper(pszFileCoper, ios::binary | ios::out);
	fsCoper << fsCopee.rdbuf();
}