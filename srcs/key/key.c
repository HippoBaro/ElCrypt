/*
** key.c for ElCrypt in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Mar  1 20:57:25 2015 Hippolyte Barraud
** Last update Sun Mar  1 20:58:07 2015 Hippolyte Barraud
*/

#include "../../includes/elcrypt.h"

char	*get_binary(intmax_t pid, int coding)
{
  char	*str;
  int 	i;

  str = xmalloc((coding + 1) * sizeof(char));
  i = 0;
  while (i < coding)
    {
      str[coding - 1 - i] = ((pid >> i) & 1) + 48;
      i++;
    }
  return (str);
}

char	*delete_lsb(char *keystr)
{
  int	i;
  int	b;
  int	oct;
  char	*out;

  i = b = oct = 0;
  out = xmalloc(65 * sizeof(char));
  while (i < 64)
    {
      if (oct == 7)
	{
	  oct = 0;
	  i++;
	  continue;
	}
      oct++;
      out[b++] = keystr[i++];
    }
  out[b] = '\0';
  return (out);
}

static void	rotate(char *array, int begin, int end)
{
  char		temp;

  while (begin < end)
    {
      temp = array[begin];
      array[begin] = array[end];
      array[end] = temp;
      begin++;
      end--;
    }
}

void	leftRotate(char *test, int number)
{
  rotate(test, 0, number - 1);
  rotate(test, number, strlen(test) - 1);
  rotate(test, 0, strlen(test) - 1);
}
