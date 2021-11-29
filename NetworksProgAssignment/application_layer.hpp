#pragma once

#include <string>
#include <vector>
namespace application {

using namespace std;

struct data {
  vector<uint8_t> raw_data;

  data(string s) : raw_data(s.begin(), s.end()) {}
};

}; // namespace application
