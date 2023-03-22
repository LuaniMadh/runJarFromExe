
#include "jar.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
#if !defined JAR || !defined CALL_CMD
    printf("Error: please define JAR and CALL_CMD in jar.c!\n");
    return 1;
#endif

    int cmdlen = strlen(CALL_CMD);
    int pathlen = strlen(JAR);

    int arglengths = cmdlen + 1 + pathlen + 1; // the first space is counted
    for (int i = 1; i < argc; i++)
    {
        arglengths += strlen(argv[i]);
        arglengths++;
    }
    char *cmd = malloc(sizeof(char) * arglengths);
    strcpy(cmd, CALL_CMD);
    cmd[cmdlen] = ' ';
    strcpy(cmd + cmdlen + 1, JAR);
    cmd[cmdlen + 1 + pathlen] = ' ';
    char *dest = cmd + cmdlen + 1 + pathlen + 1;
    for (int i = 1; i < argc; i++)
    {
        strcpy(dest, argv[i]);
        dest += strlen(argv[i]) + 1;
        *(dest - 1) = ' ';
    }
    *(dest - 1) = '\0';

#ifdef DEBUG
    printf(cmd);
#endif
#ifndef DEBUG
    return system(cmd);
#endif
}