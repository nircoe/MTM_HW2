#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"

namespace mtm
{
  Character::Character(units_t health, units_t ammo, units_t range, units_t power,
                       units_t movement_range, units_t reload_amount, units_t attack_cost, Team team)
      : movement_range(movement_range), reload_amount(reload_amount), attack_cost(attack_cost), team(team)
  {
    if (health <= 0 || ammo < 0 || range < 0 || power < 0)
    {
      throw IllegalArgument();
    }
    else
    {
      this->health = health;
      this->ammo = ammo;
      this->range = range;
      this->power = power;
    }
  }

  Character::Character(const Character &src)
      : health(src.health), ammo(src.ammo), range(src.range), power(src.power),
        movement_range(src.movement_range), reload_amount(src.reload_amount), attack_cost(src.attack_cost), team(src.team) {}

  void Character::reload()
  {
    ammo += reload_amount;
  }
  bool Character::takeDamage(int damage)
  {
    health -= damage;
    return health <= 0;
  }
  bool Character::isEnemy(Team team)
  {
    return this->team != team;
  }
  bool Character::legalMove(int length)
  {
    return length <= movement_range;
  }
  void Character::attackInRange(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
  {
    if (GridPoint::distance(dst_coordinates, src_coordinates) > range)
    {
      throw OutOfRange();
    }
  }
}