#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <string>

#include "parlay/io.h"
#include "parlay/primitives.h"
#include "parlay/sequence.h"
#include "parlay/internal/get_time.h"

using charseq = parlay::sequence<char>;
using uint = unsigned int;


parlay::sequence<unsigned int> build_suffix_array(parlay::sequence<unsigned int> s) {
    int n = s.size();
    // initializing  p (sorting first letters of each suffix
    auto p = parlay::tabulate<unsigned int>(n, [&] (unsigned int i) {return i;});
    p = parlay::integer_sort(p, [&] (const auto i) {return s[i];});

    // changes helps to create c, it checks if two consecutive letters from p are equal
    auto changes = parlay::tabulate(n, [&] (long i) {
        if (i == 0)
            return (unsigned int)0;
        return (unsigned int)(s[p[i]] != s[p[i - 1]]);
    });

    // initializing c, do prefix sum on changes, this gives us class for each prefix of suffix
    auto prefix_sums = parlay::scan_inclusive(changes);
    // c needs to have order like in the original word, so we initialize c and adjust the indices
    auto c = parlay::tabulate(n, [&] (unsigned int i) {return (unsigned int)0;});
    parlay::parallel_for(0, n, [&] (unsigned int i) {c[p[i]] = prefix_sums[i];});


    // main loop, we double the length of the suffix in each step
    for (int h = 0; (1 << h) < n; h++) {
        // initialize pn which will help us with creating new p and c arrays
        // pn is the order of second half of the prefix we are considering, pn[i] = p[i] - 2^i
        auto pn = parlay::tabulate(n, [&] (long i) {
            if ((int)p[i] - (int)(1<<h) < 0)
                return (unsigned int)((int)p[i] - (int)(1<<h) + n);
            return (unsigned int)(p[i] - (1<<h));
        });
        // we associate pn with elements from c and sort it by c, this gives us p
        p = parlay::stable_integer_sort(p, [&] (const auto i) {return c[i];});

        // updating c, we need to look at the order in p and check if the consecutive elements are different
        // similar to the way we create c in the beginning
        auto changes_n = parlay::tabulate(n, [&] (long i) {
            if (i == 0)
                return (unsigned int)0;
            std::pair<int, int> cur = {c[p[i]], c[(p[i] + (1<<h)) % n]};
            std::pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1<<h)) % n]};
            return (unsigned int)(cur != prev);
        });

        // updating c, prefix sum
        auto prefix_sums_n = parlay::scan_inclusive(changes_n);
        // c needs to have order like in the original word, so we update c and adjust the indices
        parlay::parallel_for(0, n, [&] (long i) {c[p[i]] = prefix_sums_n[i];});

        // we stop if all elements have different classes
        if (prefix_sums_n[n - 1] == n-1)
            break;

    }
    return p;
}

int main(int argc, char* argv[]) {
    charseq str = parlay::chars_from_file(argv[1]);
    auto int_seq = parlay::tabulate(str.size(), [&] (long i) {return (unsigned int)str[i];});
    int_seq.push_back(0);
    using index = unsigned int;
    long n = str.size();
    std::cout << n << "\n";
    parlay::sequence<index> result;

    parlay::internal::timer t("Time");

    for (int i=0; i < 1; i++) {
        result = build_suffix_array(int_seq);
//        for (auto r : result)
//            std::cout << r << " ";
//        std::cout << "\n";
        t.next("suffix_array_own");
    }



}
