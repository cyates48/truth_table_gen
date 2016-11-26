#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

vector<string> get_variables(vector<string> list_of_variables)
{
    string variable;
    while (variable!="x")
    {
        cout<<"Enter a variable. Enter 'x' when done."<<endl;
        cin>>variable;
        if(variable != "x")
            list_of_variables.push_back(variable);
    }

    sort(list_of_variables.begin(), list_of_variables.end());
    return list_of_variables;

}
vector<string> get_expressions(vector<string> list_expressions)
{
    string expression;
    while (expression!="x")
    {
        cout<<"Enter a string with no spaces of a boolean expression. Enter 'x' when done."<<endl;
        cin>>expression;
        if(expression != "x")
            list_expressions.push_back(expression);
    }

    return list_expressions;
}
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
            {
                temp_combo[j] = 0;
            }
        }

        combo=temp_combo;
        input_combos.push_back(combo);
    }

    return input_combos;
}
void translate_logic(vector<string> list_expressions, vector<vector<bool>> input_combos)
{

    for (auto expression: list_expressions)
    {
        vector<char> temp_variables;
        for(int i=0;i<expression.size();++i)
        {
            if (expression[i]-0>=65 && expression[i]-0<=90)
                temp_variables.push_back(expression[i]);
        }

        cout << expression << endl;
        sort(temp_variables.begin(), temp_variables.end());


        for (auto combos: input_combos)
        {
            for (auto e: temp_variables)
            {

            }
        }
        for (auto e: temp_variables)
            cout << e << endl;
    }



}
bool and_them(bool a, bool b)
{
    return a&&b;
}

bool or_them(bool a, bool b)
{
    return a||b;
}
void print_input_combos(vector<vector<bool>> input_combos)
{
    for(auto e:input_combos)
    {
        for(auto f:e)
            cout<<f<<" ";
        cout<<endl;
    }
}
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
    //print_all_variables(list_variables, list_variables_size);
    input_combos = create_input_combos(list_variables, list_variables_size);
    print_input_combos(input_combos);

    translate_logic(list_expressions, input_combos);

    return 0;
}

