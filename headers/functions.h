/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlima-fe <rlima-fe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:58:07 by rlima-fe          #+#    #+#             */
/*   Updated: 2024/01/29 17:05:23 by rlima-fe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

// FREE
char			*free_ptr(char *ptr);
char		    **free_mat(char **mat);
t_token			*free_token(t_token *token);
// LEXER
static char		*filler(char *input, int pos);
char			**lexer(char *input);

// MAIN
static char		*get_input(t_mini *ms, const char *prompt);
void			ft_sa_handler(int sig, siginfo_t *info, void *context);
static t_mini	ft_init(int argc, char *argv[], char **envp);

// PARSER
static void		insert_token(t_token **head, char *token);
static int		is_buildin(char *token);
static char		**split_args(char *input);
void			define_type(t_token **head);
int				parser(t_token **head, char *str);

// UTILS
void			exit_handler(t_mini *ms, const char *msg, int code);
int				check_quotes(char c, int quotes);
char        	**ft_matdup(char **mat);

// BUILTIN
int				execbi(t_mini *ms, char **cmd, char ***envp);
void			ft_echo(t_mini *ms, char **cmd);
void			ft_cd(t_mini *ms, char **cmd, char **env);
void 			ft_pwd(t_mini *ms, char **cmd, char **envp);
void			ft_export(t_mini *ms, char **cmd, char **envp);
void			ft_unset(t_mini *ms, char **cmd, char **envp);
void			ft_env(t_mini *ms, char **cmd, char **envp);
void			ft_exit(t_mini *ms, char **cmd);

#endif