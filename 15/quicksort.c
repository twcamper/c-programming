#include "quicksort.h"

void quicksort(int *low, int *high)
{
  int *middle;

  if (low >= high) return;
  middle = split(low, high);
  quicksort(low, middle - 1);
  quicksort(middle + 1, high);
}

int *split(int *low, int *high)
{
  int part_element = *low;

  for (;;) {
    while (low < high && part_element <= *high)
      high--;
    if (low >= high) break;
    *low = *high;
    low++;

    while (low < high && *low <= part_element)
      low++;
    if (low >= high) break;
    *high = *low;
    high--;
  }

  *high = part_element;
  return high;
}
