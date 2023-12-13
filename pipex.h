#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

int main(int argc, char **argv);

const char	*ft_strjoin(char const *s1, char const *s2);
void 		ft_free(char **array);

char	**ft_split(char const *s, char c);
#endif