/**
algo: backtrack
algo: string
algo: palindrome
cho 2 chuỗi a,b, từ các ký tự chuỗi a, xây chuỗi palindrome nhỏ nhất lớn hơn b
  **/
class Solution {
public:
    vector<int> cnt = vector<int>(26, 0);
    string res;
    int len = 0;
    bool cal(int pos, int n, const string& target, bool greater = false) {
        // khi đã có 1 phần tử lớn hơn ở nửa trái
        if (greater) {
            for (int i = 0; i < 26; ++i) {
                while (cnt[i] >= 2) {
                    res[pos] = ('a' + i);
                    res[len - 1 - pos] = ('a' + i);
                    ++pos;
                    cnt[i] -= 2;
                }
            }
            return true;
        }
        //xây xong string, kiểm tra chuỗi thỏa mãn không
        if (pos >= (len) / 2) {
            // cout<<"res:"<<res<<endl;
            return res > target;
        }
        // xây chuỗi
        if (cnt[target[pos] - 'a'] >= 2) {
            cnt[target[pos] - 'a'] -= 2;
            res[pos] = target[pos];
            res[len - 1 - pos] = target[pos];
            // cout<<"pos:"<<pos<<" "<<target[pos]<<endl;
            auto found = cal(pos + 1, n, target, false);
            cnt[target[pos] - 'a'] += 2;
            if (found) {
                return true;
            }
        }
        //xây chuỗi vs trường hợp lớn hơn
        for (int i = target[pos] - 'a' + 1; i < 26; ++i) {
            if (cnt[i] >= 2) {
                res[pos] = 'a' + i;
                res[len - 1 - pos] = 'a' + i;
                // cout<<"pos:"<<pos<<" "<<res[pos]<<endl;
                cnt[i] -= 2;
                auto found = cal(pos + 1, n, target, true);
                cnt[i] += 2;
                if (found) {
                    return true;
                }
                break;
            }
        }

        return false;
    }
    string lexPalindromicPermutation(string s, string target) {
        len = s.length();
        for (int i = 0; i < s.length(); ++i) {
            cnt[s[i] - 'a']++;
        }
        res = s;
        bool mid = false;
        //corner case
        if (len % 2 == 1) {//length lẻ, 
            for (auto i = 0; i < 26; ++i) {
                if (cnt[i] % 2 == 1) {
                    if (!mid) {
                        mid = true;
                        res[(len) / 2] = 'a' + i;//gán phần tử giữa
                        cnt[i]--;
                    } else {
                        return "";
                    }
                } else {
                }
            }
        } else {//len chẵn
            for (auto i = 0; i < 26; ++i) {
                if (cnt[i] % 2 == 1) {//tất cả đều phải chẵn
                    return "";
                }
            }
        }
        bool found = false;
        //kiểm tra từ 0 đến mid xây string
        found = cal(0, (int)(s.length() + 1) / 2, target, false);
        if (found) {
            return res;
        }
        return "";
    }
};
