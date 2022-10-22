#include<iostream>
using namespace std;

class stack{
        
    public:
        int top,size;
        char *arr;
        stack(int cap){
            size = cap;
            top=-1;
        }
        
        bool isEmpty(){
            if (top<=-1){
                return 1;
            }
            else{
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
                cout<<"Overflow: Cant push";
            }
            else{
                top+=1;
                //cout<<top<<endl;
                arr[top] = item;
            }
        }
        void pop(){
            if (isEmpty()){
                cout<<"Underflow: Cant pop";
            }
            else{
                top-=1;
                cout<<arr[top];
            }
        }
        char peek(){
            if (!isEmpty()){
                return arr[top];}
            else{return '\0';}
        }
};
int main(){
    stack *s = new stack(5);
    //s->push('a');
    s->push('c');
    
}