#include <iostream>
#include <vector>
#include <unordered_map>

/*
================================================================================
QUESTION STATEMENT: The Two Sum Problem

Given an array of integers `nums` and an integer `target`, return the indices 
of the two numbers such that they add up to `target`.

Constraints:
- You may assume that each input has exactly one solution.
- You may not use the same element twice.
- You can return the answer in any order.
- Your algorithm should run in O(n) time complexity.
================================================================================
*/

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;

    for (int i = 0; i < nums.size(); i ++) {
        int complement = target - nums[i];

        // checks if it's in seen
        if (seen.find(complement) != seen.end()) {
            return {seen[complement], i};
        }

        seen[nums[i]] = i;
    }
    
    return {}; // Fallback return
}

// ==========================================
// Test Cases
// ==========================================
void runTest(std::vector<int> nums, int target, std::vector<int> expected) {
    std::vector<int> result = twoSum(nums, target);
    
    std::cout << "Target: " << target << " | Array: [";
    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";

    if (result.size() == 2) {
        std::cout << "Result:   [" << result[0] << ", " << result[1] << "]\n";
    } else {
        std::cout << "Result:   [Not Found]\n";
    }

    std::cout << "Expected: [" << expected[0] << ", " << expected[1] << "]\n";
    std::cout << (result == expected ? "✅ PASS" : "❌ FAIL") << "\n\n";
}

int main() {
    // Test Case 1: Standard case (numbers at the beginning)
    runTest({2, 7, 11, 15}, 9, {0, 1});

    // Test Case 2: Numbers in the middle/end
    runTest({3, 2, 4}, 6, {1, 2});

    // Test Case 3: Duplicate numbers that form the target
    runTest({3, 3}, 6, {0, 1});

    // Test Case 4: Negative numbers and larger gaps
    runTest({-1, -2, -3, -4, -5}, -8, {2, 4});

    return 0;
}