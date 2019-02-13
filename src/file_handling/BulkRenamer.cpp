#include "BulkRenamer.h"
BulkRenamer::BulkRenamer()
{
	new_format = "";
}

BulkRenamer::BulkRenamer(string_vec fileList, string newFormat)
{
	loadNewFiles(fileList);
	new_format = newFormat;
}

void BulkRenamer::loadNewFiles(string_vec filePaths)
{
	for (int i = 0; i < filePaths.size(); i++)
	{
		file_list.push_back(new FileInfo(filePaths[i]));
	}
}
 	
bool BulkRenamer::loadUserInfo(string format)
{
	// Iterate through each file in list
	for (int i = 0; i < file_list.size(); i++)
	{
		if (!file_list[i]->loadUserInfo(format))
		{
			printf("ERROR: Could not load user info from file '%s'", file_list[i]->getOldFilename().c_str());
			return false;	
		}
	}
	return true;
}

bool BulkRenamer::genNewFilenames()
{
	string newfilename = "";
	string tag = "";
	time_t currtime;
	time(&currtime);

	// Iterate through each file in list
	for (int i = 0; i < file_list.size(); i++)
	{
		// Iterate through each character in new format
		for (int j = 0; j < new_format.length(); j++)
		{			
			// If a § character is encountered, it contains a tag to hold variable data
			//if (new_format[j] == '§')
			if (((int) new_format[j] == -62) && ((int) new_format[j + 1] == -89))
			{
				j += 2;
				// If a § character is encountered, read until next null character
				// and add to tag
				tag = "";
				while (((int) new_format[j] != -62) && ((int) new_format[j + 1] != -89)
					 	&& (j < new_format.length()))
				{
					tag += new_format[j];
					j++;
				}
				j += 2;
				if (((((int) new_format[j] == -62) && ((int) new_format[j + 1] == -89)) 
						&& (j == new_format.length())))
				{
					printf("ERROR MESSAGE: Incomplete Tag\n");
					return false;
				}
				// *******************************************************
				// ** Depending on the contents between null characters **
				// ** Get appropriate info and add to new filename      **
				// *******************************************************
				// Adds lower case extension to newfilename
				if (tag == "ext")
				{
					newfilename += file_list[i]->getExtension();
				}
				// Adds upper case extendion to newfilename
				else if (tag == "EXT")
				{
					newfilename += file_list[i]->getExtensionCaps();
				}
				// Adds index to filename
				else if (tag == "index")
				{
					// Adds index to filename
					newfilename += std::to_string(i);
				}
				// Adds index with leading zero to filename
				else if (tag == "l0index")
				{
					// max0 = floor(log_10(max))
					// lead0 = max0 - floor(log_10(num))
					// Prints leading zeros to newfilename
					for (int i = 0; i < floor(log10(file_list.size() - 1)) - floor(log10(i)); i++)
					{
						newfilename += "0";
					}
					// Adds index to filename
					newfilename += std::to_string(i);
				}
				// ==FILE CREATION DATES==================================================
				// =======================================================================
				// Adds file creation date to filename in format dd_mm_yyyy
				else if (tag == "create dd_mm_yyyy")
				{
					newfilename += convertDateTime(dd_mm_yyyy, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format mm_dd_yyyy
				else if (tag == "create mm_dd_yyyy")
				{
					newfilename += convertDateTime(mm_dd_yyyy, file_list[i]->getCreateTime());	
				}
				// Adds file creation date to filename in format dd_month_yyyy
				else if (tag == "create dd_month_yyyy")
				{
					newfilename += convertDateTime(dd_month_yyyy, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format month_dd_yyyy
				else if (tag == "create month_dd_yyyy")
				{
					newfilename += convertDateTime(month_dd_yyyy, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format mm_dd
				else if (tag == "create mm_dd")
				{
					newfilename += convertDateTime(mm_dd, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format dd_mm
				else if (tag == "create dd_mm")
				{
					newfilename += convertDateTime(dd_mm, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format month
				else if (tag == "create month")
				{
					newfilename += convertDateTime(month, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format month_dd
				else if (tag == "create month_dd")
				{
					newfilename += convertDateTime(month_dd, file_list[i]->getCreateTime());					
				}
				// Adds file creation date to filename in format dd_month
				else if (tag == "create dd_month")
				{
					newfilename += convertDateTime(dd_month, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format yyyy
				else if (tag == "create yyyy")
				{
					newfilename += convertDateTime(yyyy, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format dd_mon_yyyy
				else if (tag == "create dd_mon_yyyy")
				{
					newfilename += convertDateTime(dd_mon_yyyy, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format mon_dd_yyyy
				else if (tag == "create mon_dd_yyyy")
				{
					newfilename += convertDateTime(mon_dd_yyyy, file_list[i]->getCreateTime());		
				}
				// Adds file creation date to filename in format mon
				else if (tag == "create mon")
				{
					newfilename += convertDateTime(mon, file_list[i]->getCreateTime());
				}
				// Adds file creation date to filename in format mon_dd
				else if (tag == "create mon_dd")
				{
					newfilename += convertDateTime(mon_dd, file_list[i]->getCreateTime());	
				}
				// Adds file creation date to filename in format dd_mon
				else if (tag == "create dd_mon")
				{
					newfilename += convertDateTime(dd_mon, file_list[i]->getCreateTime());
				}
				// ==FILE LAST MODIFIED DATES=============================================
				// =======================================================================
				// Adds file last modified date to filename in format dd_mm_yyyy
				else if (tag == "modified dd_mm_yyyy")
				{
					newfilename += convertDateTime(dd_mm_yyyy, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format mm_dd_yyyy
				else if (tag == "modified mm_dd_yyyy")
				{
					newfilename += convertDateTime(mm_dd_yyyy, file_list[i]->getLastModTime());	
				}
				// Adds file last modified date to filename in format dd_month_yyyy
				else if (tag == "modified dd_month_yyyy")
				{
					newfilename += convertDateTime(dd_month_yyyy, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format month_dd_yyyy
				else if (tag == "modified month_dd_yyyy")
				{
					newfilename += convertDateTime(month_dd_yyyy, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format mm_dd
				else if (tag == "modified mm_dd")
				{
					newfilename += convertDateTime(mm_dd, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format dd_mm
				else if (tag == "modified dd_mm")
				{
					newfilename += convertDateTime(dd_mm, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format month
				else if (tag == "modified month")
				{
					newfilename += convertDateTime(month, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format month_dd
				else if (tag == "modified month_dd")
				{
					newfilename += convertDateTime(month_dd, file_list[i]->getLastModTime());					
				}
				// Adds file last modified date to filename in format dd_month
				else if (tag == "modified dd_month")
				{
					newfilename += convertDateTime(dd_month, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format yyyy
				else if (tag == "modified yyyy")
				{
					newfilename += convertDateTime(yyyy, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format dd_mon_yyyy
				else if (tag == "modified dd_mon_yyyy")
				{
					newfilename += convertDateTime(dd_mon_yyyy, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format mon_dd_yyyy
				else if (tag == "modified mon_dd_yyyy")
				{
					newfilename += convertDateTime(mon_dd_yyyy, file_list[i]->getLastModTime());		
				}
				// Adds file last modified date to filename in format mon
				else if (tag == "modified mon")
				{
					newfilename += convertDateTime(mon, file_list[i]->getLastModTime());
				}
				// Adds file last modified date to filename in format mon_dd
				else if (tag == "modified mon_dd")
				{
					newfilename += convertDateTime(mon_dd, file_list[i]->getLastModTime());	
				}
				// Adds file last modified date to filename in format dd_mon
				else if (tag == "modified dd_mon")
				{
					newfilename += convertDateTime(dd_mon, file_list[i]->getLastModTime());
				}
				// ==FILE LAST ACCESS DATES===============================================
				// =======================================================================
				// Adds file last access date to filename in format dd_mm_yyyy
				else if (tag == "accessed dd_mm_yyyy")
				{
					newfilename += convertDateTime(dd_mm_yyyy, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format mm_dd_yyyy
				else if (tag == "accessed mm_dd_yyyy")
				{
					newfilename += convertDateTime(mm_dd_yyyy, file_list[i]->getLastAccessTime());	
				}
				// Adds file last access date to filename in format dd_month_yyyy
				else if (tag == "accessed dd_month_yyyy")
				{
					newfilename += convertDateTime(dd_month_yyyy, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format month_dd_yyyy
				else if (tag == "accessed month_dd_yyyy")
				{
					newfilename += convertDateTime(month_dd_yyyy, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format mm_dd
				else if (tag == "accessed mm_dd")
				{
					newfilename += convertDateTime(mm_dd, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format dd_mm
				else if (tag == "accessed dd_mm")
				{
					newfilename += convertDateTime(dd_mm, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format month
				else if (tag == "accessed month")
				{
					newfilename += convertDateTime(month, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format month_dd
				else if (tag == "accessed month_dd")
				{
					newfilename += convertDateTime(month_dd, file_list[i]->getLastAccessTime());					
				}
				// Adds file last access date to filename in format dd_month
				else if (tag == "accessed dd_month")
				{
					newfilename += convertDateTime(dd_month, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format yyyy
				else if (tag == "accessed yyyy")
				{
					newfilename += convertDateTime(yyyy, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format dd_mon_yyyy
				else if (tag == "accessed dd_mon_yyyy")
				{
					newfilename += convertDateTime(dd_mon_yyyy, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format mon_dd_yyyy
				else if (tag == "accessed mon_dd_yyyy")
				{
					newfilename += convertDateTime(mon_dd_yyyy, file_list[i]->getLastAccessTime());		
				}
				// Adds file last access date to filename in format mon
				else if (tag == "accessed mon")
				{
					newfilename += convertDateTime(mon, file_list[i]->getLastAccessTime());
				}
				// Adds file last access date to filename in format mon_dd
				else if (tag == "accessed mon_dd")
				{
					newfilename += convertDateTime(mon_dd, file_list[i]->getLastAccessTime());	
				}
				// Adds file last access date to filename in format dd_mon
				else if (tag == "accessed dd_mon")
				{
					newfilename += convertDateTime(dd_mon, file_list[i]->getLastAccessTime());
				}
				// ==CURRENT DATES========================================================
				// =======================================================================
				// Adds current date to filename in format dd_mm_yyyy
				else if (tag == "current dd_mm_yyyy")
				{
					newfilename += convertDateTime(dd_mm_yyyy, currtime);
				}
				// Adds current date to filename in format mm_dd_yyyy
				else if (tag == "current mm_dd_yyyy")
				{
					newfilename += convertDateTime(mm_dd_yyyy, currtime);	
				}
				// Adds current date to filename in format dd_month_yyyy
				else if (tag == "current dd_month_yyyy")
				{
					newfilename += convertDateTime(dd_month_yyyy, currtime);
				}
				// Adds current date to filename in format month_dd_yyyy
				else if (tag == "current month_dd_yyyy")
				{
					newfilename += convertDateTime(month_dd_yyyy, currtime);
				}
				// Adds current date to filename in format mm_dd
				else if (tag == "current mm_dd")
				{
					newfilename += convertDateTime(mm_dd, currtime);
				}
				// Adds current date to filename in format dd_mm
				else if (tag == "current dd_mm")
				{
					newfilename += convertDateTime(dd_mm, currtime);
				}
				// Adds current date to filename in format month
				else if (tag == "current month")
				{
					newfilename += convertDateTime(month, currtime);
				}
				// Adds current date to filename in format month_dd
				else if (tag == "current month_dd")
				{
					newfilename += convertDateTime(month_dd, currtime);					
				}
				// Adds current date to filename in format dd_month
				else if (tag == "current dd_month")
				{
					newfilename += convertDateTime(dd_month, currtime);
				}
				// Adds current date to filename in format yyyy
				else if (tag == "current yyyy")
				{
					newfilename += convertDateTime(yyyy, currtime);
				}
				// Adds current date to filename in format dd_mon_yyyy
				else if (tag == "current dd_mon_yyyy")
				{
					newfilename += convertDateTime(dd_mon_yyyy, currtime);
				}
				// Adds current date to filename in format mon_dd_yyyy
				else if (tag == "current mon_dd_yyyy")
				{
					newfilename += convertDateTime(mon_dd_yyyy, currtime);		
				}
				// Adds current date to filename in format mon
				else if (tag == "current mon")
				{
					newfilename += convertDateTime(mon, currtime);
				}
				// Adds current date to filename in format mon_dd
				else if (tag == "current mon_dd")
				{
					newfilename += convertDateTime(mon_dd, currtime);	
				}
				// Adds current date to filename in format dd_mon
				else if (tag == "current dd_mon")
				{
					newfilename += convertDateTime(dd_mon, currtime);
				}
				else
				{
					printf("ERROR: Could Not Read New Format %s\n", new_format.c_str());
					return false;
				}
				tag = "";
			}
			// If a / is encountered, a user defined tag follows
			else if (new_format[j] == '/')
			{
				// If a / character is encountered, read until next / character
				// and add to tag
				tag = '/';
				do
				{
					j++;
					tag += new_format[j];
				}while ((new_format[j] != '/') && (j < new_format.length()));

				if (((new_format[j] != '/') && (j == new_format.length())))
				{
					printf("ERROR MESSAGE: Incomplete Tag\n");
					return false;
				}
				string temp;
				if (!file_list[i]->getInfoElem(temp, tag))
				{
					printf("ERROR MESSAGE: Could Not Find Tag %s\n", temp.c_str());
					return false;
				}
				newfilename += temp;
			}
			// Add normal characters to new filename
			else
			{
				newfilename += new_format[j];
			}	
		}
		file_list[i]->setNewFilename(newfilename);
		newfilename = "";
	}
	return true;
}

bool BulkRenamer::renameFiles()
{
	for (int i = 0; i < file_list.size(); i++)
	{
		file_list[i]->renameFile();
	}
}

string BulkRenamer::convertDateTime(BulkRenamer::DateTimeFormat dt_format, time_t rawtime) const
{
	char buffer [20];
	struct tm* timeinfo;
	if (dt_format == dd_mm_yyyy)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%d_%m_%Y", timeinfo);
	}
	else if (dt_format == mm_dd_yyyy)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%m_%d_%Y", timeinfo);
	}
	else if (dt_format == dd_mon_yyyy)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%d_%b_%Y", timeinfo);
	}
	else if (dt_format == mon_dd_yyyy)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%b_%d_%Y", timeinfo);
	}
	else if (dt_format == mm_dd)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%m_%d", timeinfo);
	}
	else if (dt_format == dd_mm)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%d_%m", timeinfo);
	}
	else if (dt_format == mon)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%b", timeinfo);
	}
	else if (dt_format == mon_dd)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%b_%d", timeinfo);
	}
	else if (dt_format == dd_mon)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%d_%b", timeinfo);
	}
	else if (dt_format == yyyy)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%Y", timeinfo);
	}
	else if (dt_format == dd_month_yyyy)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%d_%B_%Y", timeinfo);
	}
	else if (dt_format == month_dd_yyyy)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%B_%d_%Y", timeinfo);
	}
	else if (dt_format == month)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%B", timeinfo);
	}
	else if (dt_format == month_dd)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%B_%d", timeinfo);
	}
	else if (dt_format == dd_month)
	{
		// Converts raw time to local time
		timeinfo = localtime(&rawtime);

		// Converts local time to string
		strftime (buffer, 20, "%d_%B", timeinfo);
	}
	return buffer;
}

void BulkRenamer::setFileList(string_vec filePaths)
{
	file_list.clear();
	// Populates file_list with new files
	loadNewFiles(filePaths);
}

void BulkRenamer::addFile(FileInfo& newfile, int index)
{
	file_list.insert(file_list.begin() + index, new FileInfo(newfile));
}

void BulkRenamer::addFile(string newfilepath, int index)
{
	file_list.insert(file_list.begin() + index, new FileInfo(newfilepath));
}

void BulkRenamer::pushFile(FileInfo& newfile)
{
	file_list.push_back(new FileInfo(newfile));
}

void BulkRenamer::pushFile(string newfilepath)
{
	file_list.push_back(new FileInfo(newfilepath));
}

void BulkRenamer::moveFile(int index, int newIndex)
{
	FileInfo* temp = new FileInfo(*file_list[index]);
	removeFile(index);
	if (newIndex > index)
	{
		file_list.insert(file_list.begin() + newIndex, temp);
	}
	else
	{
		file_list.insert(file_list.begin() + newIndex - 1, temp);
	}
}

void BulkRenamer::removeFile(int index)
{
	std::vector<FileInfo*>::iterator it = file_list.begin();
	std::advance(it, index);

	file_list[index]->clear();
	delete file_list[index];
	file_list.erase(it);
}

void BulkRenamer::display() const
{
	// Iterate through each file in list
	for (int i = 0; i < file_list.size(); i++)
	{
		printf("~~ FILE %d)\t~~~~~~~~~~~~~~~~~~~~~~~~~", i + 1);
		printf("\n~~ NEW FORMAT ~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("%s", new_format.c_str());
		file_list[i]->display();
	}
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

//==TESTING CODE===================================================================================
//=================================================================================================
int main()
{
	BulkRenamer br;
	br.pushFile("/home/jdistefano/UIC/PersonalProjects/Bulk_Rename_Tool/src/file_handling/testfiles/01 The Doors - Break On Through.mp3");
	br.pushFile("/home/jdistefano/UIC/PersonalProjects/Bulk_Rename_Tool/src/file_handling/testfiles/02 The Doors - Light My Fire.mp3");
	br.pushFile("/home/jdistefano/UIC/PersonalProjects/Bulk_Rename_Tool/src/file_handling/testfiles/03 The Doors - The Crystal Ship.mp3");
	br.pushFile("/home/jdistefano/UIC/PersonalProjects/Bulk_Rename_Tool/src/file_handling/testfiles/04 The Doors - People Are Strange.mp3");
	br.addFile("/home/jdistefano/UIC/PersonalProjects/Bulk_Rename_Tool/src/file_handling/testfiles/19 The Doors - The End.mp3", 2);
	br.loadUserInfo("/track/ The Doors - /title/");
	br.setFormat("/track/ - /title/: The Doors Greatest Hits §current dd_mon§");
	br.genNewFilenames();
	br.display();
	return 0;
}
//=================================================================================================*/