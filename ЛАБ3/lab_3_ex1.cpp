#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Detail {
protected:
    string name;
    int id;
    static int nextId; // Статический счётчик для автоматической генерации ID

    Detail(const string& n) : name(n), id(nextId++) {
        cout << "Конструктор Detail: " << name << " (id: " << id << ")" << endl;
    }

public:
    virtual ~Detail() {
        cout << "Деструктор Detail: " << name << " (id: " << id << ")" << endl;
    }

    virtual void show() const {
        cout << "Деталь: " << name << ", ID: " << id << endl;
    }

    virtual string getType() const {
        return "Detail";
    }

    template<typename T>
    friend void addToStorage(vector<unique_ptr<Detail>>& storage,
                             const string& name, int extra);
};

// Инициализация статического счётчика
int Detail::nextId = 1;

class Assembly : public Detail {
protected:
    int partsCount;

    Assembly(const string& n, int parts)
            : Detail(n), partsCount(parts) {
        cout << "Конструктор Assembly: " << name << endl;
    }

public:
    ~Assembly() override {
        cout << "Деструктор Assembly: " << name << endl;
    }

    void show() const override {
        cout << "Сборка: " << name << ", ID: " << id
                  << ", Количество деталей: " << partsCount << endl;
    }

    string getType() const override {
        return "Assembly";
    }

    template<typename T>
    friend void addToStorage(vector<unique_ptr<Detail>>& storage,
                             const string& name, int extra);
};

template<typename T>
void addToStorage(vector<unique_ptr<Detail>>& storage,
                  const string& name, int extra) {
    if constexpr (is_same_v<T, Detail>) {
        storage.push_back(unique_ptr<Detail>(new Detail(name)));
    } else if constexpr (is_same_v<T, Assembly>) {
        storage.push_back(unique_ptr<Assembly>(new Assembly(name, extra)));
    }
}

int main() {
    system("chcp 65001 > nul"); // для отображения кириллицы

    vector<unique_ptr<Detail>> storage;

    cout << "--- Создание объектов ---" << endl;

    addToStorage<Detail>(storage, "Болт", 0);
    addToStorage<Detail>(storage, "Гайка", 0);
    addToStorage<Assembly>(storage, "Двигатель", 150);
    addToStorage<Assembly>(storage, "Коробка передач", 89);
    addToStorage<Detail>(storage, "Шайба", 0);
    addToStorage<Assembly>(storage, "Подвеска", 45);

    cout << "\n--- Полиморфизм ---" << endl;

    for (const auto& item : storage) {
        item->show();
    }

    cout << "\n--- Подсчет объектов по типам ---" << endl;
    int detailCount = 0;
    int assemblyCount = 0;


    return 0;
}