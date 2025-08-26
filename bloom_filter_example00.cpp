/** Below example shows the use of the BloomFilter<T> class.
*
* Create an instance of the BloomFilter by specifiying a type. This guarantees
* that you can only insert elements of that type into the filter instance.
*
* There is also the more generic bloom_filter class. With this you can insert
* almost anything you like into the same filter instance. What counts is only
* their bit representation.
*/
#include <iostream>
#include <string>
#include <cassert>

#include "bloom_filter.hpp"


#if defined(BUILD_MONOLITHIC)
#define main bloom_filter_example_00_main
#endif

extern "C"
int main(void) {

   bloom_parameters parameters;

   // How many elements roughly do we expect to insert?
   parameters.projected_element_count = 1000;

   // Maximum tolerable false positive probability? (0,1)
   parameters.false_positive_probability = 0.0001; // 1 in 10000

   // Simple randomizer (optional)
   parameters.random_seed = 0xA5A5A5A5;

   if (!parameters) {
      std::cout << "Error - Invalid set of bloom filter parameters!" << std::endl;
      return 1;
   }

   parameters.compute_optimal_parameters();

   //Instantiate Bloom Filter
   BloomFilter<int> filter(parameters);
   filter.insert(-3);
   // Below rightly doesn't compile.
   // filter.insert(std::string("Foo"));
   // filter.insert(3.2);
   BloomFilter<std::string> string_filter(parameters);
   string_filter.insert(std::string("foo"));
   // Doesn't compile either. Good!
   // string_filter.insert(12);

   // Query Bloom Filter
   assert(filter.contains(-3) == true);  // Remember Bloom Filter guarantee no false negatives, so use assert here.
   if (filter.contains(2)) {  // Bloom Filter only gurantee a (known) tiny false positive rate, so theoretically a false positive is possible here.
     std::cout << "False positive! 2 was found in Bloom Filter." << std::endl;
   }

   // Query string_filter
   assert(string_filter.contains("foo"));
   if (string_filter.contains("bar")) {
     std::cout << "False positive! 'bar' was found in Bloom Filter." << std::endl;
   }

   return 0;
}
