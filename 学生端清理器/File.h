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
		return FALSE; /** 如果不能找到第一个文件，那么没有目录 */
	}
	else
	{
		FindClose(hFile);
		return TRUE;
	}

}

BOOL DeleteDirectory(const char * DirName)
{
	char szCurPath[MAX_PATH];        //用于定义搜索格式
	_snprintf(szCurPath, MAX_PATH, "%s//*.*", DirName);    //匹配格式为*.*,即该目录下的所有文件
	WIN32_FIND_DATAA FindFileData;
	ZeroMemory(&FindFileData, sizeof(WIN32_FIND_DATAA));
	HANDLE hFile = FindFirstFileA(szCurPath, &FindFileData);
	BOOL IsFinded = TRUE;
	while (IsFinded)
	{
		IsFinded = FindNextFileA(hFile, &FindFileData);    //递归搜索其他的文件
		if (strcmp(FindFileData.cFileName, ".") && strcmp(FindFileData.cFileName, "..")) //如果不是"." ".."目录
		{
			std::string strFileName = "";
			strFileName = strFileName + DirName + "//" + FindFileData.cFileName;
			std::string strTemp;
			strTemp = strFileName;
			if (IsDirectory(strFileName.c_str())) //如果是目录，则递归地调用
			{
				printf("目录为:%s\n", strFileName.c_str());
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
	if (bRet == 0) //删除目录
	{
		printf("删除%s目录失败！\n", DirName);
		if (GetLastError() == 2) printf("原因：目录不存在,已经被删除\n\n");
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
		//read从in流中读取2048字节，放入buf数组中，同时文件指针向后移动2048字节
		//若不足2048字节遇到文件结尾，则以实际提取字节读取。
		in.read(buf, 2048);
		//gcount()用来提取读取的字节数，write将buf中的内容写入out流。
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