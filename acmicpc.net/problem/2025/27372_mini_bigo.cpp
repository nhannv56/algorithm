/******************************************************************************

https://www.acmicpc.net/problem/27372
Implementation
Backtracking

*******************************************************************************/
#include <iostream>
#include<bits/stdc++.h>


using namespace std;

string calculate(const string & s,bool print = false){
    int mark[9]={0,}; //rows 0-2, cols 3-5, cross 6-7 -> total 8
    //'0 1 2'
    //'3 4 5'
    //'6 7 8'
    int r,c;
    string result= "";
    for(int i = 0; i < s.length();++i){
        //always update col and row
        char cur= '0';
        r = (s[i]-'0') / 3;
        c = (s[i] -'0') % 3;
        //row
        mark[r] |= 1<<c;
        //col
        if(mark[r] == 0b111){
            cur++;
        }
        mark[c+3] |= 1<<r;
        if(mark[c+3] == 0b111){
            cur++;
        }
        //both cross
        if(s[i]== '4'){
            mark[6] |= 1<<1;
            mark[7] |= 1<<1;
            if(mark[6] == 0b111){
                cur++;
            }
            if(mark[7] ==0b111){
                cur++;
            }
        }
        //1 cross
        if(s[i] == '0'||s[i] == '2' || s[i] == '8' || s[i] == '6'){
            if(c==r){
                mark[6] |= 1<<c;
                if(mark[6] == 0b111){
                    cur++;
                }
            }else{
                mark[7] |= 1<<c;
                if(mark[7] == 0b111){
                    cur++;
                }
            }
        }
        // if(print){
        //     cout<<"round:"<<s[i]<<endl;
        //     for(int j = 0; j <  8; j++){
        //         cout<<j<<" "<<std::bitset<3>(mark[j])<<endl;
        //     }
        // }
        result.push_back(cur);
    }
    return result;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    string org = "012345678";
    string out ="";
    unordered_map<string, vector<string>> data;
    do {
        out = calculate(org);
        data[out].push_back(org);
        //std::cout << out<<" " <<org << std::endl;
    } while (std::next_permutation(org.begin(), org.end()));
    int T =0;
    string seed ="";
    string cells[3];
    cin>>T;
    while(T > 0){
        cin>>seed;
        char line = '0';
        char ci[26]={0,}; //character to index;
        for(int i = 0; i < 3;i++){
            cin>>cells[i];
            // cout<<"line:"<<line+1<<endl;
            ci[cells[i][0]-'A'] = line;
            ci[cells[i][1]-'A'] = line+1;
            ci[cells[i][2]-'A'] = line+2;
            //cout<<"cell:"<<ci[cells[2]-'A']<<endl;
            line+=3;
        }
        //
        string seedNum ="";
        for(int i = 0; i < seed.size();++i){
            //cout<<"i:"<<i<<" "<<seed[i]<<" "<<ci[seed[i]-'A']<<endl;
            seedNum.push_back(ci[seed[i]-'A']);
        }
        //cout<<"seedNum:"<<seedNum<<endl;
        string res = calculate(seedNum, true);
        auto others = data[res];
        //cout<<"others:size:"<<others.size()<<endl;
        string firstS = seed;
        string cur ="";
        for(auto os : others){
            cur = "";
            // cout<<"os:"<<os<<endl;
            for(char c : os){//number to text
                // cout<<c<<endl;
                cur.push_back(cells[(c-'0')/3][(c-'0')%3]);
            }
            firstS = min(firstS, cur);
        }
        cout<<res<<" "<<firstS<<endl;
        T--;
    }
	return 0;
}