#include "temp.h"

int main()
{
	// char	*str = "ps aux | grep mrantil | grep -v grep | grep 8 | wc -l";
	// char	*str = "cat < 2.txt | grep t > 1.txt";
	// char *str = "echo hello | grep h > text.txt ; cat text.txt ; echo again";
	// char *str = "echo try > to_me again";
	// char *str = "echo hello ; echo world";
	// char *str = "echo tjotjo > file ; cat < file > file2";
	// char *str = "cat < file | grep t > file2"; 
	char *str = "echo $PWD ; cd .. ; echo $PWD";
	t_node	*root;

	root = parse_line(&str); //make a loop and check for str != NULL and if you encouunter redir in string break out and set it to new root here
	print_tree(root);
	write(1, "\n", 1);
	exec_tree(root);
	exit(0);
}