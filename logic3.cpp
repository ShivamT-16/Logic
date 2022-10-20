#include <iostream>
using namespace std;
class node
{
public:
    string atom;
    node *left;
    node *right;
};

string l;

string inorder(node *x)
{
    if (x != NULL)
    {
        inorder(x->left);
        l += (x->atom);
        inorder(x->right);
    }
    return l;
}
