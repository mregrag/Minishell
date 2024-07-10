/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoualil <mkoualil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:16:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/10 23:59:22 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <signal.h>
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

# define OUT_FLAG  O_CREAT | O_WRONLY | O_TRUNC
# define APP_FLAG  O_CREAT | O_WRONLY | O_APPEND
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
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_gb
{
	int	signal;
}	t_gb;

extern t_gb	g_minish;

int	update_status(int status);
void	malloc_error(int error);
t_token	*process_tokenize(char *input, t_env *env);
t_token *tokenize(char *input);
void free_tokens(t_token *head);
t_env *copy_env(t_env *original);
void    init_env(t_env **env, char **envp);
char *get_env_var(t_env *env, char *name);
void	set_env_var(t_env *env, char *name, char *value);
void  unset_env_var(t_env *env, char *name);
void print_env(t_env *env);
void free_env(t_env *env);
int	 is_var_in_env(t_env *env, const char *var_name);
//------------------------tokens------------------------
t_token	*tokenize_input(char *input, t_env *env);
t_token	*new_token(char *value, t_type type);
void	clear_tokens(t_token **head);
void	token_add_back(t_token **lst, t_token *new_token);
void	skip_spaces(char **str);
int		skip_quotes(char *line, size_t *i);
int		is_redirection(t_type type);
int		ft_lstsize_token(t_token *lst);
t_type	get_operator_type(char *str);
int	check_operators(char *str);
int	is_operator(char *str);
int	check_quotes(char **line);
void	free_token(t_token *token);

//------------------------parcing------------------------

char	*extract_word(char **input);
t_node *parse_command(t_token **tokens, t_env *env);
t_node	*parse_expression(t_token **tokens, t_env *env);
t_node *parse_tokens(t_token **tokens, t_env *env);
t_node *parse_file(t_token *token, t_type type, t_env *env);
void	free_tree(t_node *node);
void	creat_cmd(t_node *node, t_token **tokens, int count, t_env *env);
t_node *new_node(t_type type);
t_node *parse_redire(t_token **tokens, t_env *env);

//-----------------------------bultin---------------------------------

int		ft_echo(t_node *node, t_env *env);
int		ft_env(t_node *node, t_env *env);
int		ft_cd(t_node *node, t_env *env);
int		ft_exit(t_node *node, t_env *env);
int		ft_export(t_node *node, t_env *env);
int		ft_unset(t_node *node, t_env *env);
int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);
int		ft_pwd(void);

//-----------------------------env---------------------------------

t_node	*init_minishell(char **env);
void	create_env_var(char *var, char *value, t_node *node);
void	update_env_var(char *var, char *new_value, t_node *node);
void	duplicate_env(t_node *node, char **envp);
void	increment_shlvl(t_env *env);
char	*ft_getenv(const char *key, t_list *env);

//---------------------------execution------------------------------------


char	*get_path(char *cmd, t_env *env);
void	executing(t_node *node, t_env *env);
void	exec_cmd(t_node *node, t_env *env);
void	exec_pipe(t_node *node, t_env *env);
int	execute_builtin(t_node *node, t_env *env);
int		heredoc(t_node *node, t_env *env);
t_node *setup_heredoc(t_node *node, int *heredoc_fd, t_env *env);
int		ft_pipe(int ends[2]);
int		ft_dup2(int filde1, int filde2);
int		redirections(t_node *node, t_env *env);
int		ft_open(const char *path, int oflag, mode_t mode);
pid_t	ft_fork(void);
int 	ft_close(int fd);
int	ft_dup(int oldfd);
int	ft_dup2(int oldfd, int newfd);
int	ft_pipe(int pipefd[2]);

//---------------------expansion-------------------------------

char	*remov_quotes(char *str);
char	*expansion_input(char *str, t_env *env);
char	*handle_dollar(char *ret, char *str, size_t *i, t_env *env);
char	*handle_quotes(char *ret, char *str, size_t *i, t_env *env);
char	*expansion_file(char *str, t_env *env);
char	*expansion_dilim(char *str);
char	*handle_quotes_dilim(char *ret, const char *str, size_t *i);
char	*expansion_content(char *str, t_env *env);
char	*handle_single_quotes(char *ret, char *str, size_t *i);
char	*handle_double_quotes(char *ret, char *str, size_t *i, t_env *env);
char	*handle_normal(char *ret, char *str, size_t *i);
char	*handle_str(char *ret, char *str, size_t *i);

//-----------------------signals------------------
void	setup_signal(t_env *envp);
void	exit_status(int status, t_env *env);
void	block_signals(struct sigaction *sa_ignore);
void	set_signal_heredoc(void);
void	restore_signals(struct sigaction *sa_default);
void	signal_handlers(struct sigaction *sa_ig, struct sigaction *sa_def);


int check_syntax(t_token *tokens);
int	exec_err(char *path, char *cmd);

#endif
