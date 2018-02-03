#include "stdafx.h"
#pragma warning(disable:4996)

#define SLEEP_TIME 377
#define MAX_KEY_LENGTH 5000
#define MAX_PATH_n 50000
#define MAX_PATH 50000
bool FFF = true;
void cal_next(char *str, int *next, int len)
{
	next[0] = -1;
	int k = -1;
	for (int q = 1; q <= len - 1; q++)
	{
		while (k > -1 && str[k + 1] != str[q])
		{
			k = next[k];
		}
		if (str[k + 1] == str[q])
		{
			k = k + 1;
		}
		next[q] = k;
	}
}

int KMP(char *str, int slen, char *ptr, int plen)
{
	int *next = new int[plen];
	cal_next(ptr, next, plen);
	int k = -1;
	for (int i = 0; i < slen; i++)
	{
		while (k >-1 && ptr[k + 1] != str[i])
			k = next[k];
		if (ptr[k + 1] == str[i])
			k = k + 1;
		if (k == plen - 1)
		{
			return i - plen + 1;
		}
	}
	return 0;
}


void RegSearch(HKEY hKey, TCHAR rootKey[], char * path)
{

	HKEY hKeyR;
	DWORD numSubKey = 0;
	DWORD i;
	DWORD sizeSubKey, lpType;
	TCHAR subKey[MAX_PATH];
	DWORD dwType = 0;
	DWORD dwSize = 0, numkey = 0, vnamelen, vdatalen;
	unsigned char pByteSubKey[MAX_PATH] = "";
	char lpValueName[10000];
	unsigned char lpData[10000];
	char hc[3] = { 0x0d,0x0a,0x00 };
	char newpath[MAX_KEY_LENGTH] = "";
	char datatemp[32] = "";


	DWORD ret = RegOpenKeyEx(hKey,
		rootKey,
		0,
		KEY_READ | KEY_ALL_ACCESS | KEY_QUERY_VALUE,
		&hKeyR);


	if (ret != ERROR_SUCCESS)
	{
		return;
	}
	else
	{
		numSubKey = 0;
		numkey = 0;
		RegQueryInfoKey(hKeyR,
			NULL,
			NULL,
			NULL,
			&numSubKey,
			NULL,
			NULL,
			&numkey,
			NULL,//&vnamelen,
			NULL,//&vdatalen ,
			NULL,
			NULL);


		if (numkey)
		{
			for (i = 0; i < numkey; i++)
			{
				vdatalen = MAX_PATH_n;
				vnamelen = MAX_PATH_n;//执行RegEnumValue前，必须有这2个操作!!

				ret = RegEnumValue(
					hKeyR,              // handle to key to query
					i,          // index of value to query
					lpValueName,     // address of buffer for value string
					&vnamelen,  // address for size of value buffer
					NULL,     // reserved
					&lpType, // address of buffer for type code
					lpData,          // address of buffer for value data
					&vdatalen        // address for size of data buffer
				);

				char tc1[] = "Mythware";
				char tc2[] = "极域";
				char tc3[] = "TopDomain";
				char tc4[] = "学生机房管理助手";
				if (KMP(lpValueName, strlen(lpValueName), tc1, strlen(tc1)) || KMP((char*)lpData, strlen((char*)lpData), tc1, strlen(tc1))
					|| KMP(lpValueName, strlen(lpValueName), tc2, strlen(tc2)) || KMP((char*)lpData, strlen((char*)lpData), tc2, strlen(tc2))
					|| KMP(lpValueName, strlen(lpValueName), tc3, strlen(tc3)) || KMP((char*)lpData, strlen((char*)lpData), tc3, strlen(tc3))
					|| KMP(lpValueName, strlen(lpValueName), tc4, strlen(tc4)) || KMP((char*)lpData, strlen((char*)lpData), tc4, strlen(tc4)))
				{
					bool flag = false;
					while (RegDeleteValue(hKeyR, lpValueName) != ERROR_SUCCESS)
					{
						if (GetLastError() == 1060)
						{
							
							cout << "同步出错, GetLastError = 1060，正在为您重新尝试暴力删除" << endl;
							for (register int i = 1; i <= 200; ++i)
								if (RegDeleteValue(hKeyR, lpValueName) == ERROR_SUCCESS)
								{
									cout << "在第" << i << "次操作中成功" << endl;
									flag = true;
									break;
								}
							if (flag) break;
							else
							{
								FFF = false;
								cout << "本次操作失败，请稍后运行本程序再次尝试" << endl;
								break;
							}
						}
					}
				}
			}
		}

		if (numSubKey)
		{
			for (i = 0; i < numSubKey; i++)
			{
				subKey[0] = '\0';
				sizeSubKey = MAX_KEY_LENGTH;

				RegEnumKeyEx(hKeyR,
					i,
					subKey,
					&sizeSubKey,
					NULL,
					NULL,
					NULL,
					NULL);

				strcpy(newpath, path);
				strcat(newpath, subKey);
				strcat(newpath, "\\");

				strcpy(subKey, _T(newpath));

				RegSearch(hKey, subKey, newpath);

			}
			RegCloseKey(hKeyR);
		}

	}

	return;
}


void spy_Hkey(HKEY hKEY, char * regpath)
{
	char path[MAX_KEY_LENGTH] = "";
	strcpy(path, regpath);
	strcat(path, "\\");
	LPTSTR	lpszSubKey = path;

	RegSearch(hKEY, lpszSubKey, path);
	return;

}


int DoKill()
{
	cout << "正在 HKEY_LOCAL_MACHINE 下删除学生端键值" << endl;
	HKEY hKEY = HKEY_LOCAL_MACHINE;

	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\S-1-5-18\\Products\\FDEE4BF597A63C540B94FE23C70AF3DC"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\S-1-5-18\\Components\\1BD5604FE0B0B694FA20D27FCA8639F8"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\UFH\\ARP"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{5FB4EEDF-6A79-45C3-B049-EF327CA03FCD}"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{5FB4EEDF-6A79-45C3-B049-EF327CA03FCD}"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\e-Learning Class V6.0"));	
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\e-Learning Class V6.0"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\WOW6432Node\\Mythware"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Mythware"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\ControlSet001\\Services\\STUDSRV"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\ControlSet002\\Services\\STUDSRV"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\STUDSRV"));
	SHDeleteKey(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services\\STUDSRV"));
	cout << "70%已经删除" << endl;
	spy_Hkey(hKEY, (char*)"SYSTEM\\ControlSet001\\Services\\bam\\UserSettings\\S-1-5-21-590368576-2678778988-308989865-1001");
	spy_Hkey(hKEY, (char*)"SYSTEM\\ControlSet002\\Services\\bam\\UserSettings\\S-1-5-21-590368576-2678778988-308989865-1001");
	cout << "85%已经删除" << endl;
	spy_Hkey(hKEY, (char*)"SYSTEM\\ControlSet001\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\FirewallRules");
	spy_Hkey(hKEY, (char*)"SYSTEM\\ControlSet002\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\FirewallRules");

	cout << "100%已经删除" << endl;
	cout << "正在 HKEY_LOCAL_MACHINE 下删除学生端键值：完成" << endl;

	cout << "正在 HKEY_USERS 下删除学生端键值" << endl;

	hKEY = HKEY_USERS;
	spy_Hkey(hKEY, (char*)"S-1-5-21-590368576-2678778988-308989865-1001\\Software\\Microsoft");
	cout << "50%已经删除" << endl;
	spy_Hkey(hKEY, (char*)"S-1-5-21-590368576-2678778988-308989865-1001\\Software\\Microsoft\\Windows\\CurrentVersion\\UFH\\SHC");
	cout << "100%已经删除" << endl;
	cout << "正在 HKEY_USERS 下删除学生端键值：完成" << endl;

	return 0;
}
