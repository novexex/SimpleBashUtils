#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

void parce(int argc, char* argv[]) {
    struct option long_opt[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'}
    };
    FILE* f;
        for (int i = 0, j = 0; j != argc; i++, j++) {
            if (argv[j][i] != '\0' && argv[j][0] != '-')
                f = fopen(argv[j], "r+");
        }
    if (f) {
        int check;
        int useless;
        int schet = 1;
        char putout;
        char prev = '\n';
        char preprev;
                while ((check = getopt_long(argc, argv, "beEnstTv", long_opt, &useless))) {
                    if (check == -1) {
                        while ((putout = fgetc(f)) != EOF)
                        fputc(putout, stdout);
                    } else {
                        if (check) {
                            switch (check) {
                                case 'b':
                                    while ((putout = fgetc(f)) != EOF) {
                                        if (prev == '\n' && putout != '\n')
                                            printf("%6d\t", schet++);
                                        fputc(putout, stdout);
                                        prev = putout;
                                    }
                                break;

                                case 'E': 
                                    while ((putout = fgetc(f)) != EOF) {
                                        if (putout == '\n')
                                            printf("$");
                                        fputc(putout, stdout);
                                    }
                                break;

                                case 'n':
                                    while (1) {
                                        putout = fgetc(f);
                                        if (prev == '\n' && putout != EOF)
                                            printf("%6d\t", schet++);
                                        if ((prev == '\n' && putout == EOF) || putout == EOF)
                                            break;
                                        fputc(putout, stdout);
                                        prev = putout;
                                    }
                                break;

                                case 's':
                                    prev = 0;
                                    while ((putout = fgetc(f)) != EOF) {
                                        if (prev == '\n' && putout == '\n' && preprev == '\n')
                                            continue;
                                        fputc(putout, stdout);
                                        preprev = prev;
                                        prev = putout;
                                    }
                                break;

                                case 'T': 
                                    while ((putout = fgetc(f)) != EOF) {
                                        if (putout == '\t') {
                                            printf("^I");
                                            continue;
                                        }
                                        fputc(putout, stdout);
                                    } 
                                break;

                                case 'v':
                                    while ((putout = fgetc(f)) != EOF) {
                                        int ch = (int)putout;
                                        if (putout < 0) {
                                            putout &= 127;
                                            ch = (int)putout;
                                            ch += 128;
                                        }
                                        if (ch != 9 && ch != 10 && ch < 32) {
                                            printf("^");
                                            putout += 64;
                                        } else if (ch == 127) {
                                            printf("^");
                                            putout = '?';
                                        } else if (ch > 127 && ch < 160) {
                                            printf("M-^");
                                            putout = ch - 64;
                                        } else if (ch > 160 && ch <= 255) {
                                            putout -= 128;
                                        }
                                        fputc(putout, stdout);
                                    }
                                break;

                                case 't':
                                    while ((putout = fgetc(f)) != EOF) {
                                        int ch = (int)putout;
                                        if (putout == '\t') {
                                            printf("^I");
                                            continue;
                                        }
                                        if (putout < 0) {
                                            putout &= 127;
                                            ch = (int)putout;
                                            ch += 128;
                                        }
                                        if (ch != 9 && ch != 10 && ch < 32) {
                                            printf("^");
                                            putout += 64;
                                        } else if (ch == 127) {
                                            printf("^");
                                            putout = '?';
                                        } else if (ch > 127 && ch < 160) {
                                            printf("M-^");
                                            putout = ch - 64;
                                        } else if (ch > 160 && ch <= 255) {
                                            putout -= 128;
                                        }
                                        fputc(putout, stdout);
                                    }
                                break;
                                
                                case 'e':
                                    while ((putout = fgetc(f)) != EOF) {
                                        int ch = (int)putout;
                                        if (putout == '\n')
                                            printf("$");
                                        if (putout < 0) {
                                            putout &= 127;
                                            ch = (int)putout;
                                            ch += 128;
                                        }
                                        if (ch != 9 && ch != 10 && ch < 32) {
                                            printf("^");
                                            putout += 64;
                                        } else if (ch == 127) {
                                            printf("^");
                                            putout = '?';
                                        } else if (ch > 127 && ch < 160) {
                                            printf("M-^");
                                            putout = ch - 64;
                                        } else if (ch > 160 && ch <= 255) {
                                            putout -= 128;
                                        }
                                        fputc(putout, stdout);
                                    }
                                break;   
                            }
                        } else {
                            while ((putout = fgetc(f)) != EOF)
                                fputc(putout, stdout);
                        }
                    }
                if (check == -1)
                    break;
            }
    } else {
        printf("file not found");
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1)
        parce(argc, argv);
    else
        printf("error");
}
