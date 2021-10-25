#include <utilities.h>

static int	strrlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	darr_size(char **str)
{
	int	cnt;

	cnt = 0;
	while (str && str[cnt])
		cnt++;
	return (cnt);
}


int	char_append(char **str, char c)
{
	char	*buf;
	int		cnt;
	buf = (char *)malloc(strrlen(str) + 2);
	if (!buf)
		return (1);
	cnt = 0;
	while (*str && (*str)[cnt])
	{
		buf[cnt] = (*str)[cnt];
		cnt++;
	}
	buf[cnt] = c;
	buf[cnt + 1] = '\0';
	if (*str)
		free(*str);
	*str = buf;
	return (0);
}

int	string_append(char ***org, char *str)
{
	char	**buf;
	int		cnt;

	buf = (char **)malloc((darr_size(*org) + 2) * sizeof(char *));
	if (!buf)
		return (1);
	cnt = 0;
	while (*org && (*org)[cnt])
	{
		buf[cnt] = (*org)[cnt];
		cnt++;
	}
	buf[cnt] = str;
	buf[cnt + 1] = NULL;
	if (*org)
		free(*org);
	*org = buf;
	return (0);
}