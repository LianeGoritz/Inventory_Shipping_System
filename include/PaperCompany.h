#ifndef PAPERCOMPANY_H
#define PAPERCOMPANY_H

#include "Inventory.h"

class PaperCompany {
 public:
     PaperCompany();
     virtual ~PaperCompany();

     void startProcess();

 private:
    Inventory inv;

};
