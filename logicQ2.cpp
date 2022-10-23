#include <iostream>
using namespace std;

class node
{
public:
	char data;
	node *left;
	node *right;

	node(char c)
	{
		data = c;
		left = NULL;
		right = NULL;
	}
};

void node_add(node** node_holder, char* atom){
	node *nn = new node(*atom);
	*node_holder = nn;
}

char *treeCreator(node **node_holder, char *atom)
{
	if (*atom == '\0')
		return NULL;

	while(1)
	{
		char *temp = NULL;
		if (*node_holder == NULL)
		{
			node_add(node_holder,atom);
		}
		else
		{
			if (*atom >= 'a' && *atom <= 'z')
			{
				return atom;
			}
            if(*atom=='~'){
                temp = treeCreator(&((*node_holder)->right), atom + 1);
			    return temp;
            }

			temp = treeCreator(&((*node_holder)->left), atom + 1);
			temp = treeCreator(&((*node_holder)->right), temp + 1);
			return temp;
		}
	}
}

int main()
{
	node *root = NULL;
	string prefix = ">p*q~r";
	treeCreator(&root, &prefix[0]);
	return 0;
}
