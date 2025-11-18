#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <cstdlib>

using namespace std;

class Base {
protected:
    string name;
    int id;
    static int nextId;

    Base(const string& n) : name(n), id(nextId++) {
        cout << "   Base создан: " << name << " (id: " << id << ")" << endl;
    }

    // Конструктор копирования
    Base(const Base& other) : name(other.name + "_copy"), id(nextId++) {
        cout << "   Base скопирован: " << name << " (id: " << id << ")" << endl;
    }

public:
    virtual ~Base() {
        cout << "   Base удален: " << name << " (id: " << id << ")" << endl;
    }

    virtual void show() const {
        cout << "Base [" << name << ", ID:" << id << "]";
    }

    virtual string getType() const {
        return "Base";
    }

    virtual unique_ptr<Base> clone() const {
        return unique_ptr<Base>(new Base(*this));
    }

    template<typename T>
    friend void createRandomObjects(vector<unique_ptr<Base>>& storage, int count);

    template<typename T>
    friend void add(vector<unique_ptr<Base>>& storage,
                    const vector<unique_ptr<Base>>& source);
};

int Base::nextId = 1;

// Производный класс
class Derived : public Base {
protected:
    int value;

    Derived(const string& n, int val) : Base(n), value(val) {
        cout << "   Derived создан: " << name << ", value=" << value << endl;
    }

    // Конструктор копирования
    Derived(const Derived& other) : Base(other), value(other.value) {
        cout << "   Derived скопирован: " << name << ", value=" << value << endl;
    }

public:
    ~Derived() override {
        cout << "   Derived удален: " << name << endl;
    }

    void show() const override {
        cout << "Derived [" << name << ", ID:" << id << ", value=" << value << "]";
    }

    string getType() const override {
        return "Derived";
    }

    unique_ptr<Base> clone() const override {
        return unique_ptr<Base>(new Derived(*this));
    }

    template<typename T>
    friend void createRandomObjects(vector<unique_ptr<Base>>& storage, int count);

    template<typename T>
    friend void add(vector<unique_ptr<Base>>& storage,
                    const vector<unique_ptr<Base>>& source);
};

// Функция для случайного создания объектов
template<typename T>
void createRandomObjects(vector<unique_ptr<Base>>& storage, int count) {
    for (int i = 0; i < count; i++) {
        if constexpr (is_same_v<T, Base>) {
            string objName = "Base_" + to_string(i + 1);
            storage.push_back(unique_ptr<Base>(new Base(objName)));
        } else if constexpr (is_same_v<T, Derived>) {
            string objName = "Derived_" + to_string(i + 1);
            int randomValue = rand() % 100 + 1;
            storage.push_back(unique_ptr<Base>(new Derived(objName, randomValue)));
        }
    }
}

// Функция add - добавляет КОПИИ объектов из source в storage
template<typename T>
void add(vector<unique_ptr<Base>>& storage,
         const vector<unique_ptr<Base>>& source) {
    for (const auto& item : source) {
        storage.push_back(item->clone());
    }
}

int main() {
    system("chcp 65001 > nul"); // для отображения кириллицы
    srand(static_cast<unsigned>(time(0)));

    vector<unique_ptr<Base>> commonStorage;

    cout << "ДЕЙСТВИЕ 1: Создание Base объектов" << endl;
    vector<unique_ptr<Base>> baseObjects;
    int baseCount = (rand() % 3 + 1) * 2; // 2, 4 или 6
    cout << "Количество: " << baseCount << " (четное)\n" << endl;
    createRandomObjects<Base>(baseObjects, baseCount);

    cout << "\nДЕЙСТВИЕ 2: Создание Derived объектов" << endl;
    vector<unique_ptr<Base>> derivedObjects;
    int derivedCount = (rand() % 3 + 1) * 2 - 1; // 1, 3 или 5
    cout << "Количество: " << derivedCount << " (нечетное)\n" << endl;
    createRandomObjects<Derived>(derivedObjects, derivedCount);

    cout << "\nКопирование объектов в общее хранилище" << endl;
    add<Base>(commonStorage, baseObjects);
    add<Derived>(commonStorage, derivedObjects);

    cout << "Содержимое общего хранилища" << endl;
    cout << "Всего объектов: " << commonStorage.size() << "\n" << endl;

    for (size_t i = 0; i < commonStorage.size(); i++) {
        cout << i + 1 << ". ";
        commonStorage[i]->show();
        cout << endl;
    }

    cout << endl;

    int baseCount_total = 0;
    int derivedCount_total = 0;

    for (const auto& item : commonStorage) {
        if (item->getType() == "Base") {
            baseCount_total++;
        } else {
            derivedCount_total++;
        }
    }

    cout << "Base объектов: " << baseCount_total << endl;
    cout << "Derived объектов: " << derivedCount_total << endl;
    cout << "Всего: " << commonStorage.size() << endl;

    // Освобождение ресурсов
    cout << "\nОсвобождение ресурсов" << endl;
    cout << "\nОчистка временных хранилищ:" << endl;
    baseObjects.clear();
    derivedObjects.clear();

    cout << "\nОчистка общего хранилища:" << endl;
    commonStorage.clear();


    return 0;
}