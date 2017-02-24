/*
Lakshay Anand
LA436231
001269497
*/
typedef	struct tree_node
{
	char string[16];  //20 is the maxlen, adding +1 to it = 21 i.e. maxlen + 1
	struct tree_node *left_child, *right_child;
}tree_node;
