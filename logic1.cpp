#include <bits/stdc++.h>
using namespace std;

bool is_operator(char c)
{
	return (!isalpha(c) && !isdigit(c));
}

int order(char C)
{
	if (C == '*' || C == '+')
		return 1;
	else if (C == '^')
		return 2;
	else if (C == '~')
		return 3;
	return 0;
}

string in_to_post(string in)
{
	in = '(' + in + ')';
	int l = in.size();
	stack<char> char_stack;
	string output;

	for (int i = 0; i < l; i++) {

		if (isalpha(in[i]) || isdigit(in[i])) {
		    
			output += in[i];
		} else if (in[i] == '(') {
		    
			char_stack.push('(');
		} else if (in[i] == ')') {
		    
			while (char_stack.top() != '(') {
				output += char_stack.top();
				char_stack.pop();
			}
			
			char_stack.pop();
			
		} else {
		    
			if (is_operator(char_stack.top())) {
			    
				if(in[i] == '^') {
				    
					while (order(in[i]) <= order(char_stack.top())) {
						output += char_stack.top();
						char_stack.pop();
					}
				}
				else
				{
					while (order(in[i]) < order(char_stack.top()))
					{
						output += char_stack.top();
						char_stack.pop();
					}
					
				}

				char_stack.push(in[i]);
			}
		}
	}
	while(!char_stack.empty()){
		output += char_stack.top();
		char_stack.pop();
	}
	return output;
}

string post_to_pre(string in)
{
	int l = in.size();
	reverse(in.begin(), in.end());

	for (int i = 0; i < l; i++) {

		if (in[i] == '(') {
			in[i] = ')';
		}
		else if (in[i] == ')') {
			in[i] = '(';
		}
	}

	string pre = in_to_post(in);
	reverse(pre.begin(), pre.end());
	return pre;
}

int main()
{
	string s = ("p*(((~p>q)*s)+r)");
	cout << post_to_pre(s) << std::endl;
	return 0;
}
