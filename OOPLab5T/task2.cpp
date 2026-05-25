// Задача 2.9
// Створити клас жорсткий диск, що має обсяг (Мбайт). Визначити конструктори й метод доступу.
// Створити клас комп'ютер, що містить клас жорсткий диск.
// Додатково є марка (вказівник на рядок), ціна.
// Визначити конструктори й деструктор.
// Визначити private- та public- похідний клас комп'ютерів з монітором (розмір монітора).
// Визначити конструктори, деструктори й функцію друку.

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// ===================== Клас HardDrive (для композиції) =====================
class HardDrive {
    int capacityMB;

public:
    HardDrive() : capacityMB(0) {
        cout << "  [HardDrive] Конструктор за замовчуванням (0 MB)\n";
    }

    explicit HardDrive(int mb) : capacityMB(mb) {
        cout << "  [HardDrive] Конструктор: " << mb << " MB\n";
    }

    HardDrive(const HardDrive& h) : capacityMB(h.capacityMB) {
        cout << "  [HardDrive] Конструктор копіювання: " << capacityMB << " MB\n";
    }

    ~HardDrive() {
        cout << "  [HardDrive] Деструктор (" << capacityMB << " MB)\n";
    }

    int getCapacity() const { return capacityMB; }
    void setCapacity(int mb) { capacityMB = mb; }

    string toString() const {
        return "HDD: " + to_string(capacityMB) + " MB ("
            + to_string(capacityMB / 1024) + " GB)";
    }
};

// ===================== Клас Computer (композиція: містить HardDrive) =====================
class Computer {
protected:
    HardDrive hdd;   // композиція
    char* brand;     // вказівник на рядок
    double price;

    void copyBrand(const char* b) {
        if (b) {
            brand = new char[strlen(b) + 1];
            strcpy_s(brand, strlen(b) + 1, b);
        }
        else {
            brand = new char[8];
            strcpy_s(brand, 8, "Unknown");
        }
    }
public:
    // Конструктор за замовчуванням
    Computer() : hdd(), price(0.0), brand(nullptr) {
        copyBrand("Unknown");
        cout << "[Computer] Конструктор за замовчуванням\n";
    }

    // Конструктор з усіма параметрами
    Computer(const char* b, double p, int hddMB)
        : hdd(hddMB), price(p), brand(nullptr) {
        copyBrand(b);
        cout << "[Computer] Конструктор: " << brand << ", " << price << " грн\n";
    }

    // Конструктор копіювання
    Computer(const Computer& c) : hdd(c.hdd), price(c.price), brand(nullptr) {
        copyBrand(c.brand);
        cout << "[Computer] Конструктор копіювання: " << brand << "\n";
    }

    virtual ~Computer() {
        cout << "[Computer] Деструктор: " << (brand ? brand : "?") << "\n";
        delete[] brand;
    }

    void setBrand(const char* b) {
        delete[] brand;
        brand = nullptr;
        copyBrand(b);
    }

    void setPrice(double p) { price = p; }

    virtual void print() const {
        cout << "Computer: " << brand
            << " | Ціна: " << price << " грн"
            << " | " << hdd.toString() << "\n";
    }
};

// ===================== public-похідний клас ComputerWithMonitor =====================
class ComputerWithMonitor : public Computer {
    double monitorInch;

public:
    ComputerWithMonitor() : Computer(), monitorInch(0.0) {
        cout << "[ComputerWithMonitor] Конструктор за замовчуванням\n";
    }

    ComputerWithMonitor(const char* b, double p, int hddMB, double inch)
        : Computer(b, p, hddMB), monitorInch(inch) {
        cout << "[ComputerWithMonitor] Конструктор: монітор " << inch << "\"\n";
    }
    // Конструктор без монітора (розмір = 0)
    ComputerWithMonitor(const char* b, double p, int hddMB)
        : Computer(b, p, hddMB), monitorInch(0.0) {
        cout << "[ComputerWithMonitor] Конструктор без монітора\n";
    }

    // Конструктор копіювання
    ComputerWithMonitor(const ComputerWithMonitor& c)
        : Computer(c), monitorInch(c.monitorInch) {
        cout << "[ComputerWithMonitor] Конструктор копіювання\n";
    }

    ~ComputerWithMonitor() {
        cout << "[ComputerWithMonitor] Деструктор\n";
    }

    void setMonitorSize(double inch) { monitorInch = inch; }

    void print() const override {
        Computer::print();
        if (monitorInch > 0)
            cout << "  Монітор: " << monitorInch << "\" дюймів\n";
        else
            cout << "  Монітор: не вказано\n";
    }
};

// ===================== private-похідний клас (обмежений доступ ззовні) =====================
class ComputerWithMonitorPrivate : private Computer {
    double monitorInch;

public:
    ComputerWithMonitorPrivate() : Computer(), monitorInch(0.0) {
        cout << "[ComputerWithMonitorPrivate] Конструктор за замовчуванням\n";
    }

    ComputerWithMonitorPrivate(const char* b, double p, int hddMB, double inch)
        : Computer(b, p, hddMB), monitorInch(inch) {
        cout << "[ComputerWithMonitorPrivate] Конструктор: " << b << ", монітор " << inch << "\"\n";
    }

    ~ComputerWithMonitorPrivate() {
        cout << "[ComputerWithMonitorPrivate] Деструктор\n";
    }

    // Метод друку доступний, але поліморфізм через Computer* неможливий
    void print() const {
        Computer::print();
        cout << "  Монітор (private-спадкування): " << monitorInch << "\"\n";
    }

    // Відкриваємо лише потрібні методи з базового класу
    using Computer::setBrand;
    using Computer::setPrice;
};
void runTask2_9() {
    cout << "=== Задача 2.9: Композиція + Ієрархія (Computer) ===\n";
    // --- Інтерактивне введення даних ---
    char brand[256];
    double price;
    int hddSize;
    double monitor;

    cin.ignore(); // очищення буфера
    cout << "Введіть марку комп'ютера: ";
    cin.getline(brand, 256);
    cout << "Введіть ціну (грн): ";
    cin >> price;
    cout << "Введіть обсяг HDD (Мбайт): ";
    cin >> hddSize;
    cout << "Введіть розмір монітора (дюйми): ";
    cin >> monitor;

    cout << "\n[Дія] Створення комп'ютера з вашими даними...\n";
    ComputerWithMonitor userPC(brand, price, hddSize, monitor);

    cout << "\n[Результат] Характеристики вашого комп'ютера:\n";
    userPC.print();

    // --- Ваш рідний автоматичний тест інших класів ---
    cout << "\n--- Запуск автоматичного тестування (HardDrive та Private-спадкування) ---\n";
    {
        HardDrive h2(512000);
        cout << h2.toString() << "\n";

        ComputerWithMonitorPrivate cp2("Asus-Private", 47000.0, 750000, 27.0);
        cp2.print();
    }
};
