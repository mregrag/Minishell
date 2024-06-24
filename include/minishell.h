/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:16:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/24 22:13:21 by mregrag          ###   ########.fr       */
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
#include "../lib/libft/libft.h"

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


typedef struct s_node {
	t_token_type type;
	char **cmd;
	struct s_node *left;
	struct s_node *right;
} t_node;

typedef struct s_gb {
	int exit_status;
	int signal;
	char *dpath;
	int	input;
	int	output;
	t_list *env;
} t_gb;

extern t_gb minish;

int heredoc(t_node *node);
int	ft_close(int fd);
int	*setup_heredocs(t_node *node, int *heredoc_count);
pid_t	ft_fork(void);
int	ft_pipe(int ends[2]);
int	ft_dup2(int filde1, int filde2);
int ft_lstsize_token(t_token *lst);
char *ft_getenv(char *key);
void create_environment_var(char *token_str, t_list **env);
void update_environment_var(char *var, char *new_value, t_list *env);
void replace_one_var(char **str);
char *replace_env_value(char **env_ptr, char *var_name, char *new_value);
void update_env_var(char *var, char *new_value, t_list *env);

void create_env_var(char *token_str, t_list **env);

int is_env_var(char *var, t_list *env);

t_token *tokenize_input(char *s);
void exit_status(int status);
void update_env_val(char *value, char *var);
void update_env_var(char *var, char *new_value, t_list *env);

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
char	*expansion_input(char *str);
char *handle_dollar(char *ret, const char *str, size_t *i);
char *handle_quote(char *ret, const char *str, size_t *i, char quote);
char *expansion_file(char *str);
char	*handle_dollar(char *ret, const char *str, size_t *i);
char	*expansion_content(char *str);
char	*handle_single_quotes(char *ret, const char *str, size_t *i);
char	*handle_double_quotes(char *ret, const char *str, size_t *i);
char	*handle_normal(char *ret, const char *str, size_t *i);

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

int redirections(t_node *node);
t_node *create_file(t_token *token);
int ft_open(const char *path, int oflag, mode_t mode);
int redirections(t_node *node);

#endif
