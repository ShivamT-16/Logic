#include<iostream>
using namespace std;
#include<string>

/// Custom Stack class 
class stack{
        
    public:
        int top,size;
        char *arr=NULL;
        /// Constructor
        stack(int cap){
	/// cap- max capacity of stack
            size = cap;
            top=-1;
            arr =new char[size];
        }
        
	/// To check if stack is empty 
        bool isEmpty(){
            if (top<=-1){
                return 1;
            }
            else{
                return 0;
            }
        }
	/// To check if stack is Full 
        bool isFull(){
            if (top>=size-1){
                return 1;
            }
            else{
                return 0;
            }
        }
	/// Pushing a new item into the stack 
        void push(char item){
            
            if (isFull()){
                /// Checking for overflow condition
                cout<<"Overflow: Cant push";
            }
            else{
                top+=1;
                arr[top] = item;
            }
        }
	/// Removing item at top 
        void pop(){
            
            if (isEmpty()){
                /// Checking for underflow condition
                cout<<"Underflow: Cant pop";
            }
            else{
                //cout<<arr[top];
                top-=1;
            }
        }
	/// Function to return topmost element of stack
        char peek(){
             
            if (!isEmpty()){
                return arr[top];}
            else{return '\0';}
        }
};

class node{
    public:
	/// pointer to left subtree 
        node *left;   
	/// value at current node  
        char atom;   
	/// pointer to left subtree 
        node *right;   
	/// truth value of atom
        bool truthValue;    

        node(char val){
            this->atom = val;
            /// making left and right pointers point to NULL
            this->left = NULL; 
            this->right = NULL;
        }
    };

class boolOps{
    public:
	/// To check if character is an operator(not an alphabet/digit)
        bool is_operator(char c)
        { 
            return (!isalpha(c) && !isdigit(c));
        }

        int order(char C)
        {
            /// Setting priority for operators 
            if (C == '*' || C == '+')
                return 1;
            else if (C == '>')
                return 2;
            else if (C == '~')
                return 3;
            return 0;
        }

         /// To find index of char in string 
        int index(char c,string s){ 
        for(int i=0;i<s.length();i++){
            if (s[i]==c){
                return i;
            }
        }
        return -1;
        }
        /// To check if char is found inside string 
        bool inside(char c,string s){
            for(int i=0;i<s.length();i++){
                if (s[i]==c){
                    return 1;
                }
            }
            return 0;
        }

        bool eval(char op,bool b1){
            /// function to return complement of atom (NOT Implementation) 
            if (op=='~'){
                return (!b1) ;}
            else{
                return -1;
            }
            }

        bool eval(char op,bool b1,bool b2){
            /// AND Implementation 
            if (op=='*'){
                return (b1 && b2) ;
            }
            /// OR Implementation 
            if (op=='+'){
                return (b1 || b2) ;
            }
            /// IMPLIES Implementation
            if (op=='>'){
                    return (eval('~',b1) || b2) ;
                }
            else{
                return -1;
            }
        }

	/// Function to evaluate parse tree and return result (task 5) 
        bool evaluate(node* n)  
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
};

class strOps{
    public:
        boolOps *b1 = new boolOps();
	/// Function to reverse given string 
        string reverse(string s){
            int l = s.length()-1;
            string rev;
            for(int i=l;i>=0;i--){
                rev=rev+s[i];
            }
            return rev;
        }

	/// Infix to Postfix
        string in_to_post(string in)
        { 
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
                    
                    if (b1->is_operator(char_stack->peek())) {
                        
                        if(in[i]=='>') {
                            
                            while (b1->order(in[i]) <= b1->order(char_stack->peek())) {
                                output+=char_stack->peek();
                                char_stack->pop();
                            }
                        }
                        else
                        {
                            while (b1->order(in[i]) < b1->order(char_stack->peek()))
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
	
/// Postfix to Prefix 
        string post_to_pre(string in)
        {
            
            int l = in.length();
            strOps *s3 = new strOps();
            string s1 = s3->reverse(in);
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

            string pre = s3->in_to_post(s2);
            string pre_ = s3->reverse(pre);
            return pre_;
        }
};

class tree{
    public:
        /// Function to add a node 
        void node_add(node** node_holder, char* atom){
            node *nn = new node(*atom);
            *node_holder = nn;
        }

        /// Function to create parse tree from prefix expression(task2) 
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

        /// Function to return In-order traversal of tree as string(Task 4) 
        void inOrder(node *root){
                if (root!=NULL){   
                    inOrder(root->left);  /// traverse left subtree
                    cout<<root->atom<<" ";   /// printing value at current node
                    inOrder(root->right);  /// traverse right subtree
                    }
                }

        /// Function to return height of tree (task 3) 
        int height(node *root)
        {
            if (root == NULL){
                return 0; }  
            else {
            /// finding the height of each subtree  
                int height_left = height(root->left);
                int height_right = height(root->right);
        
                /// We shall use the larger subtree to proceed further  
                if (height_left > height_right){
                    return (height_left + 1);}
                else{
                    return (height_right + 1);}   
            }
        }
};

int main(){

    boolOps *b1 = new boolOps();
    strOps *s1 = new strOps();
    tree *t1 = new tree();
    cout<<"Welcome to our Project :)"<<endl<<endl;
    cout<<"Please enter an Infix expression : ";
    string str;
    cin>>str;
    cout<<endl<<"Prefix form"<<endl<< s1->post_to_pre(str) <<endl;
    cout<<endl<<"Creating Parse tree from given Prefix expression..."<<endl;
    node *root = NULL;
	string prefix = s1->post_to_pre(str);        
	t1->treeCreator(&root, &prefix[0]);
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
            cout<<"Height of the tree = "<<t1->height(root)<<endl<<endl;
            }
        else if(in1==2)
            {   
                cout<<endl<<"In-order Traversal"<<endl;
                t1->inOrder(root);
                cout<<endl<<endl;
                }
        else if(in1==3){
            bool result = b1->evaluate(root);
            cout<<"Truth value of given expression is "<<result<<endl;
            }
        else{cout<<"Try again please!";}
        n++;
        }
        cout<<endl<<"Thank You!";
    return 0;
}
