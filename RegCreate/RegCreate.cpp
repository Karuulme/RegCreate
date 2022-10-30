#include <iostream>
#include <windows.h>
#include <Shlobj_core.h>
using namespace std;
int RegKeyValueAdd(HKEY,LPCSTR);
bool isUserAdmin() {
	bool adminActive = false;
	HANDLE  ProcessHandle={};
	TOKEN_ELEVATION Tuser;
	DWORD Dsize;
	if (!IsUserAnAdmin()) {
		if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &ProcessHandle)) {
			if (GetTokenInformation(ProcessHandle, TokenElevation, &Tuser, sizeof(Tuser), &Dsize)) {
				adminActive = Tuser.TokenIsElevated;
			}
		}
	}
	CloseHandle(ProcessHandle);
	return adminActive;
}

int main()
{
	


	if (isUserAdmin()) {
		cout << "ADMIN ";
	}
	else {
		
		DWORD     cbSize;
		SHELLEXECUTEINFOA pExecInfo = {sizeof(pExecInfo)};
		LPCSTR path = "runas";
		//pExecInfo->fMask = SEE_MASK_NO_CONSOLE;
		pExecInfo.lpVerb = path;
		pExecInfo.lpFile = "RegCreate.exe";// GetCommandLineA();
		pExecInfo.hwnd = NULL;
		pExecInfo.nShow = SW_NORMAL;
		if (ShellExecuteExA(&pExecInfo))
			cout << "Basarili +"<<endl;
		else cout << "Basarisiz -" << endl;
		cout << GetLastError();
	}
	
	//cout << RegKeyValueAdd(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run #Memet@Karul");

	//cout<<RegKeyValueAdd(HKEY_CURRENT_USER,"Template_1\\Template_2 #Memet@Karul");
	//cout<<RegKeyValueAdd(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run #Memet@Karul");
	//SOFTWARE\Microsoft\Windows\CurrentVersion\Run

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
	LPCSTR path =sPath.c_str();
	LPCSTR Key = sKey.c_str();
	LPCSTR Value = sValue.c_str();
	cout << "path  : " << path << endl;
	cout << "Key   : " << Key << endl;
	cout << "Value : " << Value << endl;
	HKEY hkRegOpen;
	DWORD dRegReturn;
	LONG res1 = RegCreateKeyExA(hKey, path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hkRegOpen, &dRegReturn);
	if (res1!=0) {
		RegCloseKey(hkRegOpen);
		return res1;
	}
	LONG res2=RegSetValueExA(hkRegOpen, Key, 0, REG_SZ, (LPBYTE)Value, strlen((char*)Value) + 1);
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



ADMİN MİYİZ					
yönetici olarak çalıştırma  

fotoğrafları şfireleme


OpenProcessToken
GetTokenInformation

*/

