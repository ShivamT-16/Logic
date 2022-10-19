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

        node(char val,bool b){  // overloaded constructor to set truth value of atom
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
            // finding the height of each subtree 
                int height_left = this->left->height();
                int height_right = this->right->height();
 
            // We shall use the larger subtree to proceed further 
                if (height_left > height_right){
                    return (height_left + 1);}
                else{
                    return (height_right + 1);}
            }   
        }
    };

bool eval(char op,bool b1){
    // function to return complement of atom (NOT Implementation)
    if (op=='~'){
        return (!b1) ;}
    else{
        return -1;
    }
    }

bool eval(char op,bool b1,bool b2){
    // AND Implementation
    if (op=='*'){
        return (b1 && b2) ;
    }
    // OR Implementation
    if (op=='+'){
        return (b1 || b2) ;
    }
    // IMPLIES Implication
    if (op=='>'){
            return (eval('~',b1) || b2) ;
        }
    else{
        return -1;
    }
}

bool evaluate(node* n)  // Function to evaluate parse tree and return result
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

    cout<<"Welcome to our Project :)"<<endl<<endl;
    cout<<"Please enter an Infix expression :";
    cout<<endl<<endl<<"Creating Parse tree from given Prefix expression..."<<endl<<endl;

    int n=1;
    while(n<4){
        cout<<"Please select an option"<<endl<<"1) Height of the tree"<<endl
        <<"2) In-order Traversal of tree"<<endl
        <<"3) Evaluating truth value of the expression"
        <<endl;
        int in1;
        cin>>in1;
        if(in1==1){
            cout<<"Height of the tree = "<<n0->height()<<endl<<endl;
            }
        else if(in1==2)
            {   
                cout<<endl<<"In-order Traversal"<<endl;
                n0->inOrder();
                cout<<endl;
                }
        else if(in1==3){
            bool result = evaluate(n0);
            cout<<"Truth value of given expression is "<<result<<endl;
            }
        n++;
        }
        cout<<"Do you want to have restart(0 for no,1 for yes): ";
        int in2;
        cin>>in2;cout<<endl;
        if (in2==1){main();}
        else{cout<<"Thank You!!";
            return 0;}
    return 0;
}