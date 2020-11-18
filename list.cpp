#include <iostream>
#include "add.h"

using namespace std;

list::list()
{
  begin = nullptr;
  end = nullptr;
  size = 0;
}

list::list(double *ar[], int k) {
  if(k > 1) {
    point *temp = new point;
    size = k;
    temp->x = ar[0][0];
    temp->y = ar[0][1];
    begin = temp;
    for(int i = 1; i < k-1; i++) {
      temp->next = new point;
      temp->next->x = ar[i][0];
      temp->next->y = ar[i][1];
      temp->next->prev = temp;
      temp = temp->next;
    }
    temp->next = new point;
    temp->next->x = ar[k-1][0];
    temp->next->y = ar[k-1][1];
    end = temp->next;
    end->prev = temp;
  }
  else if(k == 0) {
    begin = nullptr;
    end = nullptr;
    size = 0;
  }
  else {
    point *cur = new point;
    size = 1;
    cur->x = ar[0][0];
    cur->y = ar[0][1];
    begin = end = cur;
  }
}

list::~list() {
  if(begin != nullptr) {
    point *cur = begin;
    point *temp;
    while(cur != nullptr) {
      temp = cur;
      cur = cur->next;
      delete temp;
    }
    begin = nullptr;
    end = nullptr;
    size = 0;
  }
}

void list::addtail(double x, double y)
{
  point *temp = new point;
  temp->next = nullptr;
  temp->x = x;
  temp->y = y;
  temp->prev = end;
  if(end != nullptr) {
    end->next = temp;
  }
  if(size == 0) {
    begin = end = temp;
  }
  else {
    end = temp;
  }
  size++;
}

void list::del(double x, double y)
{
   int i = 1;
   point *del = begin;
   while(x != del->x && y != del->y)
   {
     del = del->next;
     i++;
   }
   point *prevdel = del->prev;
   point *afterdel = del->next;
   if(prevdel != nullptr && size != 1) {
     prevdel->next = afterdel;
   }
   if(afterdel != nullptr && size != 1) {
     afterdel->prev = prevdel;
   }
   if(x == begin->x && y == begin->y) {
     begin = afterdel;
   }
   if(x == end->x && y == end->y) {
     end = prevdel;
   }
   delete del;
   size--;
}

void list::show()
{
  if(begin) {
    point *cur = begin;
    while(cur) {
      cout << "(x, y) = "<< *cur << endl;
      cur = cur->next;
    }
  }
  else {
    cout << "Пустое множество" << endl;
  }
}

list &list::operator=(const list &a)
{
  if(this == &a) {
    return *this;
  }
  this-> ~list();
  point *temp = a.begin;
  while(temp != nullptr)
  {
    addtail(temp->x, temp->y);
    temp = temp->next;
  }
  return *this;
}

point* min_list(const list &a) {
  point *cur, *m;
  double x, y;
  if(a.begin != nullptr) {
    cur = a.begin;
    x = cur->x;
    y = cur->y;
    m = cur;
    while(cur != nullptr) {
      if(cur->y < y) {
        x = cur->x;
        y = cur->y;
        m = cur;
      }
      cur = cur->next;
    }
    return m;
  }
  else {
    //cout << "Empty list!" << endl;
    return nullptr;
  }
}

point* max_list(const list &b) {
  point *cur, *m;
  double x, y;
  if(b.begin != nullptr) {
    cur = b.begin;
    x = cur->x;
    y = cur->y;
    m = cur;
    while(cur != nullptr) {
      if(cur->y > y) {
        x = cur->x;
        y = cur->y;
        m = cur;
      }
      cur = cur->next;
    }
    return m;
  }
  else {
    //cout << "Empty list!" << endl;
    return nullptr;
  }
}
