/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:16:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/12 22:13:15 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <unistd.h>

#define ERROR_SYNTAX "syntax error near unexpected token"


typedef enum e_token_type {
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HERDOC,
} t_token_type;

typedef struct s_token {
	t_token_type type;
	char *value;
	struct s_token *next;
} t_token;

typedef struct s_env {
	char *env;
	struct s_env *next;
} t_env;

typedef struct s_node {
	t_token_type type;
	char **cmd;
	int fd[2];
	int flg;
	int fdh;
	struct s_node *left;
	struct s_node *right;
} t_node;

typedef struct s_gb {
	int exit_status;
	int signal;
	char *dpath;
	int	fd[2];
	t_env *env;
} t_gb;

extern t_gb minish;

int ft_atoi(const char *str);
void ft_putstr_fd(char *s, int fd);
void ft_putchar_fd(char c, int fd);
void ft_lstadd_back(t_env **lst, t_env *new);
void ft_lstadd_front(t_env **lst, t_env *new);
int ft_lstsize(t_env *lst);
int ft_strcmp(const char *s1, const char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strdup(const char *s);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strchr(const char *s, int c);
char *ft_strtrim(char const *s1, char const *set);
char *ft_substr(const char *s, unsigned int start, size_t len);
size_t ft_strlen(const char *s);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
void *ft_calloc(size_t count, size_t size);
int ft_isspace(char c);
char **ft_split(char const *s, char c);
int ft_isalpha(int c);
int ft_isalnum(int c);
int ft_isdigit(int c);
char *ft_strjoin_f(char *s1, char *s2);
int ft_lstsize_token(t_token *lst);
int ft_memcmp(const void *s1, const void *s2, size_t n);
char *ft_itoa(int n);
int ft_isdollar(int c);
int ft_issamechar(char *str, int c);
int ft_isoddeven_char(char *str, int c);
void *ft_memset(void *b, int c, size_t len);
void ft_bzero(void *s, size_t n);
t_env *ft_lstnew(char *content);
void ft_lstclear(t_env **lst, void (*del)(void *));
char *ft_getenv(char *key);
void create_environment_var(char *token_str, t_env **env);
void update_environment_var(char *var, char *new_value, t_env *env);
void replace_one_var(char **str);
char *replace_env_value(char **env_ptr, char *var_name, char *new_value);
void update_env_var(char *var, char *new_value, t_env *env);
size_t ft_strlen_arg(char **args);

void create_env_var(char *token_str, t_env **env);
char **ft_list_to_arr(t_env *lst);

int is_env_var(char *var, t_env *env);

t_token *tokenize_input(char *s);
void exit_status(int status);
void update_env_val(char *value, char *var);
void update_env_var(char *var, char *new_value, t_env *env);

int ft_isquotes(int c);
int is_separator(char *s);
void ft_skip_spaces(char **str);
int skip_quotes(char *line, size_t *i);
void quotes_error(char c);

int append_identifier(char **line_ptr, t_token **token_list);

int append_separator(t_token_type type, char **line_ptr, t_token **token_list,
		char *value);

void clear_token(t_token **lst);
void token_add_back(t_token **lst, t_token *new_token);
t_token *new_token(char *value, t_token_type type);

void exit_status(int status);
size_t ft_get_index(char *s, int c);
void initialize(char **env);

//------------------------------------execution------------------------------------

void executing(t_node *node);
void exec_cmd(t_node *node);
char *get_path_command(char *cmd);
char *find_path(char **env);
int is_builtin(char **arg);
char *get_env_val(char *key);

//-----------------------------bultin---------------------------------

int ft_echo(char **args);
int ft_env(char **args);
void ft_pwd(void);
int ft_cd(char **cmd);
int ft_exit(char **cmd);
int ft_unset(char **cmd);
int ft_export(char **argv);
int print_error(char *s1, char *s2, char *s3, char *message);
int print_error_errno(char *s1, char *s2, char *s3);
char *get_env_var(char *var);

//---------------------expanding-------------------------------

char *remov_quotes(char *str);
char *expand_cmd(char *str);
char *expand_heredoc(char *str);
bool ft_is_valid_var_char(char c);
char *handle_str(char *str, size_t *i);
char *handle_sq(char *str, size_t *i);
char *handle_dq(char *str, size_t *i);
char *handle_dollar(char *str, size_t *i);

//------------------------test------------------------

t_node *parse_cmd(t_token **tokens);
t_node *parse_redire(t_token **tokens);
t_node *buil_tree(t_token **tokens);
t_node *parse_tokens(t_token **tokens);
t_node *new_node(t_token_type type);
void free_treet(t_node *node);
t_node *create_redire(t_token **tokens, t_token *tmp);
void creat_cmd(t_node *node, t_token **tokens, int count);

void exec_pipe(t_node *node);

//-----------------------signals------------------
void setup_signal(void);

void init_minishell(t_gb *msh, char **envp);

int ft_redir(t_node *node);
t_node *create_file(t_token *token);
int ft_open(const char *path, int oflag, mode_t mode);
int redirections(t_node *node);
char	*expand_file(char *str);

#endif
