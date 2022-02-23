/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drayl <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:26:38 by drayl             #+#    #+#             */
/*   Updated: 2021/10/20 20:26:41 by drayl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# elif BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*refill_string(char *str, const char *buff, char *old_string);
char	*get_old_string(char *old_string);
int		checking_new_line(const char *str);
#endif
