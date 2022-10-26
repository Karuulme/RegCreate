#include <iostream>
#include <windows.h>
using namespace std;
int main()
{
	HKEY hkRegOpen;
	DWORD dRegReturn;

	LONG res = RegCreateKeyExA(HKEY_CURRENT_USER, "deneme\\AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, & hkRegOpen, & dRegReturn);
	
	LPCSTR value = "memet";

	LPCTSTR  data = L"Teneme\0";
	RegSetValueExA(hkRegOpen,value,0, REG_SZ, (LPBYTE)(char)data, strlen((char*)data)+1);
	
	
	
	RegCloseKey(hkRegOpen);
}