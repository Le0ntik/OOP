#include "iostream"
#include "ctime"
using namespace std;

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "rus");
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    int *arr = new int[n];

    for (int i; i < n; i++)
    {
        arr[i] = rand() % 100;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    cout << "Адрес начала массива: " << arr << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Адрес " << i << " элемента: " << arr + i << ", расстояние в байтах " << i * 4 << endl;
    }
}