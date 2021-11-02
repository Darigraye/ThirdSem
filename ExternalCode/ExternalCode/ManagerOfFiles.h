#pragma once

#include <string>
#include <vector>
#include <initializer_list>

#include "Library.h"

using std::string;
using std::vector;
using std::initializer_list;

class FolderManager;

struct Folder {
	string m_name = "Unknown folder";
	table m_content;																// files in this folder

	Folder() = default;
	Folder(const string& name) : m_name(name) {	}
	Folder(const string& folderName, const initializer_list<string>& list);

	void convertInitListToContent(const initializer_list<string>& list);			// list names of files
	bool checkDoubledFile(const string& fileName) const noexcept;
	int findKeyFile(const string& fileName) const;

	friend std::ostream& operator<<(std::ostream& out, const Folder& folder);
	friend FolderManager;

private:
	void restateKeys();

};


class FolderManager {
private:
	vector<Folder> m_folders;

	bool nameFolderIsCorrect(const Folder& folder) const noexcept;
	bool checkDoubledFolder(const Folder& folder) const noexcept;
	long long findIndexFolder(const string& folderName) const;

public:
	FolderManager() = default;
	FolderManager(const Folder& folder);
	FolderManager(const string& folderName, const initializer_list<string>& list) 
		: FolderManager(Folder(folderName, list)) {}

	inline size_t getSize() const noexcept { return m_folders.size(); }
	inline size_t getCapacity() const noexcept { return m_folders.capacity(); }
	table getContent(const string& folderName);

	void addFolder(const Folder& folder);
	void addFolder(const string& folderName, const initializer_list<string>& list);
	void changeContent(const string& folderName, const initializer_list<string>& listNewContent);
	void addFile(const string& folderName, const string& fileName);					// to which folder and which file
	void removeFile(const string& folderName, const string& fileName);
	void moveFile(const string& folderNameOut, const string& folderNameIn, const string& fileName);

	~FolderManager() = default;

	friend std::ostream& operator<<(std::ostream& out, const FolderManager& manager);

};