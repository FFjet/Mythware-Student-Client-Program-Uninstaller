// 学生端清理器.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Services.h"
#include "Pri.h"
#include "Process.h"
#include "Reg.h"
#include "File.h"
using namespace std;
inline void CloseService()
{
	CHAR S[] = TEXT("STUDSRV");
	DeleteSampleService(S);
}

inline void CloseProgram()
{
	Kill("StudentMain.exe");
	Kill("GATESRV.exe");
	Kill("MasterHelper.exe");
	Kill("ProcHelper.exe");
}
int main()
{
	ios::sync_with_stdio(false);
	st:
	EnableDebugPrivilege();
	CloseService();
	CloseProgram();

	cout << "学生端程序终止：成功" << endl;
	cout << "Student Side Service Stopped: Succeed" << endl << endl;

	CloseService();

	cout << "学生端服务删除：成功" << endl;
	cout << "Student Side Service Deleted: Succeed" << endl << endl;
	cout << "正在搜寻注册表值...请稍后" << endl;
	cout << "Now Searching registry values to delete...Please wait" << endl << endl;
	DoKill();

	cout << endl << "正在删除剩余键值(x64)：SOFTWARE\\WOW6432Node\\TopDomain" << endl;
	cout << "Deleting remainder register keys(x64)：SOFTWARE\\WOW6432Node\\TopDomain" << endl << endl;

	if (SHDeleteKey(HKEY_LOCAL_MACHINE,
		TEXT("SOFTWARE\\WOW6432Node\\TopDomain")) == ERROR_SUCCESS)
		cout << "Done" << endl << endl;

	cout << "正在删除剩余键值(x86)：SOFTWARE\\TopDomain" << endl;
	cout << "Deleting remainder register keys(x86)：SOFTWARE\\TopDomain" << endl << endl;

	if (SHDeleteKey(HKEY_LOCAL_MACHINE,
		TEXT("SOFTWARE\\TopDomain")) == ERROR_SUCCESS)
		cout << "Done" << endl << endl;

	cout << "正在强行删除学生端宿主程序" << endl;
	cout << "Now Deleting the Student Program..." << endl << endl;

	DeleteDirectory("C:\\Program Files (x86)\\Mythware");

	cout << "对于x64系统：C:\\Program Files (x86)\\Mythware删除完毕" << endl;
	cout << "For x64 system：C:\\Program Files (x86)\\Mythware deleted." << endl << endl;

	DeleteDirectory("C:\\Program Files\\Mythware");

	cout << "对于x86系统：C:\\Program Files\\Mythware删除完毕" << endl;
	cout << "For x86系统：C:\\Program Files\\Mythware deleted" << endl << endl;

	if (FFF == false)
	{
		cout << "检测到本次操作有注册表故障，是否重试？（1：是，2：否）" << endl;
		cout << "Some Problems are detected while processing in the registry, retry?(1:Yes, 2:No)" << endl;
		FFF = true;
		int a;
		cin >> a;
		if (a == 1)
		{
			system("cls");
			goto st;
		}
		else
		{
			cout << "卸载极域电子教室操作完毕！" << endl;
			cout << "Uninstall Done!" << endl << endl;
			system("pause");
			return 0;
		}
	}
	else
	{
		cout << "成功卸载极域电子教室！" << endl;
		cout << "Uninstall Successfully!" << endl << endl;
		system("pause");
	}
    return 0;
}

