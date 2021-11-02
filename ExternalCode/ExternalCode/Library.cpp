#include "library.h"
#include <algorithm>

//Реализация функций ввода:

template<typename T>

int getNum(T& a) {
    while (!(std::cin >> a)) {
        if (std::cin.eof())
            throw std::runtime_error("EOF");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверно! Повторите, пожалуйста, ввод!" << std::endl;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 1;
}

std::string get_str() {
    std::string name;
    std::cout << "Введите текстовую строку: ";
    std::getline(std::cin, name);
    if (std::cin.eof()) {
        throw std::runtime_error("EOF");
    }
    return name;
}

//Реализация конструкторов/методов работы с элементами таблицы:

element_of_table::element_of_table() noexcept {
    key = 0;
    name = "0";
}

element_of_table::element_of_table(int k, std::string n) noexcept {
    name = std::move(n);
    key = k;
}

element_of_table::element_of_table(const element_of_table& other) noexcept {
    name = other.name;
    key = other.key;
}

element_of_table::element_of_table(element_of_table&& other) noexcept {
    name = std::move(other.name);
    key = other.key;
}

element_of_table& element_of_table::operator = (element_of_table&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        key = other.key;
    }
    return *this;
}

element_of_table& element_of_table::operator = (const element_of_table& other) noexcept {
    if (this != &other) {
        name = other.name;
        key = other.key;
    }
    return *this;
}

std::string element_of_table::set_name(std::string n) noexcept {
    name = std::move(n);
    return name;
}

int element_of_table::set_key(int k) noexcept {
    key = k;
    return key;
}

//Реализация конструкторов/методов работы с таблицей:

table& table::realloc() {
    table tab(*this);
    delete[] elements;
    elements = new element_of_table[size_of_table * 2]{};
    size_of_table *= 2;
    for (int i = 0; i < current_size_of_table; ++i) {
        elements[i].set_key(tab.elements[i].get_key());
        elements[i].set_name(tab.elements[i].get_name());
    }
    return *this;
}

table::table() noexcept {//Инициализирующий конструктор(по умолчанию) 1 для таблицы
    current_size_of_table = 0;
    size_of_table = 10;
    elements = new element_of_table[size_of_table]{};
}

table::table(element_of_table* initialized_array, int size_of_array) noexcept {//Инициализирующий конструктор 2 для таблицы
    elements = new element_of_table[size_of_array * 2];
    for (int i = 0; i < size_of_array; ++i) {
        elements[i].set_key(initialized_array[i].get_key());
        elements[i].set_name(initialized_array[i].get_name());
    }
    current_size_of_table = size_of_array;
    size_of_table = size_of_array * 2;
}

table::table(const table& other) noexcept {
    elements = new element_of_table[other.size_of_table];
    for (int i = 0; i < other.current_size_of_table; ++i) {
        elements[i].set_key(other.elements[i].get_key());
        elements[i].set_name(other.elements[i].get_name());
    }
    current_size_of_table = other.current_size_of_table;
    size_of_table = other.size_of_table;
}

table::table(table&& other) noexcept {
    elements = other.elements;
    other.elements = nullptr;
    current_size_of_table = other.current_size_of_table;
    size_of_table = other.size_of_table;
}

table& table::operator = (const table& other) noexcept {
    if (this != &other) {
        delete[] elements;
        elements = new element_of_table[other.size_of_table];
        for (int i = 0; i < other.current_size_of_table; ++i) {
            elements[i].set_key(other.elements[i].get_key());
            elements[i].set_name(other.elements[i].get_name());
        }
        current_size_of_table = other.current_size_of_table;
        size_of_table = other.size_of_table;
    }
    return *this;
}

table& table::operator = (table&& other) noexcept {
    if (this != &other) {
        delete[] elements;
        elements = other.elements;
        other.elements = nullptr;
        size_of_table = other.size_of_table;
        current_size_of_table = other.current_size_of_table;
    }
    return *this;
}

table& table::operator += (const element_of_table& elem) {
    insert_element(elem);
    return *this;
}

const element_of_table& table::operator [] (int key) const {
    int index = -1;
    return find_element(key, index);
}

std::ostream& operator << (std::ostream& c, const table& tab) noexcept {
    for (int i = 0; i < tab.get_current_size_of_table(); ++i) {
        c << "Ключ: ";
        c.width(9); c << std::left << tab.get_elements_at_index(i).get_key();
        c << "Информация: " << tab.get_elements_at_index(i).get_name() << std::endl;
    }
    return c;
}

std::istream& operator >> (std::istream& s, element_of_table& element) {
    std::cout << "Введите ключ:";
    while (!(s >> element.key)) {
        if (s.eof())
            throw std::runtime_error("EOF");
        s.clear();
        s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверно! Повторите, пожалуйста, ввод!" << std::endl;
    }
    s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name;
    std::cout << "Введите текстовую строку: ";
    std::getline(s, element.name);

    if (s.eof()) {
        throw std::runtime_error("EOF");
    }
    return s;
}

int table::get_current_size_of_table()const noexcept {
    return current_size_of_table;
}

int table::get_size_of_table()const noexcept {
    return size_of_table;
}

const element_of_table* table::get_elements() const {
    return elements;
}

element_of_table table::get_elements_at_index(int index) const {
    if (index < 0 || index >= current_size_of_table) {
        throw std::out_of_range("Указан индекс, в котором элементы таблицы не определены");
    }
    return elements[index];
}

std::ostream& table::print_table(std::ostream& s) const noexcept {
    for (int i = 0; i < current_size_of_table; ++i) {
        s << "Ключ: ";
        s.width(9); std::cout << std::left << elements[i].get_key();
        s << "Информация: " << elements[i].get_name() << std::endl;
    }
    return s;
}

const element_of_table& table::find_element(int key, int& index_delete_elem) const {//Поиск элемента таблицы по введенному ключу
    int begin_of_table = 0, end_of_table = current_size_of_table - 1;
    while (begin_of_table <= end_of_table) {
        int middle_element = (begin_of_table + end_of_table) / 2;
        if (elements[middle_element].get_key() == key) {
            index_delete_elem = middle_element;
            return elements[middle_element];
        }
        (elements[middle_element].get_key() > key) ? (end_of_table = middle_element - 1) : (begin_of_table = middle_element + 1);
    }
    throw std::runtime_error("По введенному значению ключа ничего не найдено");
}

std::string table::find_information(int key) const {//Поиск информации в таблице по введенному ключу
    int i = -1;
    find_element(key, i);
    return elements[i].get_name();
}

std::string table::changing_information(int key, std::string new_name) {
    int index = -1;
    find_element(key, index);
    if (!new_name.empty()) {
        elements[index].set_name(new_name);
    }
    return new_name;
}

int table::delete_element(int key) {
    int index = -1;
    find_element(key, index);
    if (index != -1) {
        while (index < current_size_of_table - 1) {
            swap(index, index + 1);
            index += 1;
        }
        current_size_of_table -= 1;
    }
    return 1;
}

element_of_table table::enter_from_the_input_stream() const {
    int key;
    getNum<int>(key);
    std::string new_name = std::move(get_str());
    element_of_table elem(key, new_name);
    return elem;
}

int table::insert_element(const element_of_table& elem) {
    try {
        int j = -1;
        find_element(elem.get_key(), j);
    }
    catch (const std::runtime_error& a) {
        if (current_size_of_table >= size_of_table) {
            realloc();
        }
        int i = current_size_of_table - 1;
        while (i >= 0 && elements[i].get_key() > elem.get_key()) {
            swap(i, i + 1);
            i -= 1;
        }
        elements[i + 1].set_name(elem.get_name());
        elements[i + 1].set_key(elem.get_key());
        current_size_of_table += 1;
        return 1;//Элемент успешно добавлен
    }
    throw std::runtime_error("Дублирование ключей");
}

void table::swap(int i, int j) {
    element_of_table elem(elements[j]);
    elements[j].set_name(elements[i].get_name());
    elements[j].set_key(elements[i].get_key());
    elements[i].set_name(elem.get_name());
    elements[i].set_key(elem.get_key());
}