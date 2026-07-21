/**
You are given a binary string s of length n, where:

'1' represents an active section.
'0' represents an inactive section.
You can perform at most one trade to maximize the number of active sections in s. In a trade, you:

Convert a contiguous block of '1's that is surrounded by '0's to all '0's.
Afterward, convert a contiguous block of '0's that is surrounded by '1's to all '1's.
Return the maximum number of active sections in s after making the optimal trade.

Note: Treat s as if it is augmented with a '1' at both ends, forming t = '1' + s + '1'. The augmented '1's do not contribute to the final count.
  **/
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        vector<int> counts;//count  liên tiếp
        counts.push_back(-1);
        char pre ='1';
        s.push_back('1');
        s="1"+s;
        int sum = 1;
        // cout<<"s:"<<s<<endl;
      //đếm số lượng 0,1 liên tiếp
        for(int i = 1; i < s.length(); ++i){
            // cout<<"pre:"<<pre<<" "<<s[i]<<endl;
            if(s[i]==pre){
                if(s[i]=='0'){
                    ++counts[counts.size()-1];
                }else{
                    --counts[counts.size()-1];
                    ++sum;
                }
            }else{
                counts.push_back(s[i]=='0'?1:-1);
                if(s[i]=='1'){
                    ++sum;
                }
            }
            pre = s[i];
        }
        int res = 0;
        // cout<<"counts:"<<counts.size()<<endl;
      //kết quả -2 và thêm chuối 010 có thể
        if(counts.size()==1){
            res= sum-2;
            // cout<<"sum:"<<sum<<endl;
        }else if(counts.size()==3){
            res = sum-2;
        }else if (counts.size()==5){
            res = s.length()-2;
        }else{
            for(int i = 3; i < counts.size(); i+=2){
                int cur = sum +abs(counts[i] + counts[i-2]);
                res = max(cur, res);
            }
            res-=2;
        }
        return res;
    }
};
