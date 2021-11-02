#include "ManagerOfFiles.h"

#include <exception>
#include <string>
#include <algorithm>

Folder::Folder(const string& folderName, const initializer_list<string>& list) 
	: m_name(folderName) {

	convertInitListToContent(list);
}

std::ostream& operator<<(std::ostream& out, const Folder& folder) {
	out << "Folder name: " << folder.m_name << '\n';
	out << "Files:\n" << folder.m_content;

	return out;	
}

bool FolderManager::nameFolderIsCorrect(const Folder& folder) const noexcept {
	bool flagCorrect = true;

	if (folder.m_name.empty() ||
		folder.m_name == "Unknown folder") {

		flagCorrect = false;
	}

	return flagCorrect;	
}

bool FolderManager::checkDoubledFolder(const Folder& folder) const noexcept {
	bool flagDoubled = false;

	for (const auto& current : m_folders) {
		if (current.m_name == folder.m_name) {
			flagDoubled = true;
			break;
		}
	}

	return flagDoubled;
}

long long FolderManager::findIndexFolder(const string& folderName) const {
	long long findIndex = -1;

	for (size_t current = 0; current < m_folders.size(); ++current) {
		if (folderName == m_folders[current].m_name) {
			findIndex = current;
			break;
		}
	}

	if (findIndex == -1) {
		throw std::invalid_argument("Name of folder not found\n");
	}

	return findIndex;
}

void Folder::convertInitListToContent(const initializer_list<string>& list) {
	int currentKey = 0;

	for (const auto& current : list) {
		m_content.insert_element(element_of_table(currentKey, current));
		++currentKey;
	}
}

int Folder::findKeyFile(const string& fileName) const {
	int foundKey = -1;

	for (int current = 0; current < m_content.get_current_size_of_table(); ++current) {
		if (m_content[current].get_name() == fileName) {
			foundKey = m_content[current].get_key();
			break;
		}
	}

	if (foundKey == -1) {
		throw std::invalid_argument("Name of files not found\n");
	}

	return foundKey;
}

bool Folder::checkDoubledFile(const string& fileName) const noexcept {
	bool flagDoubled = false;

	for (int current = 0; current < m_content.get_current_size_of_table(); ++current) {
		if (m_content[current].get_name() == fileName) {
			flagDoubled = true;
			break;
		}
	}

	return flagDoubled;
}

void Folder::restateKeys() {
	for (size_t current = 0; current < m_content.get_current_size_of_table(); ++current) {
		const_cast<element_of_table*>(m_content.get_elements())[current].set_key(current);
	}
}

FolderManager::FolderManager(const Folder& folder) {
	if (!nameFolderIsCorrect(folder)) {
		throw std::invalid_argument("Incorrect name of folder\n");
	}

	m_folders.push_back(folder);
}

void FolderManager::addFolder(const Folder& folder) {
	if (!nameFolderIsCorrect(folder)) {
		throw std::invalid_argument("Incorrect name of folder\n");
	}

	if (checkDoubledFolder(folder)) {
		throw std::logic_error("Doubled name of folder\n");
	}

	m_folders.push_back(folder);
}

void FolderManager::addFolder(const string& folderName, const initializer_list<string>& list) {
	Folder folder(folderName, list);
	
	addFolder(folder);
}

void FolderManager::changeContent(const string& folderName, 
								  const initializer_list<string>& listNewContent) {

	long long foundIndex = findIndexFolder(folderName);

	table newContent;
	int currentKey(0);

	for (const auto& current : listNewContent) {
		newContent.insert_element(element_of_table(currentKey, current));
		++currentKey;
	}

	m_folders[foundIndex].m_content = newContent;
}

void FolderManager::addFile(const string& folderName, const string& fileName) {
	long long foundFolderIndex = findIndexFolder(folderName);
	
	if (m_folders[foundFolderIndex].checkDoubledFile(fileName)) {
		throw std::logic_error("Doubled name of file\n");
	}

	int key = m_folders[foundFolderIndex].m_content.get_current_size_of_table();
	element_of_table file(key, fileName);

	m_folders[foundFolderIndex].m_content.insert_element(file);
}

void FolderManager::removeFile(const string& folderName, const string& fileName) {
	long long foundFolderIndex = findIndexFolder(folderName);
	int key = m_folders[foundFolderIndex].findKeyFile(fileName);

	m_folders[foundFolderIndex].m_content.delete_element(key);
	m_folders[foundFolderIndex].restateKeys();
}

table FolderManager::getContent(const string& folderName) {
	long long foundIndex = findIndexFolder(folderName);

	return m_folders[foundIndex].m_content;
}

void FolderManager::moveFile(const string& folderNameOut, 
							 const string& folderNameIn, 
							 const string& fileName) {

	long long foundFolderIndexOut = findIndexFolder(folderNameOut);
	long long foundFolderIndexIn = findIndexFolder(folderNameIn);
	int key = m_folders[foundFolderIndexOut].findKeyFile(fileName);

	element_of_table file(m_folders[foundFolderIndexOut].m_content[key]);
	file.set_key(m_folders[foundFolderIndexIn].m_content.get_current_size_of_table());
	m_folders[foundFolderIndexIn].m_content.insert_element(file);

	removeFile(folderNameOut, fileName);
}

std::ostream& operator<<(std::ostream& out, const FolderManager& manager) {
	for (const auto& current : manager.m_folders) {
		out << current << '\n';
	}

	return out;
}