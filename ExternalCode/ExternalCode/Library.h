#ifndef LAB2_LIB_LIBRARY_H
#define LAB2_LIB_LIBRARY_H
#include <iostream>
#include <cstring>
#include <string>

//const int size_of_string=45;

template<typename T>

int getNum(T& a);

std::string get_str();

class element_of_table {
private:
    int key;
    std::string name;
public:
    element_of_table() noexcept;//���������������� �����������(�� ���������) 1 ��� �������� �������

    element_of_table(int k, std::string n) noexcept;//���������������� ����������� 2 ��� �������� �������

    element_of_table(const element_of_table& other) noexcept;//���������� ����������� ��� �������� �������

    element_of_table(element_of_table&& other) noexcept;//����������� ����������� ��� �������� �������

    ~element_of_table() noexcept = default;//���������� ��� �������� �������

    element_of_table& operator = (const element_of_table& other) noexcept;//���������� ��������� ������������ ������������ ��� ��������

    element_of_table& operator = (element_of_table&& other) noexcept;//�������� ������������ ������������ ��� ��������

    friend std::istream& operator >> (std::istream& c, element_of_table& elem);//������������� �������� ������ �����

    int get_key() const noexcept { return key; }//������, ������������ ����, ���������� � �������� �������

    std::string get_name() const noexcept { return name; }//������, ������������ ��������� ������, ���������� � �������� �������

    std::string set_name(std::string n) noexcept;//������, �������� �������� ��������� ������, ���������� � �������� �������

    int set_key(int k) noexcept;//������, �������� �������� �����, ����������� � �������� �������

};

class table {
private:
    element_of_table* elements;
    int current_size_of_table;
    int size_of_table;
private:
    void swap(int i, int j);
    table& realloc();
public:
    table() noexcept;//���������������� �����������(�� ���������) 1 ��� �������

    table(element_of_table* initialized_array, int size_of_array) noexcept;//���������������� ����������� 2 ��� �������

    table(const table& other) noexcept;//���������� ����������� ��� �������

    table(table&& other) noexcept;//����������� ����������� ��� �������

    ~table() noexcept { delete[] elements; }//���������� ��� �������

    table& operator = (const table& other) noexcept;//���������� ��������� ������������ ������������

    table& operator = (table&& other) noexcept;//�������� ������������ ������������ ��� �������

    table& operator += (const element_of_table& elem);//���������� ��������� �����������(������ ������� � �������)

    const element_of_table& operator[](int key) const;//���������� ��������� ���������� ������ (��������� ����� � �������)

    friend std::ostream& operator<<(std::ostream& c, const table& tab) noexcept;//���������� ��������� ������ � �����

    int get_current_size_of_table() const noexcept;//������, ������������ ������� ������ �������

    int get_size_of_table()const noexcept;//������, ������������ ������ �������

    element_of_table get_elements_at_index(int index) const;//������, ������������ ������� ������� �� �������

    const element_of_table* get_elements() const;

    std::ostream& print_table(std::ostream& s) const noexcept;//�����, ��������� �������

    const element_of_table& find_element(int key, int& index_delete_element) const;//�����, ������������ ������� �������, ��������� �� ����������� �����

    std::string changing_information(int key, std::string name);//�����, �������� ���������� �� ���������� �����

    std::string find_information(int key) const;//�����, ������������ ����������, ��������� �� ����������� �����

    int delete_element(int key);//�����, ����������� ��������

    element_of_table enter_from_the_input_stream() const;//�����, ������� ��������� ������ ���� � ���������� �� ������

    int insert_element(const element_of_table& element);//�����, ����������� ������� ��������
};

#endif //LAB2_LIB_LIBRARY_H