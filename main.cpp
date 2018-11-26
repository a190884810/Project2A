
#include <iostream>
#include "Explorer.h"

using namespace std;

int main(){
	Explorer fileExplorer;
	string folderName, fileName, folderPath, pFolder;
	int fileSize, selection = 0;
	File sFile;
	list<File> files;
	list<File>::iterator filesItr;
	do
	{
		cout << "Please select an option from the list below:\n"
			<< "1 - Add Folder\n"
			<< "2 - Delete Folder\n"
			<< "3 - Add File\n"
			<< "4 - Retrieve One File\n"
			<< "5 - Retrieve Multiple Files\n"
			<< "6 - Delete File\n"
			<< "7 - Exit" << endl;
		cin >> selection;

		switch (selection)
		{
		case 1:
			cout << "Please enter the name of the folder to be added: ";
			cin.ignore();	//stops extracting characters up to end of file at its current state
			getline(cin, folderName);

			do
			{
				cout << "Does this folder have a parent folder? (Y or N) ";
				cin >> pFolder;

				if (pFolder == "Y" || pFolder == "y" || pFolder == "yes" || pFolder == "Yes" || pFolder == "YES")
				{
					cout << "Please enter the folder pathway, excluding the folder name (Format: Folder/subfolder): ";
					cin.ignore();
					getline(cin, folderPath);
					fileExplorer.addFolder(folderPath, folderName);
				}
				else if (pFolder == "N" || pFolder == "n" || pFolder == "no" || pFolder == "No" || pFolder == "NO")
					fileExplorer.addFolder(folderName);
				else
					cout << "Invalid entry." << endl;
				//repeats while loop if none of the appropriate responses were used
			} while (pFolder != "Y" && pFolder != "y" && pFolder != "yes" && pFolder != "Yes" && pFolder != "YES"
				&& pFolder != "N" && pFolder != "n" && pFolder != "no" && pFolder != "No" && pFolder != "NO");
			break;
		case 2:
			cout << "Please enter the name of the folder to be deleted: ";
			cin.ignore();
			getline(cin, folderName);

			do
			{
				cout << "Does this folder have a parent folder? (Y or N) ";
				cin >> pFolder;

				if (pFolder == "Y" || pFolder == "y" || pFolder == "yes" || pFolder == "Yes" || pFolder == "YES")
				{
					cout << "Please enter the folder pathway, excluding the folder name (Format: Folder/subfolder): ";
					cin.ignore();
					getline(cin, folderPath);
					fileExplorer.deleteFolder(folderPath, folderName);
				}
				else if (pFolder == "N" || pFolder == "n" || pFolder == "no" || pFolder == "No" || pFolder == "NO")
					fileExplorer.deleteFolder(folderName);
				else
					cout << "Invalid entry." << endl;

			} while (pFolder != "Y" && pFolder != "y" && pFolder != "yes" && pFolder != "Yes" && pFolder != "YES"
				&& pFolder != "N" && pFolder != "n" && pFolder != "no" && pFolder != "No" && pFolder != "NO");
			break;
		case 3:
			cout << "Please enter the name of the file to be added: ";
			cin.ignore();
			getline(cin, fileName);

			cout << "Please enter the file's size (integer value, no units): ";
			cin >> fileSize;
			do
			{
				cout << "Please enter the folder pathway, including the name of the folder containing the file (Format: Folder/subfolder): ";
				cin.ignore();
				getline(cin, folderPath);
			} while (folderPath == "");

			fileExplorer.addFile(folderPath, fileName, fileSize);
			break;
		case 4:
			cout << "Please enter the name of the file to be displayed: ";
			cin.ignore();
			getline(cin, fileName);

			cout << "Please enter the folder pathway, including the name of the folder containing the file (Format: Folder/subfolder): ";
			cin.ignore();
			getline(cin, folderPath);

			//retrieves single file
			sFile = fileExplorer.getFile(folderPath, fileName);

			if (sFile.get_fileName().empty())
				cout << "File not found." << endl;
			else
				cout << "File Name: " << sFile.get_fileName()
				<< "\t|\tFile Size: " << sFile.get_fileSize();
			break;
		case 5:
			cout << "Please enter search term for the file query: ";
			cin.ignore();
			getline(cin, fileName);

			files = fileExplorer.getFilesWrapper(fileName);
			if (files.empty())
				cout << "No matches found that match your query." << endl;
			else
			{
				cout << "Files containing search term:";
				for (filesItr == files.begin(); filesItr != files.end(); filesItr++)
					cout << "\nFile Name: " << filesItr->get_fileName()
					<< "\t|\tFile Size: " << filesItr->get_fileSize();
			}
			break;
		case 6:
			cout << "Please enter the name of the file to be deleted: ";
			cin.ignore();
			getline(cin, fileName);

			cout << "Please enter the folder pathway, including the name of the folder containing the file (Format: Folder/subfolder): ";
			cin.ignore();
			getline(cin, folderPath);

			fileExplorer.deleteFile(folderPath, fileName);
			break;
		case 7:
			cout << "Thank you." << endl;
			break;
		default:
			cout << "Invalid selection." << endl;
			system("PAUSE");
			break;
		}
		system("CLS");
	} while (selection != 7);
	return 0;
}