#ifndef SHELL_H
#define SHELL_H

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
 *					allowing uniform prototype for function pointer struct
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
} details_t;

#define DETAILS_INIT \
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
	int (*func)(details_t *);
} builtin_table;


/* hsh.c */
int msl(details_t *, char **);
int finding_builtin(details_t *);
void finding_cmd(details_t *);
void forking_cmd(details_t *);

/* path.c */
int is_command(details_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(details_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fdescrip);
int _putsfd(char *str, int fdescrip);

/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtowords(char *, char *);
char **strtowords2(char *, char);

/* memory_functions */
char *_memset(char *, char, unsigned int);
void _free(char **);
void *_realloc(void *, unsigned int, unsigned int);
int freeAndNull(void **);

/* more_functions.c */
int interactive(details_t *);
int is_delim(char, char *);
int _isalpha(int);
int str_to_int(char *);
int err_str_to_int(char *);
void print_error(details_t *, char *);
int print_decimal(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);

/* builtin_emulators.c */
int _ourexit(details_t *);
int _ourcd(details_t *);
int _ourhelp(details_t *);

/* builtin_emulators2.c */
int _ourhistory(details_t *);
int _ouralias(details_t *);

/* getline.c module */
ssize_t get_input(details_t *);
int _getline(details_t *, char **, size_t *);
void signintHandler(int);

/* info.c module */
void clearing_info(details_t *);
void setting_info(details_t *, char **);
void freeing_info(details_t *, int);

/* env.c module */
char *_getenv(details_t *, const char *);
int _ourenv(details_t *);
int _oursetenv(details_t *);
int _ourunsetenv(details_t *);
int increase_env_list(details_t *);

/* env2.c module */
char **get_environ(details_t *);
int _envunset(details_t *, char *);
int _setsenv(details_t *, char *, char *);

/* file_io_functions.c */
char *getting_history_file(details_t *details);
int writing_history(details_t *details);
int reading_history(details_t *details);
int building_history_list(details_t *details, char *buff, int linecount);
int renumbering_history(details_t *details);

/* liststr.c module */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *find_node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* chain.c */
int is_chain(details_t *, char *, size_t *);
void checking_chain(details_t *, char *, size_t *, size_t, size_t);
int replacing_alias(details_t *);
int replacing_vars(details_t *);
int replacing_string(char **, char *);

#endif
