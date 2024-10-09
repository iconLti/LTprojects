#include <iostream>
using namespace std;

class Patient {
private:
    string name;
    int age;

public:
    Patient(string n, int a) : name(n), age(a) {}

    string getName() { return name ; }
    int getAge() { return age; }

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }

    void displayInfo() { cout << "Patient Name: " << name << ", Age: " << age << endl; }
};

class Doctor {
public:
    virtual void work() {  // virtual позволяет позволит переопредилить метод в производных 
    // классах и использовать полиморфизм;
        cout << "Doctor is working." << endl;       
    }
};

class Surgeon : public Doctor {
public:
    // переопределение виртуального метода
    void work() override {
        cout << "Surgeon is performing surgery." << endl;
    }
};

class Dentist : public Doctor {
public:
    void work() override {
        cout << "Dentist is treating teeth." << endl;
    }
};



int main() {

    Patient patient1("Tim Loktionov", 18);
    patient1.displayInfo();
    patient1.setAge(19);
    patient1.displayInfo();

    Patient* patient2 = new Patient("SZ", -6);
    patient2->displayInfo();

    cout << endl;
    cout << endl;

    // можно просто соззать объкт класса и тогда у него будет вызываться метод этого класса
    Surgeon s1;
    s1.work();

    // можно создать обект через ссылку на базовый класс;
    /* Полиморфизм — способность объектов разных классов реагировать на одинаковые команды 
     по-своему (например, с помощью виртуальных функций); */

    Doctor* doc1 = new Surgeon(); // --> обект класса Surgeon
    Doctor* doc2 = new Dentist(); // --> объект класса Dentist 

    // метод work(); одинаковый, но реакция разная
    doc1->work(); // Surgeon is performing surgery.
    doc2->work(); // Dentist is treating teeth.

    delete doc1;
    delete doc2;

    return 0;
}