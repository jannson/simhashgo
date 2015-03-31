%module simhashcpp

%include <typemaps.i>
%include "std_vector.i"

namespace std {
   %template(HashVector) vector<unsigned long>;
}

%include "inc/simtable.h"

