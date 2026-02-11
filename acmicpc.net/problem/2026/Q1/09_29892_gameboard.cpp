/******************************************************************************

https://www.acmicpc.net/problem/29892
algo:dp
algo:slide window
algo:prefix sum

=>  tính prefix sum theo trục tâm của từng line
nên khi tính của từng line đến tâm hình vuông thì chỉ cần tính tâm của từng line đến tâm hình vuông

=> khoảng cách các điểm trên line đến tâm hình vuông 
    = prefix sum các điểm đến tâm line + tổng các điểm * khoảng cách line đến tâm hình vuông
=> khoảng cách của tâm line -> tâm hình vuông  = ?

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>

using namespace std;
int N,M,K;
struct Node{
    int s1,s2,c1,c2;
};
vector<Node> slide(string& cols,const int& k){
    //cout<<"count:"<<cols<<" k:"<<k<<endl;
    vector<Node> res(cols.length(), {0,0,0,0});
    int cl1=0,cl2=0,cr1=0,cr2=0;//count left 1,2 count right 1, 2
    int sum1=0,sum2=0;//sum label 1, sum label2
    int mid = k/2;//tâm
    const int maxD = k/2;//khoảng cách điểm ngoài cùng đến tâm
    
    //khởi tạo 
    for(int i = 0; i < mid;++i){
        
        if(cols[i] == '1'){
            ++cl1;
        }else if(cols[i] == '2'){
            ++cl2;
        }
        sum1+=cl1;
        sum2+=cl2;
    }
    for(int i = k-1; i > mid; i--){
        
        if(cols[i] == '1'){
            ++cr1;
        }else if(cols[i] == '2'){
            ++cr2;
        }
        sum1+=cr1;
        sum2+=cr2;
    }
    
    
    res[mid] = {sum1,sum2,cl1+cr1,cl2+cr2};
    //cout<<"count:sum:"<<sum1<<" "<<sum2<<endl;
    int f = 0;
    //slide window và cập nhật sum 1, 2 đến tâm
    for(int l = k; l < cols.length(); ++l){
        //remove f a1,a2
        if(cols[f] == '1'){
            sum1 -= maxD;
            --cl1;
        }else if(cols[f] =='2'){
            sum2 -= maxD;
            --cl2;
        }
        //add mid to a1,a2
        if(cols[mid] == '1'){
            ++cl1;
        }else if(cols[mid]=='2'){
            ++cl2;
        }
        sum1+=cl1;
        sum2+=cl2;
        
        sum1-= cr1;
        sum2-= cr2;
        //remove mid+1 from b1,b2
        if(cols[mid+1] == '1'){
            --cr1;
        }else if(cols[mid+1] == '2'){
            --cr2;
        }
        
        //add l to cr1,cr2
        if(cols[l]=='1'){
            ++cr1;
            sum1+=maxD;
        }else if(cols[l] == '2'){
            ++cr2;
            sum2+=maxD;
        }
        ++f;
        ++mid;
        res[mid] = {sum1,sum2,cl1+cr1,cl2+cr2};
        // cout<<"count:sum:"<<sum1<<" "<<sum2<<endl;
        
    }
    //cout<<"count:"<<res.size()<<endl;
    return res;
}
int solve(vector<string>& grids, int K){
    int res = INT_MAX;
    int R = grids.size()-K/2;
    int C = grids[0].length() - K/2;
    vector<vector<Node>> prefix;//store prefix by row
    for(int i = 0; i < grids.size();++i){
        auto tmp = slide(grids[i],K);
        prefix.push_back(tmp);
        //cout<<"prefix:"<<prefix[i].size()<<endl;
    }
    for(int r = K/2; r < R; ++r){
        for(int c = K/2; c < C; ++c){
            //cal distance row to cell r,c
            int sum1=0, sum2=0;
            for(int i = r - K/2; i <= r+K/2;++i){
                sum1+=prefix[i][c].s1  + abs(r-i)*prefix[i][c].c1 + (grids[i][c] == '1'? abs (r-i) : 0);
                sum2+=prefix[i][c].s2 + abs(r-i)*prefix[i][c].c2 + (grids[i][c] == '2'? abs (r-i) : 0);
            }
            //cout<<"sum:"<<sum1<<" "<<sum2<<endl;
            res = min(res, abs(sum1-sum2));
        }
    }
    
    return res;
}
int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>N>>M>>K;
	vector<string> grids(N);
	for(int i = 0; i < N; ++i){
	    cin>>grids[i];
	   // cout<<grids[i]<<endl;
	}
	cout<<solve(grids,K);
	return 0;
}