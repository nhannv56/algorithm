/**
algo: disjoin set, unionfind
algo: sliding window

You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.

You are also given an integer array nums of length n sorted in non-decreasing order, and an integer maxDiff.

An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).

You are also given a 2D integer array queries. For each queries[i] = [ui, vi], determine whether there exists a path between nodes ui and vi.

Return a boolean array answer, where answer[i] is true if there exists a path between ui and vi in the ith query and false otherwise.
**/
class UnionFind {
    vector<int> parent;

public:
    UnionFind(int size) {

        parent.resize(size);

        // Initialize the parent array with each
        // element as its own representative
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    // Find the representative (root) of the
    // set that includes element i
    int find(int i) {

        // If i itself is root or representative
        if (parent[i] == i) {
            return i;
        }

        // Else recursively find the representative
        // of the parent
        return parent[i] = find(parent[i]);
    }

    // Unite (merge) the set that includes element
    // i and the set that includes element j
    void unite(int i, int j) {

        // Representative of set containing i
        int irep = find(i);

        // Representative of set containing j
        int jrep = find(j);

        // Make the representative of i's set
        // be the representative of j's set
        parent[irep] = jrep;
    }
};
class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                      vector<vector<int>>& queries) {
        int l = 0, r = 0;
        UnionFind dj(n+1);
        //slide window với condition là diff min max mảng đã sorted
        while (r < n) {
            // cout<<"l1:"<<r<<endl;
            while (r < n && nums[r] - nums[l] <= maxDiff) {
                dj.unite(r, l);                
                ++r;
            }
            while (r < n && nums[r] - nums[l] > maxDiff) {
                l++;
            }
        }
        vector<bool> res(queries.size(), false);
        for (int i = 0; i < queries.size(); ++i) {
            auto pi = dj.find(queries[i][0]);
            auto pj = dj.find(queries[i][1]);
            if (pi == pj) {
                res[i] = true;
            }
        }
        return res;
    }
};
