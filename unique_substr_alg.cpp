#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using Table = std::vector<std::vector<int64_t>>;

std::vector<uint64_t> FindPrefixFunction(std::vector<int64_t> str) {
    std::vector<uint64_t> prefix_function(str.size(), 0);
    for (uint64_t i = 1; i < str.size(); ++i) {
        int64_t curr = prefix_function[i - 1];
        while (curr > 0 && str[i] != str[curr]) {
            curr = prefix_function[curr - 1];
        }
        if (str[i] == str[curr]) {
            prefix_function[i] = curr + 1;
        }
    }
    return prefix_function;
}

uint64_t KMP(std::vector<int64_t> ex, std::vector<int64_t> str) {
    std::vector<int64_t> total_str(ex.size() + 1 + str.size());
    for (uint64_t i = 0; i < total_str.size(); ++i) {
        if (i == ex.size()) {
            total_str[i] = -1;
        } else if (i < ex.size()) {
            total_str[i] = ex[i];
        } else {
            total_str[i] = str[i - ex.size() - 1];
        }
    }
    auto prefix_func = FindPrefixFunction(total_str);
    for (int64_t i = 0; i < prefix_func.size(); ++i) {
        if (prefix_func[i] == ex.size()) {
            //std::cout << (i - 2 * ex.size()) << " is start of word\n";
            return i - 2 * ex.size();
            //found start id
        }
    }
    return -1;
    //didn`t find substr
}

void FindSubmatrix(std::vector<std::vector<int64_t>> table, std::vector<std::vector<int64_t>> fragment) {
    for (uint64_t i = 0; i < table.size(); ++i) {
        int64_t old_pivot = -1;
        int64_t counter = 0;
        for (uint64_t j = 0; j < fragment.size(); ++j) {
            int64_t new_pivot = KMP(fragment[j], table[i + j]);
            if (new_pivot == -1) {
                break;
            }
            if (old_pivot != -1 && new_pivot != old_pivot) {
                break;
            }
            ++counter;
            old_pivot = new_pivot;
            if (counter == fragment.size()) {
                std::cout << i << " " << new_pivot << "\n";
                return;
            }
        }
    }
}

int main() {
    uint64_t height = 0;
    uint64_t length = 0;
    std::cout << "Input height: ";
    std::cin >> height;
    std::cout << "Input length: ";
    std::cin >> length;
    std::vector<std::vector<int64_t>> table(height, std::vector<int64_t>(length));
    for (uint64_t i = 0; i < height; ++i) {
        for (uint64_t j = 0; j < length; ++j) {
            std::cin >> table[i][j];
        }
    }

    uint64_t frag_height = 0;
    uint64_t frag_length = 0;
    std::cout << "Input fragment height: ";
    std::cin >> frag_height;
    std::cout << "Input fragment length: ";
    std::cin >> frag_length;
    std::vector<std::vector<int64_t>> frag_table(frag_height, std::vector<int64_t>(frag_length));
    for (uint64_t i = 0; i < frag_height; ++i) {
        for (uint64_t j = 0; j < frag_length; ++j) {
            std::cin >> frag_table[i][j];
        }
    }

    FindSubmatrix(table, frag_table);
}
