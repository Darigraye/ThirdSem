#include <iostream>

#include "Interface.h"

using std::cin;
using std::cout;
using std::endl;

void Interface::menu() {
	int mode;

	try {
		do {
			cout << endl;

			for (const auto& current : m_consoleMsgs) {
				cout << current;
			}

			cout << endl;
			cin >> mode;

			if (mode < minModeMenu || mode > maxModeMenu) {
				cout << "Oooops! You input incorrect mode\n";
				continue;
			}

			switch (static_cast<Mode>(mode)) {
			case Mode::EXIT:
				break;
			case Mode::DEFAULT_INIT: {
				delete m_manager;
				m_manager = new FolderManager;
				break;
			}
			case Mode::INIT_ONE_FOLD: {
				string name_1;

				cout << "Input name folder:\n";
				cin >> name_1;

				int number;
				cout << "Number files: ";
				cin >> number;

				string name_2;
				table content;
				for (int i = 0; i < number; ++i) {
					cin >> name_2;

					content.insert_element(element_of_table(i, name_2));
				}

				Folder folder;
				folder.m_name = name_1;
				folder.m_content = content;

				delete m_manager;
				m_manager = new FolderManager(folder);
				break;
			}

			case Mode::INIT_NAME_FOLD: {
				string name_1;

				cout << "Input name folder:\n";
				cin >> name_1;

				delete m_manager;
				m_manager = new FolderManager(name_1, { "HelloWorld.c", "text.txt", "Papka_1" });
				break;
			}
			case Mode::GET_SIZE: {
				cout << m_manager->getSize();
				break;
			}
			case Mode::GET_CAPACITY: {
				cout << m_manager->getCapacity();
				break;
			}
			case Mode::GET_CONTENT: {
				string name_1;
				cout << "Input name folder: \n";
				cin >> name_1;

				cout << m_manager->getContent(name_1);
				break;
			}
			case Mode::ADD_FOLDER: {
				string name_1;
				cout << "Input name folder: ";
				cin >> name_1;

				int number;
				cout << "Number files: ";
				cin >> number;

				string name_2;
				table content;
				for (int i = 0; i < number; ++i) {
					cin >> name_2;

					content.insert_element(element_of_table(i, name_2));
				}

				Folder folder;
				folder.m_name = name_1;
				folder.m_content = content;

				m_manager->addFolder(folder);
				break;
			}
			case Mode::ADD_FOLDER_NAME: {
				string name_1;
				cout << "Input name folder: ";
				cin >> name_1;

				m_manager->addFolder(name_1, { "OOO", "Test.txt", "NotTest.cpp" });
				break;
			}
			case Mode::CHANGE_CONTENT: {
				string name_1;
				cout << "Input name folder: ";
				cin >> name_1;

				m_manager->changeContent(name_1, { "OOO", "Test.txt", "NotTest.cpp" });
				break;
			}
			case Mode::ADD_FILE: {
				string name_1;
				cout << "Input name folder: ";
				cin >> name_1;

				string name_2;
				cout << "Input name file: ";
				cin >> name_2;

				m_manager->addFile(name_1, name_2);
				break;
			}
			case Mode::REMOVE_FILE: {
				string name_1;
				cout << "Input name folder: ";
				cin >> name_1;

				string name_2;
				cout << "Input name file: ";
				cin >> name_2;

				m_manager->removeFile(name_1, name_2);
				break;
			}
			case Mode::MOVE_FILE: {
				string name_1;
				cout << "Input name folder out: ";
				cin >> name_1;

				string name_2;
				cout << "Input name folder input: ";
				cin >> name_2;

				string name_3;
				cout << "Input name file: ";
				cin >> name_3;

				m_manager->moveFile(name_1, name_2, name_3);
				break;
			}
			case Mode::OUT_MANAGER: {
				cout << (*m_manager);
				break;
			}
			default:
				cout << "Oooops! You input incorrect value\n";
				break;
			}
		} while (mode != 0);
	}
	catch (const std::exception& exc) {
		cout << exc.what();
	}

	
}
