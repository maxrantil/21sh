#include "temp.h"

// one backslag take it away, two backslshes keep one. last newline is always changes to \0
char *lexer(char *str)
{
	int i = 0;
	int j = 0;
	char *new;

	new = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		new[j++] = str[i++];
	}
	new[j - 1] = '\0';
	return (new);
}

int main()
{
	// char	*str = "ps aux | grep mrantil | grep -v grep | grep 8 | wc -l";
	// char	*str = "cat < 2.txt | grep t > 1.txt";
	// char *str = "echo hello | grep h > text.txt ; cat text.txt ; echo again";
	// char *str = "echo try > to_me again";
	// char *str = "echo hello ; echo world";
	// char *str = "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi";
	// char *str = "echo tjotjo > file ; cat < file > file2";
	// char *str = "cat < file | grep t > file2"; 
	// char *str = "echo $PWD ; cd .. ; echo $PWD";
	// char *str = "echo hello\n"; //echo hello\0 
	// char *str = "echo \'hello\n"; //echo 'hello\0 
	// char *str = "echo \\hello\n"; //echo \hello\0
	// char *str = "echo \\nhello\n";
	// char *str = "echo '\nhello\nagain'\n";
	// char *str = "echo \nhello\nagain\n";
	// char *str = "echo hello\again'\n"; // echo helloagain\0
	// one backslag take it away, two backslshes keep one. last newline is always changes to \0
	t_node	*root;

	// str = lexer(str);
	// printf("%s\n", str);
	root = parse_line(&str); //make a loop and check for str != NULL and if you encouunter redir in string break out and set it to new root here
	print_tree(root);
	write(1, "\n", 1);
	exec_tree(root);
	exit(0);
}