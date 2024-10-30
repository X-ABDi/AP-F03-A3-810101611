#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#define PLUSS '+'
#define MINUS '-'
#define MULTIPLE '*'

using namespace std;
using detectOperator = function<vector<int>(vector<int> &, vector<int> &)>;

// map<string, detectOperator> opt_map{
//     {PLUSS, plussFunction},

// };
using detectOperator = function<vector<int>(vector<int> &, vector<int> &)>;

string getInput()
{
    string item;
    cin >> item;
    cin >> item;
    return item;
}

void processInput(vector<int> &number_vector, vector<char> &symbol_vector, string line)
{
    int i{0};
    size_t length{line.length()};
    string each_num;
    for (i = 0; i < length; i++)
    {
        if (isdigit(line[i]))
        {
            each_num.push_back(line[i]);
        }
        else
        {
            number_vector.push_back(stoi(each_num));
            each_num.clear();
            symbol_vector.push_back(line[i]);
        }
        if (i == length - 1)
        {
            number_vector.push_back(stoi(each_num));
        }
    }
}

void eraseDuplicate(vector<int> &result)
{
    sort(result.begin(), result.end());
    vector<int>::iterator it;
    it = unique(result.begin(), result.end());
    result.erase(it, result.end());
}

vector<int> plussFunction(vector<int> &left_result, vector<int> &right_result)
{
    vector<int> result;
    for (int i = 0; i < left_result.size(); i++)
    {
        for (int j = 0; j < right_result.size(); j++)
        {
            result.push_back(left_result[i] + right_result[j]);
        }
    }
    eraseDuplicate(result);
    return result;
}

vector<int> minusFunction(vector<int> &left_result, vector<int> &right_result)
{
    vector<int> result;
    for (int i = 0; i < left_result.size(); i++)
    {
        for (int j = 0; j < right_result.size(); j++)
        {
            result.push_back(left_result[i] - right_result[j]);
        }
    }
    eraseDuplicate(result);
    return result;
}

vector<int> multipleFunction(vector<int> &left_result, vector<int> &right_result)
{
    vector<int> result;
    for (int i = 0; i < left_result.size(); i++)
    {
        for (int j = 0; j < right_result.size(); j++)
        {
            result.push_back(left_result[i] * right_result[j]);
        }
    }
    eraseDuplicate(result);
    return result;
}

vector<int> doTheCalculation(vector<int> &left_result, vector<int> &right_result, char opt)
{
    vector<int> final_result(0);
    if (opt == PLUSS)
    {
        final_result = plussFunction(left_result, right_result);
    }
    else if (opt == MINUS)
    {
        final_result = minusFunction(left_result, right_result);
    }
    else if (opt == MULTIPLE)
    {
        final_result = multipleFunction(left_result, right_result);
    }
    return final_result;
}

vector<int> sandwitchingCount(int start_index, int end_index, vector<int> &number_vector, vector<char> &symbol_vector)
{
    cout << "start index: " << start_index << "  end index: " << end_index << endl;
    if (end_index - start_index == 1)
    {
        vector<int> result;
        if (symbol_vector[start_index] == PLUSS)
        {
            result.push_back(number_vector[start_index] + number_vector[end_index]);
            return result;
        }
        else if (symbol_vector[start_index] == MINUS)
        {
            result.push_back(number_vector[start_index] - number_vector[end_index]);
            return result;
        }
        else if (symbol_vector[start_index] == MULTIPLE)
        {
            result.push_back(number_vector[start_index] * number_vector[end_index]);
            return result;
        }
    }
    else if (end_index == start_index)
    {
        vector<int> result{number_vector[start_index]};
        return result;
    }

    vector<int> ans;
    int i{0};
    for (i = start_index; i < end_index; i++)
    {
        cout << "in for loop,,:  " << start_index << " " << i  << " " << i + 1 << " " << end_index << endl;
        vector<int> left_result{sandwitchingCount(start_index, i, number_vector, symbol_vector)};
        vector<int> right_result{sandwitchingCount(i + 1, end_index, number_vector, symbol_vector)};
        vector<int> new_res{doTheCalculation(left_result, right_result, symbol_vector[i])};
        ans.insert(ans.begin(), new_res.begin(), new_res.end());

    }
    eraseDuplicate(ans);
    return ans;
}

int main()
{
    string line{getInput()};
    vector<int> number_vector;
    vector<char> symbol_vector;
    vector<int> ans;
    processInput(number_vector, symbol_vector, line);

    vector<int> diff_possibility{sandwitchingCount(0, number_vector.size() - 1, number_vector, symbol_vector)};    

    return 0;
}