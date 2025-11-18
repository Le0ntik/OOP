#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum BookType {
    FICTION,    // Художественная
    TECHNICAL   // Техническая
};

class Book {
public:
    string author;
    string title;
    BookType type;

    Book(string a, string t, BookType tp) {
        if (a.empty() || t.empty()) {
            throw invalid_argument("Автор и название не могут быть пустыми!");
        }
        author = a;
        title = t;
        type = tp;
    }
};

class Library {
public:
    vector<Book> books;

    void addBook(string author, string title, BookType type) {
        try {
            books.push_back(Book(author, title, type));
            cout << "Добавлена: \"" << title << "\" - " << author << endl;
        }
        catch (invalid_argument& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }

    // Процедура с использованием switch
    void countWithSwitch() {
        int fiction = 0, technical = 0;

        for (int i = 0; i < books.size(); i++) {
            switch (books[i].type) {
                case FICTION:
                    fiction++;
                    break;
                case TECHNICAL:
                    technical++;
                    break;
            }
        }

        cout << "\n=== С использованием switch ===" << endl;
        cout << "Художественных книг: " << fiction << endl;
        cout << "Технических книг: " << technical << endl;
    }

    // Процедура без использования switch
    void countWithoutSwitch() {
        int fiction = 0, technical = 0;

        for (int i = 0; i < books.size(); i++) {
            if (books[i].type == FICTION)
                fiction++;
            else
                technical++;
        }

        cout << "\n=== Без использования switch ===" << endl;
        cout << "Художественных книг: " << fiction << endl;
        cout << "Технических книг: " << technical << endl;
    }

    void showAll() {
        cout << "\n=== Книги в библиотеке ===" << endl;
        for (int i = 0; i < books.size(); i++) {
            cout << i + 1 << ". \"" << books[i].title << "\" - " << books[i].author;
            cout << (books[i].type == FICTION ? " [Художественная]" : " [Техническая]") << endl;
        }
    }
};

int main() {
    system("chcp 65001 > nul"); // для отображения кириллицы

    Library lib;

    // Наполнение библиотеки
    cout << "=== Наполнение библиотеки ===" << endl;
    lib.addBook("Михаил Булгаков", "Мастер и Маргарита", FICTION);
    lib.addBook("Рэй Брэдбери", "451 градус по Фаренгейту", FICTION);
    lib.addBook("Джоан Роулинг", "Гарри Поттер и философский камень", FICTION);
    lib.addBook("Эндрю Хант, Дэвид Томас", "Программист-прагматик", TECHNICAL);
    lib.addBook("Дональд Кнут", "Искусство программирования", TECHNICAL);
    lib.addBook("Эндрю Таненбаум", "Современные операционные системы", TECHNICAL);

    // Попытки добавить ошибочные книги
    cout << "\n=== Проверка на ошибки ===" << endl;
    lib.addBook("", "Книга без автора", FICTION);
    lib.addBook("Книга без названия", "", TECHNICAL);

    lib.showAll();
    lib.countWithSwitch();
    lib.countWithoutSwitch();

    return 0;
}