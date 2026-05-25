#define _CRT_SECURE_NO_WARNINGS // Щоб компілятор не сварився на С-функції
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <utility> // ОБОВ'ЯЗКОВО ДЛЯ std::move

using namespace std;

// ============================================================================
// ==================== КЛАС Quadrilateral (Чотирикутник) =====================
// ============================================================================

class Quadrilateral {
protected:
    double a, b, c, d;
    char* name;

    void copyName(const char* n) {
        if (n) {
            name = new char[strlen(n) + 1];
            strcpy_s(name, strlen(n) + 1, n); // Безпечна версія для Visual Studio
        }
        else {
            name = new char[14];
            strcpy_s(name, 14, "Quadrilateral");
        }
    }

public:
    Quadrilateral() : a(0), b(0), c(0), d(0), name(nullptr) {
        copyName("Quadrilateral");
        cout << "[Quadrilateral] Конструктор за замовчуванням\n";
    }

    Quadrilateral(double a, double b, double c, double d, const char* n = "Quadrilateral")
        : a(a), b(b), c(c), d(d), name(nullptr) {
        copyName(n);
        cout << "[Quadrilateral] Конструктор з параметрами\n";
    }

    // Конструктор копіювання
    Quadrilateral(const Quadrilateral& q)
        : a(q.a), b(q.b), c(q.c), d(q.d), name(nullptr) {
        copyName(q.name);
        cout << "[Quadrilateral] Конструктор копіювання\n";
    }

    // Конструктор переміщення
    Quadrilateral(Quadrilateral&& q) noexcept
        : a(q.a), b(q.b), c(q.c), d(q.d), name(q.name) {
        q.name = nullptr;
        q.a = q.b = q.c = q.d = 0;
        cout << "[Quadrilateral] Конструктор переміщення\n";
    }

    virtual ~Quadrilateral() {
        cout << "[Quadrilateral] Деструктор\n";
        delete[] name;
    }

    // Оператор присвоєння (копіювання)
    Quadrilateral& operator=(const Quadrilateral& q) {
        if (this != &q) {
            a = q.a; b = q.b; c = q.c; d = q.d;
            delete[] name;
            name = nullptr;
            copyName(q.name);
        }
        cout << "[Quadrilateral] operator= (копіювання)\n";
        return *this;
    }

    // Оператор присвоєння (переміщення)
    Quadrilateral& operator=(Quadrilateral&& q) noexcept {
        if (this != &q) {
            a = q.a; b = q.b; c = q.c; d = q.d;
            delete[] name;
            name = q.name;
            q.name = nullptr;
            q.a = q.b = q.c = q.d = 0;
        }
        cout << "[Quadrilateral] operator= (переміщення)\n";
        return *this;
    }

    virtual double perimeter() const {
        return a + b + c + d;
    }

    virtual void print() const {
        cout << "Фігура: " << (name ? name : "?")
            << " | Сторони: a=" << a << " b=" << b << " c=" << c << " d=" << d
            << " | Периметр: " << perimeter() << "\n";
    }

    // ДРУЖНІ ОПЕРАТОРИ (Реалізовані прямо всередині глобального класу)
    friend ostream& operator<<(ostream& os, const Quadrilateral& q) {
        os << (q.name ? q.name : "Quadrilateral") << "\n"
            << q.a << "\n" << q.b << "\n" << q.c << "\n" << q.d << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Quadrilateral& q) {
        char buf[256];
        if (is >> buf) {
            delete[] q.name;
            q.name = nullptr;
            q.copyName(buf);
            is >> q.a >> q.b >> q.c >> q.d;
        }
        return is;
    }
}; // <--- КЛАС ЧОТИРИКУТНИК ЗАКРИТО ПРАВИЛЬНО!

// ============================================================================
// ==================== КЛАС Square (Квадрат) =================================
// ============================================================================

class Square : public Quadrilateral {
private:
    char* color;

    void copyColor(const char* c) {
        if (c) {
            color = new char[strlen(c) + 1];
            strcpy_s(color, strlen(c) + 1, c);
        }
        else {
            color = new char[6];
            strcpy_s(color, 6, "black");
        }
    }

public:
    Square() : Quadrilateral(0, 0, 0, 0, "Square"), color(nullptr) {
        copyColor("black");
        cout << "[Square] Конструктор за замовчуванням\n";
    }

    Square(double side, const char* col = "black")
        : Quadrilateral(side, side, side, side, "Square"), color(nullptr) {
        copyColor(col);
        cout << "[Square] Конструктор з параметрами\n";
    }

    // Конструктор копіювання
    Square(const Square& s) : Quadrilateral(s), color(nullptr) {
        copyColor(s.color);
        cout << "[Square] Конструктор копіювання\n";
    }

    // Конструктор переміщення
    Square(Square&& s) noexcept : Quadrilateral(move(s)), color(s.color) {
        s.color = nullptr;
        cout << "[Square] Конструктор переміщення\n";
    }

    ~Square() {
        cout << "[Square] Деструктор\n";
        delete[] color;
    }

    // Оператор присвоєння (копіювання)
    Square& operator=(const Square& s) {
        if (this != &s) {
            this->Quadrilateral::operator=(s);
            delete[] color;
            color = nullptr;
            copyColor(s.color);
        }
        cout << "[Square] operator= (копіювання)\n";
        return *this;
    }

    // Оператор присвоєння (переміщення)
    Square& operator=(Square&& s) noexcept {
        if (this != &s) {
            this->Quadrilateral::operator=(move(s));
            delete[] color;
            color = s.color;
            s.color = nullptr;
        }
        cout << "[Square] operator= (переміщення)\n";
        return *this;
    }

    double area() const {
        return a * a;
    }

    void print() const override {
        cout << "Квадрат: сторона=" << a
            << " | Периметр=" << perimeter()
            << " | Площа=" << area()
            << " | Колір=" << (color ? color : "?") << "\n";
    }

    friend ostream& operator<<(ostream& os, const Square& s) {
        os << static_cast<const Quadrilateral&>(s);
        os << (s.color ? s.color : "black") << "\n";
        return os;
    }

    friend istream& operator>>(istream& is, Square& s) {
        double side;
        char buf[64];
        if (is >> side >> buf) {
            s.a = s.b = s.c = s.d = side;
            delete[] s.color;
            s.color = nullptr;
            s.copyColor(buf);
        }
        return is;
    }

    void setColor(const char* col) {
        delete[] color;
        color = nullptr;
        copyColor(col);
    }

    void setSide(double side) {
        a = b = c = d = side;
    }
}; 
//  ФУНКЦІЯ ЗАПУСКУ ТЕСТУ (ЗАМІСТЬ MAIN) 
void runTask3_9() {
    cout << "\n=== Задача 3.9: Ієрархія Quadrilateral -> Square ===\n";

    // --- Інтерактивне введення даних через ВАШ оператор >> ---
    Square userSquare;
    cout << "Введіть дані Квадрата через пробіл [Сторона] [Колір]\n(наприклад: 12.5 green): ";
    cin >> userSquare;

    cout << "\n[Результат] Ваш квадрат (виведення через метод print()):\n";
    userSquare.print();

    cout << "\n[Результат] Ваш квадрат (через перевизначений оператор <<):\n";
    cout << userSquare;

    // --- Тест переміщення (Move-семантика) ---
    cout << "\n--- Тестування конструктора переміщення (Move) ---\n";
    Square movedSquare(move(userSquare));
    cout << "Новий об'єкт movedSquare (куди перемістили): ";
    movedSquare.print();

    // Використовуємо вказівник, щоб обійти попередження аналізатора Visual Studio
    Square* ptr = &userSquare;
    cout << "Старий userSquare після переміщення: ";
    ptr->print();

    cout << "\n==================================================\n";
}