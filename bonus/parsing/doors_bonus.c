#include "../includes/parsing_bonus.h"
#include <stddef.h>

int doors_parsing(char **map) {
  printf("======================================== salam hh\n");
  size_t i;
  size_t j;
  size_t len;

  i = 0;
  j = 0;
  len = ft_dbl_strlen(map) - 1;
  printf("len: %zu\n", len);
  printf("seg hh\n");
  while (map[i]) {
    j = 0;
    printf("%s\n", map[i]);
    while (map[i][j]) {
      if (map[i][j] == 'D') {
        printf("len: %zu i: %zu\n", len, i);
        if (i == len || i == 0)
          return (1);
        printf("hhhhhhhhhhhhhhhhhhhhh\n");
        if (j == 0 || j == (ft_strlen(map[i]) - 1))
          return (1);
        if (!((map[i - 1][j] == '1' && map[i + 1][j] == '1') ||
              (map[i][j + 1] == '1' && map[i][j - 1] == '1')))
          return (1);
      }
      j++;
    }
    i++;
  }
  return (0);
}
