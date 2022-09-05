#include <iostream>
#include <string>
#include <Richedit.h>
#include <Winuser.h>
#include <windows.h>
#include <cstring>
#include <cstdlib>
using namespace std;

string caps(string s, string s2);
string get_string(string s);
void send_string(string s);
void caps_press(string s);
void copy_press();
void emptyclipboard();

int main()
{
	string s, s2;
	cout << "Caleb Anderson's CAPS_LOCK function...\n" << endl;
	cout << "\nThe amount of uppercase and lowercase letters determines which case the selection will be.\n" << endl;
	cout << "If the selection is entirely uppercase or entirely lowercase, it will switch the case of that selection entirely.\n" << endl;
	cout << "\nPress CTRL+CAPS_LOCK on any selection of text in any text editor to begin..." << endl;
	while (true)
	{
		if ((GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_CAPITAL)) != 0)
		{
			copy_press();
			s = get_string(s);
			send_string(caps(s, s2).c_str());
			caps_press(s);
			emptyclipboard();
			if (s != "")
			{
				keybd_event(VK_CAPITAL, 0x3a, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				keybd_event(VK_CAPITAL, 0x3a, KEYEVENTF_EXTENDEDKEY, 0);
				// these two lines turn off caps lock after the function is used to avoid frusturation
			}
			s = "";
		}
		GetAsyncKeyState(VK_CAPITAL);
		GetAsyncKeyState(VK_CONTROL);
	}
	return 0;
}

string get_string(string s) // sends the most recent entry on the clipboard to a string
{
	if (IsClipboardFormatAvailable(CF_TEXT))
	{
		if (OpenClipboard(NULL))
		{
			HANDLE clip;
			clip = GetClipboardData(CF_TEXT);
			s = (LPSTR)GlobalLock(clip);
			GlobalUnlock(clip);
			CloseClipboard();
		}
		else
			return s = "";
	}
	return s;
}

void send_string(string s) // sends the modified string to the clipboard
{
	const char* output = s.c_str();
	const size_t len = strlen(output) + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}


void emptyclipboard() // empties the clipboard
{
	if (OpenClipboard(NULL))
	{
		EmptyClipboard();
		CloseClipboard();
	}
}

void caps_press(string s)
{
		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;

		// press ctrl key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// Press v key
		ip.ki.wVk = 'V';
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(10);

		// release v
		ip.ki.wVk = 'V';
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		// release ctrl
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		

}

void copy_press()
{
	
		INPUT ip;
		ip.type = INPUT_KEYBOARD;
		ip.ki.wScan = 0;
		ip.ki.time = 0;
		ip.ki.dwExtraInfo = 0;

		// press ctrl key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// Press c key
		ip.ki.wVk = 'C';
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));
		
		Sleep(10);

		// release c
		ip.ki.wVk = 'C';
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		// release ctrl
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
}


string caps(string s, string s2)
{
	int upper = 0;
	int lower = 0;
	int len = s.length();
	for (int p = 0; p < len; p++)
	{
		if (isupper(s[p]))
			upper++;
		if (islower(s[p]))
			lower++;
	}

	if ((upper > lower || upper == lower) && lower != 0)
	{
		for (int i = 0; i < len; i++)
		{
			if ((s[i] > 123 || s[i] < 65) || (s[i] > 90 && s[i] < 97))
			{
				s2.push_back(s[i]);
				continue;
			}
			if (islower(s[i]))
			{
				char c = toupper(s[i]);
				s2.push_back(c);
				continue;
			}
			if (isupper(s[i]))
				s2.push_back(s[i]);
		}
	}

	if (upper == 0)
	{
		for (int i = 0; i < len; i++)
		{
			if ((s[i] > 123 || s[i] < 65) || (s[i] > 90 && s[i] < 97))
			{
				s2.push_back(s[i]);
				continue;
			}
			if (islower(s[i]))
			{
				char c = toupper(s[i]);
				s2.push_back(c);
				continue;
			}
			if (isupper(s[i]))
				s2.push_back(s[i]);
		}
	}

	if (lower == 0)
	{
		for (int i = 0; i < len; i++)
		{
			if ((s[i] > 123 || s[i] < 65) || (s[i] > 90 && s[i] < 97))
			{
				s2.push_back(s[i]);
				continue;
			}
			if (isupper(s[i]))
			{
				char c = tolower(s[i]);
				s2.push_back(c);
				continue;
			}
			if (islower(s[i]))
				s2.push_back(s[i]);
		}
	}

	if ((lower > upper) && upper != 0)
	{
		for (int i = 0; i < len; i++)
		{
			if ((s[i] > 123 || s[i] < 65) || (s[i] > 90 && s[i] < 97))
			{
				s2.push_back(s[i]);
				continue;
			}
			if (isupper(s[i]))
			{
				char c = tolower(s[i]);
				s2.push_back(c);
				continue;
			}
			if (islower(s[i]))
				s2.push_back(s[i]);
		}
	}
	return s2;
}
