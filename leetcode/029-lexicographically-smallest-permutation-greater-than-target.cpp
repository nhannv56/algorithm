/**
algo: backtrack
tìm string nhỏ nhất cấu thành từ a và lớn hơn string b
  **/
class Solution {
public:
    vector<int> cnt = vector<int>(26, 0);
    string res;
    bool cal(int pos, int n, const string& target, bool greater = false) {
        // cout<<"pos:"<<pos<<endl;
        if (greater) {
            for (int i = 0; i < 26; ++i) {
                while (cnt[i] > 0) {
                    res[pos] = ('a' + i);
                    ++pos;
                    --cnt[i];
                }
            }
            return true;
        }
        if (pos >= n) {
            return false;
        }
        if (cnt[target[pos] - 'a'] > 0) {
            --cnt[target[pos] - 'a'];
            res[pos] = target[pos];
            // cout<<"pos:"<<pos<<" "<<target[pos]<<endl;
            auto found = cal(pos + 1, n, target, false);
            ++cnt[target[pos] - 'a'];
            if (found) {
                return true;
            }
        }

        for (int i = target[pos] - 'a' + 1; i < 26; ++i) {
            if (cnt[i] > 0) {
                res[pos] = 'a' + i;
                // cout<<"pos:"<<pos<<" "<<res[pos]<<endl;
                --cnt[i];
                auto found = cal(pos + 1, n, target, true);
                ++cnt[i];
                if (found) {
                    return true;
                }
                break;
            }
        }

        return false;
    }
    string lexGreaterPermutation(string s, string target) {

        for (int i = 0; i < s.length(); ++i) {
            cnt[s[i] - 'a']++;
        }
        res = s;
        bool found = false;

        found = cal(0, (int)s.length(), target, found);
        if (found) {
            return res;
        }
        return "";
    }
};
