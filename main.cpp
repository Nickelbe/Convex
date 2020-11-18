#include <iostream>
#include <vector>
#include "add.h"

using namespace std;

int main() {
  unsigned int command;
  convex *stack;
  int n;
  cout << "=============== Построение Выпуклой Оболочки ==============="<< endl;
  cout << "                     Список команд: " << endl;
  cout << "        1 - Добавить точку" << endl;
  cout << "        2 - Удалить точку" << endl;
  cout << "        3 - Получить количество точек в оболочке" << endl;
  cout << "        4 - Вывести множество и его оболочку" << endl;
  cout << "        5 - Положение заданной точки относительно оболочки (внутри - снаружи)" << endl;
  cout << "        6 - Площадь оболочки" << endl;
  cout << "        7 - Периметр оболочки" << endl;
  cout << "        8 - Высшая (max) точка оболочки" << endl;
  cout << "        9 - Низшая (min) точка оболочки" << endl;
  cout << "        10 - Получить массив оболочки" << endl;
  cout << "        0 - Завершить работу" << endl << endl;
  cout << "Сколько оболочек вы будете использовать? (Введите число n): ";
  mark0:
  try {
    cin >> n;
    if(n <= 0) throw n;
    else {
      //Создадим хранилище для оболочек программы
      stack = new convex[n];
    }
  }
  catch (int) {
    cout << "Число оболочек >= 0.(Введите снова)" << endl;
    goto mark0;
  }

  int com;
  for(int i = 0; i < n; i++) {
    cout << "Оболочка №"<< i << endl;
    cout << "Создать оболочку по массиву или оставить её пустой? (1 - по массиву, 0 - пустая) " << endl;
    mark00:
    cin >> com;
    if(com == 0) {}
    else if(com == 1) {
      mark01:
      try {
        int l;
        cout << "Введите число точек множества: " << endl;
        cin >> l;
        if(l < 3) throw l;
        else {
          double x, y;
          double **ar = new double *[l];
          for(int f = 0; f < l; f++) {
            cout << "Введите (x" << f << ", y"<< f <<"): ";
            cin >> x >> y;
            ar[f] = new double[2];
            ar[f][0] = x;
            ar[f][1] = y;
          }
          convex a(ar, l);
          stack[i] = a;
          for(int j = 0; j < l; j++) {
            delete [] ar[j];
          }
          delete [] ar;
        }
      }
      catch (int) {
        cout << "Размер должен быть >= 3" << endl;
        goto mark01;
      }
    }
    else {
      cout << "Подобных команд нет. Введите заново (0/1)" << endl;
      goto mark00;
    }
  }

  bool marker = true;
  //Пока не закончим
  while(marker) {
    mark:
    cout << "Введите команду:" << endl;
    cin >> command;
    switch (command) {
      //Добавление точки
      mark1:
      case 1:
      {
        try {
          double x, y;
          int i;
          cout << "Введите (x, y): ";
          cin >> x >> y;
          cout << "В какую оболочку добавить? (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            stack[i].add(x, y);
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark1;
        }
      }
      //Удаление точки
      mark2:
      case 2:
      {
        try {
          double x, y;
          int i;
          cout << "Введите (x, y): ";
          cin >> x >> y;
          cout << "Из какой оболочки удалить? (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            if(stack[i].cvx.size + stack[i].set.size != 0) {
              stack[i].remove(x, y);
            }
            else {
              cout << "Пустое множество - удалять нечего" << endl;
            }
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark2;
        }
      }
      //Получить количество точек в оболочке
      mark3:
      case 3:
      {
        try {
          int i;
          cout << "Число точек в оболочке... (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            cout << "Размер оболочки - " << getsize(stack[i]) << endl;
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark3;
        }
      }
      //Вывести оболочку по заданному номеру
      mark4:
      case 4:
      {
        try {
          int i;
          cout << "Какую оболочку вывести? (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            stack[i].show_cvx();
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark4;
        }
      }
      //Положение точки
      mark5:
      case 5:
      {
        try {
          int i;
          double x, y;
          cout << "Введите (x, y): ";
          cin >> x >> y;
          cout << "Положение относительно оболочки... (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            position(stack[i], x, y);
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark5;
        }
      }
      //Площадь
      mark6:
      case 6:
      {
        try {
          int i;
          cout << "Площадь оболочки... (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            cout << "Площадь оболочки = " << getsquare(stack[i]) << endl;
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark6;
        }
      }
      //Периметр
      mark7:
      case 7:
      {
        try {
          int i;
          cout << "Периметр оболочки... (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            cout << "Периметр оболочки = " << perimeter(stack[i]) << endl;
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark7;
        }
      }
      //Наибольшая точка
      mark8:
      case 8:
      {
        try {
          int i;
          cout << "Точка max... (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            if(getmax(stack[i]) == nullptr) {
              cout << "Список пуст" << endl;
            }
            else {
              cout << "Точка max = " << *getmax(stack[i]) << endl;
            }
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark8;
        }
      }
      //Наименьшая точка
      mark9:
      case 9:
      {
        try {
          int i;
          cout << "Точка min... (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            if(getmin(stack[i]) == nullptr) {
              cout << "Список пуст" << endl;
            }
            else {
              cout << "Точка min = " << *getmin(stack[i]) << endl;
            }
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark9;
        }
      }
      mark10:
      case 10:
      {
        try {
          int i;
          cout << "Получить массив оболочки... (введите индекс от 0 до n-1, где n - число оболочек в программе). Ваш индекс: ";
          cin >> i;
          if(i < 0 || i >= n) throw i;
          else {
            double **p = nullptr;
            int l = 0;
            getcvx(stack[i], p, l);
            if(p == nullptr) {
              cout << "Оболочка пуста" << endl;
            }
            else {
              for(int m = 0; m < l; m++) {
                cout <<"(x, y) = (" << p[m][0] << ", " << p[m][1] << ")" << endl;
              }
              for(int m = 0; m < l; m++) {
                delete [] p[m];
              }
              delete [] p;
            }
          }
          goto mark;
        }
        catch (int) {
          cout << "Проверьте введённый индекс! (оболочек под таким номером нет)" << endl;
          goto mark10;
        }
      }
      //Конец выполнения программы
      default:
      {
        if(command != 0) {
          break;
        }
      }
    } //конец switch
    if(command == 0) {
      cout << "Завершение работы" << endl;
      marker = !marker;
      break;
    }
  }
  //Очистка материала для программы
  delete [] stack;
  return 0;
}
