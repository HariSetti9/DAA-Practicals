#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string parenthesize(int i, int j, const vector<vector<int>>& split) {
    if (i == j) return "A" + to_string(i);
    int k = split[i][j];
    return "(" + parenthesize(i, k, split) + " x "
               + parenthesize(k + 1, j, split) + ")";
}

void printCostTable(const vector<vector<long long>>& cost, int n) {
    cout << "\nM TABLE (minimum scalar multiplications)\n";
    cout << left << setw(8) << "i\\j";
    for (int j = 1; j <= n; ++j) cout << setw(10) << j;
    cout << '\n';

    for (int i = 1; i <= n; ++i) {
        cout << left << setw(8) << i;
        for (int j = 1; j <= n; ++j) {
            if (j < i) cout << setw(10) << "-";
            else cout << setw(10) << cost[i][j];
        }
        cout << '\n';
    }
}

void printSplitTable(const vector<vector<int>>& split, int n) {
    cout << "\nK TABLE (best split position)\n";
    cout << left << setw(8) << "i\\j";
    for (int j = 1; j <= n; ++j) cout << setw(10) << j;
    cout << '\n';

    for (int i = 1; i <= n; ++i) {
        cout << left << setw(8) << i;
        for (int j = 1; j <= n; ++j) {
            if (j <= i) cout << setw(10) << "-";
            else cout << setw(10) << split[i][j];
        }
        cout << '\n';
    }
}

int main() {
    const vector<int> p = {4, 10, 3, 8};
    const int n = static_cast<int>(p.size()) - 1;

    vector<vector<long long>> cost(n + 1, vector<long long>(n + 1, 0));
    vector<vector<int>> split(n + 1, vector<int>(n + 1, 0));

    cout << "MATRIX CHAIN MULTIPLICATION USING DYNAMIC PROGRAMMING\n";
    cout << "-----------------------------------------------------\n";
    cout << "Dimension array p = {4, 10, 3, 8}\n\n";
    for (int i = 1; i <= n; ++i) {
        cout << "A" << i << " = " << p[i - 1] << " x " << p[i] << '\n';
    }

    cout << "\nSTEP-BY-STEP DP CALCULATION\n";
    for (int length = 2; length <= n; ++length) {
        cout << "\nChain length = " << length << '\n';
        for (int i = 1; i <= n - length + 1; ++i) {
            int j = i + length - 1;
            cost[i][j] = LLONG_MAX;
            cout << "\nFinding m[" << i << "][" << j << "] for A"
                 << i << "...A" << j << ":\n";

            for (int k = i; k < j; ++k) {
                long long leftCost = cost[i][k];
                long long rightCost = cost[k + 1][j];
                long long multiplyCost = 1LL * p[i - 1] * p[k] * p[j];
                long long total = leftCost + rightCost + multiplyCost;

                cout << "  k = " << k << ": m[" << i << "][" << k << "] + m["
                     << k + 1 << "][" << j << "] + p[" << i - 1 << "]*p["
                     << k << "]*p[" << j << "]\n";
                cout << "         = " << leftCost << " + " << rightCost << " + "
                     << p[i - 1] << "*" << p[k] << "*" << p[j] << '\n';
                cout << "         = " << leftCost << " + " << rightCost << " + "
                     << multiplyCost << " = " << total << '\n';

                if (total < cost[i][j]) {
                    cost[i][j] = total;
                    split[i][j] = k;
                    cout << "         -> New minimum; set m[" << i << "][" << j
                         << "] = " << total << " and k[" << i << "][" << j
                         << "] = " << k << '\n';
                } else {
                    cout << "         -> Not smaller than current minimum "
                         << cost[i][j] << '\n';
                }
            }
        }
    }

    printCostTable(cost, n);
    printSplitTable(split, n);

    string optimal = parenthesize(1, n, split);
    cout << "\nHOW THE BRACKETS ARE FORMED\n";
    cout << "k[1][3] = " << split[1][3]
         << ", so split A1...A3 after A" << split[1][3] << ".\n";
    cout << "Left part A1...A" << split[1][3]
         << " becomes " << parenthesize(1, split[1][3], split) << ".\n";
    cout << "Right part A" << split[1][3] + 1 << "...A3 becomes "
         << parenthesize(split[1][3] + 1, 3, split) << ".\n";
    cout << "Combine both parts: " << optimal << '\n';

    cout << "\nOPTIMAL MULTIPLICATION ORDER\n";
    cout << "Step 1: (A1 x A2) = (4 x 10) x (10 x 3)\n";
    cout << "        Result dimension = 4 x 3\n";
    cout << "        Scalar multiplications = 4*10*3 = 120\n";
    cout << "Step 2: ((A1 x A2) x A3) = (4 x 3) x (3 x 8)\n";
    cout << "        Result dimension = 4 x 8\n";
    cout << "        Scalar multiplications = 4*3*8 = 96\n";
    cout << "Total = 120 + 96 = " << cost[1][n] << '\n';

    cout << "\nFINAL ANSWER\n";
    cout << "Optimal parenthesization: " << optimal << '\n';
    cout << "Minimum scalar multiplications: " << cost[1][n] << '\n';
    cout << "Time complexity: Theta(n^3)\n";
    cout << "Space complexity: Theta(n^2)\n";
    return 0;
}

