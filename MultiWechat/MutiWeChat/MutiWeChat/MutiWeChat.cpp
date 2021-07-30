#include <iostream>
#include <AclAPI.h>
#include<windows.h>
#include<tchar.h>

int WINAPI _tWinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPTSTR szCmdLine, IN int iCmdShow)
{
	HANDLE hMutex = CreateMutexW(NULL, FALSE, L"_WeChat_App_Instance_Identity_Mutex_Name");
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY; //当前运行权限
	PSID pEveryoneSID = NULL;
	char szBuffer[4096];
	PACL pAcl = (PACL)szBuffer;
	AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pEveryoneSID);
	InitializeAcl(pAcl, sizeof(szBuffer), ACL_REVISION);
	AddAccessDeniedAce(pAcl, ACL_REVISION, MUTEX_ALL_ACCESS, pEveryoneSID);
	SetSecurityInfo(hMutex, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pAcl, NULL);
	WinExec(_T("./WeChat.exe"), SW_HIDE);
	return false;
}
