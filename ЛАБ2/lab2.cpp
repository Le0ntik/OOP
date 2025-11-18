#include "iostream"
#include "string"

using namespace std;


class sales{
protected:
    float sales_arr[3];

public:
    void getdata(){
        cout << "Продажи за 3 месяца: ";
        for (int i = 0; i < 3; i++){
            cout << i + 1 << " месяц: ";
            cin >> sales_arr[i];
        }
    }

    void putdata() const{
        cout << "Продажи: " << sales_arr[0] << ", "
             << sales_arr[1] << ", " << sales_arr[2] << endl;
    }
};

class Publication{
protected:
    string name;
    float price;

public:
    void getdata(){
        cout << "Название: ";
        if (cin.peek() == '\n') cin.ignore();  // очищаем только если нужно
        getline(cin, name);
        cout << "Цена: ";
        cin >> price;
    }

    void putdata() const{
        cout << "Название: " << name << endl;
        cout << "Цена: " << price << endl;

    }
};

class book : public Publication, public sales{
private:
    int pages;

public:
    void getdata(){
        Publication::getdata();
        cout << "Страниц: ";
        cin >> pages;
        sales::getdata();
    }

    void putdata() const{
        Publication::putdata();
        cout << "Страниц: " << pages << endl;
        sales::putdata();
    }
};

class type : public Publication, public sales{
private:
    int time;

public:
    void getdata(){
        Publication::getdata();
        cout << "Время(мин):";
        cin >> time;
        sales::getdata();
    }

    void putdata() const{
        Publication::putdata();
        cout << "Время: " << time << " мин." << endl;
        sales::putdata();
    }
};


int main(){
    system("chcp 65001 > nul"); // для отображения кириллицы

    cout << "--КНИГА--" << endl;
    book b;
    b.getdata();

    cout << "--РЕЗУЛЬТАТ--" << endl;
    b.putdata();
    cout << "\n";

    cout << "--АУДИО--" << endl;
    type t;
    t.getdata();

    cout << "--РЕЗУЛЬТАТ--" << endl;
    t.putdata();
    cout << "\n";
 }