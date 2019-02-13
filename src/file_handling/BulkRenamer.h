#include "FileInfo.h"
#include <cmath>
#include <iostream>
class BulkRenamer
{
	private:
		std::vector<FileInfo*> file_list;	// A list of file info objects
		string new_format;					// A string representing the new format for new filenames
	
	public:
		// enum used for formatting date and time into a string, in convertDateTime()
		enum DateTimeFormat {dd_mm_yyyy, mm_dd_yyyy, dd_month_yyyy, month_dd_yyyy, 
				mm_dd, dd_mm, month, month_dd, dd_month, yyyy, dd_mon_yyyy,
				mon_dd_yyyy, mon, mon_dd, dd_mon};

	public:
		BulkRenamer();
		/*=====================================================================
		Default constructor for bulk renamer. Sets new_format to ""
		=====================================================================*/

		BulkRenamer(string_vec fileList, string new_format = "");
		/*=====================================================================
		Adds all strings in fileList to file_list and sets new_format to
		parameter, "" by default 
		=====================================================================*/

		void loadNewFiles(string_vec filePaths);
		/*=====================================================================
		Constructs FileInfo objects for each file at filePaths, adds to
		file_list
		=====================================================================*/

		bool loadUserInfo(string format);
		/*=====================================================================
		Populates user_file_info for each file in file_list
		=====================================================================*/

		bool genNewFilenames();
		/*=====================================================================
		Sets the new_filename for each fileInfo object, according to the
		new_format string
		Program Wide Info Tag Key:
		===========================================================
		§ext§: Lower Case Extension
		§EXT§: Upper Case Extension
		§index§: Index of file in file_list
		§0index§: Index of file in file_list with leading zeros
		DATE FORMATTING (MAY CHANGE)
		dd_mm_yyyy
		mm_dd_yyyy
		dd_mon_yyyy
		dd_month_yyyy
		mon_dd_yyyy
		month_dd_yyyy
		mm_dd
		dd_mm
		mon
		month
		mon_dd
		month_dd
		dd_mon
		dd_month
		yyyy
		§create [datetime format]§: File Date Creation
		§modified [datetime format]§: Last Modified Date
		§accessed [datetime format]§: Last Accessed Date
		§current [datetime format]§: Current Date
		=====================================================================*/

		bool renameFiles();
		/*=====================================================================
		Renames all files in file_list using each FileInfo object's
		new_filename member.
		=====================================================================*/

		string convertDateTime(BulkRenamer::DateTimeFormat dt_format, time_t rawtime) const;
		/*=====================================================================
		Converts the time in seconds from epoch into a variety of string
		representations using the Datetime Options enum
		=====================================================================*/

//======MUTATORS====================================================================================
//=================================================================================================
		void setFileList(string_vec filePaths);
		/*=====================================================================
		Empties file_list and adds all strings in filePaths
		=====================================================================*/

		void addFile(FileInfo& newfile, int index = 0);
		/*=====================================================================
		Adds a file to the file list, adds to start by default.
		=====================================================================*/

		void addFile(string newfilepath, int index = 0);
		/*=====================================================================
		Adds a file to the file list, adds to start by default.
		=====================================================================*/

		void pushFile(FileInfo& newfile);
		/*=====================================================================
		Pushes a file to the end of the file list
		=====================================================================*/

		void pushFile(string newfilepath);
		/*=====================================================================
		Pushes a file to the file list
		=====================================================================*/

		void moveFile(int index, int newIndex);
		/*=====================================================================
		Move the FileInfo object at index to newIndex in file_list
		=====================================================================*/

		void removeFile(int index);
		/*=====================================================================
		Removes the FileInfo object at index in file_list
		=====================================================================*/

		void setFormat(string newFormat) {new_format = newFormat;}
		/*=====================================================================
		Sets new_format to parameter
		=====================================================================*/

//======ACCESSORS==================================================================================
//=================================================================================================
		FileInfo getFile(int index) const {return *(file_list[index]);}
		/*=====================================================================
		Returns the file at index in file_list
		=====================================================================*/

		string getFormat() const {return new_format;}
		/*=====================================================================
		Returns the new_format string
		=====================================================================*/

		void display() const;
		/*=====================================================================
		Displays the content of BulkRenamer in console
		=====================================================================*/
};