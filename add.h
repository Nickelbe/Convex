#pragma once
#include <iostream>

using namespace std;

class point
{
public:
  double x,y;
  point *next;
  point *prev;
  point()
  {
    x = 0;
    y = 0;
    next = nullptr;
    prev = nullptr;
  }
  point(double x, double y)
  {
    this->x = x;
    this->y = y;
    next = nullptr;
    prev = nullptr;
  }
  point &operator=(const point &a)
  {
    if(this != &a) {
      this->x = a.x;
      this->y = a.y;
    }
    return *this;
  }
  friend ostream &operator<<(ostream &, const point &c)
  {
    cout << "(" << c.x << "," << c.y<< ")" << endl;
    return cout;
  }
};

class list
{
public:
  point *begin;
  point *end;
  int size;
  ~list();
  list();
  list(double **, int);
  void show();
  void del(double, double);
  void addtail(double, double);
  list &operator=(const list &);
  friend point* min_list(const list &);
  friend point* max_list(const list &);
};

class convex
{
public:
  list set, cvx;
  convex();
  convex(double **, int);
  void show_cvx();
  void swap(double *[], int, int);
  void add(double, double);
  void remove(double, double);
  convex &operator=(const convex &);
  friend void getcvx(const convex &, double **&, int &);
  friend double mod(double, double);
  friend point* getmin(const convex &);
  friend point* getmax(const convex &);
  friend int getsize(const convex &);
  friend double getsquare(const convex &);
  friend double perimeter(const convex &);
  friend void position(const convex &, double, double);
};
