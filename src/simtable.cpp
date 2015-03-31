#include "common.h"
#include "simtable.h"
#include "simhash.h"

#include <iostream>

using namespace Simhash;

#define TABLE() ((Table*)(this->tb))

//swig -go -c++ -intgosize 64  simhashcpp.swig
//go tool 6c -I /home/janson/projects/cloud/go/pkg/linux_amd64 simhashcpp_gc.c
//go tool 6g simhashcpp.go
SimTable::SimTable(size_t d, std::vector<unsigned long>& p) {
    this->tb = new Table(d, p);
}
SimTable::~SimTable() {
    delete TABLE();
}
void SimTable::insert(unsigned long hash) {
    TABLE()->insert(hash);
}
void SimTable::remove(unsigned long hash) {
    TABLE()->remove(hash);
}
unsigned SimTable::find(unsigned long query){
   return  TABLE()->find(query);
}
void SimTable::findm(unsigned long query, std::vector<unsigned long>& results){
    TABLE()->find(query, results);
}
unsigned long SimTable::permute(unsigned long hash){
    return TABLE()->permute(hash);
}
unsigned long SimTable::unpermute(unsigned long hash){
    return TABLE()->unpermute(hash);
}
unsigned long SimTable::get_search_mask(){
    return TABLE()->get_search_mask();
}

