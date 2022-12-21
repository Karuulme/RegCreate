#include <iostream>
#include <windows.h>
#include <Shlobj_core.h>
using namespace std;
int RegKeyValueAdd(HKEY,LPCSTR);
int main()
{	
	if (IsUserAnAdmin()) //Admin Control
		RegKeyValueAdd(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run #Memet @Karul");
	else {
		//we run the program with ShellExecuteExA as administrator.
		char  path[MAX_PATH];
		GetModuleFileNameA(NULL, path, MAX_PATH);

		SHELLEXECUTEINFOA  pExecInfo = { sizeof(pExecInfo) };
		pExecInfo.lpVerb = "runas";
		pExecInfo.lpFile = path;   
		pExecInfo.hwnd = NULL;
		pExecInfo.nShow = SW_NORMAL;

		auto DShelError = ShellExecuteExA(&pExecInfo);
		if (!DShelError) {
			cout << "ShellExecuteExA." << GetLastError() << endl;
		}
	}
	return 0;
}
int  RegKeyValueAdd(HKEY hKey,LPCSTR  pathKeyValue) {
	//Format -> Template_1\\Template_2 #Memet@Karul
	string  _pathKeyValue;
	
	for (int i = 0; i < strlen(pathKeyValue);i++) {//pathKeyValue space clear; //boşluk olduğunda hatalı dosya işlemi yapıyor.
		if ((char)pathKeyValue[i]!= 32) {
			_pathKeyValue += pathKeyValue[i];
		}
	}
	int i=0;
	string sPath;
	string sKey;
	string sValue;
	for (; i < _pathKeyValue.length(); i++) {
		if (_pathKeyValue[i] == '#') break;
		sPath += _pathKeyValue[i];
	}
	int j = i + 1;
	for (; j < _pathKeyValue.length(); j++) {
		if (_pathKeyValue[j] == '@') break;
		sKey += _pathKeyValue[j];
	}
	int k = j+1;
	for (; k < _pathKeyValue.length(); k++) {
		sValue += _pathKeyValue[k];
	}
	cout << "path  : " << sPath << endl;
	cout << "Key   : " << sKey << endl;
	cout << "Value : " << sValue << endl;

	HKEY hkRegOpen;
	DWORD dRegReturn;
	sPath = sPath + "\0";
	LONG res1 = RegCreateKeyExA(hKey, sPath.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS , NULL, &hkRegOpen, &dRegReturn);
	cout <<"res1."<< res1 << endl;
	if (res1!= ERROR_SUCCESS) 
		return res1;
	LONG res2=RegSetValueExA(hkRegOpen, (LPCSTR)sKey.c_str(), 0, REG_SZ, (LPBYTE)sValue.c_str(), strlen((char*)sValue.c_str()) + 1);
	cout << "res2."<<res2 << endl;
	if (res2 != ERROR_SUCCESS) 
		return res2;
	RegCloseKey(hkRegOpen);
	return 0;
}

