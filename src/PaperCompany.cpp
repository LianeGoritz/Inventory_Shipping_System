#include "PaperCompany.h"

PaperCompany::PaperCompany() {
}

void PaperCompany::startProcess()
{
    std::cout << "Dunder Mifflin Paper Company:\n\n";

    inv.viewInventory();
}
