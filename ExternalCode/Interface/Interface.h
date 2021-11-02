#pragma once

#include <string>

#include"../ExternalCode/ManagerOfFiles.h"

class Interface {
private:
	static const int minModeMenu = 0;
	static const int maxModeMenu = 13;
	
	FolderManager* m_manager = nullptr;

	enum class Mode {
		EXIT = 0,
		DEFAULT_INIT = 1,
		INIT_ONE_FOLD = 2,
		INIT_NAME_FOLD = 3,
		GET_SIZE = 4,
		GET_CAPACITY = 5,
		GET_CONTENT = 6,
		ADD_FOLDER = 7,
		ADD_FOLDER_NAME = 8,
		CHANGE_CONTENT = 9,
		ADD_FILE = 10,
		REMOVE_FILE = 11,
		MOVE_FILE = 12,
		OUT_MANAGER = 13,
	};

	const std::string m_consoleMsgs[14] = { "0.Exit\n",
										"1.Default init\n",
										"2.Init one card\n",
										"3.Init name folder\n",
										"4.Get size\n",
										"5.Get capacity\n",
										"6.Get content\n",
										"7.Add folder\n",
										"8.Add folder name\n",
										"9.Change content\n",
										"10.Add file\n",
										"11.Remove file\n",
										"12.Move file\n",
										"13.Out to console\n"};

public:
	void menu();
};