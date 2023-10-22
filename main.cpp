#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    const int kNumsAfterComma = 6;
    int length;
    std::cin >> length;
    std::vector<double> volume;
    std::vector<double> log_vol;
    volume.resize(length);
    log_vol.resize(length + 1);
    for (int i = 0; i < length; ++i) {
        std::cin >> volume[i];
        volume[i] = std::log2(volume[i]);
    }
    log_vol[0] = 0;
    for (int i = 1; i <= length; ++i) {
        log_vol[i] = (log_vol[i - 1] + volume[i - 1]);
    }
    int questions;
    std::cin >> questions;
    int left;
    int right;
    for (int i = 0; i < questions; ++i) {
        std::cin >> left >> right;
        std::cout << std::fixed << std::setprecision(kNumsAfterComma)
                  << std::pow(2, (log_vol[right + 1] - log_vol[left]) /
                                 (right - left + 1))
                  << "\n";
    }
    return 0;
}
