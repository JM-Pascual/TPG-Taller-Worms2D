#ifndef WORMS2D_WEAPON_H
#define WORMS2D_WEAPON_H

#include "../common/const.h"
#include "box2d/b2_math.h"
#include "Player.h"
#include "proyectile.h"


#define BAZOOKA_AMMO uint8_t(10000) //Se supone que tiene que ser infinita
#define GREEN_GRENADE_AMMO uint8_t(10000)

class Player;
class Game;
class Battlefield;

class Weapon {
protected:
    uint8_t ammo;
public:

    explicit Weapon(uint8_t ammo);

    virtual void execute(Game& game, Battlefield& battlefield, Player& player_) = 0;
    virtual std::shared_ptr<Projectile>
    prepare_ammo(Game& game,Battlefield &battlefield, b2Vec2 projectile_position, WeaponsAndTools type);
    //prepare_ammo(Game& game,Battlefield &battlefield, b2Vec2 projectile_position, WeaponsAndTools type) = 0;

};

//~~~~~~~~~~~~~~~~~~~ Bazooka ~~~~~~~~~~~~~~~~~~~~

class Bazooka : public Weapon{
public:
    Bazooka();
    void execute(Game& game, Battlefield& battlefield, Player& player) override;

};
/*
//~~~~~~~~~~~~~~~~~~~ Green_grenade ~~~~~~~~~~~~~~~~~~~~

class Green_grenade : public Weapon{
public:
    Green_grenade();
    void execute(Game& game, Battlefield& battlefield, Player& player) override;

};
*/

#endif //WORMS2D_WEAPON_H
