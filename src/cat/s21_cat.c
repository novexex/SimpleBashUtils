#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>

void find_file(int argc, char* argv[]);
void processing_flags(FILE* f, int argc, char* argv[], int j);

int main(int argc, char* argv[]) {
    if (argc > 1)
        find_file(argc, argv);
    else
        printf("Ввод через stdin обрабатывать не обязательно\n");
}

void find_file(int argc, char* argv[]) {
    FILE* f;
        for (int j = 1; j < argc; j++) {
            if (argv[j][0] != '-') {
                f = fopen(argv[j], "r+");
                processing_flags(f, argc, argv, j);
                fclose(f);
            }
        }
}

void processing_flags(FILE* f, int argc, char* argv[], int j) {
        static struct option long_opt[] = {
        {"number-nonblank", no_argument, NULL, 'b'},
        {"number", no_argument, NULL, 'n'},
        {"squeeze-blank", no_argument, NULL, 's'}
        };

        if (f) {
        int useless;
        int schet = 1;
        char putout;
        char prev = '\n';
        char preprev;
        int check = getopt_long(argc, argv, "beEnstTv", long_opt, &useless);
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
            }
        if (check == -1) {
            while ((putout = fgetc(f)) != EOF)
            fputc(putout, stdout);
        }
    } else {
        printf("s21_cat: %s: %s\n", argv[j], strerror(errno));
    }
}
