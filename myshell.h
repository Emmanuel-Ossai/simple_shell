#ifndef MY_SHELL_H
#define MY_SHELL_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>

#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_STRTOK 0
#define USE_GETLINE 0
#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"

extern char **environ;

/**
 * struct liststr - a struct that list singly-linked list
 * @num: the number
 * @str: a string passed
 * @next: the next node
 **/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;


/**
 * struct passinfo - a struct that get argv and pass info to a function
 * @arg: the argument
 * @argv: the argument vector
 * @path: the path of command
 * @argc: the argument count
 * @line_count: count of error
 * @err_num: the code of error in exit
 * @linecount_flag: the line count
 * @fname: the filename of program
 * @env: the environment
 * @environ: the modified environment
 * @history: the history
 * @alias: the alias
 * @env_changed: the changed environment
 * @status: the status of last actioned command
 * @cmd_buf: the cmd buffer
 * @cmd_buf_type: the cmd buffer type
 * @readfd: the input line read
 * @histcount: the history count
 **/
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

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - a struct of builtin strings
 * @type: the builtin type
 * @func: the function of the program
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int builtin_check(info_t *);
void cmd_check(info_t *);
void fork_cmd(info_t *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *path_check(info_t *, char *, char *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _puts_str(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *string_copy(char *, char *);
char *duplicate_str(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **_string_t(char *str, char *d);
char **_string_t2(char *str, char d);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int synergy(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int str_int(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void uncomment(char *);
int _myexit(info_t *);
int _cd(info_t *);
int _help(info_t *);
int _history(info_t *);
int _alias(info_t *);
ssize_t _input_catch(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_getenv(info_t *, const char *);
int _env(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int environ_list(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char *check_hist(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int history_built(info_t *info, char *buf, int linecount);
int hist_organize(info_t *info);
list_t *node_addition(list_t **, const char *, int);
list_t *_add_ext(list_t **, const char *, int);
size_t strlist_print(const list_t *);
int del_indx(list_t **, unsigned int);
void list_freed(list_t **);
size_t list_len(const list_t *);
char **string_n_list(list_t *);
size_t print_list(const list_t *);
list_t *prefix_node(list_t *, char *, char);
ssize_t node_ind_check(list_t *, list_t *);
int chain_conf(info_t *, char *, size_t *);
void chain_chekd(info_t *, char *, size_t *, size_t, size_t);
int alias_change(info_t *);
int vars_change(info_t *);
int replace_string(char **, char *);

#endif
