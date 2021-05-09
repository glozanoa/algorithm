/*
 * Classes to read and write numbers from (to) a file to (from) a vector (ONLY FOR TESTING PURPOSE)
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

#ifndef _IO_H
#define _IO_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

#include "cast.hpp"

namespace read
{
  template<class T>
  vector<T> from_file(string file_name)
  {
    ifstream fn;
    vector<T> numbers;
    try
      {
        fn.open(file_name);
        T number;
        string line;
        while(getline(fn, line))
          {
            number = str2<T>(line);
            numbers.push_back(number);
          }
        fn.close();
      }
    catch(exception& error)
      {
        cout << error.what() << endl;
        if(fn.is_open())
          fn.close();
      }
    return numbers;
  }
};

namespace write
{
  template<class ForwardIterator>
  void to_file(ForwardIterator first, ForwardIterator last, string file_name)
  {
    ofstream fn;
    try
      {
        fn.open(file_name);
        for(ForwardIterator itr = first; itr != last; itr++)
          fn << *itr << endl;
        fn.close();
        cout << "Data was saved to " << file_name << endl;
      }
    catch(exception& error)
      {
        cout << error.what() << endl;
        if(fn.is_open())
          fn.close();
      }
  }
}

#endif //_IO_H
