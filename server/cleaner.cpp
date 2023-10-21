#include "cleaner.h"


Cleaner::Cleaner(): Thread(), killed(false) {}

void Cleaner::run() {}

void Cleaner::kill() { killed = true; }
