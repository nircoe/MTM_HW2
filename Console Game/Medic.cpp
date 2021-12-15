#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"
#include "Medic.h"

#include <memory>
#include <map>

namespace mtm
{
    static const int MEDIC_MOVEMENT_RANGE = 5;
    static const int MEDIC_RELOAD_AMOUNT = 5;
    static const int MEDIC_ATTACK_COST = 1;

    Medic::Medic(units_t health, units_t ammo, units_t range, units_t power, Team team)
        : Character(health, ammo, range, power, MEDIC_MOVEMENT_RANGE, MEDIC_RELOAD_AMOUNT, MEDIC_ATTACK_COST, team) {}

    std::shared_ptr<Character> Medic::clone() const
    {
        std::shared_ptr<Character> ptr(new Medic(*this));
        return ptr;
    }

    void Medic::attack(std::map<GridPoint, std::shared_ptr<Character>, classcomp> &board,
                       const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        attackInRange(src_coordinates, dst_coordinates);
        if (ammo <= 0)
        {
            throw OutOfAmmo();
        }
        if (src_coordinates.row == dst_coordinates.row && src_coordinates.col == dst_coordinates.col)
        {
            throw IllegalTarget();
        }

        if (board.find(dst_coordinates) == board.end())
        {
            throw IllegalTarget();
        }
        else
        {
            std::shared_ptr<Character> target = board.at(dst_coordinates);
            if (target->isEnemy(team))
            {
                if (target->takeDamage(power))
                {
                    board.erase(dst_coordinates);
                }
                ammo -= attack_cost;
            }
            else
            {
                target->takeDamage(-power);
            }
        }
    }

    CharacterType Medic::getType()
    {
        return CharacterType::MEDIC;
    }
}