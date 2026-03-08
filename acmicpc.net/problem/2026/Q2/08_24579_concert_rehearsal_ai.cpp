#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

void solve() {
    ll n, p, k;
    if (!(cin >> n >> p >> k)) return;

    vector<ll> d(n);
    ll sum_d = 0;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        sum_d += d[i];
    }

    // 1. Tiền xử lý số vòng cố định mỗi ngày
    ll fixed_cycles = p / sum_d;
    ll rem_p = p % sum_d;

    // 2. Mảng cộng dồn nhân đôi để xử lý vòng tròn (pref[0] = 0)
    vector<ll> pref(2 * n + 1, 0);
    for (int i = 0; i < 2 * n; i++) {
        pref[i + 1] = pref[i] + d[i % n];
    }

    // next_start[i]: vị trí bắt đầu ngày hôm sau nếu hôm nay bắt đầu tại i
    // cycles_earned[i]: số vòng hoàn thành thêm được trong ngày đó
    vector<int> next_start(n);
    vector<ll> cycles_earned(n);

    for (int i = 0; i < n; i++) {
        // Tìm vị trí xa nhất có thể đi được với rem_p
        // pref[j] - pref[i] <= rem_p  => pref[j] <= rem_p + pref[i]
        auto it = upper_bound(pref.begin() + i, pref.end(), rem_p + pref[i]);
        int j = distance(pref.begin(), it) - 1;

        int num_acts = j - i;
        next_start[i] = (i + num_acts) % n;
        cycles_earned[i] = fixed_cycles + (i + num_acts) / n;
    }

    // 3. Tìm chu kỳ (Cycle Detection)
    vector<ll> visited_day(n, -1);
    vector<ll> total_at_day(n, -1);

    ll curr_pos = 0;
    ll total_cycles = 0;
    bool jumped = false;

    for (ll day = 0; day < k; day++) {
        // Nếu thấy vị trí này đã từng bắt đầu một ngày trước đó -> Nhảy chu kỳ
        if (!jumped && visited_day[curr_pos] != -1) {
            ll prev_day = visited_day[curr_pos];
            ll prev_total = total_at_day[curr_pos];

            ll day_diff = day - prev_day;
            ll cycle_diff = total_cycles - prev_total;

            ll num_jumps = (k - 1 - day) / day_diff;
            day += num_jumps * day_diff;
            total_cycles += num_jumps * cycle_diff;
            jumped = true; // Chỉ nhảy một lần duy nhất
        }

        if (!jumped) {
            visited_day[curr_pos] = day;
            total_at_day[curr_pos] = total_cycles;
        }

        total_cycles += cycles_earned[curr_pos];
        curr_pos = next_start[curr_pos];
    }

    cout << total_cycles << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}