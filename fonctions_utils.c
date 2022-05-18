#include "projet.h"
#include <string.h>
#include <math.h>

// fonction suplementaire pour tranformer les nombre en str

static char *ft_strdup(char *str)
{
	int i;
	char *res; 

	i = 0;
	res = malloc(sizeof(char)*(strlen(str)+1));
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}


static int ft_strlen(char *str)
{
	int i; 

	i = 0;
	while (str[i])
		i++;
	return (i);
}
static int	nb_malloc(long n, char *base)
{
	int	res;
	int j = ft_strlen(base);

	res = 1;
	if (n < 0)
	{
		res = res + 1;
		n = -n;
	}
	while (n >= j)
	{
		res++;
		n = n / j;
	}
	return (res);
}

static char	*int_min(long n)
{
	if (n == -2147483648)
		return (strdup("-2147483648"));
	if (n == 0)
		return (strdup("0"));
	return (NULL);
}

char	*ft_itoa(long n, char *base)
{
	char			*str;
	int				i;
	long			nb;
	//char			base[16];

	//base = "0123456789abcdef";
	i = nb_malloc(n,base);
	nb = n;
	if (n == -2147483648 || n == 0)
		return (int_min(n));
	str = malloc((sizeof(char) * i + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		nb = -n;
	}
	str[i] = '\0';
	i--;
	while (nb > 0)
	{
		str[i] = base[nb % 16];
		nb = nb / 16;
		i--;
	}
	return (str);
}

static int	get_base_length(char *base)
{
	int	base_length;
	int	j;

	base_length = 0;
	while (base[base_length])
	{
		if (base[base_length] == '-' || base[base_length] == '+')
			return (0);
		j = base_length + 1;
		while (base[j])
		{
			if (base[base_length] == base[j])
				return (0);
			++j;
		}
		++base_length;
	}
	if (base_length < 2)
		return (0);
	return (base_length);
}

static int	check_errors(char *str, char *base)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	while (str[start] != '\0' && (str[start] == ' ' || str[start] == '\t' ||
		str[start] == '\r' || str[start] == '\n' || str[start] == '\v' ||
		str[start] == '\f'))
		start++;
	i = start;
	while (str[i])
	{
		j = 0;
		while (base[j] && (str[i] != base[j] ||
				(str[i] == '-' || str[i] == '+')))
			++j;
		if (str[i] != base[j] && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

static int	get_nb(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}



static char	*ft_str(char *s1, char *s2)
{
	if (s1 == NULL)
		return (strdup(s2));
	if (s2 == NULL)
		return (strdup(s1));
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (ft_str((char *)s1, (char *)s2));
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while (i++, s1[i])
	{
		dest[j] = s1[i];
		j++;
	}
	i = 0;
	while (s2[i])
	{
		dest [j] = s2[i];
		i++;
		j++;
	}
	free(s1);
	free(s2);
	dest[j] = '\0';
	return (dest);
}

static int		ft_in_base(char c, char *base)
{
	int i;

	i = -1;
	while (base[++i])
		if (c == base[i])
			return (i);
	return (-1);
}

static int		ft_checkbase(char *base)
{
	int i;

	i = -1;
	while (base[++i])
		if (base[i] == '+' || base[i] == '-' || base[i] == ' '
			|| ft_in_base(base[i], base + i + 1) >= 0
			|| (base[i] >= 9 && base[i] <= 13))
			return (0);
	return ((i < 2) ? 0 : i);
}

int		ft_atoi_base(char *str, char *base, int size)
{
	int i;
	int n;
	int negative;

	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	negative = 0;
	while (*str == '-' || *str == '+')
		if (*str++ == '-')
			negative = 1 - negative;
	n = 0;
	while ((i = ft_in_base(*str++, base)) >= 0)
		n = n * size + i;
	if (negative)
		n *= -1;
	return (n);
}

static int		ft_nbrlen(unsigned int n, unsigned int base_size)
{
	if (n < base_size)
		return (1);
	return (1 + ft_nbrlen(n / base_size, base_size));
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char			*dest;
	unsigned int	nb;
	int				size;
	int				i;
	int				n;

	n = ft_checkbase(base_from);
	if (!(n && (size = ft_checkbase(base_to))))
		return (NULL);
	n = ft_atoi_base(nbr, base_from, n);
	nb = (n < 0) ? -n : n;
	i = ft_nbrlen(nb, size) + ((n < 0) ? 1 : 0);
	if (!(dest = malloc((i + 1) * sizeof(char))))
		return (NULL);
	dest[i] = '\0';
	while (i--)
	{
		dest[i] = base_to[nb % size];
		nb /= size;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}


/*int main ()
{
	printf("%s\n",ft_itoa(125789,"0123456789abcdef"));
	return (0);
}
*/