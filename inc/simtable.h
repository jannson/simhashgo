#ifndef __SIMTABLE_H_
#define __SIMTABLE_H_

#include <iostream>
#include <vector>

class SimTable {
public:
    SimTable(size_t d, std::vector<unsigned long>& p);
    ~SimTable();
    void insert(unsigned long hash);
    void remove(unsigned long hash);
    unsigned find(unsigned long query);
    void findm(unsigned long query, std::vector<unsigned long>& results);
    unsigned long permute(unsigned long hash);
    unsigned long unpermute(unsigned long hash);
    unsigned long get_search_mask();
private:
    void* tb;
};

#endif

