#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct file_chunk {
  size_t sz;
  size_t chunk_no;
  string buf;
  file_chunk() {}
  file_chunk(size_t _sz, size_t _chunk_no, string _buf)
      : sz(_sz), chunk_no(_chunk_no), buf(_buf) {}
};

array<file_chunk, 10> splitter(const char *name) {
  fstream fp(name);
  stringstream strm;
  copy(istreambuf_iterator<char>(fp), istreambuf_iterator<char>(),
       ostreambuf_iterator<char>(strm));
  fp.close();
  string buffer = strm.str();

  int filesize = buffer.size();
  int one_chunk_size = filesize / 10;

  array<file_chunk, 10> chunks;

  auto it = buffer.begin();
  string tmp;
  for (int i = 0; i < 9; i++) {
    copy(it, it + one_chunk_size, back_inserter(tmp));
    it += one_chunk_size;
    chunks[i] = file_chunk(one_chunk_size, i, move(tmp));
  }
  copy(it, buffer.end(), back_inserter(tmp));
  chunks[9] = file_chunk(distance(it, buffer.end()), 9, move(tmp));
  return chunks;
}

/*
 * int main() {
 *   auto chunks = splitter("file_splitter.cpp");
 *   for (auto &chnk : chunks) {
 *     cout << chnk.chunk_no << '\n';
 *     cout << chnk.buf << "\n\n\n";
 *   }
 *   return 0;
 * }
 */
