#ifndef FileAllocManager_hpp
#define FileAllocManager_hpp

#include <memory>
#include <ctime>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Node.hpp"
#include "LinkedList.hpp"

const int MAX_FILES = 32;      
const int MAX_BLOCKS = 32;     
const int TOTAL_SIZE_KiB = 64;
const int BLOCK_SIZE_KiB = 2;  

// Block struct
struct Block
{
  bool occupied; //Block occupied
  int *arr;      //Pointer to file
  int arrSize;   //size
};

// File struct
struct File 
{
  std::string name;     //name of the file
  int size;             //size of the file in KiB
  Block* indexBlock;    //pointer to the index block, each file has an index block
};

class FileAllocManager
{
public:
  FileAllocManager();
  ~FileAllocManager();
  void clear();
  std::vector<unsigned int> addFile (std::string filename, int filesize);
  bool deleteFile(std::string filename);
  int seekFile(std::string filename, int blocknumber) const;
  std::vector<std::string> listFiles() const;
  std::vector<unsigned int> printDisk() const;
  unsigned int numOccupiedBlocks() const { return occupiedBlocks; };
  const LinkedList<File>& getDirectory() const { return directory; }
    
private:
  //Disk
  Block disk[MAX_BLOCKS];
  // The directory of files
  LinkedList<File> directory;
  //occupied blocks on disk
  int occupiedBlocks;
 
  int findFile(std::string filename) const;
  int findFirstAvailBlock(int start) const;
    
};

#endif
