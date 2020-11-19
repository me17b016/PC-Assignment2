# PC-Assignment2
```
Consider a 2D grid of data stored as a Matrix of doubles.The elements are updated iteratively until 
some condition is satisfied. The element’s new value is the average of the element’s current value 
and the current values of its four neighbors.Every element in the matrix is similarly updated. 
At the end of each iteration, the maximum value change is determined (the difference between its old 
value and its current computed value). That maximum of all these differences is computed across the 
entire matrix. If the maximum difference for a given iteration falls below a given threshold, the 
calculation ends,else, the next iteration starts.
```
# Plagiarism Self Declaration:
```
I, Raj Garg , certify that this assignment is my own work,
and entirely based on my personal study and understanding. I have not copied in part or
whole or otherwise plagiarised the work of other students and/or persons.
```
## Compile
`g++ -std=c++14 -o obj ME17B016.cpp -fopenmp`
## run
`./obj.exe [N length of array] [T tolerance]`

`./obj.exe 200 .01`
## Output
```
Time take is 9937 us
Number of Iterations: 75
Number of threads 1
```
## Graph Time vs N
![Analysis](https://github.com/me17b016/PC-Assignment2/blob/main/line-graph.png)

## Analysis
|N         | TIME (μs)     | ITERATION |
| -------- | ------------- | --------- |
|1         |   1992        |   5       |
|2         |   9872        |   75      |
|10        |   8388        |   61      | 
|20        |   9943        |   64      |
|50        |   12964       |   66      |
|100       |   15964       |   65      |
|200       |   27923       |   70      |
|500       |   119784      |   69      |
|800       |   243995      |   69      |
|1000      |   383468      |   69      |
|1200      |   540116      |   69      |
|1500      |   877911      |   71      |
|2000      |   1563691     |   72      |
