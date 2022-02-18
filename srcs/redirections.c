#include "minishell.h"

#define	r_move_input			//	[n]<&digit-			/* 1<&2- */
#define	r_move_output			//	[n]>&digit-			/* 1>&2- */
#define	r_move_input_word		//	[n]<&digit-			/* 1<&$foo- */
#define	r_move_output_word		//	[n]>&digit-			/* 1>&$foo- */
#define	r_input_direction		//	[n]<word			/* <foo */			YES
#define	r_output_direction		//	[n]>[|]word			/* >foo */			YES
#define	r_inputa_direction		//						/* foo & makes this. */
#define	r_reading_until			//	<<stop_word 		/* << foo */		YES
#define	r_deblank_reading_until	//	<<-					/* <<-foo */
#define	r_reading_string		//	<<<					/* <<< foo */
#define	r_duplicating_input_word//	[fd]<&WORD	(WORD need to be exposed)		/* 1<&$foo */
#define	r_duplicating_output_word//	[fd]>&WORD	(WORD need to be exposed)		/* 1>&$foo */
#define	r_duplicating_input		//	[fd]<&				/* 1<&2 */
#define	r_duplicating_output	//	[fd]>&				/* 1>&2 */
#define	r_err_and_out			//	&>word or >&word	/* &>filename */
#define	r_append_err_and_out	//	&>>word				/* &>> filename */
#define r_input_output			//	[n]<>word			/* <>foo */
#define	r_output_force			//						/* >| foo */
#define	r_appending_to			//	[n]>>word			/* >>foo */			YES
#define r_close_this			//	<&- or >&-			/* <&- */




int ft_do_redirections_internal(t_redirect *redirect, int flags, char **fnp)
{
	char	*redirectee_word;
	int		fd;

	if (redirect->redir_type == E_IN || redirect->redir_type == E_OUT || redirect->redir_type == E_APPEND)
	{
		redirectee_word = ft_redirection_expand(redirect->redirectee.filename);
		if (redirectee_word == NULL)
			return (AMBIGUOUS_REDIRECT);
		fd = ft_redir_open(redirectee_word, redirect->redir_flag, 0666, redirect->redir_type);
		if (fnp != NULL)
			*fnp = redirectee_word;
		else
			free(redirectee_word);
		if (fd < 0)
			return (errno);
		if (flags & RX_ACTIVE)	//we'll really make redirections
		{
			if (redirect->redirector.fd == 1 && fileno(stdout) == redirect->redirector.fd)
			{
				fflush(stdout);
				fpurge(stdout);
			}
			else if (redirect->redirector.fd == 2 && fileno(stderr) == redirect->redirector.fd)
			{
				fflush(stderr);
				fpurge(stderr);
			}
			if (fd != redirect->redirector.fd && dup2(fd, redirect->redirector.fd) < 0)
			{
				close(fd);
				return (errno);
			}
		}
		if (fd != redirect->redirector.fd)
			close(fd);
		return (0);
	}
	if (redirect->redir_type == E_HEREDOC)
	{
		if (redirect->redirectee.filename)
		{
			fd = ft_heredoc_to_fd(redirect->redirectee.filename, redirect->redir_type);
			if (fd < 0)
				return (HEREDOC_REDIRECT);
			if (flags & RX_ACTIVE)
			{
				if (fd != redirect->redirector.fd && dup2(fd, redirect->redirector.fd) < 0)
				{
					close(fd);
					return (errno);
				}
			}
			if (fd != redirect->redirector.fd)
				close(fd);
		}
		return (0);
	}
	return (0);
}