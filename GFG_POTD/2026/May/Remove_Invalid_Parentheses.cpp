/*
Problem: Remove Invalid Parentheses
Link: https://www.geeksforgeeks.org/problems/remove-invalid-parentheses/1

Description:
Given a string s consisting of lowercase letters and parentheses '(' and ')'.
Remove the minimum number of invalid parentheses from s so that the resulting 
string becomes valid. Return all possible distinct valid strings in 
lexicographically sorted order.

Constraints:
1 <= |s| <= 20
s consists of lowercase English letters and parentheses '(' and ')'
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Helper function to check if a string has valid parentheses
    bool isValid(string s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count++;
            } else if (c == ')') {
                count--;
                // If count is negative, more ')' than '(' so far
                if (count < 0) return false;
            }
        }
        return count == 0;
    }

    vector<string> validParenthesis(string s) {
        vector<string> result;
        if (s.empty()) return {""};

        // BFS approach to find minimum removals
        queue<string> q;
        unordered_set<string> visited;

        q.push(s);
        visited.insert(s);
        bool foundAtThisLevel = false;

        while (!q.empty()) {
            int size = q.size();
            unordered_set<string> level_valid;

            for (int i = 0; i < size; i++) {
                string curr = q.front();
                q.pop();

                // If current string is valid, add to the level results
                if (isValid(curr)) {
                    level_valid.insert(curr);
                    foundAtThisLevel = true;
                }

                // If we haven't found a valid string yet, generate the next level
                if (!foundAtThisLevel) {
                    for (int j = 0; j < curr.length(); j++) {
                        // Only remove parentheses, not lowercase letters
                        if (curr[j] != '(' && curr[j] != ')') continue;

                        string next_s = curr.substr(0, j) + curr.substr(j + 1);
                        if (visited.find(next_s) == visited.end()) {
                            visited.insert(next_s);
                            q.push(next_s);
                        }
                    }
                }
            }

            // Once we find valid strings at the minimum removal level, we stop
            if (foundAtThisLevel) {
                for (const string& str : level_valid) {
                    result.push_back(str);
                }
                break;
            }
        }

        // If no valid strings found (other than potentially empty), return empty string
        if (result.empty()) return {""};

        // Sort lexicographically as per problem requirement
        sort(result.begin(), result.end());
        return result;
    }
};