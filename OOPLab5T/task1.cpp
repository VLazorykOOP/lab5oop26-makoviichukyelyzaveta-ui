// Задача 1.9
// Створити клас вікно, що має координати верхнього лівого й нижнього правого кута, колір тла.
// Визначити конструктори, деструктор і функцію друку.
// Створити похідний клас - вікно з меню, що має поле рядок.
// Визначити конструктори за замовчуванням і з різним числом параметрів, деструктори, функцію друку.
// Визначити функції перепризначення кольору тла та рядка меню.
// Написати програму тестування всіх можливостей цього класу.

#include <iostream>
#include <string>
using namespace std;

// ===================== Клас Window =====================
class Window {
protected:
    int x1, y1; // верхній лівий кут
    int x2, y2; // нижній правий кут
    string bgColor;

public:
    // Конструктор за замовчуванням
    Window() : x1(0), y1(0), x2(100), y2(100), bgColor("white") {
        cout << "[Window] Конструктор за замовчуванням\n";
    }

    // Конструктор з усіма параметрами
    Window(int x1, int y1, int x2, int y2, const string& color)
        : x1(x1), y1(y1), x2(x2), y2(y2), bgColor(color) {
        cout << "[Window] Конструктор з параметрами (" << x1 << "," << y1
            << ") - (" << x2 << "," << y2 << ") колір: " << color << "\n";
    }

    // Конструктор з координатами (без кольору)
    Window(int x1, int y1, int x2, int y2)
        : x1(x1), y1(y1), x2(x2), y2(y2), bgColor("gray") {
        cout << "[Window] Конструктор з координатами, колір за замовчуванням: gray\n";
    }

    // Конструктор копіювання
    Window(const Window& w)
        : x1(w.x1), y1(w.y1), x2(w.x2), y2(w.y2), bgColor(w.bgColor) {
        cout << "[Window] Конструктор копіювання\n";
    }

    virtual ~Window() {
        cout << "[Window] Деструктор\n";
    }

    void setBgColor(const string& color) {
        bgColor = color;
        cout << "[Window] Колір тла змінено на: " << color << "\n";
    }

    string getBgColor() const { return bgColor; }

    virtual void print() const {
        cout << "Window: (" << x1 << "," << y1 << ") - (" << x2 << "," << y2
            << ") | Колір тла: " << bgColor
            << " | Розмір: " << (x2 - x1) << "x" << (y2 - y1) << "\n";
    }

    // Перевірка коректності координат
    bool isValid() const {
        return x2 > x1 && y2 > y1;
    }
};

// ===================== Похідний клас WindowWithMenu =====================
class WindowWithMenu : public Window {
    string menuText;

public:
    // Конструктор за замовчуванням
    WindowWithMenu() : Window(), menuText("Файл | Правка | Довідка") {
        cout << "[WindowWithMenu] Конструктор за замовчуванням\n";
    }

    // Конструктор з усіма параметрами
    WindowWithMenu(int x1, int y1, int x2, int y2, const string& color, const string& menu)
        : Window(x1, y1, x2, y2, color), menuText(menu) {
        cout << "[WindowWithMenu] Конструктор з параметрами, меню: " << menu << "\n";
    }

    // Конструктор без меню (рядок меню порожній)
    WindowWithMenu(int x1, int y1, int x2, int y2, const string& color)
        : Window(x1, y1, x2, y2, color), menuText("") {
        cout << "[WindowWithMenu] Конструктор без рядка меню\n";
    }

    // Конструктор копіювання
    WindowWithMenu(const WindowWithMenu& w)
        : Window(w), menuText(w.menuText) {
        cout << "[WindowWithMenu] Конструктор копіювання\n";
    }

    ~WindowWithMenu() {
        cout << "[WindowWithMenu] Деструктор\n";
    }

    void setMenuText(const string& menu) {
        menuText = menu;
        cout << "[WindowWithMenu] Рядок меню змінено на: " << menu << "\n";
    }

    void setBgColor(const string& color) {
        Window::setBgColor(color);
        cout << "[WindowWithMenu] Колір тла вікна з меню оновлено\n";
    }

    string getMenuText() const { return menuText; }

    void print() const override {
        Window::print();
        cout << "  Меню: [" << (menuText.empty() ? "(порожнє)" : menuText) << "]\n";
    }
};
void runTask1_9() {
    cout << "\n=== ЗАПУЩЕНО: Задача 1.9 (Введення ваших даних) ===\n";

    int x1, y1, x2, y2;
    string color, menuText;

    // Програма просить вас ввести дані з клавіатури
    cout << "Введіть x1 та y1 (через пробіл): "; cin >> x1 >> y1;
    cout << "Введіть x2 та y2 (через пробіл): "; cin >> x2 >> y2;
    cout << "Введіть колір тла вікна: "; cin >> color;
    cin.ignore(); // Очищуємо буфер після введення слова, щоб коректно зчитати рядок з пробілами
    cout << "Введіть пункти меню (наприклад: Файл | Редагувати | Вихід): ";
    getline(cin, menuText);

    cout << "\n[Дія] Створення вікна з вашими параметрами...\n";
    WindowWithMenu userWindow(x1, y1, x2, y2, color, menuText);

    cout << "\n[Результат] Щойно створене вами вікно:\n";
    userWindow.print();

    // Виконуємо над об'єктом дію
    cout << "\n[Дія] Спробуємо змінити колір вашого вікна на інший.\nВведіть новий колір: ";
    cin >> color;
    userWindow.setBgColor(color);

    cout << "\n[Результат] Вікно після зміни кольору:\n";
    userWindow.print();

    cout << "\n====================================================\n";
    cout << "--- Автоматичний тест конструктора копіювання ---\n";
    WindowWithMenu copyWindow(userWindow); // Копіюємо об'єкт користувача
    copyWindow.print();
    cout << "====================================================\n";
}
