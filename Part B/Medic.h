#ifndef MEDIC_H
#define MEDIC_H

#include "Auxiliaries.h"
#include "Character.h"

#include <memory>
#include <vector>

namespace mtm
{
    class Medic : public Character
    {
    public:
        Medic(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Medic(const Medic &) = default;
        Medic() = delete;
        ~Medic() = default;

        std::shared_ptr<Character> clone() const override;
        /**
         * @brief attack function of medic: if the attacked is an enemy it takes damage,
         * if friend - the medic heals it the amount of the power he has and dont lose ammo in the proccess.
         * @param board refrence to the game board
         * @param src_coordinates attacking character`s coords
         * @param dst_coordinates attacked character`s coords
         * @exception OutOfAmmo if the target is an enemy and the medic dont have any ammo
         * @exception IllegalTarget if the target is an empty cell
         * @exception outOfRange if the target is out of range (using attackInRange aux func)
         */
        void attack(std::map<GridPoint, std::shared_ptr<Character>, classcomp> &board,
                    const GridPoint &src_coordinates, const GridPoint &dst_coordinates) override;
        CharacterType getType() override;
    };
}
#endif