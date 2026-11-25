#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <windows.h>

using namespace std;

/*
==========================================================================================================================================
                                          Алгоритми STL. Підрахунок, перевірки, підсумки
==========================================================================================================================================

                                                 ПІДРАХУНОК І ПЕРЕВІРКИ
  count і count_if рахують, скільки елементів дорівнюють значенню або задовольняють умову.
  any_of, all_of і none_of відповідають на питання «чи є хоч один?», «чи всі?», «чи жоден?» — і повертають bool.

                                                 НАЙБІЛЬШИЙ І НАЙМЕНШИЙ
  max_element і min_element знаходять найбільший і найменший елемент і повертають ІТЕРАТОР на нього.
  Для об'єктів класів правило порівняння задають лямбдою.

                                                       ПІДСУМОК
  accumulate з бібліотеки <numeric> накопичує значення: за замовчуванням додає всі елементи до початкового значення,
  а з лямбдою — накопичує будь-що, наприклад суму балів усіх студентів.

  ----------------------------------------------------------------------------------------------------------------------------------------

      count(first, last, value)              скільки елементів дорівнюють value
      count_if(first, last, predicate)       скільки елементів задовольняють умову
      any_of / all_of / none_of(first, last, predicate)
      max_element / min_element(first, last)               для чисел і рядків
      max_element(first, last, comparator)                 компаратор відповідає на питання «a МЕНШЕ за b?»
      accumulate(first, last, start)                       сума, start — початкове значення
      accumulate(first, last, start, operation)            лямбда (total, element) повертає нове total

  Тип start визначає тип результату: accumulate(…, 0, …) рахує в int, accumulate(…, 0.0, …) — у double.
  max_element і min_element для порожнього контейнера повертають end() — розіменовувати його не можна.
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
};

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // ===================================== Основний синтаксис =====================================

    vector<int> grades = { 10, 7, 12, 7, 9 };
    cout << "Сімок: " << count(grades.begin(), grades.end(), 7) << endl;                        // 2
    cout << "Найвища: " << *max_element(grades.begin(), grades.end()) << endl;                  // 12 (* — значення за ітератором)
    cout << "Сума: " << accumulate(grades.begin(), grades.end(), 0) << endl;                    // 45

    // ============================================== Програма ==============================================

    vector<Student> group = {
        Student("Олена Коваль", 20, 11.5),
        Student("Богдан Мельник", 35, 9.8),
        Student("Марія Бондар", 27, 10.2),
        Student("Андрій Ткач", 42, 7.4),
        Student("Софія Лисенко", 19, 11.9)
    };

    cout << "--- Підрахунок ---" << endl;
    double minAverage = 10;
    auto honors = count_if(group.begin(), group.end(), [minAverage](const Student& s)
        {
            return s.getAverage() >= minAverage;
        });
    cout << "Студентів з балом від " << minAverage << ": " << honors << endl;

    cout << "--- Перевірки ---" << endl;
    bool hasDebtors = any_of(group.begin(), group.end(), [](const Student& s) { return s.getAverage() < 8; });
    bool allAdults = all_of(group.begin(), group.end(), [](const Student& s) { return s.getAge() >= 18; });
    cout << "Є боржники? " << hasDebtors << endl;               // 1
    cout << "Усі повнолітні? " << allAdults << endl;            // 1

    cout << "--- Найвищий і найнижчий бал ---" << endl;
    auto best = max_element(group.begin(), group.end(), [](const Student& a, const Student& b)
        {
            return a.getAverage() < b.getAverage();                 // для max_element компаратор — «менше»
        });
    auto worst = min_element(group.begin(), group.end(), [](const Student& a, const Student& b)
        {
            return a.getAverage() < b.getAverage();                 // той самий компаратор — «менше»
        });
    cout << "Найкращий бал: " << best->getName() << endl;
    cout << "Найнижчий бал: " << worst->getName() << endl;

    cout << "--- Середній бал групи ---" << endl;
    double sum = accumulate(group.begin(), group.end(), 0.0, [](double total, const Student& s)
        {
            return total + s.getAverage();                          // total — накопичене значення, починається з 0.0
        });
    cout << "Середній бал: " << sum / static_cast<double>(group.size()) << endl;

    return 0;
}

/*
==========================================================================================================================================
                                                  ІНСАЙТИ / ЛАЙФХАКИ / BEST PRACTICES
==========================================================================================================================================

  1. Типова помилка: accumulate(v.begin(), v.end(), 0) для дробових чисел. Початкове значення 0 — це int,
     тому дробові частини губляться. Для double пишіть 0.0.

  2. max_element повертає ітератор, а не значення: щоб отримати значення, пишуть *it або it->метод().

  3. count_if повертає не int, а цілий тип різниці ітераторів; зручно зберігати результат в auto.

==========================================================================================================================================
                                                              ПРАКТИКА
==========================================================================================================================================

  Завдання. Статистика команди.
  Клас Player і заповнення вектора вже готові — скопіюйте їх у свій файл:

      class Player
      {
      private:
          string nickname;
          int score;
          int wins;

      public:
          Player(const string& nickname, int score, int wins) : nickname(nickname), score(score), wins(wins)
          {}

          string getNickname() const { return nickname; }
          int getScore() const { return score; }
          int getWins() const { return wins; }
      };

      // у main:
      vector<Player> team = {
          Player("ShadowFox", 2300, 14),
          Player("IronBear", 1800, 9),
          Player("Pixel", 2750, 20),
          Player("Noob42", 150, 0),
          Player("Valkyrie", 2100, 12)
      };

    1. Через count_if порахуйте гравців, у яких понад 2000 очок.
    2. Через any_of перевірте, чи є в команді гравець без жодної перемоги.
    3. Через all_of перевірте, чи всі гравці мають понад 100 очок.
    4. Через max_element знайдіть гравця з найбільшою кількістю перемог, через min_element — з найменшою кількістю очок.
    5. Через accumulate з лямбдою порахуйте загальну кількість очок команди і виведіть її та середнє на гравця.
*/
