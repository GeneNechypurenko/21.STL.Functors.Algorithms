#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

/*
==========================================================================================================================================
                                                Алгоритми STL. Зміна і видалення
==========================================================================================================================================

                                                           ДІЯ НАД КОЖНИМ
  for_each виконує дію (найчастіше лямбду) для кожного елемента діапазону. Якщо лямбда приймає елемент за посиланням,
  вона може його змінити.

                                                            ПЕРЕТВОРЕННЯ
  transform перетворює кожен елемент і записує результат в інший або в той самий контейнер: наприклад, з вектора студентів
  отримати вектор їхніх імен.

                                                         ВИДАЛЕННЯ ЗА УМОВОЮ
  erase_if (C++20) видаляє з контейнера всі елементи, що задовольняють умову, одним рядком — без ручного циклу з ітераторами і erase.

  ----------------------------------------------------------------------------------------------------------------------------------------

      for_each(first, last, action)                       action — лямбда з одним параметром-елементом
      transform(first, last, destination, operation)      operation — лямбда: елемент → новий елемент
      erase_if(container, predicate)                       це функція контейнера, а не з <algorithm>; повертає кількість видалених

  Контейнер-приймач для transform має вже містити потрібну кількість елементів:
      vector<string> names(group.size());   — створює вектор з group.size() порожніх рядків
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
    double getAverage() const { return average; }

    void setAverage(double average) { this->average = average; }

    void print() const
    {
        cout << name << ", середній бал " << average << endl;
    }
};

void printGroup(const vector<Student>& group)
{
    for (const Student& student : group)
    {
        student.print();
    }
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // ===================================== Основний синтаксис =====================================

    vector<int> prices = { 100, 250, 80 };
    for_each(prices.begin(), prices.end(), [](int& price) { price = price * 9 / 10; });   // знижка 10%: 90 225 72
    vector<int> doubled(prices.size());
    transform(prices.begin(), prices.end(), doubled.begin(), [](int price) { return price * 2; });   // 180 450 144
    for (int value : doubled)
    {
        cout << value << " ";
    }
    cout << endl;
    erase_if(prices, [](int price) { return price < 80; });                                           // 90 225
    for (int price : prices)
    {
        cout << price << " ";
    }
    cout << endl;

    // ============================================== Програма ==============================================

    vector<Student> group = {
        Student("Олена Коваль", 20, 11.5),
        Student("Богдан Мельник", 35, 9.8),
        Student("Марія Бондар", 27, 10.2),
        Student("Андрій Ткач", 42, 7.4),
        Student("Софія Лисенко", 19, 11.9)
    };

    cout << "--- for_each: бонус за олімпіаду ---" << endl;
    for_each(group.begin(), group.end(), [](Student& s)     // Student& — змінюємо самих студентів
        {
            s.setAverage(s.getAverage() + 0.5);
        });
    printGroup(group);

    cout << "--- transform: список імен для журналу ---" << endl;
    vector<string> names(group.size());
    transform(group.begin(), group.end(), names.begin(), [](const Student& s) { return s.getName(); });
    for (const string& name : names)
    {
        cout << name << endl;
    }

    cout << "--- erase_if: відрахування ---" << endl;
    auto expelled = erase_if(group, [](const Student& s) { return s.getAverage() < 8; });
    cout << "Відраховано: " << expelled << endl;
    printGroup(group);

    return 0;
}

/*
==========================================================================================================================================
                                                  ІНСАЙТИ / ЛАЙФХАКИ / BEST PRACTICES
==========================================================================================================================================

  1. Для простої дії над кожним елементом цикл по діапазону і for_each рівноцінні. for_each зручний тоді,
     коли лямбду вже створено окремо або діапазон — лише частина контейнера.

  2. До C++20 видаляли за умовою так званою ідіомою erase-remove:
         group.erase(remove_if(group.begin(), group.end(), predicate), group.end());
     remove_if сам нічого не видаляє: лише зсуває «потрібні» елементи на початок. Цей запис трапляється в старому коді.

  3. Якщо приймач для transform не підготувати (vector<string> names; без розміру), програма запише дані
     за межі вектора — невизначена поведінка. Розмір задають заздалегідь.

==========================================================================================================================================
                                                              ПРАКТИКА
==========================================================================================================================================

  Завдання. Бій загону.
  Клас Unit уже готовий — скопіюйте його у свій файл:

      class Unit
      {
      private:
          string name;
          int health;
          int damage;

      public:
          Unit(const string& name, int health, int damage) : name(name), health(health), damage(damage)
          {}

          string getName() const { return name; }
          int getHealth() const { return health; }
          int getDamage() const { return damage; }

          void takeDamage(int amount) { health -= amount; }
          void addDamage(int amount) { damage += amount; }

          void print() const
          {
              cout << name << ": здоров'я " << health << ", шкода " << damage << endl;
          }
      };

  У main:
    1. Створіть vector<Unit> squad: «Лицар» 100 15, «Лучник» 60 20, «Маг» 40 30, «Розвідник» 30 10.
    2. Бард зіграв бойову пісню: через for_each збільште шкоду кожного на 5 (addDamage). Виведіть загін.
    3. Дракон дихнув вогнем: через for_each завдайте кожному 40 шкоди (takeDamage). Виведіть загін.
    4. Через erase_if приберіть усіх, у кого здоров'я 0 або менше, і виведіть «Загинуло: 2» та загін.
    5. Через transform отримайте vector<int> damages зі шкодою тих, хто вижив, і виведіть його.
*/
