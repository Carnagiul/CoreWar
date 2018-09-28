#include <asm.h>

void	asm_write_color_error(char *color, int len, int output)
{
	if (color == NULL)
		return ;
	if (isatty(output) == 1)
		write(output, color, len);
}