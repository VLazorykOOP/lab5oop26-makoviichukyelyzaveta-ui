#include <iostream>
#include <windows.h>
#include "task1.cpp"  
#include "task2.cpp"  
#include "task3.cpp"

using namespace std;

// Оголошуємо функції з інших файлів, щоб main їх бачив
void runTask1_9();
void runTask2_9();
void runTask3_9();

int main() {
    // Налаштування української локалі
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");

    int choice;
    do {
        cout << "\n==================================================\n";
        cout << "  ЛАБОРАТОРНА РОБОТА №5. СПАДКУВАННЯ ТА КОМПОЗИЦІЯ\n";
        cout << "==================================================\n";
        cout << "1. Запустити Задачу 1.9 (Вікно з меню)\n";
        cout << "2. Запустити Задачу 2.9 (Комп'ютер з монітором)\n";
        cout << "3. Запустити Задачу 3.9 (Чотирикутник і Квадрат)\n";
        cout << "0. Вихід з програми\n";
        cout << "--------------------------------------------------\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        cout << "\n";
        switch (choice) {
        case 1:
            runTask1_9(); // запускає код першої задачі
            break;
        case 2:
            runTask2_9(); // запускає код другої задачі
            break;
        case 3:
            runTask3_9(); // запускає код третьої задачі
            break;
        case 0:
            cout << "Вихід з програми. Лабораторна завершена!\n";
            break;
        default:
            cout << "Некоректний вибір! Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}
