// contigsum.hpp
// Aisha Peters
// 12 October 2017
// For CS 411 Assignment 3 Exercise A

#ifndef CONTIGSUM_HPP_INCLUDED
#define CONTIGSUM_HPP_INCLUDED
#include <iterator>
#include <algorithm>
using std::max;

// Data structure for storing ABCD values of algorithm
// used by solve
struct seqValue {
    int A;
    int B;
    int C;
    int D;
};

// Function finds Greatest Contiguous Sum (GCS) of a sequence using divide and conquer
// used by contigSum
template<typename RAIter>
seqValue solve(RAIter first, RAIter last)
{
    // Initialize values
    seqValue answ;
    answ.A = 0;
    answ.B = 0;
    answ.C = 0;
    answ.D = 0;

    // Base case
    if(first == last)
    {
        return answ;
    }

    // Single element check
    auto n = std::distance(first, last);
    if(n == 1)
    {
        answ.A = max(*first, 0);
        answ.B = *first;
        answ.C = *first;
        answ.D = *first;
        return answ;
    }

    // Find middle of the sequence
    int m = n/2;
	auto mid = first;
	std::advance(mid, m);

	// Find ABCD values for left and right side of sequence
	seqValue left = solve(first, mid);
    seqValue right = solve(mid, last);

	// Find GCS of full sequence (A)
    answ.A = max(max(left.A, right.A), left.C+right.B);

    // Find GCS including first value (B)
    answ.B = max(left.B, left.D+right.B);

    // Find GCS including last value (C)
    answ.C = max(right.C, right.D+left.C);

    // Find sequence sum (D)
    answ.D = left.D+right.D;

    return(answ);
}

// Calls function solve on given iterators and returns GCS
template<typename RAIter>
int contigSum(RAIter first, RAIter last)
{
    seqValue sol = solve(first, last);
    return(sol.A);
}

#endif // CONTIGSUM_HPP_INCLUDED
