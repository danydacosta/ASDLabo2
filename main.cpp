#include "pieces.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "pieces.h"

int main() {
   Pieces pieces(PIECES);
   high_resolution_clock::time_point t1 = high_resolution_clock::now();
   resoudrePuzzle(pieces);
   high_resolution_clock::time_point t2 = high_resolution_clock::now();
   cout << "temps en ms : " << fixed << double(duration_cast<nanoseconds>(t2 - t1).count());
}