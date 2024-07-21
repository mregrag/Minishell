/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 07:06:41 by mregrag           #+#    #+#             */
/*   Updated: 2024/07/19 07:41:22 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	heredoc_file(char *content)
{
	int		fd;
	char	*line;
	char	*file_name;
	char	**her_cnt;
	char	*new_cnt;

	file_name = random_f();
	new_cnt = NULL;
	if (content)
	{
		her_cnt = ft_split(content, "\v", 0);
		while (*her_cnt)
		{
			line = expand_heredoc(*her_cnt);
			new_cnt = ft_strjoin(new_cnt, line, 0);
			line = NULL;
			her_cnt++;
		}
	}
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	write(fd, new_cnt, ft_strlen(new_cnt));
	close(fd);
	fd = open(file_name, O_RDWR);
	return (unlink(file_name), fd);
}
char	*random_f(void)
{
	char	*file_name;
	int		file_len;
	int		fd_rd;
	int		fd_tmp;

	fd_rd = open("/dev/urandom", O_RDONLY, 0777);
	if (fd_rd < 0)
		return (perror("cannot open /dev/urandom"), NULL);
	file_len = 21;
	file_name = my_malloc(file_len + 1, 1, 0);
	file_name[0] = '/';
	file_name[1] = 't';
	file_name[2] = 'm';
	file_name[3] = 'p';
	file_name[4] = '/';
	read(fd_rd, file_name + 5, 16);
	close(fd_rd);
	file_name[file_len] = 0;
	fd_tmp = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_tmp < 0)
		return (random_f());
	close(fd_tmp);
	unlink(file_name);
	return (file_name);
}

char	*expand_heredoc(char *line)
{
	char	*clean;
	char	*dollar_out;
	int		index;

	index = 0;
	clean = NULL;
	dollar_out = NULL;
	while (line[index])
	{
		if (line[index] == '$' && only_identifier(&line[index + 1]))
		{
			dollar_out = dollar(&line[index], &index, 1);
			clean = ft_strjoin(clean, dollar_out, 0);
		}
		else
			clean = add_c(clean, line[index++], 0);
	}
	return (clean);
}

static char	*fill_file(t_redir *alter)
{
	char		*line;
	char		*content;
	extern int	g_sig;

	content = NULL;
	while (1)
	{
		line = readline("heredoc>");
		if (!line || !doc_strcmp(line, alter->file) || g_sig == 2)
		{
			(1) && (free(line), line = NULL);
			break ;
		}
		if (line)
			content = ft_strjoin(content, ft_strjoin(line, "\n\v", 0), 0);
		(line) && (free(line), line = NULL);
	}
	if (g_sig == 2)
		return (NULL);
	return (content);
}

char	*_heredoc_(t_redir *alter)
{
	char		*content;
	int			fd;
	extern int	g_sig;

	fd = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_h);
	content = fill_file(alter);
	if (!content)
	{
		g_sig = 1;
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (content);
}
static char	*fill_file(t_redir *alter)
{
	char		*line;
	char		*content;
	extern int	g_sig;

	content = NULL;
	while (1)
	{
		line = readline("heredoc>");
		if (!line || !doc_strcmp(line, alter->file) || g_sig == 2)
		{
			(1) && (free(line), line = NULL);
			break ;
		}
		if (line)
			content = ft_strjoin(content, ft_strjoin(line, "\n\v", 0), 0);
		(line) && (free(line), line = NULL);
	}
	if (g_sig == 2)
		return (NULL);
	return (content);
}

char	*_heredoc_(t_redir *alter)
{
	char		*content;
	int			fd;
	extern int	g_sig;

	fd = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_h);
	content = fill_file(alter);
	if (!content)
	{
		g_sig = 1;
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (content);
}
