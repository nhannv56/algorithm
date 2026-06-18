//https://leetcode.com/contest/weekly-contest-317/problems/height-of-binary-tree-after-subtree-removal-queries/
// tree dfs 
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class DepthOfVal{
public:
    int val;// giá trị của phần tử
    int deep; //chiều sâu phần tử tới lá
    
};
bool copmare (DepthOfVal i,DepthOfVal j) {
        return (i.deep > j.deep);
    }
class Solution {
public:
    vector<vector<DepthOfVal>> deeps= vector<vector<DepthOfVal>>(100001); //lưu các phần tử cùng chiều sâu
    //vector<int> dp = vector<int>(100001); //chiều sâu từ lá đến cur
    vector<int> ptoCur = vector<int>(100001);//chiều sâu từ cha đến cur
    //int maxDeep = 0;
    int initializeDeeps(TreeNode* root, int cur = 0){
        if(root != nullptr){
            
            
            ptoCur[root->val] = cur;
            int deepLeft = initializeDeeps(root->left,cur+1) + 1;
            int deepRight = initializeDeeps(root->right, cur+1) + 1;
            //dp[root->val] = deepLeft < deepRight ?  deepRight : deepLeft;
            
            
            DepthOfVal cc;
            cc.val = root->val;
            cc.deep = deepLeft < deepRight ?  deepRight : deepLeft;
            deeps[cur].push_back(cc);
            
            //cout<<"setRes:"<<root->val<<","<<dp[root->val]<<endl;
            return cc.deep;
        }else{
            return -1;
        }
    }
    int getDeep(int val, TreeNode* root, int cur=0){
        if(root!= nullptr){
            if(root->val == val){
                return cur;
            }else{
                int leftD= getDeep(val, root->left,cur+1);
                if(leftD != -1){
                    return leftD;
                }else{
                    return getDeep(val, root->right,cur+1);
                }
            }
        }else{
            return -1;
        }
    }
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        vector<int> result;
        initializeDeeps(root);
        for(int i = 0; i < 100001;i++){
            if(deeps.size() > 0){
                sort(deeps[i].begin(), deeps[i].end(),copmare);
            }else{
                break;
            }
        }
        for(int q : queries){
            //int deep = getDeep(q, root, 0);
            int deep = ptoCur[q];
            //cout<<q<<" deep:"<<deep<<endl;
            int res = -1;
            //cout<<"size:"<<deeps[deep].size()<<endl;
            for(int i = 0; i < deeps[deep].size();i++){
                if(deeps[deep][i].val != q){
                    res = deeps[deep][i].deep;
                    break;
                }else{
                    if(deeps[deep].size()>1){
                        res = deeps[deep][1].deep;
                        break;
                    }
                }
            }
            //cout<<q<<" res:"<<res<<endl;
            result.push_back(deep+res);
        }
        return result;
    }
};
