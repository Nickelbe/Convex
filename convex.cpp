#include <iostream>
#include <math.h>
#include "add.h"

using namespace std;

convex::convex() {}
convex::convex(double *ar[], int l)
{
  //find the lowest point
  double x_m = ar[0][0];
  double y_m = ar[0][1];
  int ind_temp = 0;
  for(int i = 0; i < l; i++) {
    if(ar[i][1] < y_m) {
      y_m = ar[i][1];
      x_m = ar[i][0];
      ind_temp = i;
    }
    else if(ar[i][1] == y_m) {
      if(ar[i][0] < x_m) {
        y_m = ar[i][1];
        x_m = ar[i][0];
        ind_temp = i;
      }
    }
  }

  //move it at the beginning
  if(ind_temp != 0) {
    swap(ar, ind_temp, 0);
  }

  int cvx_l = 1;
  int mark = 0;
  for(int i = 0; i < l-1; i++) {
    for(int j = i+1; j < l; j++) {
      mark = 0;
      for(int k = 0; k < l; k++) {
        if(k != j) {
          if((ar[j][0]-ar[i][0])*(ar[k][1]-ar[i][1]) -
          (ar[j][1]-ar[i][1])*(ar[k][0]-ar[i][0]) < 0) {
            mark = 1;
          }
        }
      }
      if(mark == 0) {
        if(j != i+1) {
          swap(ar, j, i+1);
          cvx_l++;
        }
        else {
          cvx_l++;
        }
        break;
      }
    }
  }

  //constructing two arrays for list constructing
  double **cvx_temp = (double**)malloc(cvx_l*sizeof(double*));
  for(int i = 0; i < cvx_l; i++) {
    cvx_temp[i] = (double*)malloc(2*sizeof(double));
  }
  double **set_temp = (double**)malloc((l - cvx_l)*sizeof(double*));
  for(int j = 0; j < l-cvx_l; j++) {
    set_temp[j] = (double*)malloc(2*sizeof(double));
  }

  //fill them
  for(int i = 0; i < l; i++) {
    if(i >= cvx_l) {
      set_temp[i-cvx_l][0] = ar[i][0];
      set_temp[i-cvx_l][1] = ar[i][1];
    }
    else {
      cvx_temp[i][0] = ar[i][0];
      cvx_temp[i][1] = ar[i][1];
    }
  }

  //finally construct convex:
  list temp1(cvx_temp, cvx_l);
  list temp2(set_temp, l-cvx_l);

  cvx = temp1;
  set = temp2;

  for(int i = 0; i < cvx_l; i++) {
    free(cvx_temp[i]);
  }
  for(int j = 0; j < l-cvx_l; j++) {
    free(set_temp[j]);
  }
  free(cvx_temp);
  free(set_temp);
}

void convex::show_cvx()
{
  cout << "Множество:" << endl;
  set.show();
  cout << "Его оболочка:" << endl;
  cvx.show();
}

double mod(double a, double b)
{
  return sqrt(a*a + b*b);
}

void convex::swap(double *b[], int idx, int dest)
{
  double x, y;
  x = b[dest][0];
  y = b[dest][1];
  b[dest][0] = b[idx][0];
  b[dest][1] = b[idx][1];
  b[idx][0] = x;
  b[idx][1] = y;
}

void convex::add(double x, double y)
{
  int l;
  double **p;
  point *c1 = cvx.begin;
  point *c2 = set.begin;
  l = cvx.size + set.size;
  p = new double *[l+1];
  for(int i = 0; i < l; i++) {
    p[i] = new double[2];
    if(i < cvx.size) {
      p[i][0] = c1->x;
      p[i][1] = c1->y;
      c1 = c1->next;
    }
    else {
      p[i][0] = c2->x;
      p[i][1] = c2->y;
      c2 = c2->next;
    }
  }
  p[l] = new double[2];
  p[l][0] = x;
  p[l][1] = y;
  convex temp(p, l+1);
  cvx = temp.cvx;
  set = temp.set;
  for(int i = 0; i < l+1; i++) {
    delete [] p[i];
  }
  delete [] p;
}

void convex::remove(double x, double y)
{
  int l = cvx.size + set.size;
  double **p;
  point *c1 = cvx.begin;
  point *c2 = set.begin;
  p = (double**)malloc(l*sizeof(double*));
  int i = 0;
  while(c2 != nullptr) {
    p[i] = (double*)malloc(2*sizeof(double));
    p[i][0] = c2->x;
    p[i][1] = c2->y;
    c2 = c2->next;
    i++;
  }
  while(c1 != nullptr) {
    p[i] = (double*)malloc(2*sizeof(double));
    p[i][0] = c1->x;
    p[i][1] = c1->y;
    c1 = c1->next;
    i++;
  }
  int mark = 0;
  for(int i = 0; i < l; i++) {
    if((p[i][0] == x) && (p[i][1] == y)) {
      p[i][0] = p[l-1][0];
      p[i][1] = p[l-1][1];
      mark = 1;
    }
  }
  //p = (double**)realloc(p, (l-1)*sizeof(double*));
  if(mark == 1) {
    convex temp(p, (l-1));
    *this = temp;
  }
  else {
    convex temp(p, l);
    *this = temp;
  }
  for(int k = 0; k < l; k++) {
    free(p[k]);
  }
  free(p);
}

convex &convex::operator=(const convex &a)
{
  if(this != &a) {
    set = a.set;
    cvx = a.cvx;
  }
  return *this;
}

int getsize(const convex &a)
{
  if(a.cvx.size != 0) {
    return a.cvx.size;
  }
  else {
    return 0;
  }
}

//get square
double getsquare(const convex &b)
{
  double square = 0;
  if(b.cvx.begin != nullptr) {
    point *cur = b.cvx.begin;
    while(cur->next != nullptr) {
      square += 0.5*((cur->x - 0)*(cur->next->y - 0) -
      (cur->next->x - 0)*(cur->y - 0));
      cur = cur->next;
    }
    square += 0.5*((b.cvx.end->x - 0)*(b.cvx.begin->y - 0) -
    (b.cvx.begin->x - 0)*(b.cvx.end->y - 0));
    return abs(square);
  }
  else {
    cout << "Оболочка пуста" << endl;
    return 0;
  }
}

double perimeter(const convex &a)
{
  double perimeter = 0;
  if(a.cvx.begin != nullptr) {
    point *cur = a.cvx.begin;
    while(cur->next != nullptr) {
      perimeter += mod(cur->next->x - cur->x, cur->next->y - cur->y);
      cur = cur->next;
    }
    if(a.cvx.end->x - a.cvx.begin->x != 0 && a.cvx.end->y - a.cvx.begin->y != 0) {
      perimeter += mod(a.cvx.end->x - a.cvx.begin->x, a.cvx.end->y - a.cvx.begin->y);
      return perimeter;
    }
    else {
      return perimeter;
    }
  }
  else {
    cout << "Оболочка пуста" << endl;
    return 0;
  }
}

void position(const convex &a, double x, double y)
{
  int l;
  double **p = nullptr;
  getcvx(a, p, l);
  if(l != 0) {
    bool result = false;
    int j = l - 1;
    for(int i = 0; i < l; i++) {
      if ( (p[i][1] < y && p[j][1] >= y || p[j][1] < y && p[i][1] >= y) &&
      (p[i][0] + (y - p[i][1]) / (p[j][1] - p[i][1]) * (p[j][0] - p[i][0]) < x) ) {
        result = !result;
      }
      j = i;
    }
    if(result) {
      cout << "Внутри" << endl;
    }
    else {
      cout << "Снаружи" << endl;
    }
    for(int i = 0; i < l; i++) {
      delete [] p[i];
    }
    delete [] p;
  }
}

void getcvx(const convex &b, double **&ar, int &l)
{
  if(b.cvx.begin != nullptr) {
    l = b.cvx.size;
    point *cur = b.cvx.begin;
    ar = new double*[l];
    int i = 0;
    while(cur != nullptr) {
      ar[i] = new double[2];
      ar[i][0] = cur->x;
      ar[i][1] = cur->y;
      cur = cur->next;
      i++;
    }
  }
  else {
    ar = nullptr;
    l = 0;
  }
}

point* getmin(const convex &c)
{
  return min_list(c.cvx);
}

point* getmax(const convex &d)
{
  return max_list(d.cvx);
}
