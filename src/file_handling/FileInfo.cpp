#include "FileInfo.h"

FileInfo::FileInfo()
{
	file_path = "";
	old_filename = "";
	extension = "";
	new_filename = "";
	

	create_time = (time_t)0;
	last_mod_time = (time_t)0;
	last_access_time = (time_t)0;
	user_file_info = std::vector< string_vec > (2, string_vec(1, ""));
}

FileInfo::FileInfo(string filepath)
{
	file_path = filepath;	// Sets file_path to the given filepath parameter
	// Searches the filepath for the last '.' and last '/' character, reads the
	// string inbetween as the old_filename
	int dot_pos = filepath.length() - 1;
	while (dot_pos > 0 && filepath[dot_pos] != '.')
	{
		dot_pos--;
	}
	int slash_pos = dot_pos;
	while (slash_pos > 0 && filepath[slash_pos] != '/')
	{
		slash_pos--;
	}
	directory = filepath.substr(0, slash_pos + 1);
	old_filename = filepath.substr(slash_pos + 1, dot_pos - slash_pos - 1);
	new_filename = "";

	user_file_info = std::vector< string_vec > (2, string_vec(1, ""));

	// Loads in information for extension, create_time last_mod_time and last_access_time
	updateInfo();
}

FileInfo::FileInfo(const FileInfo &copy)
{
	file_path = copy.getFilePath();
	old_filename = copy.getOldFilename();
	new_filename = copy.getNewFilename();
	extension = copy.getExtension();
	directory = copy.getDirectory();
	create_time = copy.getCreateTime();
	last_mod_time = copy.getLastModTime();
	last_access_time = copy.getLastAccessTime();
	user_file_info = copy.getFileInfo();
}

FileInfo::~FileInfo()
{
	clear();
}

FileInfo FileInfo::operator=(const FileInfo& copy)
{
	file_path = copy.getFilePath();
	old_filename = copy.getOldFilename();
	new_filename = copy.getNewFilename();
	extension = copy.getExtension();
	directory = copy.getDirectory();
	create_time = copy.getCreateTime();
	last_mod_time = copy.getLastModTime();
	last_access_time = copy.getLastAccessTime();
	user_file_info = copy.getFileInfo();	
}

bool FileInfo::loadUserInfo(string format)
{	
	// Create a vector for the constant elements and info titles
	//string_vec info_titles;
	string_vec const_strings;
	string sub_str("");
	
	// Breaks down format string into two vectors of constants and info_titles
	for (int i = 0; i < format.length(); i++)
	{
		// If a / is encountered, record and place in info_titles
		if (format[i] == '/')
		{	
			// Read old_filename until '/', place result in constant vector
			const_strings.push_back(sub_str);
			sub_str.assign("/");
			// Read everything until next '/', place in info title vector
			do
			{
				i++;
				sub_str.push_back(format[i]);
			}while ((format[i] != '/') && (i < format.length() - 1));

			// ERROR HANDLING
			if ((format[i] != '/') && (i == format.length() - 1))
			{
				printf("ERROR MESSAGE: Incomplete Tag\n");
				return false;
			}
			if (sub_str.c_str() == "//")
			{
				printf("ERROR MESSAGE: Empty info title\n");
				return false;
			}
			else if (titleExists(sub_str))
			{
				printf("ERROR MESSAGE: Duplicate title\n");	
				return false;
			}
			if (user_file_info[0][0] == "")
			{
				user_file_info[0][0] = sub_str;
			}
			else
			{
				user_file_info[0].push_back(sub_str);
			}
			sub_str.assign("");
		}
		// Otherwise continue adding to substring
		else
		{
			sub_str += format[i];
		}
		//Breakpoint 
	}
	// Add whatever is left in sub_str into const_strings. If "", old_filename ends with info
	const_strings.push_back(sub_str);

	// ==================================================================================
	// Reads data from the old old_filename and stores it into user_file_info
	// prevEnd is set to the length of the first constant string - 1
	int prevEnd = 0 + const_strings[0].length();
	// currStart represents where the beginning of the current constant string is
	int currStart;
	// info_str represents the string to be added to user_file_info
	string info_str;
	// Goes through each constant word and collects data from between them
	for (int constIndex = 1; constIndex < const_strings.size(); constIndex++)
	{	
		// If the last element in const_strings is an empty string, then data is to
		// be read until the end of the old_filename
		if ((constIndex == const_strings.size() - 1 )
			&& (const_strings[constIndex] == ""))
		{
			info_str = old_filename.substr(prevEnd);
			// If the first entry in user_file_info is the empty string, replace it
			if (user_file_info[1][0] == "")
			{
				user_file_info[1][0] = info_str;
			}
			// Otherwise push new data onto the end of it
			else
			{
				user_file_info[1].push_back(info_str);
			}
		}
		// Otherwise record data between constant strings
		else
		{
			// Finds the next constant string and records its starting position
			currStart = old_filename.find(const_strings[constIndex], prevEnd);
			if (currStart != -1)
			{
				// Adds characters from prevEnd to currStart to info_str
				while(prevEnd < currStart)
				{
					info_str += old_filename[prevEnd];
					prevEnd++;
				}
				// If the first entry in user_file_info is the empty string, replace it
				if (user_file_info[1][0] == "")
				{
					user_file_info[1][0] = info_str;
				}
				// Otherwise push new data onto the end of it
				else
				{
					user_file_info[1].push_back(info_str);
				}
				info_str = "";
				// Sets prevEnd to the end of the current constant string
				prevEnd = currStart + const_strings[constIndex].length();	
			}
			else
			{
				printf("ERROR: Unable to Find %s\n", const_strings[constIndex].c_str());
				return false;
			}
		}
	}
	return true;
}

bool FileInfo::updateInfo()
{

	if (!findExtension(extension))
	{
		printf("ERROR: Unable to find extension\n");
		return false;
	}
	if (!findCreateTime(create_time))
	{
		printf("ERROR: Unable to find file creation time\n");
		return false;
	}
	if (!findLastModTime(last_mod_time))
	{
		printf("ERROR: Unable to find file last modified time\n");
		return false;
	}
	if (!findLastAccessTime(last_access_time))
	{
		printf("ERROR: Unable to find file last access time\n");
		return false;
	}
	return true;
}

bool FileInfo::findExtension(string& extension)
{
	int dot_pos = file_path.length() - 1;
	while (dot_pos > 0 && file_path[dot_pos] != '.')
	{
		dot_pos--;
	}
	if (dot_pos != 0)
	{
		extension = file_path.substr(dot_pos + 1, file_path.length() - dot_pos);
		return true;
	}
	else
	{
		return false;
	}
}

bool FileInfo::findCreateTime(time_t& time)
{	
	struct stat f_info;
	if(stat(file_path.c_str(), &f_info) != 0)
	{
		return false;
	}

	time = f_info.st_ctime;
	return true;
}

bool FileInfo::findLastModTime(time_t& time)
{
	struct stat f_info;
	if(stat(file_path.c_str(), &f_info) != 0)
	{
		return false;
	}

	time = f_info.st_mtime;
	return true;
}

bool FileInfo::findLastAccessTime(time_t& time)
{
	struct stat f_info;
	if(stat(file_path.c_str(), &f_info) != 0)
	{
		return false;
	}

	time = f_info.st_atime;
	return true;
}
bool FileInfo::titleExists(string title) const
{
	for (int i = 0; i < user_file_info[0].size(); i++)
	{
		if (user_file_info[0][i] == title)
		{
			return true;
		}
	}
	return false;
}


bool FileInfo::getInfoTitle(string &title, int index) const
{
	if (index > user_file_info[0].size() - 1)
		return false;
	else
		title = user_file_info[0][index];
	return true;
}

bool FileInfo::getInfoElem(string& elem, string title) const
{
	for (int i = 0; i < user_file_info[0].size(); i++)
	{
		if (user_file_info[0][i] == title)
		{
			elem = user_file_info[1][i];
			return true;
		}
	}
	return false;
}

string FileInfo::getExtensionCaps() const
{
	string extCaps = extension;
	// Check every character, if it is a-z, change to A-Z
	for (int i = 0; i < extCaps.length(); i++)
	{
		if (extCaps[i] >= 97 && extCaps[i] <= 122)
		{
			extCaps[i] = extCaps[i] - 32;
		}
	}
	return extCaps;
}

void FileInfo::addDataElem(string title, string elem)
{
	// If the title in user_file_info is the empty string, replace it
	if (user_file_info[0][0] == "")
	{
		user_file_info[0][0] = title;
	}
	// Otherwise push new data onto the end of it
	else
	{
		user_file_info[1].push_back(title);
	}

	// If the info string in user_file_info is the empty string, replace it
	if (user_file_info[1][0] == "")
	{
		user_file_info[1][0] = elem;
	}
	// Otherwise push new data onto the end of it
	else
	{
		user_file_info[1].push_back(elem);
	}
}

void FileInfo::replaceStr(string str, string new_str)
{
	// Sets new_filename to a copy of old_filename
	new_filename = old_filename;

	// Iterates through every character in new_filename 
	for (int i = 0; i < new_filename.length() - str.length(); i++)
	{
		// If the characters following i are identical to the search string then replace with new_str
		if (new_filename.substr(i, str.length()) == str)
			new_filename.replace(new_filename.begin()+i, new_filename.begin() + i + str.length(),
			new_str.begin(), new_str.end());
	}
}

void FileInfo::renameFile()
{
	string new_filepath = file_path;
	new_filepath = directory + new_filename + "." + extension;

	if (rename(file_path.c_str(), new_filepath.c_str()) == 0)
	{
		old_filename = new_filename;
		file_path = new_filepath;
		new_filename = "";
		updateInfo();
	}
	else
	{
		printf("ERROR: Could Not Rename File to %s\n", new_filepath.c_str());
	}
}

void FileInfo::display() const
{
	printf("\n========================================");
	printf("\nOld Filename:\t%s", old_filename.c_str());
	printf("\nFile Path:\t%s", file_path.c_str());
	printf("\nDirectory:\t%s", directory.c_str());
	printf("\nNew Filename:\t%s", new_filename.c_str());
	printf("\nExtension:\t%s", extension.c_str());
	char buffer [30];
	struct tm* timeinfo;

	timeinfo = localtime(&create_time);
	strftime (buffer, 30, "%c", timeinfo);
	printf("\nCreate Date:\t%s", buffer);

	timeinfo = localtime(&last_mod_time);
	strftime (buffer, 30, "%c", timeinfo);
	printf("\nLast Modified Date:\t%s", buffer);

	timeinfo = localtime(&last_access_time);
	strftime (buffer, 30, "%c", timeinfo);
	printf("\nLast Accessed Date:\t%s", buffer);

	printf("\n-- USER FILE INFO ----------------------");
	for (int i = 0; i < user_file_info[0].size(); i++)
		printf("\n%s\t\t%s", user_file_info[0][i].c_str(), user_file_info[1][i].c_str());
	printf("\n========================================\n");
}

void FileInfo::clear()
{
	user_file_info[0].clear();
	user_file_info[1].clear();
	user_file_info.clear();
}