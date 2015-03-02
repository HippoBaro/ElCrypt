/*
** main.c for ElCrypt in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sun Mar  1 20:50:07 2015 Hippolyte Barraud
** Last update Sun Mar  1 21:53:53 2015 Hippolyte Barraud
*/

#include "../includes/elcrypt.h"

char	*strdup(const char *str)
{
  int	n;
  char	*dup;

  n = strlen(str) + 1;
  dup = xmalloc(n);
  strcpy(dup, str);
  return (dup);
}

FILE	*open_files(FILE *file, char *src, int *size)
{
  file = fopen(src, "rb");
  if (!file)
    print_error("Impossible d'ouvrir les fichiers", TRUE);
  if (fseek(file, 0L, SEEK_END) != 0)
    print_error("Erreur lecture", TRUE);
  *size = ftell(file);
  if (fseek(file, 0L, SEEK_SET) != 0)
    print_error("Erreur lecture", TRUE);
  return (file);
}

unsigned char		*read_file(t_query *query, FILE **filesrc)
{
  static FILE		*file = NULL;
  static unsigned char	buff[9];
  int			ret;

  if (file == NULL)
    file = open_files(*filesrc, query->src, &query->MaxByte);
  buff[8] = '\0';
  *filesrc = file;
  ret = fread(buff, sizeof(char), 8, file);
  query->CurrentByte += ret;
  if (ret < 0)
    print_error("Erreur de lecture", TRUE);
  else if (ret == 0)
    return (get_pad_block(query));
  else if (ret != 8)
    add_pading(&buff[0], query, ret);
  return (&buff[0]);
}

void			init(t_query *query)
{
  FILE			*filedest;
  FILE			*filesrc;
  int			writeSize;
  unsigned char		*cipher_ans;
  unsigned char		*read;
  t_turn		turn;

  filesrc = NULL;
  filedest = fopen(query->dest, "wc");
  while (TRUE)
    {
      if ((read = read_file(query, &filesrc)) == NULL)
	break;
      cipher_ans = cipher(query, &turn, read);
      writeSize = fwrite(cipher_ans, 1, query->towrite, filedest);
      if (writeSize != query->towrite)
	print_error("Erreur d'écriture", TRUE);
    }
  fclose(filedest);
  fclose(filesrc);
  puts("Opération effectué avec succès !");
}

int		main(int ac, char **av)
{
  t_query	query;

  query = parse_query(ac, av);
  query.CurrentByte = 0;
  query.towrite = 8;
  query.ditpad = FALSE;
  init(&query);
  free(query.src);
  free(query.dest);
  return (0);
}
