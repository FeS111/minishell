#include "../include/minishell.h"
#include <stdio.h>

t_parse_cmd *handle_io(t_token **tokens, int *in, int *out, int *i) {
  if (!ft_strncmp(tokens[*i]->value, "<<", 3)) {
    if (!tokens[*i + 1])
      return (panic_token(tokens[*i]->value), NULL);
    return (here_doc(tokens, in, out, i));
  } else if (!ft_strncmp(tokens[*i]->value, "<", 2)) {
    if (!tokens[*i + 1] || tokens[*i + 1]->type != WORD)
      return (panic_token(tokens[*i]->value), NULL);
    return (left_redir(tokens, in, out, i));
  } else if (!ft_strncmp(tokens[*i]->value, ">", 2))
    return (right_redir(tokens, in, out, i));
  return (NULL);
}

t_parse_cmd *handle_word(t_token **tokens, int *in, int *out, int *i) {
  t_parse_cmd *new;
  char *word;
  char *tmp;
  char *tmp2;
  char **tmp3;
  int j;

  tmp = NULL;
  tmp2 = NULL;
  tmp3 = ft_calloc(sizeof(char *), token_size(tokens) + 1);
  j = -1;

  if (*i > 0 && tokens[*i]->value && tokens[*i - 1]->type == PIPE)
    *in = PIPE_FD;
  if (*i > 0 && tokens[*i]->value && tokens[*i - 1]->type == IO)
    *out = WRITE;
  if (tokens[*i + 1] && tokens[*i + 1]->type == IO) {
    if (!ft_strncmp(tokens[*i + 1]->value, ">", 1)) {
      new = new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL);
      return (new);
    } else if (!ft_strncmp(tokens[*i + 1]->value, ">>", 2)) {
      new = new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL,
                    ft_split(tokens[*i]->value, 0));
      return (new);
    } else {
      *in = READ;
      new = new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL);
      return (new);
    }
  } else {
    word = ft_strdup(tokens[*i]->value);
    *i += 1;
    while (tokens[*i]) {
      if (tokens[*i] && tokens[*i]->type == OPTION) {
        if (tmp)
          tmp = ft_strjoin_gnl(tmp, " ");
        tmp = ft_strjoin_gnl(tmp, tokens[*i]->value);
      }
      if (tokens[*i] && tokens[*i]->type == OPTION2) {
        if (tmp2)
          tmp2 = ft_strjoin_gnl(tmp2, " ");
        tmp2 = ft_strjoin_gnl(tmp2, tokens[*i]->value);
      }
      if (tokens[*i] && is_woo2(tokens[*i]->type))
        tmp3[++j] = ft_strdup(tokens[*i]->value);
      if (tokens[*i] && !is_woo2(tokens[*i]->type))
        break;
      *i += 1;
    }
    new = new_cmd(word, tmp, tmp2, tmp3);
    if (tokens[*i] && tokens[*i]->type == IO)
      *i -= 1;
    if (tokens[*i] && tokens[*i]->type == PIPE)
      *out = PIPE_FD;
    return (new);
  }
  return (NULL);
}
