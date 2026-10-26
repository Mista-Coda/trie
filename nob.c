#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    Cmd cmd = {0};
    cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-Wpedantic");
    cmd_append(&cmd, "main.c");
    cmd_append(&cmd, "-o", "trie");
    if (!cmd_run(&cmd)) return 1;
    return 0;
}
