#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

#define PANIC(fmt, ...) do {                                                        \
    fprint(stderr, "PANIC at %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    abort();                                                                        \
} while (0)

#define LOG_ERROR(fmt, ...) do {                                                     \
    fprintf(stderr, "ERROR at %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit(EXIT_FAILURE);                                                              \                                 
} while (0)                             

#define SYS_ERROR(message) do {                             \
    fprintf(stderr, "SYS_ERROR at %s:%d: ", __FILE__, __LINE__); \
    perror(message);                                             \
    exit(EXIT_FAILURE);                                         \
} while(0)    

const char *read_source_file(const char *path);