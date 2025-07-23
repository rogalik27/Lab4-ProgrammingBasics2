#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Базовий клас Людина
class Human {
    protected:
        int age;
    public:
        Human(int age) : age(age) {}
        virtual void printInfo() const {
            cout << "Людина" << ", Вік: " << age << endl;
        }
};

class Citizen : public Human {
    protected:
        string name;
        string nationality;

    public:
        Citizen(const string& name, int age, const string& nationality)
            : name(name), Human(age), nationality(nationality) {}

        void printInfo() const override {
            cout << "Громадянин: " << name << ", Національність: " << nationality << ", Вік: " << age << endl;
        }
};

class Student : public Citizen {
    string university;
    int year;

    public:
        Student(const string& name, int age, const string& nationality, const string& university, int year)
            : Citizen(name, age, nationality), university(university), year(year) {}

        void printInfo() const override {
            cout << "Студент: " << name << ", Нац.: " << nationality
                 << ", Унiверситет: " << university << ", Курс: " << year << ", Вік: " << age << endl;
        }
};

class Employee : public Citizen {
    string company;
    string position;

    public:
        Employee(const string& name, int age, const string& nationality, const string& company, const string& position)
            : Citizen(name, age, nationality), company(company), position(position) {}

        void printInfo() const override {
            cout << "Спiвробiтник: " << name << ", Нац.: " << nationality
                 << ", Компанiя: " << company << ", Посада: " << position  << ", Вік: " << age << endl;
        }
};

int main() {
    vector<Human*> people;

    people.push_back(new Human(34));
    people.push_back(new Citizen("Олена", 25, "Українка"));
    people.push_back(new Student("Ігор", 20, "Українець", "ХПІ", 2));
    people.push_back(new Employee("Михайло", 17, "Українець", "NETWAYS", "Інженер"));

    for (auto& person : people) {
        person->printInfo();
    }

    for (auto& person : people) {
        delete person;
    }

    return 0;
}

