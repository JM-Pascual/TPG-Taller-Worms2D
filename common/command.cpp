#include "command.h"


Command::Command(uint8_t id): client_id(id) {}

Move::Move(uint8_t id, MoveDir dir): Command(id), direction(dir) {}

Jump::Jump(uint8_t id, JumpDir dir): Command(id), direction(dir) {}

Damage::Damage(uint8_t id, int8_t dmg): Command(id), dmg(dmg) {}
