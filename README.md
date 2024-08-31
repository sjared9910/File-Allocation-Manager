# File Allocation Manager
Using the indexed allocation method, this program simulates the creation of files where data will be assigned to random blocks along with an index block. For each file
there is an index block which holds the list of addresses of the file block. 
# Features
- Two different usage modes: Interactive mode, and read from file
- Add a file of varying size
- Delete a file
- List files in the directory
- Seek a file block
- List the disk contents
# Usage
To run in interactive mode, execute the program using no additional inputs. The list of commands:
- Add (filename)(size in kilobytes) &emsp;&emsp; &emsp;&emsp; Adds a file to the directory
- del (filename) &emsp;&emsp;&emsp; &emsp; &emsp; &emsp;&emsp;&emsp; &emsp; &emsp;&ensp;&nbsp; Deletes a file from the directory
- list &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; Lists files in the directory
- seek (filename)(block index) &emsp;&emsp;&emsp;&emsp;&emsp;&emsp; Seeks a particular block in the file
- disk &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&ensp; Prints the disk contents

To run the program in non-interactive mode, launch the program as FileAllocDriver.exe -f (filename) where (filename) is a text file containing
commands to run. An example input file:
</br>
![Capture](https://github.com/user-attachments/assets/2e8178ba-896d-4294-a763-d79775b69579)
</br>

The maximum number of files and blocks along with the total size (in kilobytes) and block size (in kilobytes) can be changed within the FileAllocManager.hpp header file
