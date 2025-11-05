#include "../includes/parsing_bonus.h"

void pad_map_lines_n(char **map, int rows)
{
    size_t max_len;
    int i;
    if (!map || rows <= 0)
        return;

    /* find max_len */
    max_len = 0;
    i = 0;
    while (i < rows)
    {
        char *s = map[i];
        size_t len = 0;
        if (s)
        {
            while (s[len])
                len++;
            if (len > max_len)
                max_len = len;
        }
        i++;
    }

    /* pad each line to max_len by realloc and writing '1' */
    i = 0;
    while (i < rows)
    {
        char *s = map[i];
        size_t len = 0;
        if (s)
        {
            while (s[len])
                len++;
            if (len < max_len)
            {
                char *newp = realloc(s, max_len + 1);
                if (!newp)
                {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                /* fill added bytes with '1' */
                while (len < max_len)
                {
                    newp[len] = '1';
                    len++;
                }
                newp[max_len] = '\0';
                map[i] = newp;
            }
        }
        else
        {
            /* if line is NULL, allocate a full line of '1's */
            char *newp = malloc(max_len + 1);
            if (!newp)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            len = 0;
            while (len < max_len)
            {
                newp[len] = '1';
                len++;
            }
            newp[max_len] = '\0';
            map[i] = newp;
        }
        i++;
    }
}

/* Pads a NULL-terminated map (char **map) */
void pad_map_lines(char **map)
{
    int rows = 0;
    if (!map)
        return;
    while (map[rows])
        rows++;
    pad_map_lines_n(map, rows);
}