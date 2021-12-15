#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"
#include "Soldier.h"

#include <memory>
#include <map>
#include <vector>
#include <iterator>
#include <cmath>

namespace mtm
{
    static const int SOLDIER_MOVEMENT_RANGE = 3;
    static const int SOLDIER_RELOAD_AMOUNT = 3;
    static const int SOLDIER_ATTACK_COST = 1;

    Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team)
        : Character(health, ammo, range, power, SOLDIER_MOVEMENT_RANGE, SOLDIER_RELOAD_AMOUNT, SOLDIER_ATTACK_COST, team) {}

    std::shared_ptr<Character> Soldier::clone() const
    {
        std::shared_ptr<Character> ptr(new Soldier(*this));
        return ptr;
    }

    void Soldier::attack(std::map<GridPoint, std::shared_ptr<Character>, classcomp> &board,
                         const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        attackInRange(src_coordinates, dst_coordinates);
        if (ammo <= 0)
        {
            throw OutOfAmmo();
        }
        if (src_coordinates.row != dst_coordinates.row && src_coordinates.col != dst_coordinates.col)
        {
            throw IllegalTarget();
        }
        std::shared_ptr<Character> target;
        if (board.find(dst_coordinates) != board.end())
        {
            target = board.at(dst_coordinates);
            if (target->isEnemy(team))
            {
                if (target->takeDamage(power))
                {
                    board.erase(dst_coordinates);
                }
            }
        }
        std::vector<GridPoint> kills;
        int current_range;
        for (std::map<GridPoint, std::shared_ptr<Character>, classcomp>::iterator itr = board.begin(); itr != board.end(); ++itr)
        {
            current_range = GridPoint::distance(dst_coordinates, itr->first);
            if (current_range != 0 && current_range <= (int)ceil((double)range / 3.0))
            {
                target = itr->second;
                if (target->isEnemy(team))
                {
                    if (target->takeDamage((int)ceil((double)power / 2.0)))
                    {
                        kills.push_back(itr->first);
                    }
                }
            }
        }
        for (GridPoint target : kills)
        {
            board.erase(target);
        }
        ammo -= attack_cost;
    }

    CharacterType Soldier::getType()
    {
        return CharacterType::SOLDIER;
    }
}