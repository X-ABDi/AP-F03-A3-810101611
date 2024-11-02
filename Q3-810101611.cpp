#include <climits>
#include <iostream>
#include <vector>

using namespace std;

vector<int> getInput ()
{
    int faculty_number{0};
    cin >> faculty_number;
    vector<int> each_faculty_student(faculty_number);
    while (faculty_number > 0)
    {
        cin >> each_faculty_student[faculty_number - 1];
        faculty_number -= 1;
    }    
    return each_faculty_student;
}

int sweetCount (vector<int>& capacities, vector<int> &sweet_count, int index = 0)
{
    if(index == capacities.size() - 1)
    {
        return 0;
    }
    else if(index >= capacities.size())
    {
        return INT_MAX - abs(capacities[index] - capacities[index - 2]);
    }

    int one_step{sweetCount(capacities, sweet_count, index + 1)};
    int two_step{sweetCount(capacities, sweet_count, index + 2)};

    if (one_step + abs(capacities[index] - capacities[index + 1]) > two_step + abs(capacities[index] - capacities[index+2]))
    {
        return two_step + abs(capacities[index] - capacities[index+2]);
    }
    return one_step + abs(capacities[index] - capacities[index + 1]);
}

int main ()
{
    vector<int> capacities {getInput()};
    vector<int> sweet_count;
    int least_sweet{sweetCount(capacities, sweet_count)};
    cout << least_sweet << endl;
}