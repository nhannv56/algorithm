/**
algo: matrix exp
**/
typedef long long ll;

vector<vector<ll>> MultipleMatrix(const vector<vector<ll>> & A,const vector<vector<ll>> & B,const ll& P){
    vector<vector<ll>> m(A.size(), vector<ll>(B[0].size(),0));
    for(int r = 0; r < m.size(); ++r){
        for(int c = 0; c < m[0].size(); ++c){
            for(int j = 0; j < A[0].size(); ++j){
                m[r][c] = (m[r][c]+(A[r][j]*B[j][c])%P) %P;
            }
        }
    }
    return m;
}
vector<vector<ll>> PowerMaxtrix( vector<vector<ll>> A, ll exp, ll& P){
    int K = A.size();
    vector<vector<ll>> Result(K, vector<ll>(K, 0));
    for(int i = 0; i < K; ++i) Result[i][i] = 1;
    
    while (exp > 0) {
        if (exp & 1) {
            Result = MultipleMatrix(Result, A, P);
        }
        A = MultipleMatrix(A, A, P);
        exp >>= 1; // exp = exp / 2
    }
    return Result;
}
class Solution {
public:
    long long MOD = 1e9+7;
    /***
    thuật toán dp, với độ dài x từ 2->n với xu hướng tăng/giảm thì hiện tại có bao nhiêu chuỗi
    có bao nhiêu chuỗi có thể sinh ra tiếp theo kết thúc bằng i có độ dài x+1
    Tính với độ dài x kết thúc bởi phần tử giá trị i có bao nhiêu cách vs 2 xu hướng
    **/
    
    int zigZagArrays(int n, int l, int r) {
        int k = r-l+1;
        long long res = 0;
        vector<vector<long long>> r2(k*2,vector<long long>(1,0 ));
        for(int i = 1; i <= k; ++i){
            r2[i-1][0]= (long long)(k-i);// với n = 2 xu hướng trước đó là giảm kết thúc bởi i thì có bao nhiêu cách
            r2[i+k-1][0]=(long long)(i-1); // với n = 2 xu hướng trước đó là tăng kết thúc bởi i thì có bao nhiêu cách
        }
        // for(auto it : r2){
        //     for(auto i : it){
        //         cout<<i<<" ";
        //     }cout<<endl;
        // }
        vector<vector<ll>> T(k*2, vector<long long>(k*2, 0));
        for(int i = 0; i < k*2;++i){
            // T[i][i]=1;
            if(i < k){
                for(int j = i+k+1; j < k*2;++j){
                    T[i][j]=1;
                }
            }else{
                for(int j = 0; j < i-k;++j){
                    T[i][j]=1;
                }
            }
        }
        // for(auto it : T){
        //     for(auto t : it){
        //         cout<<t<<" ";
        //     }cout<<endl;
        // }
        auto resM = r2;
        if(n>2){
            auto Tnmk = PowerMaxtrix(T,n-2, MOD);
            resM = MultipleMatrix(Tnmk,r2,MOD);
            // for(auto tp : Tnmk){
            //     for(auto t : tp){
            //         cout<<t<<" ";
            //     }cout<<endl;
            // }
        }
        for(auto tp : resM){
            for(auto t : tp){
                // cout<<"t:"<<t<<endl;
                res=(res+t)%MOD;
            }
        }
        return res;

    }
};
