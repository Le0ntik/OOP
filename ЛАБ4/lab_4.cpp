#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

class ProgramError {
protected:
    string message;
public:
    ProgramError(const string& msg) : message(msg) {}
    virtual void print() const {
        cout << "Ошибка: " << message << endl;
    }
};

class MemoryError : public ProgramError {
public:
    MemoryError() : ProgramError("Недостаточно памяти") {}
};

class IOError : public ProgramError {
public:
    IOError() : ProgramError("Ошибка ввода/вывода") {}
};

class FileReadError : public IOError {
public:
    FileReadError() : IOError() {
        message = "Ошибка чтения файла";
    }
};

class FileWriteError : public IOError {
public:
    FileWriteError() : IOError() {
        message = "Ошибка записи файла";
    }
};

template <class T>
class PointerArray {
private:
    T** data;
    size_t size;
    static const size_t MAX_SIZE = 1000;

public:
    PointerArray(size_t n) : size(n) {

        if (n > MAX_SIZE)
            throw length_error("Размер массива слишком большой");

        data = new T*[size];
        for (size_t i = 0; i < size; i++)
            data[i] = nullptr;
    }

    ~PointerArray() {
        for (size_t i = 0; i < size; i++)
            delete data[i];
        delete[] data;
    }

    T*& operator[](size_t index) {
        if (index >= size)
            throw MemoryError();
        return data[index];
    }

    size_t getSize() const { return size; }
};

class Student {
private:
    string name;
    int age;
    double grade;

public:
    Student(const string& name, int age, double grade)
            : name(name), age(age), grade(grade) {}

    void print() const {
        cout << "Студент: " << name
             << ", Возраст: " << age
             << ", Средний балл: " << grade << endl;
    }
};

int main() {
    system("chcp 65001 > nul");

    // 1. Работа произвольного класса (Student)
    try {
        PointerArray<Student> arr(3);
        arr[0] = new Student("Данил", 19, 44);
        arr[1] = new Student("Семен", 19, 45);
        arr[2] = new Student("Саша", 19, 45);

        cout << "Вывод класса Student:\n";
        for (size_t i = 0; i < arr.getSize(); i++)
            arr[i]->print();
    }
    catch (ProgramError& e) {
        e.print();
    }

    // 2. Массив int
    try {
        PointerArray<int> arrInt(3);
        arrInt[0] = new int(100);
        arrInt[1] = new int(200);
        arrInt[2] = new int(300);

        cout << "\nВывод int:\n";
        for (size_t i = 0; i < arrInt.getSize(); i++)
            cout << *arrInt[i] << endl;
    }
    catch (ProgramError& e) {
        e.print();
    }

    // 3. Массив String
    try {
        PointerArray<string> arrStr(2);
        arrStr[0] = new string("Привет");
        arrStr[1] = new string("Мир");

        cout << "\nВывод string:\n";
        for (size_t i = 0; i < arrStr.getSize(); i++)
            cout << *arrStr[i] << endl;
    }
    catch (ProgramError& e) {
        e.print();
    }


    // 4. Ошибка length_error
    try {
        cout << "\nПробуем создать слишком большой массив...\n";
        PointerArray<int> bigArr(5000000);
    }
    catch (const length_error& e) {
        cout << "Исключение length_error: " << e.what() << endl;
    }

    cout << "\n";
    // 5. Ошибка чтения файла
    try {
        ifstream f("нет_такого_файла.txt");
        if (!f)
            throw FileReadError();
    }
    catch (ProgramError& e) {
        e.print();
    }

    cout << "\n";
    // 6. Ошибка записи файла
    try {
        ofstream out("C://Windows//system//locked_file.txt");
        if (!out)
            throw FileWriteError();
    }
    catch (ProgramError& e) {
        e.print();
    }

    return 0;
}