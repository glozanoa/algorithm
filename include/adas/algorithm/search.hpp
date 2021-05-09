/*
 * search algortihms
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */



#ifndef _SEARCH_H
#define _SEARCH_H

#include <iostream>
#include <iterator>
#include <utility>
using namespace std;

#include "./utilities/helper.hpp"
#include "./utilities/timer.hpp"
#include "./utilities/print.hpp" // ONLY FOR TESTING PURPOSES

#include "omp.h"

namespace adas::algorithm
{
  namespace search
  {
    namespace serial
    {
      //tested - date May 1 2021
      template<class ForwardIterator>
      ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
      {
        ForwardIterator min = first;
        ForwardIterator itr = first;
        while(++itr != last)
          {
            if(*itr < *min)
              min = itr;
          }
        return min;
      }

      //tested - date May 1 2021
      template<class ForwardIterator>
      ForwardIterator _double_iterator_min_element(typename vector<ForwardIterator>::iterator first,
                                                   typename vector<ForwardIterator>::iterator last)
      {
        typename vector<ForwardIterator>::iterator min = first;
        typename vector<ForwardIterator>::iterator itr = first;
        while(++itr != last)
          {
            if(**itr < **min)
              min = itr;
          }
        return *min;
      }


      //debuged - date May 4 2021
      template<class ForwardIterator>
      ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
      {
        ForwardIterator max = first;
        ForwardIterator itr = first;
        while(++itr != last)
          {
            if(*max < *itr)
              max = itr;
          }
        return max;
      }

      //tested - date May 7 2021
      template<class ForwardIterator>
      ForwardIterator _double_iterator_max_element(typename vector<ForwardIterator>::iterator first,
                                                   typename vector<ForwardIterator>::iterator last)
      {
        typename vector<ForwardIterator>::iterator max = first;
        typename vector<ForwardIterator>::iterator itr = first;
        while(++itr != last)
          {
            if(**max < **itr)
              max = itr;
          }
        return *max;
      }

      //debuged - date May 4 2021
      template<class RandomAccessIterator>
      pair<RandomAccessIterator, RandomAccessIterator> minmax_element(RandomAccessIterator first,
                                                                      RandomAccessIterator last)
      {
        RandomAccessIterator min = first;
        RandomAccessIterator max = first;
        RandomAccessIterator itr = first+1;

        while(itr != last && itr != last+1)
          {
            pair<RandomAccessIterator, RandomAccessIterator> mm = minmax(itr, itr+1);

            if(*mm.first < *min)
              min = mm.first;
            if(*max < *mm.second)
              max = mm.second;

            itr += 2;
          }
        return make_pair(min, max);
      }


      template<class ForwardIterator, class T>
      ForwardIterator secuential(ForwardIterator first, ForwardIterator last, const T value)
      {
        while(first != last)
          {
            if(*first == value)
              return first;
            first++;
          }
        return last;
      }



      template<class ForwardIterator, class T>
      bool is_element(ForwardIterator first, ForwardIterator last, const T value)
      {
        while(first != last)
          {
            if(*first == value)
              return true;
            first++;
          }
        return false;
      }
    }

    namespace parallel
    {
      template<class ForwardIterator>
      ForwardIterator min_element(ForwardIterator first, ForwardIterator last, unsigned int omp_nthreads)
      {
        unsigned int d = distance(first, last);
        unsigned int nthreads = omp_nthreads;
        omp_set_num_threads(nthreads);
        vector<Boundaries<ForwardIterator>> limits(nthreads);
        vector<ForwardIterator> local_min(nthreads);

#pragma omp parallel shared(limits) firstprivate(first, last, nthreads)
        {
          unsigned int idthread = omp_get_thread_num();
          ForwardIterator init = first + idthread*(d/nthreads);
          ForwardIterator end = first + (idthread+1)*(d/nthreads);

          if(idthread == nthreads-1)
            end = last;

          Boundaries<ForwardIterator> limit;
          limit.init = init;
          limit.end = end;

          limits[idthread] = limit;

          ForwardIterator local_min_element =  serial::min_element(init, end);
          local_min[idthread] = local_min_element;

          // ONLY FOR DEBUG PURPOSE
#pragma omp critical
          {
            cout << "Thread " << idthread << " : " << *local_min_element << endl;
          }
        }

        return serial::_double_iterator_min_element<ForwardIterator>(local_min.begin(), local_min.end());
      }

      template<class ForwardIterator>
      ForwardIterator max_element(ForwardIterator first, ForwardIterator last, unsigned int omp_nthreads)
      {
        unsigned int d = distance(first, last);
        unsigned int nthreads = omp_nthreads;
        omp_set_num_threads(nthreads);
        vector<Boundaries<ForwardIterator>> limits(nthreads);
        vector<ForwardIterator> local_max(nthreads);

#pragma omp parallel shared(limits) firstprivate(first, last, nthreads)
        {
          unsigned int idthread = omp_get_thread_num();
          ForwardIterator init = first + idthread*(d/nthreads);
          ForwardIterator end = first + (idthread+1)*(d/nthreads);

          if(idthread == nthreads-1)
            end = last;

          Boundaries<ForwardIterator> limit;
          limit.init = init;
          limit.end = end;

          limits[idthread] = limit;

          ForwardIterator local_max_element =  serial::max_element(init, end);
          local_max[idthread] = local_max_element;

          // ONLY FOR DEBUG PURPOSE
#pragma omp critical
          {
            cout << "Thread " << idthread << " : " << *local_max_element << endl;
          }
        }

        return serial::_double_iterator_max_element<ForwardIterator>(local_max.begin(), local_max.end());
      }
    }

}


//   template<class RandomAccessIterator, class T>
//   RandomAccessIterator binary_search(RandomAccessIterator first, RandomAccessIterator last,
//                                      const T value)
//   {
//     print::to_stdout(first, last);
//     unsigned int d = distance(first, last);
//     RandomAccessIterator midpoint  = first + d/2;

//     if(*midpoint == value)
//       return midpoint;
//     else if(1 < d)
//       {
// #pragma omp parallel sections
//         {
// #pragma omp section
//           {
//             RandomAccessIterator lsearch = binary_search(first, midpoint, value);
//             if(*lsearch == value) return lsearch;
//           }

// #pragma omp section
//           {
//             RandomAccessIterator rsearch = binary_search(midpoint+1, last, value);
//             if(*rsearch == value) return rsearch;
//           }
//         }
//       }
//     return last;
//   }

  // template<class BidirectionalIterator, class T>
  // BidirectionalIterator binary_search(BidirectionalIterator first, BidirectionalIterator last, const T value)
  // {
  //   BidirectionalIterator end = last;
  //   return  binary_search(first, last, value, end);
  // }
}


/*  OLD CODE  */

// template<typename T>
// class Search
// {
// public:
//   static int secuential(vector<T> elements, T element, bool verbose)
//   /*
//    * Search secuentialy element in elements vector.
//    * Return the position of element if element belongs to elements otherwise return -1
//    */
//   {
//     unsigned int length = elements.size();
//     int index = -1; //
//     for(int i=0; i<length; i++)
//       {
//         if(element == elements[i])
//           {
//             index = i;
//             if(verbose)
//               cout << "(Found value, Iteration " << i << ")"
//                    << " index:" << index << ", value:" << element << endl;
//             break;
//           }
//       }
//     return index;
//   }

//   static int binary(vector<T> elements, T element, bool verbose, bool timer)
//   /*
//    * Search an element in elements (ordered) vector using binary search algorithm.
//    *
//    * Return:
//    *      The position of an element if it belongs to elements vector otherwise return -1
//    *
//    * Input:
//    *      If verbose is true show steps of binary algorithm otherwise run quietly
//    *      If timer is true count how much time the binary algorithm takes to search an element
//    */
//   {
//     if(timer)
//       {
//         Timer time;
//         time.start();
//       }

//     int index = -1; // index of element in elements vector
//     unsigned int lower = 0;
//     unsigned int upper = elements.size() -1;
//     unsigned int midpoint = floor((lower+upper)/2.0);
//     while(lower <= upper && elements[midpoint] != element)
//       {
//         if (verbose)
//           cout << "lower: " << lower << ", midpoint: " << midpoint << ", upper: " << upper << endl;

//         if (element < elements[midpoint])
//           upper = midpoint -1;
//         else
//           lower = midpoint +1;

//         midpoint = floor((lower+upper)/2.0);
//       }

//     if(elements[midpoint] == element)
//       {
//         index = midpoint;
//         if(verbose)
//           cout << "Element " << element << " found in elements (index " << index << ")" << endl;
//       }

//     if(timer)
//       {
//         time.end();
//         time.report("Elapsed time");
//       }

//     return index;
//   }

// };
#endif //_SEARCH_H