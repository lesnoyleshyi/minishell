
#include "../../includes/minishell.h"
#include "sys/wait.h"

//Prints error message in format "minishval': message: <errno>"
//and returns ret_val.
int	ft_perror_and_return(char *message, int ret_val);

//This function's purpose is to handle "command not found" and "is a directory"
//errors in the way bash does it.
//*
//The reason for existence of this function is that bash returns
//"command not found" if <binary_name> not found in PATH;
//"No such file or directory" if <path_to_binary_name> not found by the specified path
//exit status code == 127 in this case
//BUT
//If pathname points to directory, not binary, bash  returns "is a directory"
//exit status code == 126
void	custom_message_exit(char *pathname, int message_code, int exit_status);

//Translates value of global variable errno to corresponding exit status code
//in the way bash does it.
//For example, "Permission denied" error
//corresponds to errno == 13 and exit status code == 126
int	translate_errno_to_exit_status(int errno_val);

int	ft_perror_and_return(char *message, int ret_val)
{
	write(2, "minishval': ", 12);
	perror(message);
	return (ret_val);
}

void	custom_message_exit(char *pathname, int message_code, int exit_status)
{
	write(2, "minishval': ", 12);
	write(2, pathname, ft_strlen(pathname));
	if (message_code == CMD_NOT_FOUND)
		write(2, ": command not found\n", 20);
	else if (message_code == CMD_IS_DIR)
		write(2, ": is a directory\n", 17);
	exit(exit_status);
}

int	get_child_exit_status(pid_t pid)
{
	int exit_status;
	int errno_val;

	waitpid(pid, &exit_status, 0);
	if (exit_status == 0)
		return (0);
	errno_val = WEXITSTATUS(exit_status);
	return (translate_errno_to_exit_status(errno_val));
}


//	todo-Stycho add all possible variants
int	translate_errno_to_exit_status(int errno_val)
{
	if (errno_val == 2)
		return (127);
	if (errno_val == 13)
		return (126);
	return (errno_val);
}
