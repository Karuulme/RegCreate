
#include <iostream>
//#include <winreg.h>
#include <windows.h>
using namespace std;
int main()
{
	//LSTATUS RegCreateKeyExA(
	//	[in]            HKEY                        hKey,       				HKEY_USERS      
	//	[in]            LPCSTR                      lpSubKey,					DnemeUygulamasÄ±      
	//	DWORD                       Reserved,									0      
	//	[in, optional]  LPSTR                       lpClass,					NULL      
	//	[in]            DWORD                       dwOptions,					REG_OPTION_BACKUP_RESTORE     
	//	[in]            REGSAM                      samDesired,					KEY_SET_VALUE      
	//	[in, optional]  const LPSECURITY_ATTRIBUTES lpSecurityAttributes,		lsRegOpen      
	//	[out]           PHKEY                       phkResult,					      
	//	[out, optional] LPDWORD                     lpdwDisposition				      
	//);
	HKEY hkRegOpen;
	DWORD dRegReturn;

	LONG res = RegCreateKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &hkRegOpen, &dRegReturn);

	if (res == REG_CREATED_NEW_KEY) {
		cout << "Başarılı" << endl;

	}
	//	CloseHandle(res);

		/*const char* keyloc = "wulf\\comms\\memetbirdeneme";

		LONG res = RegCreateKeyExA(HKEY_CURRENT_USER, keyloc, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
			NULL, &hkRegOpen, &dRegReturn);
		if (res == ERROR_SUCCESS) {
			return 0;
		}
		else {
			return -1;
		}*/
}