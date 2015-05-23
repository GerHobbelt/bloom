# Bloom Filter Library in C++
This implements a Bloom Filter in C++.

## Get started
Clone the repository or copy the file `bloom_filter.hpp` into your project.

Use it like this:

    #include <iostream>
    #include "bloom_filter.hpp"
    
    int main() {
      // Choose your parameters
      bloom_parameters params;
      params.projected_elements_count = 1000;
      params.false_positive_probability = 1e-4;
      if (!params) {
        std::cerr << "Invalid Bloom Filter parameters." << std::endl;
        return 1;
      }
      
      // Create a Bloom Filter
      BloomFilter<int> filter(params);
      filter.insert(0);
      filter.insert(12);
      
      // Query for membership
      filter.contains(0); // Returns a bool. In this case 'true'
      filter.contains(1); // Should return 'false' but false positives are possible
      filter.contains(12);  // Will return 'true'.
    }

## Overview
The code consists just of the header file `bloom_filter.hpp`, there are four examples that show you the various uses.
Also implemented is a Compressible Bloom Filter. Have a look at `bloom_filter_example03.cpp` for details.

Classes: 
* `BloomFilter<T>` this is the type safe implementation. `typename T` must be a C++ POD-type class. 
Any basic type (int, float, etc) will work. 
* `bloom_filter` This is a generic Bloom Filter, it will take any POD-type object, look at its bit represenation and
insert it into the filter.
* `compressible_bloom_filter` A compressible Bloom Filter. 
