/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:24:07 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/15 23:07:22 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include "queue.h"

# define ERR_MALLOC "ERR_MALLOC"

int		ft_arrlen(void **arr);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putstr_fd(int fd, const char *str);
void	ft_putstr(const char *str);
int		ft_isdigit(int c);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_error(const char *str);
void	ft_error_exit(const char *str);
char	**msk_split(char const *s, int (*f)(char c));
int		ft_strcmp(char *str1, char *str2);
void	*ft_malloc(size_t size);
void	free_all(void);
char	*ft_itoa(int n);
int		file_error(char *file_name);
int		ft_isalnum(int c);
int		is_int(const char *str);

#endif
