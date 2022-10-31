#include <iostream>
#include <windows.h>
#include <Shlobj_core.h>
using namespace std;
int RegKeyValueAdd(HKEY,LPCSTR);
int main()
{	
	if (IsUserAnAdmin()) //Admin Control
		cout << RegKeyValueAdd(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run #Memet@Karul");
	
	else {
		cout << "ADMIN DEGIL" << endl;
		char  path[MAX_PATH];
		GetModuleFileNameA(NULL, path, MAX_PATH);
		cout << "path." << path << endl;
		SHELLEXECUTEINFOA  pExecInfo = { sizeof(pExecInfo) };
		//pExecInfo.fMask = SEE_MASK_DEFAULT ;
		pExecInfo.lpVerb = "runas";
		pExecInfo.lpFile = path;//  GetCommandLineA();    
		pExecInfo.hwnd = NULL;
		pExecInfo.nShow = SW_NORMAL;

		auto DShelError = ShellExecuteExA(&pExecInfo);
		DWORD dwError = GetLastError();
		cout << "error." << dwError << endl;
		if (!DShelError) {
			cout << "ERROR. " << GetLastError << endl;
			DWORD dwError = GetLastError();
			if (dwError == ERROR_CANCELLED)
				cout << "ERROR. " << dwError << endl;
				return -1;
		}
	}
}

int  RegKeyValueAdd(HKEY hKey,LPCSTR  pathKeyValue) {
	//Format -> Template_1\\Template_2 #Memet@Karul
	int i=0;
	string sPath;
	string sKey;
	string sValue;
	for (; i < strlen(pathKeyValue);i++) {
		if (pathKeyValue[i] == '#') break;
		sPath += pathKeyValue[i];
	}
	int j = i + 1;
	for (; j < strlen(pathKeyValue); j++) {
		if (pathKeyValue[j] == '@') break;
		sKey += pathKeyValue[j];
	}
	int k = j+1;
	for (; k < strlen(pathKeyValue); k++) {
		sValue += pathKeyValue[k];
	}
	cout << "path  : " << sPath << endl;
	cout << "Key   : " << sKey << endl;
	cout << "Value : " << sValue << endl;
	HKEY hkRegOpen;
	DWORD dRegReturn;
	LONG res1 = RegCreateKeyExA(hKey, sPath.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hkRegOpen, &dRegReturn);
	if (res1!=0) {
		RegCloseKey(hkRegOpen);
		return res1;
	}
	LONG res2=RegSetValueExA(hkRegOpen, sKey.c_str(), 0, REG_SZ, (LPBYTE)sValue.c_str(), strlen((char*)sValue.c_str()) + 1);
	if (res2 != 0) {
		RegCloseKey(hkRegOpen);
		return res2;
	}
	RegCloseKey(hkRegOpen);
	return 0;
}


/*
***RESOURCES***
https://learn.microsoft.com/en-us/windows/win32/com/the-com-elevation-moniker?redirectedfrom=MSDN




fotoğrafları şfireleme


OpenProcessToken
GetTokenInformation

*/

