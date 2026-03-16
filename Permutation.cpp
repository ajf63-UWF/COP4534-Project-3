#include "Permutation.hpp"

void initializePermutation(std::vector<int>& values, int start, int end) {
    values.clear();

    for (int i = start; i <= end; i++) {
        values.push_back(i);
    }
}

void swapPositions(std::vector<int>& values, int index1, int index2) {
    int temp = values[index1];
    values[index1] = values[index2];
    values[index2] = temp;
}

bool perm1(std::vector<int>& values) {
    int numElements = static_cast<int>(values.size());

    if (numElements <= 1) {
        return false;
    }

    int m = numElements - 2;

    while (m >= 0 && values[m] > values[m+1]) {
        m = m - 1;
    }

    if (m < 0) {
        return false;
    }

    int k = numElements - 1;

    while (values[m] > values[k]) {
        k = k - 1;
    }

    swapPositions(values, m, k);

    int p = m + 1;
    int q = numElements - 1;

    while (p < q) {
        swapPositions(values, p, q);
        p++;
        q--;
    }

    return true;
}