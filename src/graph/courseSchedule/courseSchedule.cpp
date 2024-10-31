/*
207. Course Schedule
Solved
Medium
Topics
Companies
Hint

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

Return true if you can finish all courses. Otherwise, return false.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

 

Constraints:

    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    All the pairs prerequisites[i] are unique.


*/

#include <vector>
#include <unordered_set>
#include <queue>
#include <iostream>

#include <utils/printHelper.h>

using namespace std;
using namespace utils;

class SolutionNaive {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        const int maxCourses = 2000;
        // this problem tests whether Kahn's Algorithm works for a graph of courses as nodes with prequesites as dependencies.
        // We need to first find a list of nodes with no prequisites.
        unordered_set<int> no_prerequisites;
        // initialize the set with all courses, and remove the ones with prerequisites.
        for (int i = 0; i < numCourses; ++i)
        {
            no_prerequisites.insert(i);
        }
        // also, keep track of the which nodes each node depends on, and for any given node, what nodes depend on it
        unordered_set<int> reverse_dependencies[maxCourses];
        unordered_set<int> dependencies[maxCourses];
        for (auto prerequisite : prerequisites)
        {
            if (no_prerequisites.contains(prerequisite[0]))
                no_prerequisites.erase(prerequisite[0]);
            dependencies[prerequisite[0]].insert(prerequisite[1]);
            reverse_dependencies[prerequisite[1]].insert(prerequisite[0]);
        }

        // finally, process our dependency graph in order of dependencies, starting with non-dependent nodes
        // remove each dependency from the graph in order.
        // if this graph isn't empty by the time we process all nodes, return that it is not a valid schedule. 
        
        while (!no_prerequisites.empty())
        {
            // process the next leaf node in the graph
            int current = *(no_prerequisites.begin());
            
            // process all nodes that are dependent on this node.
            for (auto dependent : reverse_dependencies[current])
            {
                dependencies[dependent].erase(current);

                // if this dependency has no other dependencies, process it next as a leaf node.
                if (dependencies[dependent].empty())
                {
                    no_prerequisites.insert(dependent);
                }
            }
            
            no_prerequisites.erase(current);
        }

        bool allDependenciesEmpty = true;
        for (auto dependencySet : dependencies)
        {
            allDependenciesEmpty &= dependencySet.empty();
        }

        return allDependenciesEmpty;
    }
};

class SolutionEfficient {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // We can still use Kahn's algorithm, just using more efficient data structures for access, insertion, removal and keeping track of leaf nodes.
        // the "O(1)" insertion, access and removal from hashsets lead to an order of magnitde slower time for all the comparisons and updates we need to make.
        // use flat arrays instead for all data access.

        // we can represent a leaf node by keeping track of the degree of all nodes in our graph, and keep track of connectivity using a 2D array, given that we only need to worry about 2000 elements max, requiring only 16MB of memory to store the entire graph, and 8KB to keep track of their degree.
        vector<vector<int>> graph(numCourses);
        vector<int> degree(numCourses, 0);

        // process the input prerequisite list, creating our graph and node degree in memory.
        for (auto prerequisite : prerequisites)
        {
            // we want our graph to represent which nodes depend on the current node, providing ease of access for our algorithm.
            graph[prerequisite[1]].push_back(prerequisite[0]);
            degree[prerequisite[0]]++;
        }

        queue<int> leafNodes;
        // prepopulate our queue of nodes to visit with the current 
        for (int i = 0; i < numCourses; ++i)
        {
            if (degree[i] == 0)
            {
                leafNodes.push(i);
            }
        }

        // we can also avoid another O(n) traversal to keep track of if we visited all nodes in the graph.
        int nodesVisited = 0;
        // finally, traverse the tree in order of dependency -> dependent
        while (!leafNodes.empty())
        {
            nodesVisited++;
            int current = leafNodes.front();
            for (auto dependent : graph[current])
            {
                int& curDegree = --degree[dependent]; // decrement before accessing.
                if (curDegree == 0)
                {
                    leafNodes.push(dependent);
                }
            }
            leafNodes.pop();
        }

        // we have a valid schedule if we can traverse all nodes by tracing through their dependencies.
        return nodesVisited == numCourses;
    }
};

class Solution : public SolutionEfficient {};

int main()
{
    {
        vector<vector<int>> input = {{1,0}};
        int numCourses = 2;
        bool expected = true;
        
        Solution s;
        auto result = s.canFinish(numCourses, input);
        cout << "Input: [";
        for (auto vector : input)
        {
            cout << printVector(vector) << ", ";
        }
        cout << "] " << numCourses << endl;
        cout << "Output: " << result << " Expected: " << expected << endl;
    }
    {
        vector<vector<int>> input = {{1,0}, {0,1}};
        int numCourses = 2;
        bool expected = false;
        
        Solution s;
        auto result = s.canFinish(numCourses, input);
        cout << "Input: [";
        for (auto vector : input)
        {
            cout << printVector(vector) << ", ";
        }
        cout << "] " << numCourses << endl;
        cout << "Output: " << result << " Expected: " << expected << endl;
    }
}