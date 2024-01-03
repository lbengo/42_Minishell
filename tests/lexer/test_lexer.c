#include <stdio.h>
#include <string.h>

#include <criterion/criterion.h>

#include "libft.h"
#include "minishell.h"

Test(Lexer_test, test_1_simple_test)
{
	char			**func_ans;
	unsigned int	func_len;
	char			correct_ans[2][7] = {{"simple\0"}, {"test1\0"}};

	func_ans = lexer("simple test");
	func_len = ft_tablerows(func_ans);
	cr_expect(func_len == 2, "Expected tokens length 2, real length %i", func_len);
	cr_expect(strcmp(func_ans[0], correct_ans[0]) == 0\
						&& strcmp(func_ans[1], correct_ans[1]) == 0, \
					"CORRECT RETURN:\narr[0] = %s\narr[1] = %s\nREAL RETURN:\narr[0] = %s\narr[1] = %s", \
					correct_ans[0], correct_ans[1], func_ans[0], func_ans[1]);
	ft_doublefree(func_ans);
}

Test(Lexer_test, test_2_empty)
{
	char			**func_ans;
	unsigned int	func_len;
	char			correct_ans[2][7] = {{"prueba\0"}, {"simple\0"}};

	func_ans = lexer("");
	func_len = ft_tablerows(func_ans);
	cr_expect(func_len == 0, "Expected tokens length 0, real length %i", func_len);
	cr_expect(strcmp(func_ans[0], ""), "CORRECT RETURN:\narr[0] = %s\narr[1] = %s", \
						correct_ans[0], correct_ans[1]);
	ft_doublefree(func_ans);
}
