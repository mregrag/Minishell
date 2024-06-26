/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:16:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/02 00:10:56 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <sys/param.h>
# include <sys/wait.h>
#include <sys/stat.h>
# include <unistd.h>
# include "../lib/libft/libft.h"

# define ERRTOKEN "syntax error near unexpected token"
# define ERRSYNT "syntax error near unexpected token `newline'"
# define ERRSYNT "syntax error near unexpected token `newline'"

typedef enum e_type
{
	T_WORD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HERDOC,
}	t_type;

typedef struct s_env
{
	t_list *env;
} t_env;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_node
{
	char			**cmd;
	t_type			type;
	t_env			*env;
	int			flag;
	int			fdh;
	int			fd[2];
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_gb
{
	int	exit_status;
	int	signal;
}	t_gb;

extern t_gb	g_minish;
t_env *copy_env(t_env *original);
t_env *init_env(char **envp);
char *get_env_var(t_env *env, const char *name);
int set_env_var(t_env *env, const char *name, const char *value);
int unset_env_var(t_env *env, const char *name);
void print_env(t_env *env);
void free_env(t_env *env);
//------------------------tokens------------------------
t_token	*tokenize_input(char *input, t_env *env);
t_token	*new_token(char *value, t_type type);
void	clear_token(t_token **lst);
void	token_add_back(t_token **lst, t_token *new_token);
void	skip_spaces(char **str);
int		process_word(char **line, t_token **tokens);
int		process_word1(char **line, t_token **tokens);
int		add_separator(t_type type, char **line, t_token **token, char *value);
int		is_separator(char *s);
int		skip_quotes(char *line, size_t *i);
int		is_redirection(t_type type);
int		ft_lstsize_token(t_token *lst);

//------------------------parcing------------------------

t_node *parse_cmd(t_token **tokens, t_env *env);
t_node	*buil_tree(t_token **tokens);
t_node *parse_tokens(t_token **tokens, t_env *env);
t_node *create_redire(t_token **tokens, t_token *tmp, t_env *env);
t_node *create_file(t_token *token, t_type type, t_env *env);
void	free_tree(t_node *node);
void	creat_cmd(t_node *node, t_token **tokens, int count);
t_node *new_node(t_type type, t_env *env);
t_node *parse_redire(t_token **tokens, t_env *env);

//-----------------------------bultin---------------------------------

int		ft_echo(t_node *node);
int		ft_env(t_node *node);
int		ft_cd(t_node *node);
int		ft_exit(t_node *node);
int		ft_export(t_node *node);
int		ft_unset(t_node *node);
int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);
int		ft_pwd(void);

//-----------------------------env---------------------------------

// void	init_minishel(t_node *node, char **env);
t_node	*init_minishell(char **env);
void	create_env_var(char *var, char *value, t_node *node);
void	update_env_var(char *var, char *new_value, t_node *node);
// int update_env_var(t_env *env, const char *name, const char *value);
void	duplicate_env(t_node *node, char **envp);
// void	increment_shlvl(t_node *node);
void	increment_shlvl(t_env *env);
char	*ft_getenv(const char *key, t_list *env);

//---------------------------execution------------------------------------


char	*get_path(char *cmd, t_env *env);
void	executing(t_node *node);
void	exec_cmd(t_node *node);
void	exec_pipe(t_node *node);
int		is_builtin(t_node *node);
int		heredoc(t_node *node);
t_node *setup_heredoc(t_node *node, int *heredoc_fd);
int		ft_pipe(int ends[2]);
int		ft_dup2(int filde1, int filde2);
int		redirections(t_node *node);
int		ft_open(const char *path, int oflag, mode_t mode);
pid_t	ft_fork(void);
int 	ft_close(int fd);
int	ft_dup(int oldfd);
int	ft_dup2(int oldfd, int newfd);
int	ft_pipe(int pipefd[2]);

//---------------------expansion-------------------------------

char	*remov_quotes(char *str);
char	*expansion_input(char *str, t_node *node);
char	*handle_dollar(char *ret, char *str, size_t *i, t_node *node);
char	*handle_quotes(char *ret, char *str, size_t *i, t_node *node);
char	*expansion_file(char *str, t_node *env);
char	*expansion_dilim(char *str, t_node *node);
char	*handle_quotes_dilim(char *ret, const char *str, size_t *i);
char	*expansion_content(char *str, t_node *env);
char	*handle_single_quotes(char *ret, char *str, size_t *i);
char	*handle_double_quotes(char *ret, char *str, size_t *i, t_node *env);
char	*handle_normal(char *ret, char *str, size_t *i);
char	*handle_str(char *ret, char *str, size_t *i);

//-----------------------signals------------------
void	setup_signal(void);
void	exit_status(int status, t_node *node);
void	update_exit_status(t_node *node, int status);

int	deal_w_redir(t_node *node);
int	ft_redir(t_node *node);

int check_syntax(t_token *tokens);

// t_node *init_minishell(char **env);
void	reset_in_out(int *in, int *out);
int	exec_err(errno_t err, char *path, char *cmd);

void	sigint_h(int sigN);
void	sig_ign(void);
void	sig_allow(void);
void	heredoc_h(int n);
#endif
