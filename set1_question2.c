#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

static void skipSpaces(char **p) {
    while (**p == ' ' || **p == '\t' || **p == '\n' || **p == '\r')
        (*p)++;
}

static int parseExpression(char **p);
static int parseTerm(char **p);
static int parseFactor(char **p);

static int parseFactor(char **p) {
    int value = 0, sign = 1;
    skipSpaces(p);

    if (**p == '+') {
        (*p)++;
        return parseFactor(p);
    }
    if (**p == '-') {
        sign = -1;
        (*p)++;
    }

    skipSpaces(p);
    if (**p == '(') {
        (*p)++;
        value = parseExpression(p);
        skipSpaces(p);
        if (**p != ')') {
            printf("Invalid expression\n");
            exit(1);
        }
        (*p)++;
        return sign * value;
    }

    if (**p < '0' || **p > '9') {
        printf("Invalid expression\n");
        exit(1);
    }

    while (**p >= '0' && **p <= '9') {
        value = value * 10 + (**p - '0');
        (*p)++;
    }

    return sign * value;
}

static int parseTerm(char **p) {
    int value = parseFactor(p);
    skipSpaces(p);

    while (**p == '*' || **p == '/') {
        char op = **p;
        (*p)++;
        int rhs = parseFactor(p);
        if (op == '*')
            value *= rhs;
        else {
            if (rhs == 0) {
                printf("Division by zero is not allowed\n");
                exit(1);
            }
            value /= rhs;
        }
        skipSpaces(p);
    }
    return value;
}

static int parseExpression(char **p) {
    int value = parseTerm(p);
    skipSpaces(p);

    while (**p == '+' || **p == '-') {
        char op = **p;
        (*p)++;
        int rhs = parseTerm(p);
        if (op == '+')
            value += rhs;
        else
            value -= rhs;
        skipSpaces(p);
    }
    return value;
}

int main(int argc, char *argv[]) {
    char expr[MAX];
    char *p;

    if (argc > 1) {
        int i;
        char *dest = expr;
        for (i = 1; i < argc; i++) {
            while (*argv[i])
                *dest++ = *argv[i]++;
            if (i < argc - 1)
                *dest++ = ' ';
        }
        *dest = '\0';
    } else {
        printf("Enter expression: ");
        if (!fgets(expr, sizeof(expr), stdin)) {
            printf("Invalid expression\n");
            return 1;
        }
        expr[strcspn(expr, "\r\n")] = '\0';
    }

    p = expr;
    skipSpaces(&p);
    int result = parseExpression(&p);
    skipSpaces(&p);

    if (*p != '\0') {
        printf("Invalid expression\n");
        return 1;
    }

    printf("%d\n", result);
    return 0;
}
