#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <errno.h>

void find_file(int argc, char* argv[]);
void s21_grep(FILE* f, int argc, char* argv[], int j, int i, int files, int woflags);
void check_n(FILE* f, char* line_from_file);

int main(int argc, char* argv[]) {
    if (argc > 2)
        find_file(argc, argv);
}

void find_file(int argc, char* argv[]) {
    FILE *f;
    int files = 0;
    int woflags = 0;
    int fori = 2;
    for (int j = 1; j < argc; j++) {
        if (argv[j][0] == '-') {
            for (int i = 2; i < argc - 1; i++) {
                if (argc > 4)
                    files++;
                f = fopen(argv[i + j], "r+");
                s21_grep(f, argc, argv, j, i, files, woflags);
                fclose(f);
            }
            break;
        } else if (argv[j+1][0] == '-') {
            for (int i = 2; i < argc - 1; i++) {
                if (argc > 4)
                    files++;
                f = fopen(argv[i + j], "r+");
                s21_grep(f, argc, argv, j, i, files, woflags);
                fclose(f);
            }
            break;
        } else {
            if (argv[1][0] != '-')
                woflags++;
            if (argc > 3) {
                files++;
                for (; fori <= argc - 1; fori++) {
                    if (woflags)
                    f = fopen(argv[fori], "r+");
                    s21_grep(f, argc, argv, 0, fori, files, woflags);
                    fclose(f);
                }
            } else {
                f = fopen(argv[2], "r+");
                if (f) {
                    s21_grep(f, argc, argv, j, 0, files,  woflags);
                    fclose(f);
                    break;
                } else {
                    break;
                }
            }
            break;
        }
    }
}

void s21_grep(FILE* f, int argc, char* argv[], int j, int i, int files, int woflags) {
    FILE* f2;
    regex_t regex;
    size_t line_size = 0;
    size_t len;
    char *line_from_file = NULL;
    int str_num = 0;
    int for_c = 0;
    int legit = -1;
    int option;
    option = getopt(argc, argv, "e:i:v:c:l:n:h:s:f:o:");
        switch (option) {
        case 'e':
                if (f) {
                    regcomp(&regex, optarg, 0);
                    while (getline(&line_from_file, &line_size, f) != -1) {
                        legit = regexec(&regex, line_from_file, 0, NULL, 0);
                        if (legit == 0) {
                            if (files) {
                                printf("%s:%s", argv[i + j], line_from_file);
                            } else {
                                printf("%s", line_from_file);
                            }
                            check_n(f, line_from_file);
                        }
                    }
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;

        case 'i':
                if (f) {
                    regcomp(&regex, optarg, REG_ICASE);
                    while (getline(&line_from_file, &line_size, f) != -1) {
                        legit = regexec(&regex, line_from_file, 0, NULL, 0);
                        if (legit == 0) {
                            if (files)
                                printf("%s:%s", argv[i + j], line_from_file);
                            else
                                printf("%s", line_from_file);
                            check_n(f, line_from_file);
                        }
                        if (files)
                            optind = 1;
                    }
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;

        case 'v':
            if (f) {
                    regcomp(&regex, optarg, 0);
                    while (getline(&line_from_file, &line_size, f) != -1) {
                        legit = regexec(&regex, line_from_file, 0, NULL, 0);
                        if (legit != 0) {
                            if (files)
                                printf("%s:%s", argv[i + j], line_from_file);
                            else
                                printf("%s", line_from_file);
                            check_n(f, line_from_file);
                        }
                        if (files)
                            optind = 1;
                    }
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;

        case 'c':
                if (f) {
                    regcomp(&regex, optarg, 0);
                    while (getline(&line_from_file, &line_size, f) != -1) {
                        legit = regexec(&regex, line_from_file, 0, NULL, 0);
                        if (legit == 0)
                            for_c++;
                    }
                    if (files) {
                        printf("%s:%d\n", argv[i+j], for_c);
                        optind = 1;
                    } else {
                        printf("%d\n", for_c);
                    }
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;

        case 'l':
                if (f) {
                    int check = 0;
                    regcomp(&regex, optarg, 0);
                    while (getline(&line_from_file, &line_size, f) != -1) {
                        legit = regexec(&regex, line_from_file, 0, NULL, 0);
                        if (legit >= 0)
                            check++;
                    }
                    if (check)
                        printf("%s\n", argv[j+i]);
                    if (files)
                            optind = 1;
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;

        case 'n':
                if (f) {
                regcomp(&regex, optarg, 0);
                while (getline(&line_from_file, &line_size, f) != -1) {
                    str_num++;
                    legit = regexec(&regex, line_from_file, 0, NULL, 0);
                    if (legit == 0) {
                        if (files)
                            printf("%s:%d:%s", argv[i+j], str_num, line_from_file);
                        else
                            printf("%d:%s", str_num, line_from_file);
                        check_n(f, line_from_file);
                    }
                    if (files)
                        optind = 1;
                }
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;

        case 'h':
                if (f) {
                    regcomp(&regex, optarg, 0);
                    while (getline(&line_from_file, &line_size, f) != -1) {
                        legit = regexec(&regex, line_from_file, 0, NULL, 0);
                        if (legit == 0) {
                            printf("%s", line_from_file);
                            check_n(f, line_from_file);
                        }
                        if (files)
                            optind = 1;
                    }
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;

        case 's':
                if (f) {
                    regcomp(&regex, optarg, 0);
                    while (getline(&line_from_file, &line_size, f) != -1) {
                        legit = regexec(&regex, line_from_file, 0, NULL, 0);
                        if (legit == 0) {
                            printf("%s", line_from_file);
                            check_n(f, line_from_file);
                        }
                        if (files)
                            optind = 1;
                    }
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;

        case 'f':
                if (f) {
                    f2 = fopen(optarg, "r+");
                    if (f2) {
                        char *line_from_tmp_file = NULL;
                        int leng;
                        while (getline(&line_from_tmp_file, &line_size, f2) != -1) {
                            leng = strlen(line_from_tmp_file);
                            if (line_from_tmp_file[leng-1] == '\n')
                                line_from_tmp_file[leng-1] = 0;
                            regcomp(&regex, line_from_tmp_file, 0);
                            while (getline(&line_from_file, &line_size, f) != -1) {
                                legit = regexec(&regex, line_from_file, 0, NULL, 0);
                                if (legit == 0) {
                                    if (files)
                                        printf("%s:%s", argv[i+j], line_from_file);
                                    else
                                        printf("%s", line_from_file);
                                    check_n(f, line_from_file);
                                }
                                if (files)
                                    optind = 1;
                            }
                        }
                        free(line_from_tmp_file);
                    } else {
                        printf("s21_grep: %s: No such file or directory\n", argv[j+1]);
                    }
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                fclose(f2);
                regfree(&regex);
            break;

        case 'o':
                if (f) {
                    int roll = 0;
                    int buffroll;
                    regmatch_t match;
                    size_t offset;
                    regcomp(&regex, optarg, 0);
                    while (getline(&line_from_file, &line_size, f) != -1) {
                            roll++;
                            offset = 0;
                            len = strlen(line_from_file);
                            while (regexec(&regex, line_from_file + offset, 1, &match, 0) == 0) {
                                if (files && buffroll != roll) {
                                    buffroll = roll;
                                    printf("%s:%s\n", argv[i+j], optarg);
                                } else {
                                    printf("%s\n", optarg);
                                }
                                offset += match.rm_eo;
                                if (match.rm_so == match.rm_eo)
                                    offset += 1;
                                if (offset > len)
                                    break;
                            }
                    }
                    if (files)
                        optind = 1;
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;

        default:
                if (f) {
                    if (files && !woflags)
                        regcomp(&regex, argv[2], 0);
                    else
                        regcomp(&regex, argv[1], 0);
                    while (getline(&line_from_file, &line_size, f) != -1) {
                        legit = regexec(&regex, line_from_file, 0, NULL, 0);
                        if (legit == 0) {
                            if (files)
                                printf("%s:%s", argv[i + j], line_from_file);
                            else
                                printf("%s", line_from_file);
                            check_n(f, line_from_file);
                        }
                    }
                } else {
                    printf("s21_grep: %s: No such file or directory\n", argv[j+2]);
                }
                regfree(&regex);
            break;
        }
    free(line_from_file);
}

void check_n(FILE* f, char* line_from_file) {
    int check = getc(f);
    int len = strlen(line_from_file);
    if (check == EOF && line_from_file[len-1] != '\n')
        printf("\n");
    ungetc(check, f);
}
