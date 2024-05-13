#include "../minishell.h"

void    close_non_related(t_execlist *execl, int **fd, int i)
{
    int c;
    
    c = -1;
    //while (execl->chunk[++c] != NULL)
	while (++c < execl->valid_cmds)
    {
        if (c != i && c != (i + 1))
        {
            close(fd[c][0]);
            close(fd[c][1]);
        }
    }
}

void    write_heredoc(t_execlist *execl, char *str, int **fd, int i)
{
    int pid;

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
    close_non_related(execl, fd, i);
	close(fd[i][1]); //fecha o pipe local (so escreve no proximo)
	if (execl->chunk[i]->heredoc == 1 && execl->chunk[i]->inpipe == 1) //1, heredoc valido
	{
        write_heredoc(execl, execl->chunk[i]->infile, fd, i);
        dup2(fd[i][0], STDIN_FILENO);
	}
    else if (execl->chunk[i]->heredoc == 0 && execl->chunk[i]->inpipe == 1
		&& execl->chunk[i]->infile != NULL) //1, normal infile
	{
        redir[i][0] = open(execl->chunk[i]->infile, O_RDONLY);
        dup2(redir[i][0], STDIN_FILENO);
		close(redir[i][0]); //depois de dup, fecha-se
    }
	else if (i > 0) //resto, ate ao ultimo
	{
        dup2(fd[i][0], STDIN_FILENO);
		close(fd[i][0]);
	}
    close(fd[i][0]);
}

void	exec_output(t_execlist *execl, int **fd, int **redir, int i)
{
	if ((i + 1) < execl->valid_cmds)
		close(fd[i + 1][0]);
	if (execl->chunk[i]->outfile != NULL) //1, outfile
	{
		if (execl->chunk[i]->append == 1) //append
			redir[i][1] = open(execl->chunk[i]->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
		else // truncate
			redir[i][1] = open(execl->chunk[i]->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(redir[i][1], STDOUT_FILENO);
		close(redir[i][1]); //depois de dup, fecha-se
		if ((i + 1) < execl->cmd_nmb) //outfile inside pipeline
		{
			close(fd[i + 1][1]);
			fd[i + 1][1] = redir[i][1];
			return ;
		}
	}
	else if ((i + 1) < execl->valid_cmds && execl->chunk[i]->outfile == NULL) //2, inside pipeline, non outfile
	{
		close(fd[i + 1][1]);
		dup2(fd[i + 1][1], STDOUT_FILENO);
		//close(fd[i + 1][1]);
	}
	if ((i + 1) < execl->valid_cmds)
		close(fd[i + 1][1]);
}
