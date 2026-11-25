#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

/*
==========================================================================================================================================
                                                            Лямбда-вирази
==========================================================================================================================================

                                                            ЛЯМБДА-ВИРАЗ
  ЛЯМБДА-ВИРАЗ — безіменна функція, записана прямо в місці використання. Компілятор сам створює для неї
  безіменний клас-функтор.
  Лямбду передають у функцію або алгоритм, коли потрібне своє правило: умова відбору, порядок сортування, дія над елементом.
  Лямбда може ЗАХОПЛЮВАТИ змінні з навколишнього коду: за копією (лише читати значення) або за посиланням (змінювати саму змінну).

  ----------------------------------------------------------------------------------------------------------------------------------------

  Синтаксис:
      [захоплення](параметри) { тіло }          тип результату виводиться з return

  Захоплення:
      []      нічого                        [x]     копію x               [&x]    x за посиланням
      [=]     копії всіх використаних       [&]     усі використані за посиланням

  Тип лямбди знає лише компілятор, тому її зберігають в auto або передають у шаблонний параметр функції:
      auto isAdult = [](int age) { return age >= 18; };
      template <typename Condition> void printIf(const vector<Student>& group, Condition condition)
*/

class Student
{
private:
    string name;
    int age;
    double average;

public:
    Student(const string& name, int age, double average) : name(name), age(age), average(average)
    {}

    string getName() const { return name; }
    int getAge() const { return age; }
    double getAverage() const { return average; }

    void print() const
    {
        cout << name << ", " << age << " років, середній бал " << average << endl;
    }
};

// Шаблонна функція приймає будь-яку умову — зокрема лямбду
template <typename Condition>
void printIf(const vector<Student>& group, Condition condition)
{
    for (const Student& student : group)
    {
        if (condition(student))                          // викликаємо умову як функцію
        {
            student.print();
        }
    }
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // ===================================== Основний синтаксис =====================================

    auto square = [](int x) { return x * x; };          // лямбда в змінній
    cout << "5 у квадраті: " << square(5) << endl;      // виклик як функції: 25

    int bonus = 10;
    auto addBonus = [bonus](int score) { return score + bonus; };   // [bonus] — копія: лише читаємо
    cout << "80 + бонус: " << addBonus(80) << endl;     // 90

    int counter = 0;
    auto increment = [&counter]() { counter++; };       // [&counter] — посилання: змінюємо саму змінну
    increment();
    increment();
    cout << "counter: " << counter << endl;             // 2

    // ============================================== Програма ==============================================

    vector<Student> group = {
        Student("Олена Коваль", 20, 11.5),
        Student("Ігор Мельник", 35, 9.8),
        Student("Марія Бондар", 27, 10.2),
        Student("Андрій Ткач", 42, 8.7)
    };

    cout << "--- Старші за 30 ---" << endl;
    printIf(group, [](const Student& student) { return student.getAge() > 30; });

    cout << "--- Бал не нижчий за поріг ---" << endl;
    double minAverage = 10;                             // значення могло б прийти від користувача
    printIf(group, [minAverage](const Student& student) { return student.getAverage() >= minAverage; });

    cout << "--- Та сама лямбда кілька разів ---" << endl;
    auto isYoung = [](const Student& student) { return student.getAge() < 30; };
    printIf(group, isYoung);

    return 0;
}

/*
==========================================================================================================================================
                                                  ІНСАЙТИ / ЛАЙФХАКИ / BEST PRACTICES
==========================================================================================================================================

  1. Захоплення за копією [x] запам'ятовує значення в момент створення лямбди: якщо x потім зміниться,
     лямбда цього не побачить. Захоплення за посиланням [&x] завжди бачить актуальне значення.

  2. [&] небезпечне, якщо лямбда живе довше за змінні, які вона захопила: посилання вкаже на вже знищену змінну.
     Якщо лямбда використовується одразу (як у printIf), [&] безпечне.

  3. Уникайте [=] і [&] у великому коді: явний список [minAverage, &counter] одразу показує, від чого залежить лямбда.

  4. Лямбди є майже в усіх сучасних мовах: у C# це  s => s.Age > 30,  у JavaScript —  s => s.age > 30.

==========================================================================================================================================
                                                              ПРАКТИКА
==========================================================================================================================================

  Завдання. Бестіарій і лікування.
  Клас Monster уже готовий — скопіюйте його у свій файл:

      class Monster
      {
      private:
          string name;
          int level;
          int health;

      public:
          Monster(const string& name, int level, int health) : name(name), level(level), health(health)
          {}

          string getName() const { return name; }
          int getLevel() const { return level; }
          int getHealth() const { return health; }

          void print() const
          {
              cout << name << ", рівень " << level << ", здоров'я " << health << endl;
          }
      };

    1. Напишіть шаблонну функцію  template <typename Condition> void printIf(const vector<Monster>& monsters, Condition condition)
       — як printIf у прикладі.
    2. У main створіть vector<Monster>: «Гоблін» 2 30, «Тролль» 6 180, «Скелет» 3 45, «Дракон» 15 900, «Слиз» 1 10.
    3. Виведіть монстрів зі здоров'ям понад 100 через лямбду без захоплення.
    4. Створіть змінну int heroLevel = 5 і виведіть монстрів, рівень яких не перевищує heroLevel,
       через лямбду із захопленням [heroLevel].
    5. Створіть змінну int heroHealth = 50 і лямбду  auto heal = [&heroHealth](int amount) { … },
       яка додає amount до здоров'я героя. Викличте heal(20) двічі і виведіть «Здоров'я героя: 90».
*/
