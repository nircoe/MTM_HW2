#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"
#include "Sniper.h"

#include <memory>
#include <map>
#include <cmath>

namespace mtm
{
    static const int SNIPER_MOVEMENT_RANGE = 4;
    static const int SNIPER_RELOAD_AMOUNT = 2;
    static const int SNIPER_ATTACK_COST = 1;

    Sniper::Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team)
        : Character(health, ammo, range, power, SNIPER_MOVEMENT_RANGE, SNIPER_RELOAD_AMOUNT, SNIPER_ATTACK_COST, team), shots_fired(0) {}

    std::shared_ptr<Character> Sniper::clone() const
    {
        std::shared_ptr<Character> ptr(new Sniper(*this));
        return ptr;
    }
    void Sniper::attackInRange(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        Character::attackInRange(src_coordinates, dst_coordinates);
        int n1 = GridPoint::distance(dst_coordinates, src_coordinates);
        int n2 = (int)ceil((double)range / 2.0);
        if (n1 < n2)
        {
            throw OutOfRange();
        }
    }
    void Sniper::attack(std::map<GridPoint, std::shared_ptr<Character>, classcomp> &board,
                        const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        attackInRange(src_coordinates, dst_coordinates);
        if (ammo <= 0)
        {
            throw OutOfAmmo();
        }

        if (board.find(dst_coordinates) == board.end())
        {
            throw IllegalTarget();
        }
        else
        {
            std::shared_ptr<Character> target = board.at(dst_coordinates);
            if (!target->isEnemy(team))
            {
                throw IllegalTarget();
            }

            else
            {
                shots_fired++;
                if (target->takeDamage(shots_fired % 3 ? power : 2 * power))
                {
                    board.erase(dst_coordinates);
                }
            }

            ammo -= attack_cost;
        }
    }
    CharacterType Sniper::getType()
    {
        return CharacterType::SNIPER;
    }
}