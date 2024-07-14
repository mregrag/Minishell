/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:16:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/14 07:47:44 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <sys/param.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include "../lib/libft/libft.h"

typedef enum e_type
{
	T_CMD,
	T_PIPE,
	T_IN,
	T_OUT,
	T_APPEND,
	T_HERDOC,
}	t_type;

typedef struct s_env
{
	t_list	*env;
}	t_env;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_fd
{
	int		fd[2];
	int		fdh;
	int		in;
	int		out;
}	t_fd;

typedef struct s_node
{
	char			**cmd;
	t_type			type;
	t_env			*env;
	int			fdh;
	int			fd[2];
	int				flag;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

extern int	g_sig;

void	malloc_error(void);
//------------------------tokens------------------------
t_token	*tokenize_input(char *input, t_env *env);
t_token	*new_token(char *value, t_type type);
void	clear_tokens(t_token **head);
void	free_token(t_token *token);
void	token_add_back(t_token **lst, t_token *new_token);
void	skip_spaces(char **str);
int		skip_quotes(char *line, size_t *i);
int		is_redirection(t_type type);
int		ft_lstsize_token(t_token *lst);
t_type	get_operator_type(char *str);
int		check_operators(char *str);
int		is_operator(char *str);
int		check_quotes(char **line);

//------------------------parcing------------------------

t_node	*parse_command(t_token *tokens, t_env *env);
t_node	*parse_expression(t_token *tokens, t_env *env);
t_node	*parse_tokens(t_token *tokens, t_env *env);
t_node	*parse_file(t_token *token, t_type type, t_env *env);
t_node	*create_redire(t_token *tokens, t_token *tmp, t_env *env);
t_node	*new_node(t_type type);
t_node	*parse_redire(t_token *tokens, t_env *env);
void	free_tree(t_node *node);
void	creat_cmd(t_node *node, t_token *tokens, int count, t_env *env);
char	*extract_word(char **input);
int		check_syntax(t_token *tokens);

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

// ----------------------------env---------------------------------

 int fd_in(t_node *node);
void	increment_shlvl(t_env *env);
void	init_env(t_env **env, char **envp);
void	print_env(t_env *env);
void	set_env_var(t_env *env, char *name, char *value);
void	unset_env_var(t_env *env, char *name);
void	free_env(t_env *env);
void	set_std_fds(int in, int out);
void	get_std_fds(int *in_out);
void	append_env_var(t_env *env, char *var, char *value);
int		is_var_in_env(t_env *env, const char *var_name);
char	*get_env_var(t_env *env, char *name);

//---------------------------execution------------------------------------

int	ft_redir(t_node *node , t_env *env);
t_node	*find_heredoc(t_node *node);
char	*get_path(char *cmd, t_env *env);
void	executing(t_node *node, t_env *env);
void	exec_cmd(t_node *node, t_env *env);
void	heredoc_content(t_node *node, int fd, char *content, t_env *env);
int		execute_builtin(t_node *node, t_env *env);
int		heredoc(t_node *node, t_env *env);
int		check_file(t_node *node);
int		ft_pipe(int ends[2]);
int		ft_dup2(int filde1, int filde2);
int		redirections(t_node *node, t_env *env);
int		ft_open_append(char *file);
int		ft_open_output(char *file);
int		ft_open_input(char *file);
int		redir_input(t_node *node, t_env *env, int *fd);
int		redire_output(t_node *node, int *fd);
void		exec_pipe(t_node *node, t_env *env);
pid_t	ft_fork(void);
int		ft_dup(int oldfd);
int		ft_dup2(int oldfd, int newfd);
int		ft_pipe(int pipefd[2]);

//---------------------expansion-------------------------------

char	*remov_quotes(char *str);
char	*handle_quotes(char *ret, char *str, size_t *i, t_env *env);
char	*expansion_dilim(char *str);
char	*expansion_input(char *str, t_env *env);
char	*handle_dollar(char *ret, char *str, size_t *i, t_env *env);
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
void	signal_middle_exec(t_env *env);
void	handle_eof(t_env *envp);
int		exec_err(char *path, char *cmd, t_env *env);
#endif
