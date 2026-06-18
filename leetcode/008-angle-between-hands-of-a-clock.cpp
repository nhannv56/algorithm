/***
https://leetcode.com/problems/angle-between-hands-of-a-clock/description/?envType=daily-question&envId=2026-06-18
algo: math
  **/
class Solution {
public:
    double angleClock(int hour, int minutes) {
        // hour*= 1e5;
        // minutes*=1e5;
        int  mDegree = minutes*60; // part 60*60
        int hDegree = (hour*5*60+minutes*10/2)%(3600);
        // cout<<mDegree<<" "<<hDegree<<endl;
        int result = abs(mDegree-hDegree);
        // cout<<"result:"<<result<<endl;
        double res = result;
        // res=res/1e6;
        res/=10;
        if(res > 180){
            res=360-res;
        }
        return res;
    }
};
