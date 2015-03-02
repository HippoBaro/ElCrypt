/*
** cipher.c for ElCrypt in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Mar  1 20:53:55 2015 Hippolyte Barraud
** Last update Sun Mar  1 20:55:50 2015 Hippolyte Barraud
*/

#include "../../includes/elcrypt.h"

void		apply_xor(unsigned char *blockA, unsigned char *blockB,
			  unsigned char *subkey)
{
  int		i;
  unsigned char blocktmp[5];

  i = 0;
  blocktmp[4] = '\0';
  while (i < 4)
    {
      blocktmp[i] = blockB[i] ^ subkey[i];
      i++;
    }
  i = 0;
  while (i < 4)
    {
      blockA[i] = blockA[i] ^ blocktmp[i];
      i++;
    }
  blockA[4] = blockB[4] = '\0';
}

static void	merge_block(unsigned char *bA,
			    unsigned char *bB, unsigned char *out)
{
  out[0] = bA[0];
  out[1] = bA[1];
  out[2] = bA[2];
  out[3] = bA[3];
  out[4] = bB[0];
  out[5] = bB[1];
  out[6] = bB[2];
  out[7] = bB[3];
}

unsigned char		*decipher(t_query *query, t_turn *turn,
				  unsigned char *bytes)
{
  int			i;
  static unsigned char	out[9];

  i = 7;
  out[0] = '\0';
  turn->blockA[0] = bytes[0];
  turn->blockA[1] = bytes[1];
  turn->blockA[2] = bytes[2];
  turn->blockA[3] = bytes[3];
  turn->blockB[0] = bytes[4];
  turn->blockB[1] = bytes[5];
  turn->blockB[2] = bytes[6];
  turn->blockB[3] = bytes[7];
  while (i > -1)
    {
      get_subkey(query, turn, i);
      if (i % 2 == 0)
	apply_xor(&turn->blockB[0], &turn->blockA[0], &turn->subkey[0]);
      else
	apply_xor(&turn->blockA[0], &turn->blockB[0], &turn->subkey[0]);
      i--;
    }
  merge_block(turn->blockB, turn->blockA, out);
  out[8] = '\0';
  return (out);
}

unsigned char		*encipher(t_query *query, t_turn *turn,
				  unsigned char *bytes)
{
  int			i;
  static unsigned char	out[9];

  i = 0;
  out[0] = '\0';
  turn->blockA[0] = bytes[0];
  turn->blockA[1] = bytes[1];
  turn->blockA[2] = bytes[2];
  turn->blockA[3] = bytes[3];
  turn->blockB[0] = bytes[4];
  turn->blockB[1] = bytes[5];
  turn->blockB[2] = bytes[6];
  turn->blockB[3] = bytes[7];
  while (i < 8)
    {
      get_subkey(query, turn, i);
      if (i % 2 == 0)
	apply_xor(&turn->blockA[0], &turn->blockB[0], &turn->subkey[0]);
      else
	apply_xor(&turn->blockB[0], &turn->blockA[0], &turn->subkey[0]);
      i++;
    }
  merge_block(turn->blockB, turn->blockA, out);
  out[8] = '\0';
  return (out);
}

unsigned char		*cipher(t_query *query, t_turn *turn,
				unsigned char *bytes)
{
  unsigned char		*out;

  reset_buff(turn->blockA, 5);
  reset_buff(turn->blockB, 5);
  if (query->action == DECRYPT)
    {
      out = decipher(query, turn, bytes);
      if (query->CurrentByte == query->MaxByte)
	query->towrite = delete_padding(out, query);
    }
  else
    out = encipher(query, turn, bytes);
  return (out);
}
