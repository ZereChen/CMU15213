#include <stdio.h>

int square(int a, int b){
  int ret = a*a + b*b;
  return ret;
}

int doCalc(int num1, int num2){
  int ret = square(num1, num2);
  return ret;
}

int main(){
  int param1 = 1;
  int param2 = 2;
  int result = doCalc(param1,param2);
  printf("result is%d\n",result);
}
