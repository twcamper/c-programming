#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 100
float compute_GPA(char grades[], int n);

int main(void)
{
  char ch, grades[SIZE];
  int i = 0;
  printf("Enter up to %d letter grades: ", SIZE);

  while ((ch = getchar()) != '\n' && i < SIZE) {
    if (ch != ' ') {
      grades[i] = ch;
      i++;
    }
  }

  printf("GPA: %.2f\n", compute_GPA(grades, i));
  return 0;
}

float compute_GPA(char grades[], int n)
{
  float sum = 0.0;
  int i;

  for (i = 0; i < n; i++)  {
    switch(toupper(grades[i])) {
      case 'A':
        sum += 4.0f;
        break;
      case 'B':
        sum += 3.0f;
        break;
      case 'C':
        sum += 2.0f;
        break;
      case 'D':
        sum += 1.0f;
        break;
      case 'F':
        sum += 0.0f;
        break;
      default:
        fprintf(stderr, "Invalid input: %c\n", grades[i]);
        exit(1);
    }
  }
  return sum / (float) n;
}
