#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <windows.h>

using namespace std;

/*
==========================================================================================================================================
                                              Алгоритми STL. Сортування і пошук
==========================================================================================================================================

                                                    АЛГОРИТМИ STL
  АЛГОРИТМ STL — готова шаблонна функція з бібліотеки <algorithm> (числові — з <numeric>), яка обробляє елементи
  в ДІАПАЗОНІ, заданому двома ітераторами: від first включно до last НЕ включно. Найчастіше це весь контейнер: begin(), end().
  Алгоритм не знає, з яким контейнером працює: йому достатньо ітераторів.
  Що саме робити з елементами, алгоритму передають стандартним функтором або лямбдою.
  Готові алгоритми перевірені, швидкі, а їхні назви одразу пояснюють, що робить код, — тому власні цикли
  для сортування, пошуку чи підрахунку в реальних проєктах не пишуть.

                                                  СОРТУВАННЯ І ПОШУК
  sort впорядковує елементи: за замовчуванням за зростанням, або за правилом, яке задає функтор чи лямбда.
  find шукає елемент із заданим значенням, find_if — перший елемент, що задовольняє умову.
  Обидва повертають ітератор на знайдений елемент або end(), якщо нічого не знайдено.

  ----------------------------------------------------------------------------------------------------------------------------------------

      sort(first, last)                      за зростанням (потрібен оператор <)
      sort(first, last, greater<T>())        за спаданням
      sort(first, last, comparator)          за власним правилом: лямбда (a, b) повертає true, якщо a має стояти раніше за b
      find(first, last, value)               знайти значення
      find_if(first, last, predicate)        знайти перший елемент, для якого предикат повертає true

  Після find і find_if результат ЗАВЖДИ порівнюють з end().
  sort працює з vector, але не з list (у list є власний метод list.sort()).
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

    vector<int> scores = { 70, 95, 40, 88 };
    sort(scores.begin(), scores.end());                       // 40 70 88 95
    sort(scores.begin(), scores.end(), greater<int>());       // 95 88 70 40
    for (int score : scores)
    {
        cout << score << " ";
    }
    cout << endl;

    auto it = find(scores.begin(), scores.end(), 88);         // пошук значення
    if (it != scores.end())
    {
        cout << "Знайдено 88" << endl;
    }

    // ============================================== Програма ==============================================

    vector<Student> group = {
        Student("Олена Коваль", 20, 11.5),
        Student("Богдан Мельник", 35, 9.8),
        Student("Марія Бондар", 27, 10.2),
        Student("Андрій Ткач", 42, 7.4),
        Student("Софія Лисенко", 19, 11.9)
    };

    cout << "--- Рейтинг: sort за балом (спадання) ---" << endl;
    sort(group.begin(), group.end(), [](const Student& a, const Student& b)
        {
            return a.getAverage() > b.getAverage();               // a раніше, якщо в нього бал вищий
        });
    printGroup(group);

    cout << "--- Журнал: sort за ім'ям ---" << endl;
    sort(group.begin(), group.end(), [](const Student& a, const Student& b)
        {
            return a.getName() < b.getName();
        });
    printGroup(group);

    cout << "--- find_if ---" << endl;
    auto found = find_if(group.begin(), group.end(), [](const Student& s) { return s.getAge() > 30; });
    if (found != group.end())                                 // обов'язкова перевірка: могли й не знайти
    {
        cout << "Перший старший за 30: " << found->getName() << endl;
    }

    return 0;
}

/*
==========================================================================================================================================
                                                  ІНСАЙТИ / ЛАЙФХАКИ / BEST PRACTICES
==========================================================================================================================================

  1. sort в STL — не бульбашка: це гібрид швидкого сортування, сортування купою і вставками зі складністю O(n log n).

  2. Компаратор відповідає на питання «чи має a стояти СТРОГО раніше за b?». Не пишіть у ньому <= :
     sort може працювати неправильно.

  3. string порівнює коди символів, а не абетку: українські І, Ї, Є, Ґ мають «чужі» коди, і «Ігор» опиниться
     перед «Андрієм». Тому в прикладі студент — Богдан.

==========================================================================================================================================
                                                              ПРАКТИКА
==========================================================================================================================================

  Завдання. Рейтинг турніру.
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

          void print() const
          {
              cout << nickname << ": " << score << " очок, перемог " << wins << endl;
          }
      };

      // у main:
      vector<Player> players = {
          Player("ShadowFox", 2300, 14),
          Player("IronBear", 1800, 9),
          Player("Pixel", 2750, 20),
          Player("Noob42", 150, 1),
          Player("Valkyrie", 2100, 12)
      };

    1. Відсортуйте гравців за очками за спаданням (sort з лямбдою) і виведіть таблицю.
    2. Виведіть трійку лідерів: перші три елементи вектора.
    3. Відсортуйте гравців за кількістю перемог за зростанням і виведіть таблицю ще раз.
    4. Через find_if знайдіть гравця з ніком «Valkyrie» і виведіть його; якщо не знайдено — «Гравця не знайдено».
    5. Створіть vector<string> banned = { "Cheater99", "Noob42" }. Через find перевірте, чи є «Noob42» у списку
       заблокованих, і виведіть «Noob42 заблоковано» або «Noob42 може грати».
*/
