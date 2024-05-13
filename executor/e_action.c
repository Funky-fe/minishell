/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_action.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:39:10 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/13 02:37:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    close_non_related(t_execlist *execl, int **fd, int i)
{
    int c;
    
    c = -1;
	//(void) i;
	while (execl->chunk[++c] != NULL)
	//while (++c < execl->valid_cmds)
    {
        if (c != i && c != (i + 1))
        {
			//ft_printf("if (%d != %i && c != (i + 1))\n", c, i);
			close(fd[c][0]);
			close(fd[c][1]);
			//ft_printf("closed fd[%d][0] = %d\n", c, fd[c][0]);
			//ft_printf("closed fd[%d][1] = %d\n", c, fd[c][1]);
        }
    }
}

/*
closes:
input - (all - i - (i + 1)) + i;
output - (i + 1);
*/

void    write_heredoc(t_execlist *execl, char *str, int **fd, int i)
{
    int pid;

    //ft_printf("writing heredoc.\n");
	pid = fork();
    if (pid == 0)
    {
		close_non_related(execl, fd, i);
		if ((i + 1) < execl->valid_cmds)
		{
			close(fd[i + 1][0]);
			close(fd[i + 1][1]);
		}
		close(fd[i][0]);
		write(fd[i][1], str, ft_strlen(str));
		close(fd[i][1]);
		exit(0);
    }
    wait(0);
}

/*
closes_non_related: 
input - (all - i - (i + 1)) + i;
output - (i + 1);
*/

void	exec_input(t_execlist *execl, int **fd, int **redir, int i)
{
	//ft_printf("preparing input for exec[%d]\n", i);
    close_non_related(execl, fd, i);
	//close(fd[i][1]); //fecha o pipe local (so escreve no proximo)
	//ft_printf("In input, closed(fd[%d][1] = %d)\n", i, fd[i][1]);
	if (execl->chunk[i]->heredoc == 1 && execl->chunk[i]->inpipe == 1) //1, heredoc valido
	{
		//ft_printf("heredoc input [%d]\n", i);
        write_heredoc(execl, execl->chunk[i]->infile, fd, i);
        dup2(fd[i][0], STDIN_FILENO);
	}
    else if (execl->chunk[i]->heredoc == 0 && execl->chunk[i]->inpipe == 1
		&& execl->chunk[i]->infile != NULL) //1, normal infile
    {
		//ft_printf("infile input [%d]\n", i);
        redir[i][0] = open(execl->chunk[i]->infile, O_RDONLY);
        dup2(redir[i][0], STDIN_FILENO);
		close(redir[i][0]); //depois de dup, fecha-se
    }
	else if (i > 0) //resto, ate ao ultimo
	{
		//ft_printf("pipeline input [%d]\n", i);
        dup2(fd[i][0], STDIN_FILENO); //last pipe, fd[i - 1][0];
		//ft_printf("dup2(fd[%d][0] = %d, STDIN_FILENO = %d);\n", i, fd[i][0], STDIN_FILENO);
	}
    //close(fd[i][0]);
	//ft_printf("In input, closed(fd[%d][0] = %d)\n", i, fd[i][0]);
}

void	exec_output(t_execlist *execl, int **fd, int **redir, int i)
{
	//ft_printf("preparing output for exec[%d]\n", i);
	//if ((i + 1) < execl->valid_cmds)
		//close(fd[i + 1][0]);
	if (execl->chunk[i]->outfile != NULL) //1, outfile
	{
		//ft_printf("inside outfile [%d]\n", i);
		if (execl->chunk[i]->append == 1) //append
		{
			//ft_printf("outfile append output [%d]\n", i);
			redir[i][1] = open(execl->chunk[i]->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		}
		else // truncate
		{
			//ft_printf("outfile truncate output [%d]\n", i);
			redir[i][1] = open(execl->chunk[i]->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		}
		dup2(redir[i][1], STDOUT_FILENO);
		close(redir[i][1]); //depois de dup, fecha-se
		if ((i + 1) < execl->cmd_nmb) //outfile inside pipeline
		{
			//ft_printf("outfile pipeline output [%d]\n", i);
			close(fd[i + 1][1]);
			fd[i + 1][1] = redir[i][1];
			//ft_printf("do you get out?\n");
			return ;
		}
	}
	else if ((i + 1) < execl->valid_cmds && execl->chunk[i]->outfile == NULL) //2, inside pipeline, non outfile
	{
		//ft_printf("pipe pipeline output [%d]\n", i);
		//ft_printf("dup2(fd[%d][1] = %d, STDOUT_FILENO = %d);\n", (i + 1), fd[i + 1][1], STDOUT_FILENO);
		dup2(fd[i + 1][1], STDOUT_FILENO);
	}
	if ((i + 1) < execl->valid_cmds)
	{
		//ft_printf("last cmd [%d]\n", i);
		//close(fd[i + 1][1]);
		//ft_printf("In output, closed(fd[%d][1] = %d)\n", (i + 1), fd[i + 1][1]);
	}
	//ft_printf("last cmd || out of output [%d]\n", i);
}
