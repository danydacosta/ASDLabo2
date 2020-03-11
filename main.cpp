#include "pieces.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

#include "pieces.h"

int main() {
   Pieces pieces(PIECES);
   high_resolution_clock::time_point t1 = high_resolution_clock::now();
   fRecur(pieces, 9);
   high_resolution_clock::time_point t2 = high_resolution_clock::now();
   cout << "temps en ms : " << fixed << double(duration_cast<microseconds>(t2 - t1).count());
}