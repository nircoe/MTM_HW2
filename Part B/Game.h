#ifndef MTM_GAME_H
#define MTM_GAME_H

#include "Auxiliaries.h"
#include "Character.h"

#include <memory>
#include <map>

namespace mtm
{
   class Game
   {
      int height, width;
      std::map<GridPoint, std::shared_ptr<Character>, classcomp> board;

      /**
       * @brief Validation function for checking if the coordinates are inside the board.
       * @exception IllegalCell if the coordinates are not in board.
       */
      void checkCellInBoard(const GridPoint &coordinates);
      /**
       * @brief Validation function for checking if a cell in the board has a character in it.
       * @exception IllegalCell if the coordinates are not inside the board.
       */
      void checkCellOccupied(const GridPoint &coordinates);
      /**
       * @brief Validation function for checking if a cell is not empty.
       * @exception CellEmpty if the cell is empty.
       */
      void checkcellIsntEmpty(const GridPoint &coordinates);
      /**
       * @brief Validation function for checking if a cell is empty.
       * @return true if the cell is empty, false if not.
       */
      bool cellIsEmpty(const GridPoint &coordinates);
      /**
       * @brief convert game board to string for printing purposes.
       * @return std::string of the game with the following logic:
       * 's' for soldier, 'n' for sniper, 'm' for medic, ' ' for empty cell.
       * if the Character is from the Powerlifters team the letter is uppercased.
       */
      std::string toString() const;

   public:
      /**
     * @brief create empty board with the given dimentions.
     * @exception IllegalArgument if one of the dimensions is non-positive.
     */
      Game(int height, int width);
      /**
       * @brief d`tor
       */
      ~Game() = default;
      /**
       * @brief copy c`tor
       * @param other game to copy
       */
      Game(const Game &other);
      /**
       * @brief assining operator override
       * @param other game to copy and assign
       * @return game copied from other
       */
      Game &operator=(const Game &other);

      /**
     * @brief get character and adds it to to board with the given coordinates.
     * @exception IllegalCell if the coordinates are not in board.
     * @exception CellOccupied if the given coordinates are of a occupied cell.
     */
      void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);

      /**
     * @brief static methos to create a character with the given info and return a shared_ptr of it.
     * @param type character`s type defiend by the enum CharacterType
     * @param team character`s team defined by the enum Team
     * @return shared_ptr of the characer created.
     * @exception IllegalArgument if health is non-positive or one of the other stats is negative.
     */
      static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                      units_t health, units_t ammo, units_t range, units_t power);

      /**
     * @brief changes character position from (src_coordinates) to (dst_coordinates).
     * @exception IllegalCell one of the coordinates is not in board.
     * @exception CellEmpty if the src_coordinates doesnt contain a character.
     * @exception MoveTooFar if the dst_coordinates is too far for the given character.
     * @exception CellOccupied if the dst_coordinates is already occupied.
     */
      void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

      /**
     * @brief the character in src_coordinates attacks the dst_coordinates cell.
     * @exception IllegalCell one of the coordinates is not in board.
     * @exception CellEmpty if the src_coordinates doesnt contain a character.
     * @exception OutOfRange if the dst_coordinates is out of the attacking character`s range.
     * @exception OutOfAmmo if the attacking character doesnt have enought ammo to attack.
     * @exception IllegalTarget if the character cant attack for any other reason (inner character logic).
     */
      void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

      /**
     * @brief adds ammo to the character in coordinates.
     * @exception IllegalCell one of the coordinates is not in board.
     * @exception CellEmpty if the coordinates doesnt contain a character.
     */
      void reload(const GridPoint &coordinates);

      /**
     * @brief checks the board for a victory.
     * @param winningTeam=NULL is changed accordingaly, if no team won this is not changed.
     * @return 
     * true if a team won (no characters left from the other team).
     * false if no character left on board.
     */
      bool isOver(Team *winningTeam = NULL) const;

      /**
       * @brief uses Auxiliaries::printGameBoard to print entire board
       */
      friend std::ostream &operator<<(std::ostream &, const Game &);
   };
}
#endif
