/*
** miscs.c for ElCrypt in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sun Mar  1 20:52:51 2015 Hippolyte Barraud
** Last update Sun Mar  1 20:53:34 2015 Hippolyte Barraud
*/

#include "../includes/elcrypt.h"

void	reset_buff(unsigned char *buff, int size)
{
  int	i;

  i = 0;
  while (i < size)
    buff[i++] = '\0';
}

void	print_error(const char *descr, bool Critical)
{
  printf("Erreur fatale : %s.\n", descr);
  if (Critical)
    exit(1);
}

void 	term_error(int num)
{
  if (num == 11)
	print_error("Erreur critique : vérifier les paramettres.", TRUE);
}

void	handle_critic(void)
{
  signal(11, term_error);
}

void	*xmalloc(const size_t size)
{
  void	*p;

  p = malloc(size);
  if (p == NULL)
    print_error("Erreur durant allocation mémoire", TRUE);
  return p;
}
