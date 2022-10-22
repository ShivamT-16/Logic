#include<iostream>
using namespace std;
#include<string>

/*class stack{
    private:
        int size,top;
        char arr[size];
    public:
        stack(int size){
            this->size = size;
            top=-1;
        }
        bool isEmpty(){
            if (top==-1){
                return 1;
            }
            else if(top>=0){
                return 0;
            }
        }
        bool isFull(){
            if (top>=size){
                return 1;
            }
            else{
                return 0;
            }
        }
        void push(char item){
            if (isFull()){
                cout<<"Overflow : Cant push";
            }
            else{
                top++;
                arr[top] = item;
            }
        }
        void pop(){
            if (isEmpty()){
                cout<<"Underflow : Cant pop";
            }
            else{
                top--;
                cout<<arr[top];
            }
        }
        char peek{
            if (!isEmpty()){
                return arr[top];}
        }
};*/

class node{
    public:
        node *left;   // pointer to left subtree
        char atom;    // value at current node 
        node *right;   // pointer to left subtree
        bool truthValue;    // truth value of atom
        string inorder;

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
            truthValue=b;   // setting truth value of atom
        }
    };

// Function to add a node
void node_add(node** node_holder, char* atom){
	node *nn = new node(*atom);
	*node_holder = nn;
}

// Function to create parse tree from prefix expression(task2)
char *treeCreator(node **node_holder, char *atom)
{
	if (*atom == '\0')
		return NULL;

	for(int i=0;i<2;i++)
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
			temp = treeCreator(&((*node_holder)->left), atom + 1);
			temp = treeCreator(&((*node_holder)->right), temp + 1);
			return temp;
		}
	}
    return NULL;
}

// Function to return In-order traversal of tree as string(Task 4)
void inOrder(node *root){
        if (root!=NULL){   
            inOrder(root->left);  // traverse left subtree
            cout<<root->atom<<" ";   // printing value at current node
            inOrder(root->right);  // traverse right subtree
            }
        }

// Function to return height of tree (task 3)
int height(node *root)
{
    if (root == NULL){
        return 0; }  
    else {
    // finding the height of each subtree 
        int height_left = height(root->left);
        int height_right = height(root->right);
 
        // We shall use the larger subtree to proceed further 
        if (height_left > height_right){
            return (height_left + 1);}
        else{
            return (height_right + 1);}   
    }
}

int index(char c,string s){
    for(int i=0;i<s.length();i++){
        if (s[i]==c){
            return i;
        }
    }
    return -1;
}
bool inside(char c,string s){
    for(int i=0;i<s.length();i++){
        if (s[i]==c){
            return 1;
        }
    }
    return 0;
}

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

bool evaluate(node* n)  // Function to evaluate parse tree and return result (task 5)
{
    static string a1;
    static string a2;
    if (n->left == NULL){
        if (n->right == NULL){
            if (!inside(n->atom,a1)){
                a1 =a1+n->atom;
                cout<<"Enter truth value for "<<n->atom<<endl;
                bool truthvalue; cin>>truthvalue;
                a2 = a2 +char(truthvalue);
                return (truthvalue); 
            }
            else{
                int i1 = index(n->atom,a1);
                return bool(a2[i1]);
            }
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

    cout<<"Welcome to our Project :)"<<endl<<endl;
    cout<<"Please enter an Infix expression :";
    cout<<endl<<endl<<"Creating Parse tree from given Prefix expression..."<<endl;
    node *root = NULL;
	string prefix = ">p+qq";        
	treeCreator(&root, &prefix[0]);
    cout<<"Tree created successfully :)"<<endl<<endl;

    int n=1;
    while(n<4){
        cout<<"Please select an option"<<endl<<"1) Height of the tree"<<endl
        <<"2) In-order Traversal of tree"<<endl
        <<"3) Evaluating truth value of the expression"
        <<endl;
        int in1;
        cin>>in1;
        if(in1==1){
            cout<<"Height of the tree = "<<height(root)<<endl<<endl;
            }
        else if(in1==2)
            {   
                cout<<endl<<"In-order Traversal"<<endl;
                inOrder(root);
                cout<<endl<<endl;
                }
        else if(in1==3){
            bool result = evaluate(root);
            cout<<"Truth value of given expression is "<<result<<endl;
            }
        else{cout<<"Try again please!";}
        n++;
        }
        /*cout<<"Do you want to have restart(0 for no,1 for yes): ";
        int in2;
        cin>>in2;cout<<endl;
        if (in2==1){main();}
        else{cout<<"Thank You!!";
            return 0;}*/
        cout<<endl<<"Thank You!";
    return 0;
}