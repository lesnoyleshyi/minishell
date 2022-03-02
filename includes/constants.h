/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 00:13:51 by drayl             #+#    #+#             */
/*   Updated: 2022/02/20 00:13:53 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define NAME "minishell"
# define HISTORY_FILE ".minisell_history_"

# define C_ECHO "echo"
# define C_CD "cd"
# define C_PWD "pwd"
# define C_EXPORT "export"
# define C_UNSET "unset"
# define C_ENV "env"
# define C_EXIT "exit"

# define REDIR_IN '<'
# define REDIR_OUT '>'
# define QUOTE '\''

# define QUOTE2 '\"'
# define SPACE ' '
# define GET_PARAM '$'
# define INIT_PARAM '='
# define PIPE '|'
# define ERROR_STATUS '?'
# define BOTTOM_LINE '_'

# define TILDA "~"
# define TIRE "-"
# define PATH "PATH"
# define PWD "PWD"
# define SH_LVL "SHLVL"
# define OLD_PWD "OLDPWD"
# define HOME "HOME"

# define FALSE 0
# define TRUE 1
# define TOTAL_PIZDEC 1

# define ERR_INIT_PARAM "syntax error near unexpected token"
# define INVALID_ARG_FOR_UNSET "not a valid identifier"
# define NOT_SET "not set"
# define ERR_CMD_NOT_FOUND "command not found"
# define MEM_ERR "memory allocation error"
# define SYN_ERR "syntax error near unexpected token"
# define NEW_LINE "newline"
#endif
