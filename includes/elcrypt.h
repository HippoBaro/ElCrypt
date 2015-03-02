/*
** elcrypt.h for ElCrypt in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sun Mar  1 21:01:56 2015 Hippolyte Barraud
** Last update Sun Mar  1 21:34:06 2015 Hippolyte Barraud
*/

#ifndef		_ELCRYPT_H_
# define	_ELCRYPT_H_

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <signal.h>
#include <inttypes.h>

# define TRUE				1
# define FALSE				0

# define PAD				0x06

typedef unsigned char			bool;
typedef enum { UNDEF, CRYPT, DECRYPT}	e_action;

typedef struct		s_query
{
  e_action		action;
  char			*src;
  char			*dest;
  char			masterkey[7];
  bool			keyset;
  int 			MaxByte;
  int			CurrentByte;
  int			towrite;
  bool			ditpad;
}		       	t_query;

typedef struct		s_turn
{
  int			turncount;
  unsigned char		subkey[5];
  unsigned char		blockA[5];
  unsigned char		blockB[5];
}		       	t_turn;

/*
** main.c
*/
void	print_error(const char *descr, bool Critical);
void	reset_buff(unsigned char *buff, int size);
void	*xmalloc(const size_t size);
char	*strdup(const char *str);

/*
** padding.c
*/
int		delete_padding(unsigned char *lastbytes, t_query *query);
void		add_pading(unsigned char *buff, t_query *query, int start);
unsigned char	*get_pad_block(t_query *query);

/*
** parser.c
*/
t_query		parse_query(int ac, char **av);

/*
** key.c
*/
void		generate_key(char *input, t_query *query);
void		get_subkey(t_query *query, t_turn *turn, int forturn);
char		*get_binary(intmax_t pid, int coding);
void		leftRotate(char *test, int number);
char		*delete_lsb(char *keystr);

/*
** cipher.c
*/
unsigned char	*cipher(t_query *query, t_turn *turn, unsigned char *bytes);

#endif /* _ELCRYPT_H_ */
