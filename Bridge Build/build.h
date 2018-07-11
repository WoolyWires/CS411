// build.cpp
// Aisha Peters
// 19 November 2017
// For CS 411 Assignment 5
//
// Header file for build.cpp

#ifndef BUILD_H_INCLUDED
#define BUILD_H_INCLUDED
#include <iostream>
#include <algorithm>
#include <vector>

using Bridge = std::vector<int>; // [west, east, toll]

// Calls solve to determine greatest attainable bridge toll
int build(int w, int e, const std::vector<Bridge> & bridges);


#endif // BUILD_H_INCLUDED
