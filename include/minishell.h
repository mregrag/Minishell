/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:16:44 by mregrag           #+#    #+#             */
/*   Updated: 2024/06/27 23:48:28 by mregrag          ###   ########.fr       */
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
# include <sys/param.h>
# include <sys/wait.h>
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

typedef struct	s_env
{
	t_list	*env;
}	t_env;

typedef struct s_token
{
	char			*value;
	t_type			type;
	int			flag;
	struct s_token	*next;
}	t_token;

typedef struct s_node
{
	char			**cmd;
	t_type			type;
	t_list			*env;
	t_token			dilim;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_gb
{
	int	exit_status;
}	t_gb;

extern t_gb	g_minish;
//------------------------tokens------------------------
t_token	*tokenize_input(char *input, t_node *node);
t_token	*new_token(char *value, t_type type);
void	clear_token(t_token **lst);
void	token_add_back(t_token **lst, t_token *new_token);
void	skip_spaces(char **str);
int		process_word(char **line, t_token **tokens);
int		add_separator(t_type type, char **line, t_token **token, char *value);
int		is_separator(char *s);
int		skip_quotes(char *line, size_t *i);
int		is_redirection(t_type type);
int		ft_lstsize_token(t_token *lst);

//------------------------parcing------------------------

t_node *parse_cmd(t_token **tokens, t_list *env);
t_node	*buil_tree(t_token **tokens);
t_node *parse_tokens(t_token **tokens, t_list *env);
t_node *create_redire(t_token **tokens, t_token *tmp, t_list *env);
t_node *create_file(t_token *token, t_type type, t_list *env);
void	free_treet(t_node *node);
void	creat_cmd(t_node *node, t_token **tokens, int count);
t_node *new_node(t_type type, t_list *env);
t_node *parse_redire(t_token **tokens, t_list *env);

//-----------------------------bultin---------------------------------

int		ft_echo(t_node *node);
int		ft_env(t_node *node);
int		ft_cd(t_node *node);
int		ft_exit(t_node *node);
int		ft_export(t_node *node);
int		ft_unset(t_node *node);
int		print_error(char *s1, char *s2, char *s3, char *message);
int		print_error_errno(char *s1, char *s2, char *s3);
char	*get_env_var(char *var);
void	ft_pwd(void);

//-----------------------------env---------------------------------

int		is_env_var(char *var, t_list *env);
void	init_minishel(t_node *node, char **env);
void	create_env_var(char *str, t_list **env);
void	update_env_var(char *var, char *new_value, t_list *env);
void	duplicate_env(t_node *node, char **envp);
void	increment_shlvl(t_node *node);
char	*replace_env_value(char **env_ptr, char *var_name, char *new_value);
char	*ft_getenv(const char *key, t_list *env);

//---------------------------execution------------------------------------

char	*get_path(char *cmd, t_list *env);
void	executing(t_node *node);
void	exec_cmd(t_node *node);
void	exec_pipe(t_node *node);
int		is_builtin(t_node *node);
int		heredoc(t_node *node);
int		*setup_heredocs(t_node *node, int *heredoc_count);
int		ft_pipe(int ends[2]);
int		ft_dup2(int filde1, int filde2);
int		redirections(t_node *node);
int		ft_open(const char *path, int oflag, mode_t mode);
pid_t	ft_fork(void);
int 	ft_close(int fd);

//---------------------expanding-------------------------------

char	*remov_quotes(char *str);
char	*expansion_input(char *str, t_list *env);
char	*handle_dollar(char *ret, const char *str, size_t *i, t_list *env);
char	*handle_quote(char *ret, const char *str, size_t *i, char quote);
char	*expansion_file(char *str, t_list *env);
char	*expansion_dilim(char *str);
char	*expansion_content(char *str, t_list *env);
char	*handle_single_quotes(char *ret, const char *str, size_t *i);
char	*handle_double_quotes(char *ret, const char *str, size_t *i, t_list *env);
char	*handle_normal(char *ret, const char *str, size_t *i);

//-----------------------signals------------------
void	setup_signal(void);
void	exit_status(int status);

int	deal_w_redir(t_node *node);
int	ft_redir(t_node *node);

int check_syntax(t_token *tokens);

t_node *init_minishell(char **env);
#endif
