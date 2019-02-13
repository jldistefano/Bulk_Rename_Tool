#include <string>
#include <vector>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
typedef std::string string;
typedef std::vector<string> string_vec;

class FileInfo
{
	private:
		string file_path;		// The full file path for this file
		string old_filename;	// The old filename of this file, excluding extension
		string new_filename;	// The new filename of this file, after processing
		string directory;

		string extension;			// The extension of the file, all characters after the last .
		time_t create_time;			// The time of creation of the file, seconds  from epoch
		time_t last_mod_time;		// The time of last modification of the file, seconds  from epoch
		time_t last_access_time;	// The time of last access of the file, seconds  from epoch
		std::vector< string_vec > user_file_info;	// Two Dimensoinal vector for user defined information from filename

	public:
		FileInfo();
		/*=====================================================================
		Default constructor for FileInfo. Sets all string members to "".
		Initializes user_file_info and file_info vectors.
		=====================================================================*/

		FileInfo(string filepath);
		/*=====================================================================
		This populates all members of FileInfo from a given filepath. Sets
		file_path to the given filepath parameter. old_filename is set to the
		string between the last '/' character and last '.' character.
		new_filename is set to "". file_info is loaded using loadInfo().
		=====================================================================*/

		FileInfo(const FileInfo &copy);
		/*=====================================================================
		Copy constructor for FileInfo, sets all string data members equal to 
		eachother sets all time_t data members equal to eachother. Creates a 
		copy of the two dimensional vector
		=====================================================================*/

		~FileInfo();
		/*=====================================================================
		Destructor for FileInfo
		=====================================================================*/

		FileInfo operator=(const FileInfo& copy);
		/*=====================================================================
		Copies all members of copy into parent object
		=====================================================================*/

		bool loadUserInfo(string format);
		/*=====================================================================
		Using a given filename format from parameter, information is extracted
		from filename and stored in user_file_info. format is a string _ as
		"expectedstring/data/expectedstring...". Where plain text represents
		expected text and /data/ represents any user defined information to be
		extracted from filename.
		=====================================================================*/

		bool updateInfo();
		/*=====================================================================
		Gather information about a file, namely the extension, creation
		date/time, last modified date/time, last accessed date/time. Stores
		information in repective variables
		=====================================================================*/

		bool findExtension(string& extension);
		/*=====================================================================
		Extracts the extension of a file from its file_path, stores the string
		between the last '.' character and the end of the string into extension.
		Returns True if successful, False otherwise.
		=====================================================================*/

		bool findCreateTime(time_t& time);
		/*=====================================================================
		Extracts the creation time from the file at file_path, stores result in
		time parameter. Returns True if successful, False otherwise.
		=====================================================================*/

		bool findLastModTime(time_t& time);
		/*=====================================================================
		Extracts the last modified time from the file at file_path, stores 
		result in time parameter. Returns True if successful, False otherwise.
		=====================================================================*/

		bool findLastAccessTime(time_t& time);
		/*=====================================================================
		Extracts the last modified time from the file at file_path, stores 
		result in time parameter. Returns True if successful, False otherwise.
		=====================================================================*/

		bool titleExists(string title) const;
		/*=====================================================================
		Determines if a given title exists in user_file_info, returns true if
		exists, false otherwise
		=====================================================================*/

//=====ACCESSORS===============================================================
//=============================================================================
		bool getInfoTitle(string &title, int index) const;

		bool getInfoElem(string &elem, string title) const;

		std::vector< string_vec > getFileInfo() const {return user_file_info;}

		string getFilePath() const {return file_path;}

		string getOldFilename() const {return old_filename;}

		string getNewFilename() const {return new_filename;}

		string getDirectory() const {return directory;}

		string getExtension() const {return extension;}

		string getExtensionCaps() const;

		time_t getCreateTime() const {return create_time;}

		time_t getLastModTime() const {return last_mod_time;}

		time_t getLastAccessTime() const {return last_access_time;}

		void display() const;

//=====MUTATORS================================================================
//=============================================================================

		void setNewFilename(string newfilename) {new_filename = newfilename;}
		/*=====================================================================
		Sets new_filename to newfilename
		=====================================================================*/

		void setFilePath(string newfilepath) {newfilepath = file_path;}
		/*=====================================================================
		Sets file_path ot newfilepath
		=====================================================================*/

		void setOldFilename(string newfilename) {newfilename = old_filename;}
		/*=====================================================================
		Sets old_filename to newfilename
		=====================================================================*/

		void setDirectory(string newDir) {directory = newDir;}
		/*=====================================================================
		Sets directory to newDir
		=====================================================================*/

		void addDataElem(string title, string elem);
		/*=====================================================================
		Adds a new column to user_file_info, sets element in row 0 to title, 
		sets element in row 1 to elem
		=====================================================================*/

		void replaceStr(string str, string new_str);
		/*=====================================================================
		Replaces any instance of str in old_filename with new_str
		=====================================================================*/

		void renameFile();
		/*=====================================================================
		Saves the file using the new_filename, sets old_filename to new
		filename
		=====================================================================*/

		void clear();
		/*=====================================================================
		Empties user_file_info vector
		=====================================================================*/

};