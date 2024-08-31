#include "FileAllocManager.hpp"

//Default constructor
FileAllocManager::FileAllocManager()
{
	//Initalizes variables to 0
	srand(time(NULL));
	occupiedBlocks = 0;

	//changes disk locations to nonoccupied
	for (int i = 0; i < MAX_BLOCKS; i++)
	{
		disk[i].occupied = false;
	}
}

//Destructor
FileAllocManager::~FileAllocManager()
{
	clear();
}

//Clears the directory linked list
void FileAllocManager::clear()
{
	while (directory.getLength() != 0)
	{
		for (int i = 1; i <= directory.getLength(); i++)
		{
			File test = directory.getEntry(i);
			std::string hello = test.name;
			deleteFile(hello);
		}
	}
	directory.clear();
}

//Add a new file to the directory and allocate the required number of blocks to the file if the disk has enough unoccupied blocks.
std::vector<unsigned int> FileAllocManager::addFile(std::string filename, int filesize)
{
	//Creates and assigns input variables to the File struct
	File newFile;
	newFile.name = filename;
	newFile.size = filesize;

	//Goes through directory linkedlist to see if file exists
	for (int i = 1; i <= directory.getLength(); i++)
	{
		File test = directory.getEntry(i);
		std::string NameCheck = test.name;
		//If the file is found then a empty vector is returned
		if (NameCheck == filename)
		{
			std::cout << "File already exists" << std::endl;
			std::vector<unsigned int> empty;
			return empty;
		}
	}

	//Check to make sure filesize is valid
	if (filesize < 0)
	{
		std::cout << "file size not valid" << std::endl;
		std::vector<unsigned int> empty;
		return empty;
	}

	//Check whether there is enough space for the new file
	int storageCheck;

	if (filesize % 2 == 0)
	{
		storageCheck = filesize / BLOCK_SIZE_KiB;
	}
	else
	{
		storageCheck = (filesize / BLOCK_SIZE_KiB) + 1;
	}

	//Creates vector to return
	std::vector<unsigned int> check;

	//New file requires index blocks
	if (storageCheck + 1 > MAX_BLOCKS - occupiedBlocks)
	{
		//Returns empty vector and message that there is not enough space
		std::cout << "Invalid command or parameter" << std::endl;
		std::vector<unsigned int> empty;
		return empty;
	}

	//Allocate the index block using a random position
	int indexBlock = findFirstAvailBlock(rand() % MAX_BLOCKS);
	std::cout << "Index block at position " << indexBlock << std::endl;
	check.push_back(indexBlock);

	//If findFirstAvailBlock returns -1 then there is no availble disk space
	if (indexBlock == -1)
	{
		//Returns empty vector and message that there is not enough space
		std::cout << "Not enough unoccupied blocks" << std::endl;
		std::vector<unsigned int> empty = {};
		return empty;
	}

	//Assigns struct variables
	newFile.indexBlock = &disk[indexBlock];
	newFile.indexBlock->occupied = true;
	occupiedBlocks++;

	//Gives heap memory to the index block arr variable
	newFile.indexBlock->arr = (int*)calloc(sizeof(int), MAX_BLOCKS);
	newFile.indexBlock->arrSize = 0;

	//Assigns disk memory
	int i = 0;
	while (i < storageCheck)
	{
		int block = findFirstAvailBlock(rand() % MAX_BLOCKS);
		//If findFirstAvailBlock returns -1 then there is no availble disk space
		if (block == -1)
		{
			//Returns empty vector and message that there is not enough space
			std::cout << "Not enough unoccupied blocks" << std::endl;
			std::vector<unsigned int> empty = {};
			return empty;
		}
		//couts the block location and value
		std::cout << "Block " << i << " is at position " << block <<"." << std::endl;

		//Assigns value to block
		disk[block].occupied = true;
		occupiedBlocks++;
		newFile.indexBlock->arr[newFile.indexBlock->arrSize++] = block;

		check.push_back(block);
		i++;
	}

	//Adds newfile to the directory linked list
	directory.insert(directory.getLength() + 1, newFile);
	return check;
}

//Delete a file from the directory and deallocate all the blocks belong to this file
bool FileAllocManager::deleteFile(std::string filename)
{
	int position = -1;

	//Goes through directory linkedlist to see if file exists
	for (int i = 1; i <= directory.getLength(); i++)
	{
		File test = directory.getEntry(i);
		std::string NameCheck = test.name;
		//If the file is found its position is assigned
		if (NameCheck == filename)
		{
			position = i;
			break;
		}
	}
	//If the file is found
	if (position != -1)
	{
		File test = directory.getEntry(position);
		File* file = &test;
		
		//Marks blocks as unoccupied
		for (int i = 0; i < file->indexBlock->arrSize; i++)
		{
			disk[file->indexBlock->arr[i]].occupied = false;
			occupiedBlocks--;
		}

		//Marks index blocks as unoccupied
		file->indexBlock->occupied = false;
		occupiedBlocks--;
		// free index block's arr location
		free(file->indexBlock->arr);
		//Position set to null
		file->indexBlock->arr = NULL;
		file->indexBlock->arrSize = 0;

		//Removes file from linked list
		directory.remove(position);
		return true;
	}
	//Returns false if file wasnt found
	std::cout << "Invalid command or parameter" << std::endl;
	return false;
}

//Read file name and the index to storage block to seek and print out which block number that corresponds to on the disk
int FileAllocManager::seekFile(std::string filename, int blocknumber) const
{
	int position = -1;

	if (blocknumber >= 0 && blocknumber <= MAX_BLOCKS)
	{
		//Goes through directory linkedlist to see if file exists
		for (int i = 1; i <= directory.getLength(); i++)
		{
			File test = directory.getEntry(i);
			std::string hello = test.name;

			//If the file is found its position is assigned
			if (hello == filename)
			{
				position = i;
				break;
			}
		}

		//If the file is found
		if (position != -1)
		{
			File test = directory.getEntry(position);
			File* file = &test;

			//Check if block doesnt exceed number of storage blocks
			if (blocknumber < file->indexBlock->arrSize)
			{
				//returns value stored in arr array
				int blockDisk = file->indexBlock->arr[blocknumber];
				std::cout << filename<< ": Block number "<< blocknumber <<" on disk is " << blockDisk <<"." << std::endl;
				return blockDisk;
			}
			//Files doesnt have a value at the position given
			std::cout << "Invalid command or parameter" <<std::endl;
			return -1;
		}
		//File not found
		std::cout << "Invalid command or parameter" << std::endl;
		return -1;
	}
	std::cout << "Invalid command or parameter" << std::endl;
	return -1;
}

//List all the file names in the directory
std::vector<std::string> FileAllocManager::listFiles() const
{
	//gets length of directory
	std::vector<std::string> check;
	int length = directory.getLength();
	
	//If the length doesnt equal 0
	if (length != 0)
	{
		//puts each variable name into a string vector
		for (int i = length; i > 0; i--)
		{
			File test = directory.getEntry(i);
			std::string hello = test.name;
			check.push_back(hello);
		}

		for (int i = 0; i < check.size(); i++)
		{
			std::cout << check[i] << std::endl;
		}

		//returns vector
		return check;
	}
	//if the length is 0 then the directory is empty
	std::cout << "Empty directory" << std::endl;
	return check;
}

//Retruns the list of all occupied blocks on disk
std::vector<unsigned int> FileAllocManager::printDisk() const
{
	//creates vector
	std::vector<unsigned int> check;

	//if blocks doesnt equal 0
	if (occupiedBlocks != 0)
	{
		//assigns each disk variable that is occupied into a vector
		for (int i = 0; i < MAX_BLOCKS; i++)
		{
			if (disk[i].occupied == true)
			{
				check.push_back(i);
			}
		}
		//prints disk output
		std::cout << "Out of " << MAX_BLOCKS << " blocks, following blocks are occupied:" << std::endl;
		for (int i = 0; i < check.size(); i++)
		{
			std::cout << check[i] << " ";
		}
		std::cout << std::endl;

		//returns vector
		return check;
	}
	//Vectors empty vector if disk is empty
	std::cout << "Out of "<< MAX_BLOCKS <<" blocks, following blocks are occupied:" << std::endl;
	return check;
}

//Find the file in the directory using file name
int FileAllocManager::findFile(std::string filename) const
{
	int position = -1;
	//Goes through directory to see if file exists
	for (int i = 1; i <= directory.getLength(); i++)
	{
		File test = directory.getEntry(i);
		std::string hello = test.name;

		//returns position if file is found
		if (hello == filename)
		{
			return i;
		}
	}
	//returns -1 if file isnt found
	return -1;
}

//starts at index start and goes to the last index
int FileAllocManager::findFirstAvailBlock(int start) const
{
	//Goes from start to end and returns location if disk isnt occupied
	for (int i = start; i < MAX_BLOCKS; i++)
	{
		if (disk[i].occupied == false)
		{
			return i;
		}
	}
	//Goes from zero to start and returns location if disk isnt occupied
	for (int i = 0; i < start; i++)
	{
		if (disk[i].occupied == false)
		{
			return i;
		}
	}
	//returns -1 if disk is full
	return -1;
}