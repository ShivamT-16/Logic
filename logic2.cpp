#include<iostream>
using namespace std;
#include<string>

class node{
    public:
        node *left;   // pointer to left subtree
        char atom;    // value at current node 
        node *right;   // pointer to left subtree
        bool truthValue;    // truth value of atom

        node(char val){
            this->atom = val;
            // making left and right pointers point to NULL
            this->left = NULL; 
            this->right = NULL;
        }

        node(char val,bool b){
            this->atom = val;
            // making left and right pointers point to NULL
            this->left = NULL; 
            this->right = NULL;
            truthValue=b;
        }
        void inOrder(){
            if (this!=NULL){   
                this->left->inOrder();  // traverse left subtree
                cout<<(this->atom)<<" ";;   // printing value at current node
                this->right->inOrder();  // traverse right subtree
                 }
            }

        int height()
        {
            if (this == NULL){
                return 0; }  
            else {
            // finding the height of each subtree //
                int height_left = this->left->height();
                int height_right = this->right->height();
 
            // We shall use the larger subtree to proceed further //
                if (height_left > height_right){
                    return (height_left + 1);}
                else{
                    return (height_right + 1);}
            }   
        }
    };

bool eval(char op,bool b1){
    if (op=='~'){
        return (!b1) ;}
    else{
        return 0;
    }
}
bool eval(char op,bool b1,bool b2){
    if (op=='*'){
        return (b1 && b2) ;
    }
    if (op=='+'){
        return (b1 || b2) ;
    }
    if (op=='>'){
            return (eval('~',b1) || b2) ;
        }
    else{
        return 0;
    }
}

bool evaluate(node* n)
{
    if (n->left == NULL){
        if (n->right == NULL){
            return (n->truthValue); 
        }
        else{
            bool b = evaluate(n->right);
            return eval('~',b);
        }
    }
    else{
        bool l = evaluate(n->left);
        bool r = evaluate(n->right);
        return eval(n->atom,l,r);
    }
}

int main(){
    node *n0 = new node('~');
    node *n1 = new node('+');
    node *n2 = new node('*');
    node *n3 = new node('>');
    node *n4 = new node('p',1);
    node *n5 = new node('q',0);
    node *n6 = new node('p',1);
    node *n7 = new node('q',0);

    n0->left=NULL;
    n0->right=n1;
    n1->left=n2;
    n1->right=n3;
    n2->left=n4;
    n2->right=n5;
    n3->left=n6;
    n3->right=n7;
    n4->left=NULL;
    n4->right=NULL;
    n5->left=NULL;
    n5->right=NULL;
    n6->left=NULL;
    n6->right=NULL;
    n7->left=NULL;
    n7->right=NULL;

    bool result = evaluate(n0);
    cout<<result<<endl;

    cout<<"In-order Traversal"<<endl;
    n0->inOrder();
    cout<<endl<<"Height of the tree "<<n0->height()<<endl;
    n1 = new node('~');
    n2 = new node('>');
    n3 = new node('*');
    n4 = new node('+');
    n5 = new node('~');
    n6 = new node('p',1);
    n7 = new node('*');
    node *n8 = new node('p',1);
    node *n9 = new node('q',1);
    node *n10 = new node('p',1);
    node *n11 = new node('q',1);
    n1->left = NULL;
    n1->right = n2;
    n2->left = n3;
    n2->right = n4;
    n4->left = n10;
    n4->right = n11;
    n3->left = n5;
    n3->right = n7;
    n7->left = n8;
    n7->right = n9;
    n8->left = NULL;
    n8->right = NULL;
    n9->left = NULL;
    n9->right = NULL;
    n5->left = NULL;
    n5->right = n6;
    n6->left = NULL;
    n6->right = NULL;
    n10->left = NULL;
    n10->right = NULL;
    n11->left = NULL;
    n11->right = NULL;
    result = evaluate(n1);
    cout<<(result);

    return 0;
}