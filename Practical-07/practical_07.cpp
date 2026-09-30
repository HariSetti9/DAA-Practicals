#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> coins = {1, 3, 4};
    int amount = 6;
    vector<int> dp(amount + 1, INT_MAX), chosen(amount + 1, -1);
    dp[0] = 0;

    cout << "MAKING CHANGE USING DYNAMIC PROGRAMMING\n";
    cout << "Coins = {1, 3, 4}, Target amount = 6\n";
    cout << "dp[0] = 0; all other entries start as INF\n\n";
    cout << "STEP-BY-STEP CALCULATION\n";
    for (int x = 1; x <= amount; ++x) {
        cout << "\nAmount " << x << ":\n";
        for (int coin : coins) {
            cout << "  Coin " << coin << ": ";
            if (coin > x) { cout << "cannot use (coin > amount)\n"; continue; }
            int candidate = dp[x - coin] == INT_MAX
                                ? INT_MAX : dp[x - coin] + 1;
            cout << "dp[" << x-coin << "] + 1 = "
                 << dp[x-coin] << " + 1 = " << candidate;
            if (candidate < dp[x]) {
                dp[x] = candidate; chosen[x] = coin;
                cout << " -> update dp[" << x << "] = " << candidate
                     << ", coin[" << x << "] = " << coin;
            } else cout << " -> no change";
            cout << '\n';
        }
        cout << "  Final: dp[" << x << "] = " << dp[x]
             << ", chosen coin = " << chosen[x] << '\n';
    }

    cout << "\nDP TABLE (minimum coins)\nAmount      ";
    for (int x=0;x<=amount;++x) cout << setw(4) << x;
    cout << "\ndp[x]       ";
    for (int x=0;x<=amount;++x) cout << setw(4) << dp[x];
    cout << "\n\nCHOICE TABLE (last coin selected)\nAmount      ";
    for (int x=0;x<=amount;++x) cout << setw(4) << x;
    cout << "\ncoin[x]     ";
    for (int x=0;x<=amount;++x) {
        if(chosen[x]<0) cout<<setw(4)<<"-";
        else cout<<setw(4)<<chosen[x];
    }

    cout << "\n\nRECONSTRUCTION\n";
    int remaining=amount, step=1;
    while(remaining>0){
        int coin=chosen[remaining];
        cout << "Step " << step++ << ": amount " << remaining
             << " uses coin " << coin << "; remaining = " << remaining
             << " - " << coin << " = " << remaining-coin << '\n';
        remaining-=coin;
    }
    cout << "Selected coins: {3, 3}\nTotal value: 3 + 3 = 6\nMinimum number of coins: " << dp[amount] << '\n';
    cout << "Time complexity: Theta(A*m)\nSpace complexity: Theta(A)\n";
}