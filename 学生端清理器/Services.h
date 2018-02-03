#include "stdafx.h"

//安装服务
BOOL CreateSampleService(CHAR* N1, CHAR* N2, CHAR* Path)
{
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

																			
	if (schSCManager == NULL)
	{
		return FALSE;
	}
	SC_HANDLE schService = CreateService(schSCManager, N1, N2,
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
		Path,
		NULL, NULL, NULL, NULL, NULL);
	if (schService == NULL)
	{
		return FALSE;
	}
	CloseServiceHandle(schSCManager);
	CloseServiceHandle(schService);
	return TRUE;
}



//删除服务
BOOL DeleteSampleService(CHAR *Serv)
{
	SERVICE_STATUS status;

	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS); 

	if (schSCManager == NULL)

	{

		return FALSE;

	}

	SC_HANDLE schService = OpenService(schSCManager, Serv,

		SERVICE_ALL_ACCESS | DELETE);   // 获得服务句柄

	if (schService == NULL)

	{

		return FALSE;

	}

	QueryServiceStatus(schService, &status);  // 获得服务的当前状态

	if (status.dwCurrentState != SERVICE_STOPPED)   // 如果服务不处于停止状态，则将其状态设置为

													//停止状态
		ControlService(schService, SERVICE_CONTROL_STOP, &status);

	DeleteService(schService);    // 删除服务
	CloseServiceHandle(schSCManager);  // 关闭服务句柄
	CloseServiceHandle(schService);

	return TRUE;
}



//启动服务
BOOL StartSampleService(CHAR *Serv)
{
	SERVICE_STATUS status;

	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);   // 打开服务控制管

																				 //理数据库，并返回服务控制管理数据库的句柄
	if (schSCManager == NULL)
	{
		return FALSE;
	}

	SC_HANDLE schService = OpenService(schSCManager, Serv,

		SERVICE_ALL_ACCESS | DELETE);    // 获得服务句柄
	if (schService == NULL)
	{
		return FALSE;
	}

	QueryServiceStatus(schService, &status);   // 获得服务的当前状态

	if (status.dwCurrentState = SERVICE_STOPPED)   // 如果服务处于停止状态，则将其状态设置为启动

												   //状态
		StartService(schService, 0, NULL);   //启动服务

	CloseServiceHandle(schSCManager);   // 关闭服务句柄
	CloseServiceHandle(schService);

	return TRUE;
}