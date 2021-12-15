#ifndef SNIPER_H
#define SNIPER_H

#include "Auxiliaries.h"
#include "Character.h"

#include <memory>
#include <vector>

namespace mtm
{
    class Sniper : public Character
    {
        int shots_fired;

    public:
        Sniper(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Sniper(const Sniper &) = default;
        Sniper() = delete;
        ~Sniper() = default;

        std::shared_ptr<Character> clone() const override;
        void attackInRange(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) override;
        /**
         * @brief attack function of sniper: if the attacked character is inside the (range//2) range from the sniper
         * the attack is illegal, every third successful shot the sniper does twice the regular damage.
         * @param board refrence to the game board
         * @param src_coordinates attacking character`s coords
         * @param dst_coordinates attacked character`s coords
         * @exception OutOfAmmo if the sniper dont have any ammo
         * @exception IllegalTarget if the target is an empty cell or a friend.
         * @exception outOfRange if the target is out of range (using attackInRange aux func)
         * or inside the (range//2) range.
         */
        void attack(std::map<GridPoint, std::shared_ptr<Character>, classcomp> &board,
                    const GridPoint &src_coordinates, const GridPoint &dst_coordinates) override;
        CharacterType getType() override;
    };
}
#endif