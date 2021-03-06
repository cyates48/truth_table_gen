#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

// this function considers the precedence for characters 
//  when it is looking at the boolean expressions
int precedence(const string & op)
{
    switch(op[0])
    {
    case '*':
    case '/':
    case '%':
        return 2;

    case '+':
    case '-':
        return 1;

    default:
        return 0;
    }
}

// as the name suggests, it puts a string from infix position to a postfix position
//      we use this function when putting the boolean expression into the stack
string infix_to_postfix(const string & infix)
{
    string token;
    stack<string> s;
    string ans;

    for(int i=0;i<infix.size();++i)
    {
        token=infix[i];

        if (token == "(")
            s.push(token);

        if (token == ")")
        {
            while (s.top() != "(")
            {
                ans += " ";
                ans += s.top();
                s.pop();
            }
            s.pop();

        }
        if (token == "+" || token == "-" || token == "*" ||
                token == "/" || token == "%")
        {
            while (!s.empty() &&
                   (precedence(s.top()) >= precedence(token)))
                {
                    ans += " ";
                    ans += s.top();
                    s.pop();
                }
             s.push(token);
        }
        else // operand
        {
            ans += " ";
            ans += token;

        }
    }
    while (!s.empty())
    {
        ans += " ";
        ans += s.top();
        s.pop();
    }
    return ans;
}

// this function simply takes the AND of two variables
bool and_them(bool a, bool b)
{
    return a&&b;
}

// this functions inverts the boolean value
bool invert(bool a)
{
    if (a==1)
        return 0;
    return 1;
}

// this function takes the OR value of two variables
bool or_them(bool a, bool b)
{
    return a||b;
}

// this function prompts the user to type in a certain amount of variables
//  and returns the list of variables in a vector
vector<string> get_variables(vector<string> list_of_variables)
{
    string variable;
    while (variable!="X")
    {
        cout<<"Enter a variable. Enter 'X' when done."<<endl;
        cin>>variable;
        if(variable != "X")
            list_of_variables.push_back(variable);
    }

    sort(list_of_variables.begin(), list_of_variables.end());
    return list_of_variables;

}

// this function prompts the user to put in any number of boolean expressions,
//  which are stored and returned in a vector
vector<string> get_expressions(vector<string> list_expressions)
{
    string expression;
    while (expression!="X")
    {
        cout<<"Enter a string with no spaces of a boolean expression. Enter 'X' when done."<<endl;
        cin>>expression;
        if(expression != "X")
            list_expressions.push_back(expression);
    }

    return list_expressions;
}

// this function produces 2^n (where n = size of list_of_variables) binary combinations 
vector<vector<bool>> create_input_combos(vector<string> list, int list_size)
{
    vector<vector<bool>> input_combos;
    vector<bool> combo;

    for (int i=0; i<list.size(); ++i)
    {
        combo.push_back(0);
    }

    input_combos.push_back(combo);
    vector<bool> temp_combo=combo;
    for (int i = 1; i < pow(2,list_size); ++i)
    {
        for(int j=temp_combo.size()-1;j>=0;--j)
        {
            if (temp_combo[j] == 0)
            {
                temp_combo[j] = 1;
                j = -1;
            }
            else
                temp_combo[j] = 0;
        }
        combo=temp_combo;
        input_combos.push_back(combo);
    }
    return input_combos;
}

// this function creates a boolean result by inputting the combos into the expressions
void translate_logic(vector<string> list_expressions, vector<vector<bool>> input_combos)
{
    pair<char,bool> cbpair;
    string ilyas="'Chris";
    char invert_symbol=ilyas[0];

    for (auto expression: list_expressions)
    {
        vector<char> expression_variables;
        cout<<"-----------------------------------"<<endl;
        cout<<expression<<endl;

        expression=infix_to_postfix(expression);

        for(int i=0;i<expression.size();++i)
        {
            if (expression[i]-0>=65 && expression[i]-0<=90)
                expression_variables.push_back(expression[i]);
        }

        sort(expression_variables.begin(), expression_variables.end());

        for (auto combo: input_combos)
        {
            stack<bool> s;
            for (auto character:expression)
            {
                if(character-0>=65 && character-0<=90)
                {
                    for(int i=0;i<expression.size();++i)
                    {
                        if(character==expression_variables[i])
                        {
                             cbpair=make_pair(character,combo[i]);
                             s.push(cbpair.second);
                        }
                    }
                }
                else
                {
                    if (character=='+')
                    {
                        bool value1=s.top();
                        s.pop();
                        bool value2=s.top();
                        s.pop();
                        bool new_value=or_them(value1,value2);
                        s.push(new_value);
                    }

                    else if (character=='*')
                    {
                        bool value1=s.top();
                        s.pop();
                        bool value2=s.top();
                        s.pop();
                        bool new_value=and_them(value1,value2);
                        s.push(new_value);
                    }

                    else if (character == invert_symbol)
                    {
                        bool value=s.top();
                        s.pop();
                        value=invert(value);
                        s.push(value);
                    }
                }
            }

            for (int i=0;i<combo.size();++i)
                cout<<combo[i];
            cout<<": "<<s.top()<<endl;
        }
         cout<<"-----------------------------------"<<endl;
    }
}

// prints 2^n combos
void print_input_combos(vector<vector<bool>> input_combos)
{
    for(auto e:input_combos)
    {
        for(auto f:e)
            cout<<f<<" ";
        cout<<endl;
    }
}

// prints all the variables
void print_all_variables (vector<string> list,int list_size)
{
    for (auto e:list)
        cout<<e<<" ";
    cout<<endl;

    cout<<"Amount of variables: "<<list_size<<endl;
}

int main(int argc, char *argv[])
{

    vector<string> list_variables;
    vector<string> list_expressions;
    vector<vector<bool>> input_combos;

    list_variables = get_variables(list_variables);
    list_expressions = get_expressions(list_expressions);

    int list_variables_size = list_variables.size();
//    print_all_variables(list_variables, list_variables_size);

    input_combos = create_input_combos(list_variables, list_variables_size);
//    print_input_combos(input_combos);

    translate_logic(list_expressions, input_combos);

    return 0;
}
