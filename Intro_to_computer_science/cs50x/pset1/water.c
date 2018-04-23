#include <stdio.h>
#include <iostream>

int main()
{
  int time;
  printf("How long was your shower in minutes? : ");
  std::cin >> time;
  int bottles = time*12;
  printf("Number of bottles : %i", bottles);
  printf("\n");
}
