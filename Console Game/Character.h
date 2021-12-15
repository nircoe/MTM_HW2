#ifndef CHARACTER_H
#define CHARACTER_H

#include <map>
#include <memory>

#include "Auxiliaries.h"

namespace mtm
{
    struct classcomp
    {
        /**
         * @brief compare function between 2 gridpoints, used by the map
         * actring as a < operator
         * @return true if g1<g2 (comes before him on the board)
         */
        bool operator()(const GridPoint &g1, const GridPoint &g2) const
        {
            return (g1.row == g2.row) ? g1.col < g2.col : g1.row < g2.row;
        }
    };

    class Character
    {
    protected:
        units_t health, ammo, range, power;
        units_t movement_range, reload_amount, attack_cost;
        Team team;

    public:
        /**
         * @brief parameter c`tor.
         * @param health health of the character (positive)
         * @param ammo ammo units the character have (non-negative)
         * @param range attack range of the character (non-negative)
         * @param power attack power of the character (non-negative)
         * @param movement_range how many cells the character can move in a single move (const for each character)
         * @param reload_amount how many ammo units the character reloads in a reload (const for each character)
         * @param attack_cost how many ammo units the character loses each attack (const for each character)
         * @param team the character`s team: POWERLIFTERS or CROSSFITTERS (enum)
         * @exception IllegalArgument if one of the argument is illegal (health is negative or the others are non-positive)
         */
        Character(units_t health, units_t ammo, units_t range, units_t power,
                  units_t movement_range, units_t reload_amount, units_t attack_cost, Team team);
        /**
         * @brief copy c`tor
         */
        Character(const Character &);
        Character() = delete;
        Character &operator=(const Character &) = default;
        virtual ~Character() = default;

        /**
         * @brief clone "c`tor" to create a shared_ptr of the character.
         * @param character to copy
         * @return a shared_ptr of a character copy
         */
        virtual std::shared_ptr<Character> clone() const = 0;
        /**
         * @brief interface attack function
         * @param board refrence to the game board.
         * @param src_coordinates attacking character`s cords
         * @param dst_coordinates attacked character`s cords
         * @exception detailed in each characters h file.
         */
        virtual void attack(std::map<GridPoint, std::shared_ptr<Character>, classcomp> &board, const GridPoint &src_coordinates, const GridPoint &dst_coordinates) = 0;
        /**
         * @brief aux function to validate the attack is in a legal range
         * @param src_coordinates attacking character`s cords
         * @param dst_coordinates attacked character`s cords
         * @exception OutOfRange if the coords are not in a legal range.
         */
        virtual void attackInRange(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        /**
         * @brief interface getter for the character`s type (SOLDIER/SNIPER/MEDIC)
         * @return enum CharacterType: SOLDIER/SNIPER/MEDIC
         */
        virtual CharacterType getType() = 0;
        /**
         * @brief reload function, adds ammo to the character based on the reload_amount parameter.
         */
        void reload();
        /**
         * @brief aux function, checks if the character is enemy with the given team
         * @param team to compare with
         * @return true if enemys, false if friends
         */
        bool isEnemy(Team team);
        /**
         * @brief aux function to take damge from an attack.
         * @param damage damage to reduce from tha character`s health.
         * @return true if the character died after the attack (health<=0)
         */
        bool takeDamage(int damage);
        /**
         * @brief aux function to check if a move can be made
         * @param length how much cells the character is trying to move
         * @return true if legal false if not
         */
        bool legalMove(int length);

        friend class Game;
    };
}
#endif