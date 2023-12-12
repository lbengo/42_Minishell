#include "../libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	count;

	count = 0;
	while (s1[count] && s2[count])
	{
		if (s1[count] != s2[count] || !s1[count] || !s2[count])
			return ((unsigned const char)s1[count] \
				- (unsigned const char)s2[count]);
		count++;
	}
	if (!s1[count] && !s2[count])
		return (0);
	else if (!s1[count])
		return (-(unsigned const char)s2[count]);
	else if (!s2[count])
		return ((unsigned const char)s1[count]);
	else
		return (0);
}
