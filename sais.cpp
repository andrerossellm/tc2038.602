#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

//generates buckets
void getBuckets(vector<int> & T, map<int, pair<int,int>> & buckets) {
  unordered_map<int, int> count; //count for each character
  for (auto & c : T)
    count[c]++; //map every char to its count - increment count
    
  int start = 0;
  //keys will be auto sorted with char comparators
  for (auto & [key, cnt] : count) {
    buckets[key] = {start, start + count[key]};  //maps key = (start, end) of bucket
    start += count[key]; //move starting point for bucket of next char
  }
}

void sais(vector<int> & T, vector<int> & SA){
  int n = T.size();

  //type array with n - 1 predefined as S
  vector<char> t(n, '_'); 
  t[n - 1] = 'S';
  for (int i = n - 1; i > 0; i--) {
    if (T[i - 1] == T[i])
      t[i - 1] = t[i];
    else
      t[i - 1] = T[i - 1] < T[i] ? 'S' : 'L';
  }

  map<int, pair<int,int>> buckets;
  getBuckets(T, buckets); //starting and ending point for every bucket

  unordered_map<int, int> count;
  unordered_map<int, int> LMS;
  int end = -1;

  int revoffset;
  for (int i = n - 1; i > 0; i--) {        // traverse backwards
    if (t[i] == 'S' && t[i - 1] == 'L') {  // if find L,S pattern
      revoffset = ++count[T[i]];  // increment count T[i] and set revoffset to
                                  // it
      SA[buckets[T[i]].second - revoffset] = i;    // set ending point for T[i] - count to current pos
      if (end != -1)  // if there's an ending, mark lms at that pos
        LMS[i] = end;
      end = i;  // assign end to crnt pos
    }
  }

  LMS[n - 1] = n - 1;
  count.clear();
  int offset, symbol;
  for (int i = 0; i < n; i++) {   // normal traversal
    if (SA[i] >= 0)               // for every assigned position
      if (t[SA[i] - 1] == 'L') {  // induced sort L positions
        symbol = T[SA[i] - 1];
        offset = count[symbol];
        SA[buckets[symbol].first + offset] = SA[i] - 1;
        count[symbol] = offset + 1;
      }
  }

  count.clear();
  for (int i = n - 1; i > 0; i--) {  // traverse backwards
    if (SA[i] > 0)
      if (t[SA[i] - 1] == 'S') {  // induced sort S positions
        symbol = T[SA[i] - 1];
        revoffset = ++count[symbol];
        SA[buckets[symbol].second - revoffset] = SA[i] - 1;
      }
  }

  // iterate thru SA and check if substr of T is an LMS
  // names will store unique names for each LMS substr in string T
  vector<int> namesp(n, -1);
  int name = 0;
  int prev = -1;
  for (int i = 0; i < SA.size(); i++) {
    // if LMS by LS pattern
    if (t[SA[i]] == 'S' && t[SA[i] - 1] == 'L') {
      // if diff from previous LMS substr, increment anme counter, to diff LMSs
      if (prev != -1)
        if (vector<int>(T.begin() + SA[prev], T.begin() + LMS[SA[prev]] + 1) !=
                vector<int>(T.begin() + SA[i], T.begin() + LMS[SA[i]] + 1))
          name += 1;
      prev = i;             // sets crnt as last seen LMS
      namesp[SA[i]] = name;  // assign computed name
    }
  }

  //names stores unique names for every LMS substr
  //SApIdx stores indices for every LMS substr in the OG string
  vector<int> names, SApIdx;
  for (int i = 0; i < n; i++)
    if (namesp[i] != -1) {
      names.push_back(namesp[i]);
      SApIdx.push_back(i);
    }
  
  //recursive step to sort names list if necessary
  if (name < names.size() - 1) {
    vector<int> namesCopy(names.begin(), names.end());
    names = vector<int>(names.size(), -1);
    sais(namesCopy, names);
  }

  reverse(names.begin(), names.end());

  SA = vector<int>(n, -1);  // reset SA
  count.clear();
  int pos;
  for (int i = 0; i < names.size(); i++) {  // compute pos of LMS substr in og string
    pos = SApIdx[names[i]];
    revoffset = ++count[T[pos]];
    SA[buckets[T[pos]].second - revoffset] =
        pos;  // place the LMS subst in appropriate position by buckets +
              // revoffset
  }

  count.clear();
  for (int i = 0; i < n; i++)  // induced sorting for L places
    if (SA[i] >= 0)
      if (t[SA[i] - 1] == 'L') {
        symbol = T[SA[i] - 1];
        offset = count[symbol];
        SA[buckets[symbol].first + offset] = SA[i] - 1;
        count[symbol] = offset + 1;
      }

  count.clear();
  for (int i = n - 1; i > 0; i--)  // induced sorting for S places
    if (SA[i] > 0)
      if (t[SA[i] - 1] == 'S') {
        symbol = T[SA[i] - 1];
        revoffset = ++count[symbol];
        SA[buckets[symbol].second - revoffset] = SA[i] - 1;
      }
}
