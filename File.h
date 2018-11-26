#include <string>

//holds file objects
class File
{
private:
	std::string fileName;
	int fileSize;
public:
	File (){}
	File(std::string name, int size)
	{
		fileName = name;
		fileSize = size;
	}
	std::string get_fileName() { return fileName; }
	int get_fileSize() { return fileSize; }
	void set_fileName(std::string& new_name) { fileName = new_name; }
	void set_fileSize(int& new_size) { fileSize = new_size; }
};