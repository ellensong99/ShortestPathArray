# Shortest Path Array Description
Given an array of n distinct natural numbers A[1..n], each containing k digits, where the most significant digit is in {1..9}, the algorithm finds an optimal path from A[1] to A[n].
Suppose moving from A[i] to A[j] costs 2A[j] − A[i]. You may move from A[i] to A[j] if they differ in one digit, and you may only move from numbers in A to other numbers in A. 
A optimal path moves from A[1] to A[n] with lowest total cost.

# Example
## Sample Input
  - Line 1: n and k separated by one space, n is the legnth of array A and k is the number of digits for each integer.
  - Line 2: A[1], A[2], . . . , A[n], an array separated by one space.
```bash
64
1234 4321 3234 5274 3274 5074
```

## Sample Output
  - Line 1: C and L separated by one space, where C is the optimal cost and L is the number of vertices on the optimal path.
  - Line 2: p<sub>1</sub>, p<sub>2</sub>, . . . , p<sub>L</sub>, the optimal path separated by one space.
```bash
20696 5
1234 3234 3274 5274 5074
```
