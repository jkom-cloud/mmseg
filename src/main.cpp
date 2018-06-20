/*=============================================================================
#     FileName: main.cpp
#         Desc: mmseg c++ 实现 main 测试代码
#       Author: Daniel
#        Email: daneustc@gmail.com
#     HomePage: http://ustcdane.github.io/
#      Version: 0.0.1
#   LastChange: 2016-01-09 18:43:16
#
# modify from https://github.com/jdeng/mmseg
# Data files from mmseg4j https://code.google.com/p/mmseg4j/
# util from https://github.com/aszxqw/limonp
# Compile with:
# If use src/Mmseg.hpp, just include src/Mmseg.hpp then
# g++ -Ofast -march=native -funroll-loops -o mmseg -std=c++11 main.cpp
# If use src/Mmseg.h just include src/Mmseg.h then
# g++ -Ofast -march=native -funroll-loops -o mmseg -std=c++11  main.cpp src/Mmseg.cpp
# UTF-8 or gbk input
# MIT LICENSE
=============================================================================*/

#include "Mmseg.h"
using namespace mmsegSpace;

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cout<<"Usage: mmseg <dictionary> [input.txt]"<<std::endl;
    return 0;
  }

  MMSeg * pmmseg = MMSeg::getInstance();

  pmmseg->load(argv[1]);

  if (argc == 3) {
    std::ifstream ifs(argv[2]);
    if (! ifs.good()) {
      std::cerr << "Failed to open " << argv[2] << std::endl;
      return -1;
    }
    std::stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();

    time_t now = time(0);
    auto s = ss.str();
    auto so = pmmseg->segment(s);

    ss.clear();
    std::cout << so << std::endl;

    std::cout << "Done in " << time(0)  - now << " seconds,  words from " << s.size() << " chars" << std::endl;
    pmmseg->unload();

    return 0;
  }

  while (true) {
    std::cout << "Input String: ";
    std::string line;
    if (! std::getline(std::cin, line)) break;
    std::string ss = pmmseg->segment(trim(line));
    std::cout <<ss << std::endl; 
  }

  return 0;
}

