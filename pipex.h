#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

int main(int argc, char **argv, char **envp);

const char	*ft_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void 		ft_free(char **array);
void 		ft_error_exit(void);

char		**ft_split(char const *s, char c);
#endif