/*
** padding.c for ElCrypt in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Mar  1 20:56:07 2015 Hippolyte Barraud
** Last update Sun Mar  1 20:56:51 2015 Hippolyte Barraud
*/

#include "../../includes/elcrypt.h"

void	add_pading(unsigned char *buff, t_query *query, int start)
{
  int	i;
  int	c;

  if (query->action == DECRYPT || query->ditpad == TRUE)
    return;
  i = start;
  c = 8 - start;
  while (i < 8)
    buff[i++] = c;
  query->ditpad = TRUE;
}

unsigned char		*get_pad_block(t_query *query)
{
  static unsigned char	block[9];
  int			i;

  if (query->ditpad == TRUE || query->action == DECRYPT)
    return (NULL);
  i = 0;
  while (i < 8)
    block[i++] = 0x08;
  block[8] = '\0';
  query->ditpad = TRUE;
  return (&block[0]);
}

int	delete_padding(unsigned char *lastbytes, t_query *query)
{
  int	del;

  if (query->action == CRYPT)
    return (8);
  del = lastbytes[7];
  return (8 - del);
}
