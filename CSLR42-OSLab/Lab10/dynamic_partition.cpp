#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
string FREE = "Free";
string Allocated = "Allocated";

using status = string;
using block_size = size_t;

int main()
{
  fstream inp("input.txt");
  string tmp;
  int n;
  inp >> n; // first line is number of blocks
  vector<pair<block_size, status>> blocks(n);
  for (pair<block_size, status> &block : blocks)
  {
    inp >> block.first;  // size of block
    inp >> block.second; // status
  }
  vector<pair<block_size, status>> blocks_cloned = blocks;
  cout << "The blocks are: \n";
  for (pair<block_size, status> &block : blocks)
  {
    cout << block.first << " " << block.second << '\n';
  }
  cout << "\n\n";

  block_size request;
  vector<block_size> requests;
  // first fit strategy
  //
  int req_no = 0;
  cout << "First fit strategy\n";
  while ((inp >> request))
  {
    requests.push_back(request);
    int i = 0;
    for (pair<block_size, status> &block : blocks)
    {
      if (block.first >= request && block.second != Allocated)
      {
        cout << "Request no. " << req_no << " of size " << request
             << " allocated to block number " << i << " of size " << block.first << '\n';
        block.second = Allocated;
        break;
      }
      i++;
    }
    req_no++;
  }

  // next fit strategy
  // just a modified first fit algorithm
  req_no = 0;
  blocks = blocks_cloned;
  int last_stopped = 0;
  cout << "Next fit strategy\n";
  for (int req : requests)
  {
    int i = last_stopped + 1;
    while ((i % blocks.size()) != last_stopped)
    {
      pair<block_size, status> &block = blocks[i];
      if (block.first >= req && block.second != Allocated)
      {
        cout << "Request no. " << req_no << " of size " << req
             << " allocated to block number "
             << (i % blocks.size()) << " of size " << block.first << '\n';
        last_stopped = i % blocks.size();
        block.second = Allocated;
        break;
      }
      i++;
    }
    req_no++;
  }
}
