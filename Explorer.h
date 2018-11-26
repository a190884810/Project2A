#include "Folders.h"
#include <list>

class Explorer
{
private:
	AVL_Tree<Folders> folderTree;

public:
	
	void addFolder(std::string sName)
	{
		Folders newFolder(sName);

		//insert folder into tree
		if (folderTree.insert(newFolder))
			std::cout << "Folder added successfully." << std::endl;
		else
			std::cout << "Folder already exists! Please use another name for the folder." << std::endl;
	}

	void addFolder(std::string sPath, std::string sName)
	{
		Folders newFolder(sPath+'/'+sName);

		if (folderTree.insert(newFolder))
			std::cout << "Folder added successfully." << std::endl;
		else
			std::cout << "Folder already exists! Please use another name for the folder." << std::endl;
	}

	void addFile(std::string filePath, std::string fName, int fSize)
	{
		Folders fldr(filePath);

		//if function returns true, the size of the file list did not change, meaning the file was not added
		if (folderTree.find(fldr).addFileToFolder(fName, fSize))
			std::cout << "File already exists! Please use another name for the file." << std::endl;
		else
		{
			std::cout << "File added successfully." << std::endl;
			//after adding file, recalculate the all folders sizes
			folderSizewrapper();
		}
	}

	void deleteFolder(std::string dName)
	{
		//create temp folder value to look for in the folder tree
		Folders delFolder(dName);

		if (folderTree.erase(delFolder))
		{
			std::cout << "Folder deleted successfully." << std::endl;
			//after deleting the folder, recalculate the all folders sizes
			folderSizewrapper();
		}
		else
			std::cout << "Folder does not exist! Please search for another folder name." << std::endl;
	}

	void deleteFolder(std::string dPath, std::string dName)
	{
		Folders delFolder(dPath+'/'+dName);

		if (folderTree.erase(delFolder))
		{
			std::cout << "Folder deleted successfully." << std::endl;
			folderSizewrapper();
		}
		else
			std::cout << "Folder does not exist! Please search for another folder name." << std::endl;
	}

	void deleteFile(std::string filePath, std::string fName)
	{
		Folders fldr(filePath);

		//if function returns true, the size of the file list did not change, meaning the file was not added
		if (folderTree.find(fldr).removeFileFromFolder(fName))
			std::cout << "File does not exist! Please enter another file name." << std::endl;
		else
		{
			std::cout << "File deleted successfully." << std::endl;
			//after deleting the file, recalculate the all folders sizes
			folderSizewrapper();
		}
	}
	//update folder size
	void folderSizewrapper()
	{
		//initialize file size as zero and assign NULL to the pathway so it starts at the root folder
		int filesize = 0;
		folderSize(&folderTree, "", filesize);
	}

	void folderSize(AVL_Tree<Folders>* localroot, std::string fPath, int filesize)
	{
		if (localroot->is_null())
			return;
		
		//add all the file sizes together in the map object
		std::map<std::string, File>::iterator it;
		Folders tempFldr = localroot->get_data();
		//if the file at the pointer location contains fPath in its folder pathway, it is a subfolder of the folder
		if (tempFldr.get_filePath().substr(0, fPath.size()) == fPath)
		{
			for (it = tempFldr.get_filesInFolder()->begin(); it != tempFldr.get_filesInFolder()->end(); it++)
			{
				filesize += it->second.get_fileSize();
			}
		}
		//update fPath to include only appropriate subfolders as it transverses the tree
		fPath = tempFldr.get_filePath();
		folderSize(&localroot->get_left_subtree(), fPath, filesize);
		folderSize(&localroot->get_right_subtree(), fPath, filesize);
		//update file size for folder
		tempFldr.set_folderSize(filesize);
	}

	File getFile(std::string path, std::string oneFile) 
	{
		Folders fldr(path);
		//locates the fldr value in the folderTree, opens the filesInFolder map value, finds the file name,
		//and returns the associated file
		return folderTree.find(fldr).get_filesInFolder()->find(oneFile)->second;
	}

	std::list<File> getFilesWrapper(std::string sQuery)
	{
		std::list<File> fileList;
		return getFiles(&folderTree, sQuery, fileList);
	}

	std::list<File> getFiles(AVL_Tree<Folders>* localroot, std::string query, std::list<File>& fList)
	{
		if (!localroot->is_null())
		{
			Folders tempFldr = localroot->get_data();
			std::map <std::string, File>::iterator itr = tempFldr.get_filesInFolder()->begin();

			//NOTE: consider moving this map search to Folders.h
			for (itr; itr != tempFldr.get_filesInFolder()->end(); itr++)
			{
				if (itr->first.size() >= query.size())
				{
					if (itr->first.substr(0, query.size()) == query)
						fList.push_back(itr->second);
				}
			}
		}
		getFiles(&localroot->get_left_subtree(), query, fList);
		getFiles(&localroot->get_right_subtree(), query, fList);
		
		return fList;
	}

	AVL_Tree<Folders> get_folderTree() { return folderTree; }
};