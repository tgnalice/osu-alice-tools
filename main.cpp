#include<iostream>
#include<cstring>
#include"taptraining.cpp"

void welcomeSequence() // text displayed after opening.
{
	const std::string version{"0.1.0-alpha.1"};
	std::cout << "----------Alice's osu! tool suite----------\n";
	std::cout << "Creator: tgnalice\n";
	std::cout << "osu! user ID: 15180662\n";
	std::cout << "Version: " << version << "\n";
}

int main()
{
	bool sixSeven{true}; //i had no clue what to name this, so i just called it this, when its false the loop will exit
	welcomeSequence();
	do
	{
		int userMenuSelection{};
		std::cout << "   - Select tool -\n";
		std::cout << "0 - Exit\n";
		std::cout << "1 - Tapping Trainer\n";
		std::cin >> userMenuSelection;
		if(userMenuSelection==0)
		{
			sixSeven = false;
			break;
		}
		else if(userMenuSelection==1)
		{
			std::cin.ignore();
			tapTraining();
		}
		else
		{
			std::cout << "Invalid option selected\n";
		}
	} while(sixSeven==true);

	return 0;

}