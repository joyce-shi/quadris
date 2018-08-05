#include <iostream>
#include "cell.h"

using namespace std;

Cell::Cell(): taken{false}, blocktype{'E'} {
  //cout << "cell Made (" << r << ", " << c << ")" << endl;
}

void Cell::setCell(char btype) {
  //cout << "STATUS UPDATE: case3.0.0 cell set" << endl;
  //cout << "Setting: " << btype << endl;
  blocktype = btype;
  //cout << "STATUS UPDATE: case3.0.1 cell set" << endl;
  if (btype == 'E' || btype == 'H'){
    //cout << "STATUS UPDATE: case3.0.2 cell set" << endl;
    this->taken = false;
    //cout << "STATUS UPDATE: case3.0.3 cell set" << endl;
  }
  else {
    //cout << "STATUS UPDATE: case3.0.4 cell set" << endl;
    this->taken = true;
    //cout << "STATUS UPDATE: case3.0.5 cell set" << endl;
  }
}
