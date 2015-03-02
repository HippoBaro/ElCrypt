/*
** parser.c for ElCrypt in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sun Mar  1 20:58:39 2015 Hippolyte Barraud
** Last update Sun Mar  1 21:39:56 2015 Hippolyte Barraud
*/

#include "../../includes/elcrypt.h"

extern char	*optarg;

static void	init_query(t_query *query)
{
  query->action = UNDEF;
  query->dest = NULL;
  query->src = NULL;
}

static void	detect_action(int c, t_query *out)
{
  if (c == 'd')
    {
      if (out->action == UNDEF)
	out->action = DECRYPT;
      else
	print_error("Les opérations de cryptage et "
		    "décryptage sont mutuellement exclusives.", TRUE);
    }
  else if (c == 'e')
    {
      if (out->action == UNDEF)
	out->action = CRYPT;
      else
	print_error("Les opérations de cryptage et "
		    "décryptage sont mutuellement exclusives.", TRUE);
    }
}

static void	get_args(int c, t_query *out)
{
  if (c == 'f')
    out->src = strdup(optarg);
  else if (c == 'o')
    out->dest = strdup(optarg);
  else if (c == 'k')
    {
      if (strncmp(optarg, "0x", 2) != 0)
	print_error("La clé doit être rentrée"
		    " sous forme héxadécimale (0x...)", TRUE);
      generate_key(optarg, out);
      out->keyset = TRUE;
    }
}

void	test_validity(t_query *query)
{
  if (query->action == UNDEF)
    print_error("Aucune opération spécifié.", TRUE);
  else if (query->dest == NULL)
    print_error("Aucune destination spécifié", TRUE);
  else if (query->src == NULL)
    print_error("Aucune source spécifié", TRUE);
  else if (query->keyset == FALSE)
    print_error("Clé de chriffrage manquante.", TRUE);
}

t_query		parse_query(int ac, char **av)
{
  t_query	out;
  int		c;

  init_query(&out);
  out.keyset = FALSE;
  while ((c = getopt(ac , av, "def:o:k:")) != -1)
    {
      detect_action(c, &out);
      get_args(c, &out);
      if (c == '?')
	{
	  printf("Argument inconnu : -%c.\n", c);
	  break;
	}
    }
  test_validity(&out);
  return (out);
}
