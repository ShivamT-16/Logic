#include<iostream>
using namespace std;
#include<string>

class stack{
        
    // Custom Stack class
    public:
        int top,size;
        char *arr=NULL;
        // Constructor
        stack(int cap){
            size = cap;// cap- max capacity of stack
            top=-1;
            arr =new char[size];
        }
        
        bool isEmpty(){
            // To check if stack is empty
            if (top<=-1){
                return 1;
            }
            else{
                return 0;
            }
        }
        bool isFull(){
            // To check if stack is Full
            if (top>=size-1){
                return 1;
            }
            else{
                return 0;
            }
        }
        void push(int item){
            // Pushing a new item into the stack
            if (isFull()){
                // Checking for overflow condition
                cout<<"Overflow: Cant push";
            }
            else{
                top+=1;
                arr[top] = item;
            }
        }
        void pop(){
            // Remving item at top
            if (isEmpty()){
                // Checking for underflow condition
                cout<<"Underflow: Cant pop";
            }
            else{
                //cout<<arr[top];
                top-=1;
            }
        }
        char peek(){
            // Function to return topmost element of stack
            if (!isEmpty()){
                return arr[top];}
            else{return '\0';}
        }
};

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
    };


bool is_operator(char c)
{
	// To check if character is an operator(not an alphabet/digit)
    return (!isalpha(c) && !isdigit(c));
}

int order(char C)
{
    // Setting priority for operators
	if (C == '*' || C == '+')
		return 1;
	else if (C == '>')
		return 2;
	else if (C == '~')
		return 3;
	return 0;
}

string reverse(string s){
    // Function to reverse given string
    int l = s.length()-1;
    string rev;
    for(int i=l;i>=0;i--){
        rev=rev+s[i];
    }
    return rev;
}

string in_to_post(string in)
{
	// Infix to Postfix
    in = '(' + in + ')';
	int l = in.length();
	stack *char_stack = new stack(l);
	string output;

	for (int i = 0; i < l; i++) {

		if (isalpha(in[i]) || isdigit(in[i])) {
		    
			output += in[i];
		} else if (in[i] == '(') {
		    
			char_stack->push('(');
		} else if (in[i] == ')') {
		    
			while (char_stack->peek() != '(') {
				output += char_stack->peek();
				char_stack->pop();
			}
			
			char_stack->pop();
			
		} else {
		    
			if (is_operator(char_stack->peek())) {
			    
				if(in[i]=='>') {
				    
					while (order(in[i]) <= order(char_stack->peek())) {
						output+=char_stack->peek();
						char_stack->pop();
					}
				}
				else
				{
					while (order(in[i]) < order(char_stack->peek()))
					{
						output+=char_stack->peek();
						char_stack->pop();
					}
					
				}

				char_stack->push(in[i]);
			}
		}
	}
	while(!char_stack->isEmpty()){
		output+=char_stack->peek();
		char_stack->pop();
	}
	return output;
}

string post_to_pre(string in)
{
	// Postfix to Prefix
    int l = in.length();
	string s1 = reverse(in);
    string s2;

	for (int i = 0; i < l; i++) {

		if (s1[i] == '(') {
			s2+=')';
		}
		else if (s1[i] == ')') {
			s2+='(';
		}
        else{
            s2+=s1[i];
        }
	}

	string pre = in_to_post(s2);
	string pre_ = reverse(pre);
	return pre_;
}

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
    cout<<"Please enter an Infix expression : ";
    string str;
    cin>>str;
    cout<<endl<<"Prefix form"<<endl<< post_to_pre(str) <<endl;
    cout<<endl<<"Creating Parse tree from given Prefix expression..."<<endl;
    node *root = NULL;
	string prefix = post_to_pre(str);        
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
        cout<<endl<<"Thank You!";
    return 0;
}