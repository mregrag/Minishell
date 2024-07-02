#include "libft.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
    char	*result;
    int		i;
    size_t	len1, len2, len3;

    if (!s1 && !s2 && !s3)
        return (NULL);
    
    len1 = 0;
    len2 = 0;
    len3 = 0;
    if (s1)
        len1 = ft_strlen(s1);
    if (s2)
        len2 = ft_strlen(s2);
    if (s3)
        len3 = ft_strlen(s3);

    result = malloc(sizeof(char) * (len1 + len2 + len3 + 1));
    if (!result)
        return (NULL);

    i = 0;
    if (s1)
        while (*s1)
            result[i++] = *s1++;
    if (s2)
        while (*s2)
            result[i++] = *s2++;
    if (s3)
        while (*s3)
            result[i++] = *s3++;

    result[i] = '\0';
    return (result);
}
