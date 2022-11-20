/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:09:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/18 17:43:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int last_step(t_shell *sh, t_hash **ht, char *line);
static void	opener(t_shell *sh, char *path, t_hash **ht);

static void	create_bash_script(char *line, const char *path_to_script)
{
	const char	*header = "#!/bin/bash\n";
	char		*script;
	int			len;
	int			fd;

	len = ft_strlen(header) + ft_strlen(line);
	script = ft_memalloc(len + 1);
	ft_strcat(script, header);
	ft_strcat(script, line);
	fd = open(path_to_script, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fd < 0)
	{
		ft_printf("21sh: create_bash_scrip: open failed\n");
		exit (1);
	}
	if (write(fd, script, len) < 0)
	{
		ft_printf("21sh: create_bash_script: write failed\n");
		exit (1);
	}
	close (fd);
}

static void	compare_outputs(int *sh_fd, int *bash_fd, char *line)
{
	char	*sh_buf;
	char	*bash_buf;
	int		fail_flag;

	sh_buf = NULL;
	fail_flag = 0;
	close(sh_fd[1]);
	close(bash_fd[1]);
	ft_printf("TESTCMD: %s: ", line);
	while (get_next_line(sh_fd[0], &sh_buf) > 0
		&& get_next_line(bash_fd[0], &bash_buf) > 0)
	{
		if (!ft_strequ(sh_buf, bash_buf))
			fail_flag = 1;
		ft_strdel(&sh_buf);
		ft_strdel(&bash_buf);
	}
	ft_strdel(&sh_buf);
	ft_strdel(&bash_buf);
	if (fail_flag == 1 && ft_printf("\033[0;31m"))
		ft_printf("[FAIL]\n");
	else
	{
		ft_printf("\033[0;32m");
		ft_printf("[OK]\n");
	}
	ft_printf("\033[0m");
}

static void	pipe_wrap(int *fd)
{
	if (pipe(fd) < 0)
	{
		ft_printf("21sh: get_outputs: Pipe failed\n");
		exit (-1);
	}
}

static void	second_fork(int *bash_fd, char *line, const char *path_to_script)
{
	if (fork_wrap() == 0)
	{
		close(STDOUT_FILENO);
		dup(bash_fd[1]);
		close(STDERR_FILENO);
		dup(bash_fd[1]);
		close(bash_fd[0]);
		close(bash_fd[1]);
		create_bash_script(line, path_to_script);
		if (execve(path_to_script, NULL, NULL) < 0
			&& ft_printf("21sh: get_output: execve fail\n"))
			exit (1);
	}
}

/* Replace the get_input with your function which
	will take the environ and the line from gnl */
void	get_outputs(t_shell *sh, char *line, t_hash **ht)
{
	const char	*path_to_script = "autotest/line_script.sh";
	int			fd[2];
	int			bash_fd[2];

	pipe_wrap(fd);
	pipe_wrap(bash_fd);
	if (fork_wrap() == 0)
	{
		close(STDOUT_FILENO);
		dup(fd[1]);
		close(STDERR_FILENO);
		dup(fd[1]);
		close(fd[0]);
		close(fd[1]);
		last_step(sh, ht, line);
		exit (1);
	}
	wait(0);
	second_fork(bash_fd, line, path_to_script);
	compare_outputs(fd, bash_fd, line);
}

int	is_autotest(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 3)
		return (0);
	while (argv[i] && i < argc)
	{
		if (ft_strequ(argv[i], "autotest"))
			return (1);
		++i;
	}
	return (0);
}

static void	read_test_lines(t_shell *sh, int fd, t_hash **ht)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line != '#')
		{
			if (ft_strchr(line, '/'))
				opener(sh, line, ht);
			else
				get_outputs(sh, line, ht);
		}
	}
}

static void	opener(t_shell *sh, char *path, t_hash **ht)
{
	int	fd;

	if (!path)
		return ;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("21sh: autotest: open failed\n");
		exit (fd);
	}
	read_test_lines(sh, fd, ht);
}

/* You need to modify the read_test_lines() */
/* Usage ./21sh autotest <testfilepath> */
/* arguments are copy of environment,
	argc and argv are the arguments given to main */
void	autotest(t_shell *sh, int argc, char **argv, t_hash **ht)
{
	if (is_autotest(argc, argv))
	{
		opener(sh, argv[2], ht);
		exit (1);
	}
}

static char	*change_shlvl(char *shlvl)
{
	int		lvl;
	char	*str_lvl;
	char	*ret;

	lvl = ft_atoi(ft_strchr(shlvl, '=') + 1);
	if (lvl <= 999)
		++lvl;
	else
		lvl = 1;
	str_lvl = ft_itoa(lvl);
	ret = ft_strdup("SHLVL=");
	ret = ft_strupdate(ret, str_lvl);
	ft_strdel(&str_lvl);
	return (ret);
}

static size_t	env_arrlen(char **arr)
{
	size_t	len;
	ssize_t	i;

	len = 0;
	i = -1;
	while (arr[++i])
		len++;
	return (len);
}

static char	**hard_coded_env(char **env)
{
	char	cwd[MAX_PATHLEN];
	size_t	i;

	i = 0;
	env = (char **)ft_memalloc(sizeof(char *) * 5);
	env[i++] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env[i++] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	env[i++] = ft_strdup("SHLVL=1");
	env[i++] = ft_strdup("_=/usr/bin/env");
	env[i] = NULL;
	return (env);
}

static char	**get_env(char **env, size_t j, ssize_t i)
{
	extern char	**environ;
	size_t		len;

	if (*environ)
	{
		len = env_arrlen(environ);
		env = (char **)ft_memalloc(sizeof(char *) * (len + 1));
		while (environ[++i])
		{
			if (!ft_strncmp(environ[i], "SHLVL=", 6))
				env[j++] = change_shlvl(environ[i]);
			else
				env[j++] = ft_strdup(environ[i]);
		}
		env[j] = NULL;
	}
	else
		env = hard_coded_env(env);
	return (env);
}

/*
**	If optional_actions is TCSAFLUSH, the change shall occur after all output
**	written to fildes is transmitted, and all input so far received but not
**	read shall be discarded before the change is made.
*/
static struct termios	ft_init_raw(void)
{
	struct termios	orig_termios;
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
	{
		write(2, "error tcgetattr\n", 16);
		exit(1);
	}
	raw = orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	raw.c_iflag &= ~(IXON | BRKINT);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
	ft_run_capability("ti");
	ft_run_capability("cl");
	return (orig_termios);
}

void	init(t_shell *sh, t_term *t, t_hash ***ht, int argc, char **argv)
{
	ssize_t		i;
	size_t		j;

	t->orig_termios = ft_init_raw();
	ft_init_term(t);
	hash_init(ht);
	ft_putstr("\033[2J");
	ft_putstr("\033[H");
	ft_printf("\n{blu}**{gre}**{red}**{yel}**{blu}**{gre}**{red}**{yel}**{blu}**{gre}**{red}**{yel}**{blu}**{gre}**{red}**{yel}**{blu}**\n");
	ft_printf("            {blu}- {yel}2{gre}1{red}s{blu}h {yel}-\n");
	ft_printf("   {yel}made {blu}by {gre}rvourenl {red}and {yel}mrantil{blu}.");
	ft_printf("\n{yel}**{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{red}**{gre}**{blu}**{yel}**{nor}\n\n");
	sh->paths = NULL;
	sh->env = NULL;
	j = 0;
	i = -1;
	sh->env = get_env(sh->env, j, i);
	sh->temp_env = NULL;
	vec_new(&sh->v_tmp_env, 0, MAX_PATHLEN);
	autotest(sh, argc, argv, *ht);
	ft_printf("{yel}${gre}>{nor} ");
}
