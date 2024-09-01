#include <iostream>
#include <cstring>
#include <cassert>

class MyString {
private:
    char* str;
    int length;

    void allocateMemory(int size) {
        str = new char[size + 1];
        length = size;
    }

    void freeMemory() {
        delete[] str;
    }

public:
    static int objectCount;

    MyString() : str(nullptr), length(0) {
        allocateMemory(80);
        str[0] = '\0';
        ++objectCount;
    }

    MyString(int size) : str(nullptr), length(0) {
        assert(size > 0);
        allocateMemory(size);
        str[0] = '\0';
        ++objectCount;
    }

    MyString(const char* initStr) : str(nullptr), length(0) {
        int initLen = std::strlen(initStr);
        allocateMemory(initLen);
        std::strcpy(str, initStr);
        ++objectCount;
    }

    ~MyString() {
        freeMemory();
        --objectCount;
    }

    void input() {
        char buffer[1000];
        std::cin.getline(buffer, sizeof(buffer));
        int newLength = std::strlen(buffer);
        freeMemory();
        allocateMemory(newLength);
        std::strcpy(str, buffer);
    }

    void print() const {
        std::cout << str << std::endl;
    }

    void MyStrcpy(MyString& obj) {
        freeMemory();
        allocateMemory(obj.length);
        std::strcpy(str, obj.str);
    }

    bool MyStrStr(const char* substr) const {
        return std::strstr(str, substr) != nullptr;
    }

    int MyChr(char c) const {
        for (int i = 0; i < length; ++i) {
            if (str[i] == c) {
                return i;
            }
        }
        return -1;
    }

    int MyStrLen() const {
        return length;
    }

    void MyStrCat(const MyString& b) {
        int newLength = length + b.length;
        char* newStr = new char[newLength + 1];
        std::strcpy(newStr, str);
        std::strcat(newStr, b.str);
        freeMemory();
        str = newStr;
        length = newLength;
    }

    void MyDelChr(char c) {
        char* newStr = new char[length + 1];
        int j = 0;
        for (int i = 0; i < length; ++i) {
            if (str[i] != c) {
                newStr[j++] = str[i];
            }
        }
        newStr[j] = '\0';
        freeMemory();
        str = newStr;
        length = j;
    }

    int MyStrCmp(const MyString& b) const {
        int cmp = std::strcmp(str, b.str);
        if (cmp < 0) return -1;
        if (cmp > 0) return 1;
        return 0;
    }

    MyString operator+(const MyString& other) const {
        MyString result(length + other.length);
        std::strcpy(result.str, str);
        std::strcat(result.str, other.str);
        return result;
    }
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            freeMemory();
            allocateMemory(other.length);
            std::strcpy(str, other.str);
        }
        return *this;
    }

    bool operator==(const MyString& other) const {
        return std::strcmp(str, other.str) == 0;
    }

    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }
    char& operator[](int index) {
        assert(index >= 0 && index < length);
        return str[index];
    }

    const char& operator[](int index) const {
        assert(index >= 0 && index < length);
        return str[index];
    }

    static int getObjectCount() {
        return objectCount;
    }
};

int MyString::objectCount = 0;

int main() {
    MyString s1("Hello");
    MyString s2("World");

    std::cout << "Строка 1: ";
    s1.print();
    std::cout << "Строка 2: ";
    s2.print();

    MyString s3 = s1 + s2;
    std::cout << "Объединение строк: ";
    s3.print();

    s3.MyStrCat(s1);
    std::cout << "После конкатенации строки 1: ";
    s3.print();

    s3.MyDelChr('o');
    std::cout << "После удаления символа 'o': ";
    s3.print();

    std::cout << "Поиск подстроки 'Wor': " << (s3.MyStrStr("Wor") ? "Найдено" : "Не найдено") << std::endl;
    std::cout << "Поиск символа 'H': " << s3.MyChr('H') << std::endl;
    std::cout << "Длина строки: " << s3.MyStrLen() << std::endl;

    MyString s4("World");
    std::cout << "Сравнение строк: " << s1.MyStrCmp(s4) << std::endl;

    std::cout << "Общее количество созданных объектов: " << MyString::getObjectCount() << std::endl;

    return 0;
}
