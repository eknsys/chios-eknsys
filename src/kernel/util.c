#include "util.h"

int strlen(const char *s) {
    int len = 0;
    while (s[len]) len++;
    return len;
}

int strcmp(const char *a, const char *b) {
    while (*a && (*a == *b)) {
        a++;
        b++;
    }
    return *(const unsigned char*)a - *(const unsigned char*)b;
}

int str_contains(const char *str, const char *substr) {
    if (!*substr) return 1;

    while (*str) {
        const char *a = str;
        const char *b = substr;

        while (*a && *b && (*a == *b)) {
            a++;
            b++;
        }

        if (!*b) return 1;

        str++;
    }

    return 0;
}

int str_starts_with(const char *str, const char *prefix) {
    while (*prefix) {
        if (*str != *prefix) return 0;
        str++;
        prefix++;
    }
    return 1;
}

int str_ends_with(const char *str, const char *suffix) {
    int len_str = strlen(str);
    int len_suf = strlen(suffix);

    if (len_suf > len_str) return 0;

    return strcmp(str + (len_str - len_suf), suffix) == 0;
}

void str_split_at(const char *str, char delimiter, char *left, char *right) {
    int i = 0;

    while (str[i] && str[i] != delimiter) {
        left[i] = str[i];
        i++;
    }
    left[i] = '\0';

    if (str[i] == '\0') {
        right[0] = '\0';
        return;
    }

    i++;
    int j = 0;
    while (str[i]) {
        right[j++] = str[i++];
    }
    right[j] = '\0';
}

void *memset(void *ptr, int value, int num) {
    unsigned char *p = ptr;
    for (int i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}

void *memcpy(void *dest, const void *src, int num) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    for (int i = 0; i < num; i++) {
        d[i] = s[i];
    }

    return dest;
}

void str_concat(char *dest, const char *a, const char *b) {
    int i = 0;

    while (a[i]) {
        dest[i] = a[i];
        i++;
    }

    int j = 0;
    while (b[j]) {
        dest[i++] = b[j++];
    }

    dest[i] = '\0';
}

void str_concat3(char *dest, const char *a, const char *b, const char *c) {
    int i = 0;

    while (a[i]) {
        dest[i] = a[i];
        i++;
    }

    int j = 0;
    while (b[j]) {
        dest[i++] = b[j++];
    }

    j = 0;
    while (c[j]) {
        dest[i++] = c[j++];
    }

    dest[i] = '\0';
}


uint8_t to_uint8_t(const char *str) {
    uint16_t value = 0;

    while (*str) {
        if (*str < '0' || *str > '9')
            break; // ungültiges Zeichen → abbrechen

        value = value * 10 + (*str - '0');

        if (value > 255)
            return 255; // clamp auf uint8_t max

        str++;
    }

    return (uint8_t)value;
}
