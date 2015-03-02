/*
** key_gen.c for ElCrypt in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Mar  1 21:00:02 2015 Hippolyte Barraud
** Last update Sun Mar  1 21:55:13 2015 Hippolyte Barraud
*/

#include "../../includes/elcrypt.h"

static void	copy_key2(int i, int i2, char *keystr, t_turn *turn)
{
  while (i < 7)
    {
      while (i2 < 8)
	{
	  if (keystr[(i * 8) + i2] == '0')
	    turn->subkey[i - 3] = (turn->subkey[i - 3] << 1) + 0;
	  else if (keystr[(i * 8) + i2] == '1')
	    turn->subkey[i - 3] = (turn->subkey[i - 3] << 1) + 1;
	  i2++;
	}
      i2 = 0;
      i++;
    }
}

void		get_subkey(t_query *query, t_turn *turn, int forturn)
{
  char		*keystr;
  char		*tmp;
  int		a;
  int		i;
  int		i2;

  keystr = xmalloc(57 * sizeof(char));
  i2 = a = 0;
  i = 3;
  keystr[0] = '\0';
  while (a < 7)
    {
      strncat(keystr, tmp = get_binary(query->masterkey[a++], 8), 8);
      free(tmp);
    }
  leftRotate(keystr, forturn * 4);
  copy_key2(i, i2, keystr, turn);
  free(keystr);
}

static void	copy_key(int i, int i2, char *tmp, char *out)
{
  while (i < 7)
    {
      while (i2 < 8)
	{
	  if (tmp[(i * 8) + i2] == '0')
	    out[i] = (out[i] << 1) + 0;
	  else if (tmp[(i * 8) + i2] == '1')
	    out[i] = (out[i] << 1) + 1;
	  i2++;
	}
      i2 = 0;
      i++;
    }
}

void		generate_key(char *input, t_query *query)
{
  intmax_t	key;
  char		out[7];
  char		*keystr;
  char		*tmp;
  int		i;
  int		i2;

  key = strtoimax(input, NULL, 16);
  keystr = get_binary(key, 64);
  i = i2 = 0;
  tmp = delete_lsb(keystr);
  copy_key(i, i2, tmp, out);
  memcpy(query->masterkey, out, 7);
  free(keystr);
  free(tmp);
}
