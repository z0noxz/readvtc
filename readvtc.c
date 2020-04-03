#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_vt_colors(int cn)
{
    char *cfs[3] = {
        "/sys/module/vt/parameters/default_red",
        "/sys/module/vt/parameters/default_grn",
        "/sys/module/vt/parameters/default_blu",
    };
    char vtcs[16][8];
    char tk[] = ",";
    char cl[64];
    char *tp = NULL;
    FILE *fp;
    size_t r;
    int i, c, n;

    for (i = 0; i < 16; i++)
        strcpy(vtcs[i], "#000000");

    for (i = 0, r = 0; i < 3; i++) {
        if ((fp = fopen(cfs[i], "r")) == NULL)
            continue;
        while ((cl[r] = fgetc(fp)) != EOF && cl[r] != '\n')
            r++;
        cl[r] = '\0';
        for (c = 0, tp = cl, n = 0; c < 16; c++, tp++) {
            if ((r = strcspn(tp, tk)) == -1)
                break;
            for (n = 0; r && *tp >= 48 && *tp < 58; r--, tp++)
                n = n * 10 - 48 + *tp;
            vtcs[c][i * 2 + 1] = n / 16 < 10 ? n / 16 + 48 : n / 16 + 87;
            vtcs[c][i * 2 + 2] = n % 16 < 10 ? n % 16 + 48 : n % 16 + 87;
        }

        fclose(fp);
    }

    if (cn >= 0 && cn < 16) {
        fprintf(stdout, "%s\n", vtcs[cn]);
    } else {
        for (i = 0; i < 16; i++)
            fprintf(stdout, "%s\n", vtcs[i]);
    }
}

int main(int argc, char *argv[])
{
    int cn;

    if (argc == 2 && (sscanf(argv[1], "%d", &cn) == EOF))
        cn = -1;

    get_vt_colors(cn);
    return 0;
}
