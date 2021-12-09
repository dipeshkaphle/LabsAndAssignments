#pragma once

#include "application_layer.hpp"

#include <stddef.h>
#include <vector>
namespace transport {

using namespace std;

struct Segment {
  // maximum segment size
  static size_t mss;

  int32_t seq_no;

  vector<uint8_t> data;

  // Constructors
  Segment(vector<uint8_t> data, int32_t seq_no)
      : data(move(data)), seq_no(seq_no) {}

  size_t get_data_size() { return data.size(); }

  string get_data_as_string() { return string(data.begin(), data.end()); }

  /**
   * - Takes in application layer data
   * - Splits it into multiple segments
   */
  static vector<Segment> make_segments(const application::data &data) {
    auto l = data.raw_data.begin();
    auto r = min(data.raw_data.begin() + Segment::mss, data.raw_data.end());
    vector<Segment> segments;
    do {
      segments.push_back(
          Segment(vector<uint8_t>(l, r), distance(data.raw_data.begin(), l)));
      l = r;
      r = min(r + Segment::mss, data.raw_data.end());
    } while (l != data.raw_data.end());
    return segments;
  }
  //
};
}; // namespace transport
