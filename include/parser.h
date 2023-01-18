#ifndef PARSER_H
# define PARSER_H

typedef enum e_table_types
{
	CMD,
	OPT,
	OPT2,
	ARG,
} e_table_types;

typedef struct s_parse_table
{
	char	**cmd;
	char	*stdin;
	char	*stdout;
}			t_parse_table;

#endif
