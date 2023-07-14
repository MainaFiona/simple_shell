#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer */

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chain */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* Digit conversion */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* usage of System getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* Simple shell history */
#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;

/**
 * struct lister - list 
 * @num: field num
 * @str: string
 * @next: next node
 */
typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

/**
 *struct passinfo - pseudo-arguements to pass into a function,
 *allowing uniform prototype for function pointer struct
 *@arg: string generated from getline containing arguements
 *@argv: array of strings generated from arguments
 *@path: string path for the current command
 *@argc: argument count
 *@line_count: error count
 *@err_num: error code for exit()s
 *@linecount_flag: count line of input
 *@fname: program filename
 *@env: linked list local copy of environ
 *@environ: modified copy of environ from LL env
 *@history: history node
 *@alias: alias node
 *@env_changed: environ was changed
 *@status: return status of last exec'd command
 *@cmd_buff: address of pointer to cmd_buff, on if chaining
 *@cmd_buff_type: CMD_type ||, &&, ;
 *@readfd: fd from which to read line input
 *@histcount: history line number count
 */
typedef struct passinfo
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **environ;
        int env_changed;
        int status;

        char **cmd_buff;
        int cmd_buff_type;
        int readfd;
        int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

