#include <stdio.h>
int cal(int *pools, int len) {
  int *max = pools;
  for (int i = 1; i < len; i++) {
    if (pools[i] > *max) max = pools + i;
  }
  int result = 0;
  for (int *p = pools, height_by_now = 0; p != max; p++) {
    if (*p > height_by_now) height_by_now = *p;
    result += height_by_now - *p;
  }
  for (int *p = pools+len-1, height_by_now = 0; p != max; p--) {
    if (*p > height_by_now) height_by_now = *p;
    result += height_by_now - *p;
  }
  return result;
}
