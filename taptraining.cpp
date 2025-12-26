#include <iostream>
#include <cstring>
#include <chrono>

#ifdef _WIN32 // windows header
#include <conio.h>
#else // unix header
#include <termios.h>
#include <unistd.h>
#endif

char setKeys(int key) // set user keybinds
{
	char keybindInput{'\n'};
	std::cout << "\nKeybind for key " << key << " (leave blank for osu! default): ";
	std::cin.get(keybindInput);
	if(keybindInput=='\n') // empty input handling
	{
		switch(key)
		{
		case 1:
			return 'z';
		case 2:
			return 'x';
		}
	}
	else
	{
		std::cin.ignore();
		return keybindInput;
	}

}

bool retryOrNot() // pretty self explaining name lmao six-seven
{
	std::cin.sync();
	char userInput;
	do
	{
		std::cout << "\nRetry?(Y/n)";
		std::cin.get(userInput);
		std::cin.ignore();
		if(userInput=='\n'||userInput=='y'||userInput=='Y') //empty input handled as yes
		{
			return true;
		}
		else if(userInput=='n'||userInput=='N')
		{
			return false;
		}
		else
		{
			std::cout << "Invalid Input";
		}
	} while(true);
}

void tappingBenchmark(char k1, char k2) // <-- where the actual tapping happens
{
	int keyPresses{};
	do
	{
		std::cout << "\nHow many key presses? (for health reasons, it is not recommended to go above 500 presses, but the option is there!): ";
		std::cin >> keyPresses;
		std::cin.ignore();
		if(keyPresses<2)
		{
			std::cout << "\nMust have at least 2 key presses to evaluate speed!";
		}
	} while(keyPresses<2);

	std::cout << "\nPress any key to start.";
	#ifdef _WIN32 //for windows only
	while(!_kbhit())
	{
		//hold until user hits keyboard
	}
	#else
		struct termios oldTerminal, newTerminal; //terminal settings
		tcgetattr(STDIN_FILENO, &oldTerminal);
		newTerminal = oldTerminal;
		newTerminal.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newTerminal);
		char holdProgram = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminal);
	#endif
	auto initialTime = std::chrono::system_clock::now(); //get time at start of tapping

	#ifdef _WIN32
	for(int i=1;i<keyPresses;i++) //for windows only
	{
		char userPress;
		userPress = _getch();
		if(userPress!=k1&&userPress!=k2)
		{
			i--;
			continue;
		}
	}
	#else
	tcgetattr(STDIN_FILENO, &oldTerminal);
	for(int i=1;i!=keyPresses;i++) //for unix only
	{
		newTerminal = oldTerminal;
		newTerminal.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newTerminal);
		char userPress;
		userPress = getchar();
		if(userPress!=k1&&userPress!=k2)
		{
			i--; // negates the increment,so invalid key presses dont get registered 
			continue;
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminal);
	#endif
	auto tappingTimeChrono = std::chrono::system_clock::now() - initialTime;
    long int tappingTime = static_cast<long int>(std::chrono::duration_cast<std::chrono::milliseconds>(tappingTimeChrono).count());
    double bpmCalculated = 60000.0/(tappingTime/keyPresses);
    std::cout << "\nSTREAMING BPM(1/4): " << bpmCalculated/4.0 << "\nSINGLETAPPING BPM(1/2): " << bpmCalculated/2.0;
}

void tapTraining()
{
	bool tryAgain{false};
	do
	{
		char keyOne{setKeys(1)};
		char keyTwo{setKeys(2)};
		std::cout << keyOne << keyTwo; //debug
		tappingBenchmark(keyOne, keyTwo);
		tryAgain = retryOrNot();
	} while(tryAgain==true);
}