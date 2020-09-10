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
void caps_press();
void copy_press();

int main()
{
	string s, s2;
	cout << "Welcome to Caleb Anderson's CAPS_LOCK function!\n" << endl;
	cout << "\nThe amount of uppercase and lowercase letters determines which case the selection will be.\n" << endl;
	cout << "If the selection is entirely uppercase or entirely lowercase, it will switch the case of that selection entirely.\n" << endl;
	cout << "\nJust press CAPS_LOCK on any selection of text in any text editor to begin, and press SCROLL_LOCK + CAPS_LOCK to end the program . . ." << endl;
	while (GetKeyState(VK_SCROLL) == 0)
	{
		keybd_event(VK_CAPITAL, 0x3a, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		copy_press();
		s = get_string(s);
		send_string(caps(s, s2).c_str());
		caps_press();
	}
	return 0;
}

string get_string(string s) // too little knowledge, all i know is that it sends the most recent entry on the clipboard to a string
{
	if (OpenClipboard(NULL))
	{
		HANDLE clip;
		clip = GetClipboardData(CF_TEXT);
		s = (LPSTR)GlobalLock(clip);
		GlobalUnlock(clip);
		CloseClipboard();
	}
	return s;
}

void send_string(string s) // i can't tell what this does line by line, but it sends the modified string to the clipboard
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


void caps_press()
{
	while (GetKeyState(VK_CAPITAL) == 0) // while caps_lock isn't activated, loop
	{
		continue;
	}
	if (GetKeyState(VK_CAPITAL)) // when caps_lock is activated, paste the text on the clipboard to wherever the current text editor is
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

		// release v
		ip.ki.wVk = 'V';
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		// release ctrl
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
	}	
	keybd_event(VK_CAPITAL, 0x3a, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_CAPITAL, 0x3a, KEYEVENTF_EXTENDEDKEY, 0);		// these two lines turn off caps lock after the function is used to avoid frusturation
}

void copy_press()
{
	while (GetKeyState(VK_CAPITAL) == 0) // while caps_lock isn't activated, loop
	{
		continue;
	}
	if (GetKeyState(VK_CAPITAL)) // when caps_lock is activated, do ctrl+c
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
		ip.ki.wVk = 'C';
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// release v
		ip.ki.wVk = 'C';
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		// release ctrl
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));
	}
	Sleep(100);
	
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

