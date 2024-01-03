#include <criterion/criterion.h>

#include "minishell.h"
#include "parser.h"

Test(test, create)
{
	int i = 1;

	cr_expect(is_heredoc("aaa") != 1, "kaixo 1");
	cr_expect(is_heredoc("<<") == 1, "kaixo 2");
	cr_expect(i != 0, "kaixo 0");
}

Test(test2, prueba_entrada)
{
	int i = 1;

	cr_expect(i == 1, "kaixo 1");
	cr_expect(i != 2, "kaixo 2");
	cr_expect(i != 0, "kaixo 0");
}
