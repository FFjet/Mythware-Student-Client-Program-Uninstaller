#include "stdafx.h"

//��װ����
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



//ɾ������
BOOL DeleteSampleService(CHAR *Serv)
{
	SERVICE_STATUS status;

	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS); 

	if (schSCManager == NULL)

	{

		return FALSE;

	}

	SC_HANDLE schService = OpenService(schSCManager, Serv,

		SERVICE_ALL_ACCESS | DELETE);   // ��÷�����

	if (schService == NULL)

	{

		return FALSE;

	}

	QueryServiceStatus(schService, &status);  // ��÷���ĵ�ǰ״̬

	if (status.dwCurrentState != SERVICE_STOPPED)   // ������񲻴���ֹͣ״̬������״̬����Ϊ

													//ֹͣ״̬
		ControlService(schService, SERVICE_CONTROL_STOP, &status);

	DeleteService(schService);    // ɾ������
	CloseServiceHandle(schSCManager);  // �رշ�����
	CloseServiceHandle(schService);

	return TRUE;
}



//��������
BOOL StartSampleService(CHAR *Serv)
{
	SERVICE_STATUS status;

	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);   // �򿪷�����ƹ�

																				 //�����ݿ⣬�����ط�����ƹ������ݿ�ľ��
	if (schSCManager == NULL)
	{
		return FALSE;
	}

	SC_HANDLE schService = OpenService(schSCManager, Serv,

		SERVICE_ALL_ACCESS | DELETE);    // ��÷�����
	if (schService == NULL)
	{
		return FALSE;
	}

	QueryServiceStatus(schService, &status);   // ��÷���ĵ�ǰ״̬

	if (status.dwCurrentState = SERVICE_STOPPED)   // ���������ֹͣ״̬������״̬����Ϊ����

												   //״̬
		StartService(schService, 0, NULL);   //��������

	CloseServiceHandle(schSCManager);   // �رշ�����
	CloseServiceHandle(schService);

	return TRUE;
}