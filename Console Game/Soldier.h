#ifndef SOLDIER_H
#define SOLDIER_H

#include "Auxiliaries.h"
#include "Character.h"

#include <memory>
#include <map>

namespace mtm
{
    class Soldier : public Character
    {
    public:
        Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Soldier(const Soldier &) = default;
        Soldier() = delete;
        ~Soldier() = default;

        std::shared_ptr<Character> clone() const override;
        /**
         * @brief attack function of soldier: the soldier can attack any cell within his range,
         * every enemy within the (range//3) from the attacked cell takes half the damage as well.
         * the soldier can only attack in vertical or horizontal lines from his position.
         * @param board refrence to the game board
         * @param src_coordinates attacking character`s coords
         * @param dst_coordinates attacked character`s coords
         * @exception OutOfAmmo if the soldier dont have any ammo
         * @exception IllegalTarget if the target is not alligned with the soldier.
         * @exception outOfRange if the target is out of range (using attackInRange aux func)
         */
        void attack(std::map<GridPoint, std::shared_ptr<Character>, classcomp> &board,
                    const GridPoint &src_coordinates, const GridPoint &dst_coordinates) override;
        CharacterType getType() override;

        // void legalAttack(std::vector<std::vector<std::shared_ptr<Character>>> &board,
        //                  const GridPoint &src_coordinates, const GridPoint &dst_coordinates) override;
    };
}
#endif