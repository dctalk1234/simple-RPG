/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ Author: Nathaniel Stack
+ Filename: main.cpp
+ Date: 5/2/2019
+ Lab4
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "DynamicArray.h"
#include "Character.h"
#include <fstream>
#include "Monster.h"
#include "PrimaryEnemy.h"
#include "SecondaryEnemy.h"
#include "Boss.h"

using std::ofstream;
using std::ifstream;

int node<Potion>::count = 0;            //const members initialization
int node<Character>::count = 0;
int node<Monster*>::count = 0;
int numCharacters = 0;                //for keeping track how many characters are in file

Character* readFromFile();              //function prototypes
Character chooseCharacter();
Character createCharacter();
void menu();
void playStory(Character& userCharacter);
void exitGame(Character& userCharacter);
void playLevel(Character& userCharacter);
void endless(Character& userCharacter);
void bossRush(Character& userCharacter);
Character& level1(Character& userCharacter);
Character& level2(Character& userCharacter);
Character& level3(Character& userCharacter);
Character& level4(Character& userCharacter);
Character& level5(Character& userCharacter);
Character& level6(Character& userCharacter);
Character& level7(Character& userCharacter);
Character& level8(Character& userCharacter);
Character& level9(Character& userCharacter);
Character& level10(Character& userCharacter);
Character& store(Character& userCharacter);
void saveGame(Character& userCharacter);
Character loadGame();

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	DynamicArray<int> testInt;
	DynamicArray<char> testChar;

	DynamicArray<Potion> testPotion;
	list<Potion> potionList;
	list<char> charList;
	list<int> intList;


	/***************************************setup ***********************************/

	for (int i = 0; i < 2; i++)
	{
		Potion temp;
		temp.setCost(i);
		potionList.PushFront(temp);
	}
	BackPack backPack1(potionList);
	Character* playable = new Character[4];
	CoinPouch pouch1;
	list<Character> characterList;
	pouch1.addCoins(100);

	playable->setName("Ray:0");           // character 1 who has no money but starts with some potions
	playable->setPack(backPack1);

	(playable + 1)->setName("Sebastian:1");           // character 2 has no potions but starts with 1 gold
	(playable + 1)->setPouch(pouch1);

	(playable + 2)->setName("Jackson:2");           // character 3 who has money and potions
	(playable + 2)->setPack(backPack1);
	(playable + 2)->setPouch(pouch1);

	(playable + 3)->setName("Kiro:3");           // character 4 who has money and potions
	(playable + 3)->setPack(backPack1);
	(playable + 3)->setPouch(pouch1);

	for (int i = 0; i < 4; i++)
	{
		characterList.PushFront(*(playable + i));
	}


	ofstream fout;
	fout.open("data.txt", std::ios::out | std::ios::binary);
	if (fout.is_open())
	{
		numCharacters = 4;
		int temp = 0;
		fout.write(reinterpret_cast <char*> (&numCharacters), sizeof(int));
		for (int i = 0; i < 4; i++)
		{
			temp = (playable + i)->getName().getLength();
			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));
			fout.write(((playable + i)->getName().getString()), (playable + i)->getName().getLength());      //write the name of character to the file of each character

			temp = (playable + i)->getPouch().getCoins();

			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));    //write the pouch to the file for each character

			temp = (playable + i)->getPack().getPotionArr().getNumNodes();

			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write the number of nodes in the list


			for (int j = 0; j < (playable + i)->getPack().getPotionArr().getNumNodes(); j++)
			{
				temp = (playable + i)->getPack().getPotionArr().GetIthElement(j).getName().getLength();
				fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write size of name as an integer for reading back for each potion
				fout.write(((playable + i)->getPack().getPotionArr().GetIthElement(j).getName().getString()), (playable + i)->getPack().getPotionArr().GetIthElement(j).getName().getLength());    //write name for each potion

				temp = (playable + i)->getPack().getPotionArr().GetIthElement(j).getDescription().getLength();
				fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write size of description as an integer for reading back for each potion
				fout.write(((playable + i)->getPack().getPotionArr().GetIthElement(j).getDescription().getString()), (playable + i)->getPack().getPotionArr().GetIthElement(j).getDescription().getLength());    //write description for each potion

				temp = (playable + i)->getPack().getPotionArr().GetIthElement(j).getPotency().getLength();
				fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write size of potency as an integer for reading back for each potion
				fout.write(((playable + i)->getPack().getPotionArr().GetIthElement(j).getPotency().getString()), (playable + i)->getPack().getPotionArr().GetIthElement(j).getPotency().getLength());    //write potency for each potion

				temp = (playable + i)->getPack().getPotionArr().GetIthElement(j).getCost().getLength();
				fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write size of cost as an integer for reading back for each potion
				fout.write(((playable + i)->getPack().getPotionArr().GetIthElement(j).getCost().getString()), (playable + i)->getPack().getPotionArr().GetIthElement(j).getCost().getLength());    //write cost for each potion				
			}
		}


		fout.close();
	}

	/*******************user character selection**************/
	
	cout << "setup complete" << endl;
	Character userCharacter;

	userCharacter = chooseCharacter();
	saveGame(userCharacter);                            //start save file for player. Only one character may be saved in this game
	userCharacter.display();

	/*************************Menu selection***************/
	menu();



	delete[] playable;
	system("pause");
	return 0;
}

/*reads character objects in from setup "data.txt" file*/
Character* readFromFile()
{
	Character* tempCharacter = nullptr;
	ifstream fin;                                           //output characters to binary file
	fin.open("data.txt", std::ios::in | std::ios::binary);
	if (fin.is_open())
	{
		int numCharacters = 0;                //for keeping track how many characters are in file = 0;
		int numPotions = 0;
		int size = 0;
		int tempCoins = 0;

		cString tempCharacterName;
		CoinPouch tempCoinPouch;
		BackPack tempBackPack;
		char* buffer = nullptr;
		cString tempPotionName;
		cString tempPotionDescription;
		cString tempPotionPotency;
		cString tempPotionCost;

		fin.read(reinterpret_cast <char*> (&numCharacters), sizeof(int));
		tempCharacter = new Character[numCharacters];
		for (int i = 0; i < numCharacters; i++)
		{
			
			fin.read(reinterpret_cast <char*> (&size), sizeof(int));              //read length of name stored
			buffer = new char[size];
			fin.read(buffer, size);                     //write that name into buffer
			tempCharacterName = buffer;                                          //write name as cString object

			fin.read(reinterpret_cast <char*> (&tempCoins), sizeof(int));         //read number of coins into int
			tempCoinPouch.subtCoins(tempCoinPouch.getCoins());                   //make sure coin pouch is empty
			tempCoinPouch.addCoins(tempCoins);                                   //add those coins to empty pouch

			fin.read(reinterpret_cast <char*> (&numPotions), sizeof(int));         //find number of potions in list
			list<Potion> potionList;
			for (int j = 0; j < numPotions; j++)
			{
				fin.read(reinterpret_cast <char*> (&size), sizeof(int));               //read and store potion name
				delete[]buffer;
				buffer = new char[size];
				fin.read(buffer, size);
				tempPotionName = buffer;

				fin.read(reinterpret_cast <char*> (&size), sizeof(int));                   //read and store potion description
				delete[]buffer;
				buffer = new char[size];
				fin.read(buffer, size);
				tempPotionDescription = buffer;

				fin.read(reinterpret_cast <char*> (&size), sizeof(int));                //read and store potion Potency
				delete[]buffer;
				buffer = new char[size];
				fin.read(buffer, size);
				tempPotionPotency = buffer;

				fin.read(reinterpret_cast <char*> (&size), sizeof(int));            //read and store potion cost
				delete[]buffer;
				buffer = new char[size];
				fin.read(buffer, size);
				tempPotionCost = buffer;

				Potion tempPotionComplete;
				tempPotionComplete.setName(tempPotionName);
				tempPotionComplete.setDescription(tempPotionDescription);
				tempPotionComplete.setPotency(tempPotionPotency);
				tempPotionComplete.setCost(tempPotionCost);

				potionList.PushFront(tempPotionComplete);
				BackPack tempBackPack(potionList);
			}

			(tempCharacter + i)->setName(tempCharacterName);
			(tempCharacter + i)->setPouch(tempCoinPouch);
			(tempCharacter + i)->setPack(tempBackPack);
			delete[] buffer;
		}
		fin.close();
	}

	return tempCharacter;
}


/*this function allows the player to choose from one of the 4 premade characters or create their own*/
Character chooseCharacter()
{
	Character toReturn;
	char choice;
	cout << "would you like to load previous game y/n" << endl;
	cin >> choice;

	if (choice == 'y' || choice == 'Y')
	{
		toReturn = loadGame();
	}
	else
	{
		Character* defaultCharacters = readFromFile();        //get characters that have been created


		for (int i = 0; i < numCharacters; i++)
		{
			(defaultCharacters + i)->display();
		}

		int selection = 1000;
		cout << "select from characters above or enter 5 to add a new character" << endl;
		cin >> selection;

		if (selection == 5)                          //if user wants new character
		{
			toReturn = createCharacter();
		}
		else if (selection < numCharacters)
		{
			toReturn = *(defaultCharacters + selection);  //else 
		}
		else
		{
			throw "invalid selection";
		}
		delete[] defaultCharacters;
	}
	
	return toReturn;
}


/*this function continues to create characters until the user is satisfied and then returns that character as the one that will be played as*/
Character createCharacter()
{
	Character toReturn;
	bool done = false;
	char selection;
	while (!done)
	{
		Character newCharacter;
		cString tempName;
		BackPack tempPack;
		CoinPouch tempPouch;
		char buffer[25];

		cout << "enter character name" << endl;
		cin >> buffer;
		tempName = buffer;

		
		newCharacter.setName(tempName);
		newCharacter.setPack(tempPack);                    //default pack
		newCharacter.setPouch(tempPouch);                  //default pouch

		cout << "Character generated: " << endl;
		newCharacter.display();                                    //display generated character
		cout << "would you like to keep this character y/n press n to generate new character" << endl;
		cin >> selection;

		if (selection == 'y' || selection == 'Y')
		{
			toReturn = newCharacter;
			done = true;
		}

	}
	
	return toReturn;
}

/*After character selection player chooses which game mode they want to play. The function is a menu that correctly selects the proper function for user selected game mode */
void menu()
{
	Character userCharacter = loadGame();
	int choice = 0;
	cout << "What game mode would you like to play 1:Story 2:Boss Rush 3:Endless 4:Exit Game" << endl;
	cin >> choice;

	if (choice == 1)
	{
		playStory(userCharacter);
	}
	else if (choice == 2)
	{
		bossRush(userCharacter);
	}
	else if (choice == 3)
	{
		endless(userCharacter);
	}
	else if (choice == 4)
	{
		exitGame(userCharacter);
	}

}

/*Manager function for playing the story. handles the saving after each level and checks if player would like to quit or not in between levels*/
void playStory(Character & userCharacter)
{
	/****************play story**************/
	int Continue = 1;
	while (Continue == 1)
	{
		char selection;
		store(userCharacter);
		cout << "would you like to play the next level y/n" << endl;
		cin >> selection;
		if (selection == 'y' || selection == 'y')
		{
			saveGame(userCharacter);
			playLevel(userCharacter);
		}
		else
		{
			exitGame(userCharacter);
			Continue = 0;
		}
	}
}

/*handles the code for exiting the game allowing the user to save before closing out*/
void exitGame(Character & userCharacter)                      
{
	char selection;
	cout << "would you like to save your game y/n" << endl;
	cin >> selection;

	if (selection == 'y' || selection == 'Y')
	{
		saveGame(userCharacter);
	}
}

/*checks the characters current level and calls the corresponding function for the level*/
void playLevel(Character & userCharacter)
{
	int levelToPlay = 0;

	levelToPlay = userCharacter.getlevel();

	if (levelToPlay == 1)
	{
		level1(userCharacter);
	}
	else if (levelToPlay == 2)
	{
		level2(userCharacter);
	}
	else if (levelToPlay == 3)
	{
		level3(userCharacter);
	}
	else if (levelToPlay == 4)
	{
		level4(userCharacter);
	}
	else if (levelToPlay == 5)
	{
		level5(userCharacter);
	}
	else if (levelToPlay == 6)
	{
		level6(userCharacter);
	}
	else if (levelToPlay == 7)
	{
		level7(userCharacter);
	}
	else if (levelToPlay == 8)
	{
		level8(userCharacter);
	}
	else if (levelToPlay == 9)
	{
		level9(userCharacter);
	}
	else if (levelToPlay == 10)
	{
		level10(userCharacter);
	}
	else
	{
		cout << "Congratulations you have completed the game" << endl;          
		saveGame(userCharacter);                                            //save the character
		menu();                                                        //return to main menu
	}
}

/*this code randomly generates enemies for the player to fight until the player dies and then displays how many rounds they survived*/
void endless(Character & userCharacter)
{
	int roundsCompleted = 0;

	while (userCharacter.getHP() > 0)
	{

		list<Monster*> monstersToFight;
		char selection;

		for (int i = 0; i < rand() % 10; i++)
		{
			monstersToFight.PushBack(new PrimaryEnemy());
		}
		for (int i = 0; i < rand() % 10; i++)
		{
			monstersToFight.PushBack(new SecondaryEnemy());
		}

		/********************wave 1******************/

		while (monstersToFight.getHead() != nullptr)
		{
			if (userCharacter.getHP() > 0)
			{
				int monsterSelect = 20;
				int attackSelect = 0;
				monstersToFight.displayPtr();

				/*******************player attack phase****************************/
				cout << "enter the number of the monster you want to attack" << endl;
				cin >> monsterSelect;

				cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
				cin >> attackSelect;

				if (attackSelect == 1)
				{
					monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
				}
				else if (attackSelect == 2)
				{
					monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
				}
				else if (attackSelect == 3)
				{
					monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
				}


				for (int i = 0; i < monstersToFight.getNumNodes(); i++)
				{
					if (monstersToFight.GetIthElement(i)->getHP() == 0)
					{
						delete monstersToFight.GetIthElement(i);
						monstersToFight.deleteNode(i);
					}
				}
				/*****************************monster attack phase******************************/
				for (int i = 0; i < monstersToFight.getNumNodes(); i++)
				{
					userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
				}

				userCharacter.display();
			}
			else
			{
				cout << "character killed" << endl;
				roundsCompleted++;
				cout << "you completed " << roundsCompleted << " Rounds congratulations" << endl;
				menu();
				
			}
		}




	}
}

/*boss rush mode in which player fights all 10 bosses in order with no chance to save*/
void bossRush(Character & userCharacter)
{
	cout << "you must complete all bosses without dying in order to win." << endl;
	cout << "Nothing that happens to your character in this mode will be saved." << endl;
	list<Monster*> monstersToFight;
	char selection;

	
		monstersToFight.PushBack(new Boss(1));
	

	/********************Boss 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}


	
		monstersToFight.PushBack(new Boss(2));
	

	/********************Boss 2******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}

	
		monstersToFight.PushBack(new Boss(3));
	

	/********************Boss 3******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}

	
		monstersToFight.PushBack(new Boss(4));
	

	/********************Boss 4******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}

	
		monstersToFight.PushBack(new Boss(5));
	

	/********************Boss 5******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}

	
		monstersToFight.PushBack(new Boss(6));
	

	/********************Boss 6******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}

	
		monstersToFight.PushBack(new Boss(7));
	

	/********************Boss 7******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}

	
		monstersToFight.PushBack(new Boss(8));
	

	/********************Boss 8******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}

	
		monstersToFight.PushBack(new Boss(9));
	

	/********************Boss 9******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}

	
		monstersToFight.PushBack(new Boss(10));
	

	/********************Boss 10******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}

	cout << "congratulations you completed the boss run" << endl;
}


Character & level1(Character & userCharacter)
{
	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}
	
	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}		
	}
	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	
	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
		
	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(1));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
		
	}

	cout << "end of level 1" << endl;
	userCharacter.nextLevel();
	userCharacter.getPouch().addCoins(200);
	userCharacter.getPack().getPotionArr().PushFront(Potion());
	return userCharacter;
}

Character & level2(Character & userCharacter)
{

	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}
	for (int i = 0; i < 2; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}

	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 2; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(2));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	cout << "end of level 2" << endl;
	userCharacter.nextLevel();
	userCharacter.getPouch().addCoins(200);
	userCharacter.getPack().getPotionArr().PushFront(Potion());
	return userCharacter;
}

Character & level3(Character & userCharacter)
{
	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}
	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}

	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}
	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(3));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	cout << "end of level 3" << endl;
	userCharacter.nextLevel();
	userCharacter.getPack().getPotionArr().PushFront(Potion());      //rewards for completing level
	userCharacter.getPack().getPotionArr().PushFront(Potion());
	return userCharacter;
}

Character & level4(Character & userCharacter)
{
	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 6; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}
	for (int i = 0; i < 6; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 4; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(4));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	cout << "end of level 4" << endl;
	userCharacter.nextLevel();
	userCharacter.getPouch().addCoins(500);            //rewards for completing level
	return userCharacter;
}

Character & level5(Character & userCharacter)
{
	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 6; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 6; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}
	for (int i = 0; i < 6; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 6; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(5));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	cout << "end of level 5" << endl;
	userCharacter.nextLevel();
	userCharacter.getPouch().addCoins(600); //rewards for completing level
	return userCharacter;
}

Character & level6(Character & userCharacter)
{
	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 6; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 8; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 6; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(6));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	cout << "end of level 6" << endl;
	userCharacter.nextLevel();
	userCharacter.getPouch().addCoins(200);              //rewards for completing level
	userCharacter.getPack().getPotionArr().PushFront(Potion()); 
	userCharacter.getPack().getPotionArr().PushFront(Potion());
	return userCharacter;
}

Character & level7(Character & userCharacter)
{
	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 8; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 8; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 8; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(7));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	cout << "end of level 7" << endl;
	userCharacter.nextLevel();
	userCharacter.getPouch().addCoins(200);
	userCharacter.getPack().getPotionArr().PushFront(Potion());
	return userCharacter;
}

Character & level8(Character & userCharacter)
{
	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 8; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 10; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 8; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(8));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	cout << "end of level 8" << endl;
	userCharacter.nextLevel();
	userCharacter.getPouch().addCoins(500);
	return userCharacter;
}

Character & level9(Character & userCharacter)
{
	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 10; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 10; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 10; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}
	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(9));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	cout << "end of level 9" << endl;
	userCharacter.nextLevel();
	userCharacter.getPouch().addCoins(200);               //rewards for finishing level
	userCharacter.getPack().getPotionArr().PushFront(Potion());   
	userCharacter.getPack().getPotionArr().PushFront(Potion());
	return userCharacter;
}

Character & level10(Character & userCharacter)
{
	list<Monster*> monstersToFight;
	char selection;

	for (int i = 0; i < 12; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 12; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}

	/********************wave 1******************/

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}
	}
	for (int i = 0; i < 12; i++)
	{
		monstersToFight.PushBack(new SecondaryEnemy());
	}
	for (int i = 0; i < 12; i++)
	{
		monstersToFight.PushBack(new PrimaryEnemy());
	}
	/**************************wave 2********************/
	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	/*************************boss fight*********************/
	monstersToFight.PushBack(new Boss(10));

	while (monstersToFight.getHead() != nullptr)
	{
		if (userCharacter.getHP() > 0)
		{
			int monsterSelect = 20;
			int attackSelect = 0;
			monstersToFight.displayPtr();

			/*******************player attack phase****************************/
			cout << "enter the number of the monster you want to attack" << endl;
			cin >> monsterSelect;

			cout << "which attack would you like to perform 1:NormalStrike 2:Block 3:Berserk" << endl;
			cin >> attackSelect;

			if (attackSelect == 1)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.normalStrike());
			}
			else if (attackSelect == 2)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.block());
			}
			else if (attackSelect == 3)
			{
				monstersToFight.GetIthElement(monsterSelect)->takeDamage(userCharacter.berserk());
			}


			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				if (monstersToFight.GetIthElement(i)->getHP() == 0)
				{
					delete monstersToFight.GetIthElement(i);
					monstersToFight.deleteNode(i);
				}
			}
			/*****************************monster attack phase******************************/
			for (int i = 0; i < monstersToFight.getNumNodes(); i++)
			{
				userCharacter.takeDamage(monstersToFight.GetIthElement(i)->attack());
			}

			userCharacter.display();
		}
		else
		{
			cout << "character killed" << endl;
			cout << "do you want to return to menu and try again y/n" << endl;
			cin >> selection;

			if (selection == 'y' || selection == 'Y')
			{
				menu();
			}
		}

	}

	cout << "end of level 10" << endl;
	userCharacter.nextLevel();  
	userCharacter.getPouch().addCoins(10000);                   //huge rewards from finishing game so character can be better used in other game modes
	for (int i = 0; i < 10; i++)
	{
		userCharacter.getPack().getPotionArr().PushFront(Potion());
	}

	return userCharacter;
}

/*This is the store function which allows the character to purchase upgrades to stats as well as health potions*/
Character& store(Character& userCharacter)
{
	int notDone = 1;
	while (notDone > 0)                         //the store prompts will loop until the user says no to every choice or cannot make anymore actions
	{
		notDone = 0;
		char selection;
		int temp;
		cout << "current potion list" << endl;                    

		userCharacter.getPack().display();                  //display potions already in pack

		cout << "would you like to use a potion to replenish or increase hp y/n" << endl;
		cin >> selection;
		if (selection == 'y' || selection == 'y')
		{
			notDone++;
			if (userCharacter.getPack().getPotionArr().getNumNodes() != 0)            //if there is a potion use it
			{
				temp = userCharacter.getPack().getPotionArr().GetIthElement(0).usePotion();
				userCharacter.increaseHP(temp);
				userCharacter.getPack().getPotionArr().PopFront();
			}
			else                                                                 //if not tell user
			{
				notDone--;
				cout << "you do not have any potions" << endl;
			}
		}

		cout << "would you like to spend 100 coins to increase amor by 200 y/n" << endl;
		cin >> selection;
		if (selection == 'y' || selection == 'y')
		{
			notDone++;
			if (userCharacter.getPouch().getCoins() >= 100)
			{
				userCharacter.getPouch().subtCoins(100);                      //subt cost
				userCharacter.increaseArmor(200);									//increase armor
			}
			else
			{
				notDone--;
				cout << "not enough coins" << endl;
			}
		}

		cout << "would you like to spend 100 coins to increase attack by 200 y/n" << endl;
		cin >> selection;
		if (selection == 'y' || selection == 'y')
		{
			notDone++;
			if (userCharacter.getPouch().getCoins() >= 100)
			{
				userCharacter.getPouch().subtCoins(100);                 //subt cost
				userCharacter.increaseAttack(200);              //increase attack
			}
			else
			{
				cout << "not enough coins" << endl;
			}
		}

		cout << "would you like to spend 200 coins to purchase a health potion y/n" << endl;
		cin >> selection;
		if (selection == 'y' || selection == 'y')
		{
			notDone++;
			if (userCharacter.getPouch().getCoins() >= 200)
			{
				userCharacter.getPouch().subtCoins(200);                       //subt cost from pouch
				userCharacter.getPack().getPotionArr().PushFront(Potion());  //add potion to backpack
			}
			else                                                             //if can't afford don't do anything
			{
				notDone--;
				cout << "not enough coins" << endl;
			}
		}
	}

	return userCharacter;
}

/*code to save a character to the "saveGame.txt" file */
void saveGame(Character & userCharacter)
{
	ofstream fout;
	fout.open("saveGame.txt", std::ios::out | std::ios::binary);
	if (fout.is_open())
	{
		numCharacters = 1;
		int temp = 0;
		fout.write(reinterpret_cast <char*> (&numCharacters), sizeof(int));
		
			temp = (userCharacter).getName().getLength();
			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));
			fout.write(((userCharacter).getName().getString()), (userCharacter).getName().getLength());      //write the name of character to the file

			temp = userCharacter.getArmor();                                            //write character armor characteristic
			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));

			temp = userCharacter.getHP();                                            //write character HP characteristic
			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));

			temp = userCharacter.getAttack();                                            //write character attack characteristic
			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));

			temp = userCharacter.getlevel();                                          //write character level characteristic
			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));

			temp = userCharacter.getRange();                                          //write character range characteristic
			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));

			temp = (userCharacter).getPouch().getCoins();
			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));    //write the pouch to the file for each character

			temp = (userCharacter).getPack().getPotionArr().getNumNodes();

			fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write the number of nodes in the list


			for (int j = 0; j < (userCharacter).getPack().getPotionArr().getNumNodes(); j++)
			{
				temp = (userCharacter).getPack().getPotionArr().GetIthElement(j).getName().getLength();
				fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write size of name as an integer for reading back for each potion
				fout.write(((userCharacter).getPack().getPotionArr().GetIthElement(j).getName().getString()), (userCharacter).getPack().getPotionArr().GetIthElement(j).getName().getLength());   
				//write name for each potion

				temp = (userCharacter).getPack().getPotionArr().GetIthElement(j).getDescription().getLength();
				fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write size of description as an integer for reading back for each potion
				fout.write(((userCharacter).getPack().getPotionArr().GetIthElement(j).getDescription().getString()), (userCharacter).getPack().getPotionArr().GetIthElement(j).getDescription().getLength());    
				//write description for each potion

				temp = (userCharacter).getPack().getPotionArr().GetIthElement(j).getPotency().getLength();
				fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write size of potency as an integer for reading back for each potion
				fout.write(((userCharacter).getPack().getPotionArr().GetIthElement(j).getPotency().getString()), (userCharacter).getPack().getPotionArr().GetIthElement(j).getPotency().getLength()); 
				//write potency for each potion

				temp = (userCharacter).getPack().getPotionArr().GetIthElement(j).getCost().getLength();
				fout.write(reinterpret_cast <char*> (&temp), sizeof(int));     //write size of cost as an integer for reading back for each potion
				fout.write(((userCharacter).getPack().getPotionArr().GetIthElement(j).getCost().getString()), (userCharacter).getPack().getPotionArr().GetIthElement(j).getCost().getLength());    //write cost for each potion				
			}
		fout.close();
	}
}

/*load previos save*/
Character loadGame()
{
	Character tempCharacter;
	ifstream fin;                                           //output characters to binary file
	fin.open("saveGame.txt", std::ios::in | std::ios::binary);
	if (fin.is_open())
	{
		int numCharacters = 0;                //for keeping track how many characters are in file = 0;
		int numPotions = 0;
		int size = 0;
		int tempCoins = 0;
		int tempArmor = 0;
		int tempHP = 0;
		int tempRange = 0;
		int tempAttack = 0;
		int tempLevel = 0;

		cString tempCharacterName;
		CoinPouch tempCoinPouch;
		BackPack tempBackPack;
		char* buffer = nullptr;
		cString tempPotionName;
		cString tempPotionDescription;
		cString tempPotionPotency;
		cString tempPotionCost;

		fin.read(reinterpret_cast <char*> (&numCharacters), sizeof(int));
		for (int i = 0; i < numCharacters; i++)
		{
			fin.read(reinterpret_cast <char*> (&size), sizeof(int));              //read length of name stored
			buffer = new char[size];
			fin.read(buffer, size);                     //write that name into buffer
			tempCharacterName = buffer;                                          //write name as cString object


			//read character armor characteristic
			fin.read(reinterpret_cast <char*> (&tempArmor), sizeof(int));           //read each attribute

			//read character HP characteristic
			fin.read(reinterpret_cast <char*> (&tempHP), sizeof(int));

			//read character attack characteristic
			fin.read(reinterpret_cast <char*> (&tempAttack), sizeof(int));

			//read character level characteristic
			fin.read(reinterpret_cast <char*> (&tempLevel), sizeof(int));

			//read character range characteristic
			fin.read(reinterpret_cast <char*> (&tempRange), sizeof(int));

			fin.read(reinterpret_cast <char*> (&tempCoins), sizeof(int));         //read number of coins into int
			tempCoinPouch.subtCoins(tempCoinPouch.getCoins());                   //make sure coin pouch is empty
			tempCoinPouch.addCoins(tempCoins);                                   //add those coins to empty pouch



			fin.read(reinterpret_cast <char*> (&numPotions), sizeof(int));         //find number of potions in list
			list<Potion> potionList;
			for (int j = 0; j < numPotions; j++)
			{
				fin.read(reinterpret_cast <char*> (&size), sizeof(int));               //read and store potion name
				delete[] buffer;
				buffer = new char[size];
				fin.read(buffer, size);
				tempPotionName = buffer;

				fin.read(reinterpret_cast <char*> (&size), sizeof(int));                   //read and store potion description
				delete[] buffer;
				buffer = new char[size];
				fin.read(buffer, size);
				tempPotionDescription = buffer;

				fin.read(reinterpret_cast <char*> (&size), sizeof(int));                //read and store potion Potency
				delete[] buffer;
				buffer = new char[size];
				fin.read(buffer, size);
				tempPotionPotency = buffer;

				fin.read(reinterpret_cast <char*> (&size), sizeof(int));            //read and store potion cost
				delete[] buffer;
				buffer = new char[size];
				fin.read(buffer, size);
				tempPotionCost = buffer;

				Potion tempPotionComplete;
				tempPotionComplete.setName(tempPotionName);
				tempPotionComplete.setDescription(tempPotionDescription);
				tempPotionComplete.setPotency(tempPotionPotency);
				tempPotionComplete.setCost(tempPotionCost);

				potionList.PushFront(tempPotionComplete);
				BackPack tempBackPack(potionList);
			}

			tempCharacter.setName(tempCharacterName);               //assemble character from tempary attributes
			tempCharacter.setPouch(tempCoinPouch);
			tempCharacter.setPack(tempBackPack);
			tempCharacter.setArmor(tempArmor);
			tempCharacter.setHP(tempHP);
			tempCharacter.setAttack(tempAttack);
			tempCharacter.setLevel(tempLevel);
			tempCharacter.setRange(tempRange);

			delete[] buffer;
		}
		fin.close();
	}

	return tempCharacter;
}
