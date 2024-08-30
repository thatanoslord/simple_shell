#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* llopedshell.c */
int shell_hsh(info_t *, char **);
int shell_find_builtin(info_t *);
void shell_find_cmd(info_t *);
void shell_fork_cmd(info_t *);

/* pars.c */
int shell_is_cmd(info_t *, char *);
char *shell_dup_chars(char *, int, int);
char *shell_find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* error.c */
void shell_eputs(char *);
int shell_eputchar(char);
int shell_putfd(char c, int fdd);
int shell_putsfd(char *strr, int fdd);

/* string.c */
int shell_strlen(char *);
int shell_strcmp(char *, char *);
char *shell_starts_with(const char *, const char *);
char *shell_strcat(char *, char *);

/* string1.c */
char *shell_strcpy(char *, char *);
char *shell_strdup(const char *);
void shell_puts(char *);
int shell_putchar(char);

/* ext.c */
char *shell_strncpy(char *, char *, int);
char *shell_strncat(char *, char *, int);
char *shell_strchr(char *, char);

/* strtow.c */
char **shell_strtow(char *, char *);
char **shell_strtow2(char *, char);

/* memset.c */
char *shell_memset(char *, char, unsigned int);
void shell_ffree(char **);
void *shell_realloc(void *, unsigned int, unsigned int);

/* memo_func.c */
int shell_bfree(void **);

/* _artoint.c */
int my_interactive(info_t *);
int my_is_delim(char, char *);
int my_isalpha(int);
int my_atoi(char *);

/* error1.c */
int shell_erratoi(char *);
void shell_print_error(info_t *, char *);
int shell_print_d(int, int);
char *shell_convert_number(long int, int, int);
void shell_remove_comments(char *);

/* builtin.c */
int my_myexit(info_t *);
int my_mycd(info_t *);
int my_myhelp(info_t *);

/* builtin1.c */
int shell_myhistory(info_t *);
int shell_myalias(info_t *);

/*getln.c */
ssize_t shell_get_input(info_t *);
int shell_getline(info_t *, char **, size_t *);
void shell_sigintHandler(int);

/* info_func.c */
void shell_clear_info(info_t *);
void shell_set_info(info_t *, char **);
void shell_free_info(info_t *, int);

/* environ.c */
int shell_myenv(info_t *);
char *shell_getenv(info_t *, const char *);
int shell_mysetenv(info_t *);
int shell_myunsetenv(info_t *);
int shell_populate_env_list(info_t *);

/*getenviron.c */
char **shell_get_environ(info_t *);
int shell_unsetenv(info_t *, char *);
int shell_setenv(info_t *, char *, char *);

/* history_func.c */
char *shell_get_history_file(info_t *infoo);
int shell_write_history(info_t *infoo);
int shell_read_history(info_t *infoo);
int shell_build_history_list(info_t *infoo, char *buf, int linecount);
int shell_renumber_history(info_t *infoo);

/* lists.c */
list_t *shell_add_node(list_t **, const char *, int);
list_t *shell_add_node_end(list_t **, const char *, int);
size_t shell_print_list_str(const list_t *);
int shell_delete_node_at_index(list_t **, unsigned int);
void shell_free_list(list_t **);

/* lists1.c */
size_t shell_list_len(const list_t *);
char **shell_list_to_strings(list_t *);
size_t shell_print_list(const list_t *);
list_t *shell_node_starts_with(list_t *, char *, char);
ssize_t shell_get_node_index(list_t *, list_t *);

/* vars.c */
int shell_is_chain(info_t *, char *, size_t *);
void shell_check_chain(info_t *, char *, size_t *, size_t, size_t);
int shell_replace_alias(info_t *);
int shell_replace_vars(info_t *);
int shell_replace_string(char **, char *);

#endif
