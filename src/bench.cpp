#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include <vector>

/* Hashes we can use */
#include "hashes/jenkins.h"
#include "hashes/murmur.h"
#include "hashes/fnv.h"

/* Tokenizers we can use */
#include "tokenizers/strspn.h"

#include "simhash.h"

int main(int argc, char* argv[]) {
    uint64_t limit(100000);

    if (argc == 2) {
        limit = static_cast<uint64_t>(atol(argv[1]));
    } else if (argc > 2) {
        std::cout << "Usage: " << argv[0] << " [number of hashes]" << std::endl;
    }

    std::vector<Simhash::hash_t> masks;

    /* This is a vector of bitmasks describing a valid permutation. This
     * particular permutation has 6 blocks, where each of the blocks is kept in
     * the order that you'd expect. Changing the order of these items has the
     * effect of reordering the blocks. */
    masks.push_back(0xFFE0000000000000);
    masks.push_back(0x1FFC0000000000  );
    masks.push_back(0x3FF80000000     );
    masks.push_back(0x7FF00000        );
    masks.push_back(0xFFE00           );
    masks.push_back(0x1FF             );

    /* Create a table where we're interested in matches with 3 or fewer bytes
     * differing between two near-duplicate documents. */
    Simhash::Table duplicates(3, masks);

    /* We're going to insert a bunch of hashes, and then run a bunch of queries
     * on some hashes that should be considered near duplicates and some that
     * should not */
    std::cout << "Inserting " << limit << " hashes..." << std::endl;
    for (uint64_t i = 1; i < limit; ++i) {
        duplicates.insert(i << 28);
    }

    std::cout << "Running " << limit * 4 << " queries..." << std::endl;
    Simhash::hash_t query(0), first(0), errors(0);
    for (uint64_t i = 1; i < limit; ++i) {
        query   = (i << 28) | 3;
        first   = duplicates.find(query);
        errors += first ? 0 : 1;

        query   = (i << 28) | 9;
        first   = duplicates.find(query);
        errors += first ? 0 : 1;

        query   = (i << 28) | 65;
        first   = duplicates.find(query);
        errors += first ? 0 : 1;

        query   = (i << 28) | 15;
        first   = duplicates.find(query);
        if (first) {
            std::cout << "Found " << first << " when looking for " << query << "(" << Simhash::num_differing_bits(first, query) << ")" << std::endl;
        }
        errors += !first ? 0 : 1;
    }

    std::cout << "Queries complete with " << errors << " errors" << std::endl;

    size_t count(0);
    Simhash::Table::const_iterator it( duplicates.begin());
    Simhash::Table::const_iterator end(duplicates.end());
    for(; it != end; ++it, ++count) {}

    std::cout << "There are " << count << " items in the table" << std::endl;

    return 0;
}
