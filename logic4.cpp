#include <iostream>
using namespace std;
class node
{
public:
    string atom;
    node *left;
    node *right;
};

int height(node *x)
{
    if (x == NULL)
    {
        return 0;
    }
    else
    {
        int a = height(x->left);
        int b = height(x->right);
        return max(a, b) + 1;
    }
}