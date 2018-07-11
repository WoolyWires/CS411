// build.cpp
// Aisha Peters
// 19 November 2017
// For CS 411 Assignment 5
//
// Uses dynamic programming to determine the greatest toll attainable from given bridges.

#include "build.h"
using std::vector;
using std::max;
using std::sort;

// Checks if Bridge B is greater than Bridge A in sorted bridges
bool valid(const Bridge & A, const Bridge & B)
{
    return (B[0] > A[0] && B[1] > A[1]);
}

// Comparison to sort bridges by west bank city in decreasing order
bool compare(const Bridge & A, const Bridge & B)
{
    return A[0] > B[0];
}

// Recursively looks through valid bridge combinations and returns greatest toll sum
int solve(int place, const vector<Bridge> & bridges, int n, vector<vector<int>> & table)
{
    // Base case: no more bridges or already solved
    if(n < 0)
        return 0;
    else if(table[place][n] != -1)
        return table[place][n];

    // Check if valid bridge combination
    // If not, check next combination
    if(!valid(bridges[place], bridges[n]))
    {
        table[place][n] = solve(place, bridges, n-1, table);
        return table[place][n];
    }
    // If so, find max sum with and without new bridge
    else
    {
        table[place][n] = max(bridges[n][2] + solve(n, bridges, n-1, table), solve(place, bridges, n-1, table));
        return table[place][n];
    }
}

// Calls solve to determine greatest attainable bridge toll
int build(int w, int e, const vector<Bridge> & bridges)
{
    int n = bridges.size();

    // Create table for solved subproblems, +1 for dummy bridge
    vector<vector<int>> table(n+1, vector<int>(n+1,-1));

    // Create a sorted copy of bridges
    vector<Bridge> bridges_sort(bridges);
    sort(bridges_sort.begin(), bridges_sort.end(), compare);

    // Add dummy bridge for starting place in recurrence
    Bridge dummy = {-1,-1,0};
    bridges_sort.push_back(dummy);

    // Find greatest toll
    return solve(n, bridges_sort, n-1, table);
}
