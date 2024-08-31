#include "FileAllocManager.hpp"

typedef char String[32];
#define NUM 32

bool isNumber(const std::string& str);

int main(int argc, char * argv[])
{
	//If argc is 3 then there are 3 inputs into the command prompt
	if (argc == 3)
	{
		//sets strings to prompt inputs
		std::string Manual = argv[1];
		std::string Filename = argv[2];

		//check to see if -f for file run
		if (Manual == "-f")
		{
			//checks length of filename
			int length = Filename.length();
			int i = 0;

			FileAllocManager m;

			if (!Filename.empty())
			{
				//check to make sure last 4 characters are .txt
				std::string fileTest = Filename.substr((length - 4), length);
				if (fileTest == ".txt")
				{
					//opens filename
					std::ifstream testFile(Filename);
					if (!testFile)
					{
						std::cout << "Command file cannot be read" << std::endl;
						return -1;
					}
					//takes each line from text file
					std::string command;

					while (std::getline(testFile, command))
					{
						if (!command.empty())
						{
							//shows arrows and command input
							std::cout << ">>> ";
							std::cout << command << std::endl;

							//Iniliazes values
							char c;
							int space = 0;
							std::string Function;
							std::string name;
							std::string Size;

							//loops through command input and assigns strings
							for (int i = 0; i < command.size(); i++)
							{
								c = command[i];

								if (c == ' ')
								{
									space++;
								}
								else
								{
									if (space == 0)
									{
										Function += c;
									}
									else if (space == 1)
									{
										name += c;
									}
									else
									{
										Size += c;
									}
								}
							}

							//Check to make sure input is real number
							bool check = isNumber(Size);

							if (check)
							{
								//checks function array for add
								if (Function == "add")
								{
									m.addFile(name, stoi(Size));
								}
								//checks function array for delete
								else if (Function == "del")
								{
									bool t = m.deleteFile(name);
									if (t)
									{
										std::cout << name << " is deleted successfully!" << std::endl;
									}
								}
								//checks function array for kist
								else if (Function == "list")
								{
									m.listFiles();
								}
								//checks function array for seek
								else if (Function == "seek")
								{
									m.seekFile(name, stoi(Size));
								}
								//checks function array for disk
								else if (Function == "disk")
								{
									m.printDisk();
								}
								//checks function array for exit
								else if (Function == "exit")
								{
									std::cout << "Closing Program" << std::endl;
									i = 1;
								}
								//if any incorrect command or parameter is found a message is sent
								else
								{
									std::cout << "Invalid command or parameter" << std::endl;
								}
								std::cout << std::endl;
							}
							else
							{
								std::cout << "Invalid command or parameter" << std::endl;
								std::cout << std::endl;
							}
						}
					}
				}
				//if file name isnt valid
				else
				{
					std::cout << "Command file cannot be read" << std::endl;
					return -1;
				}
			}
			//if file name isnt valid
			else
			{
				std::cout << "Command file cannot be read" << std::endl;
				return -1;
			}
		}
		//if -f isnt found
		else
		{
			std::cout << "Invalid command or parameter" << std::endl;
			return -1;
		}
	}

	else if (argc == 2)
	{
		std::string Manual = argv[1];
		if (Manual == "-f")
		{
			std::cout << "Command file cannot be read" << std::endl;
			return -1;
		}
		else
		{
			std::cout << "Invalid command or parameter" << std::endl;
			return -1;
		}
	}
	//if argc is 1 then program is launched in interactive mode
	else if (argc == 1)
	{
		FileAllocManager m;

		//program runs while i doesnt equal 1
		while (true)
		{
			std::string command;

			//couts arrows and command line
			std::cout << ">>> ";
			std::getline(std::cin, command);

			if (!command.empty())
			{
				//Iniliazes values
				char c;
				int space = 0;
				std::string Function;
				std::string name;
				std::string Size;

				//loops through command input and assigns strings
				for (int i = 0; i < command.size(); i++)
				{
					c = command[i];

					if (c == ' ')
					{
						space++;
					}
					else
					{
						if (space == 0)
						{
							Function += c;
						}
						else if (space == 1)
						{
							name += c;
						}
						else
						{
							Size += c;
						}
					}
				}
				//Check to make sure input is real number
				bool check = isNumber(Size);

				if (check)
				{
					//checks function array for add
					if (Function == "add")
					{
						m.addFile(name, stoi(Size));
					}
					//checks function array for delete
					else if (Function == "del")
					{
						bool t = m.deleteFile(name);
						if (t)
						{
							std::cout << name << " is deleted successfully!" << std::endl;
						}
					}
					//checks function array for kist
					else if (Function == "list")
					{
						m.listFiles();
					}
					//checks function array for seek
					else if (Function == "seek" && space == 2)
					{
						m.seekFile(name, stoi(Size));
					}
					//checks function array for disk
					else if (Function == "disk")
					{
						m.printDisk();
					}
					//checks function array for exit
					else if (Function == "exit")
					{
						std::cout << "Have a nice day" << std::endl;
						return 0;
					}
					//if any incorrect command or parameter is found a message is sent
					else
					{
						std::cout << "Invalid command or parameter" << std::endl;
					}
					std::cout << std::endl;
				}
				else
				{
					std::cout << "Invalid command or parameter" << std::endl;
					std::cout << std::endl;
				}
			}
			else
			{
				std::cout << "Invalid command or parameter" << std::endl;
				std::cout << std::endl;
			}
		}
	}
	return -1;
}

bool isNumber(const std::string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}
