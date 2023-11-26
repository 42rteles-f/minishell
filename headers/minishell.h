/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:44:21 by rteles-f          #+#    #+#             */
/*   Updated: 2023/09/17 00:24:58 by rteles-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <libft.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <dirent.h>
# include <sys/types.h>
# define PARENT -350
// # define HERE write(1, "here\n", 5)
// # define ALMOST write(1, "almost\n", 7)
// # define THERE write(1, "there\n", 6)
# define RED "\001\e[01;31m\004"
# define BOLD "\001\e[01;1m\004"
# define BLUE "\001\e[01;34m\004"
# define YELLOW "\001\e[01;33m\004"
# define RESET "\001\e[0m\004"

typedef struct s_control	t_control;
typedef struct s_command	t_command;
typedef struct sigaction	t_sigaction;
typedef void				(*t_exe)();
typedef struct s_iterate	t_iterate;

struct s_control {
	char		*input;
	char		*prompt;
	char		**envp;
	char		**paths;
	char		*home;
	char		***tokens;
	int			in_out[2];
	int			status;
	int			input_count;
	t_list		*commands;
} ;

struct s_command {
	char		*exec_path;
	char		**flags;
	char		**terminal;
	int			id;
	int			status;
	int			is_parent;
	int			parse;
	int			in_pipe[2];
	int			out_pipe[2];
	t_control	*main;
	t_exe		execute;
} ;

// Setup + 2
void		setup(t_control *get, char **envp);
char		*get_prompt(void);
void		update_paths(char **envp, t_control *get);
// Utils
char		**get_envaddress(char **envp, char *find);
void		control_c(int signal, t_control *control);
void		control_d(t_control *get);

// Main + 2
t_control	**control(void);

// Normalize + 3
int			normalize_input(t_control *get);
char		**copy_split_size(char **split, int size);
// Utils
int			count_cases(char **string);
int			is_end_of_command(char *token);

// Commands + 4
void		structure_commands(t_control *get);
// Utils
void		jump_command(t_command *command, int index);
void		delete_command(void *command);
t_command	*new_command(t_control *get);
void		stop_command(char ***split);
int			is_executable(char *check);

// Execution
void		run_input(t_control *get);
// Utils
void		safe_close_fd(int fd, int fd2);
void		check_dup2(int in, int out);

// Cleanup/Reset
void		end_shell(t_control *get);
void		input_reset(t_control *get);
void		safe_free_null(char **string);
int			*here_doc(t_control *get, char *eof);

// Quotes
int			remove_pair(char *string, char *find);
int			find_pair(char *string, char *jump);

// Expansion + 2
char		*input_expand(char *input, char **envp, int ignore);
char		**wildcard(char *str);
char		**wildcard_aux(char **split);

// Built-in: prepare | execute
void		cd_prepare(t_command *command, int index);
void		pwd_prepare(t_command *get, int index);
void		env_prepare(t_command *command, int index);
void		echo_prepare(t_command *command, int index);
void		unset_prepare(t_command *command, int index);
void		export_prepare(t_command *command, int index);
void		exit_prepare(t_command *command, int index);
void		bonus_execute(t_command *command, int index);
void		builtin_execute(char *print, char **fd,
				char **len, t_command *command);
void		input_redirect(t_command *command, int index);
void		output_redirect(t_command *command, int index);
void		do_nothing(void);
int			execute_now(t_command *get);
int			stderror_export(t_command *command, char *str);

// Shellsplit + 4
char		**shell_split(char *s);
// Utils
int			split_case(char *line);
char		**copy_shellsplit(char **split);
void		*free_split(char **arg);
int			ignore_quotes(char *string);

// Libft Plus
char		*sttc_itoa(int number);
char		*sttc_llitoa(long long number);
char		*ft_stradd(char **original, char *add);
char		*ft_unsplit(char **split, int posize, char c, int flag_nl);
int			is_space(char c);
void		*free_triple_pointer(char ***pointer);

void		finish_list_with(char **list, char *put);
void		print_split_input(char ***input);

char		**find_var(char *name, char **env, int *index, int *size);

void		print_split(char **input);
void		change_env_variable(char *variable, char *value);
int			split_size(char **split);
int			ft_strlenchr(char *str, char c);
int			can(char *str);

// Parse
char		**parse(char *str, t_control *get);
int			parsing(char **split);
char		**ft_join_split(char **split, char **add, int *index);
int			last_split_index(char **split);
void		stop_heredoc(int signal);
char		**env_copy(char **env, char *new_str);
int			check_last_char(char **split);
int			check_first_char(char **split);
int			count_char(char **split, char c);
int			check_in_out_parse(char **split);
int			check_last_parenteses(char **split);

// Wildcard
int			count_wildcards(char *str);
int			count_wildcard_chars(char *str);
int			count_wildcard(char *str);
char		**split_sort_by_order(char **split);
int			ft_split_wildcard_count(char *str);
char		**build_wildcard_list(char *str, int count);
int			count_wildcard(char *str);
int			check_wildcard(char *str, char *name);
char		**ft_split_wildcard(char *str);
void		close_doc_pipes(char ***tokens);
int			new_pipe(int **newpipe, t_control *get);

void		update_pwd(t_control *get);

long long	ft_atoll(char *nptr);

void		close_doc_pipes(char ***tokens);
int			new_pipe(int **newpipe, t_control *get);

#endif
