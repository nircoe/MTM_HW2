#include "Exceptions.h"
#include <string>
#include <cstring>
#include <stdexcept>

namespace mtm
{
    Exception::Exception(std::string name)
    {
        std::string msg_s = "A game related error has occurred: " + name;
        msg = new char[msg_s.length() + 1];
        strcpy(msg, msg_s.c_str());
    }
    const char *Exception::what() const noexcept
    {
        return msg;
    }

    IllegalArgument::IllegalArgument() : Exception("IllegalArgument") {}
    IllegalCell::IllegalCell() : Exception("IllegalCell") {}
    CellEmpty::CellEmpty() : Exception("CellEmpty") {}
    MoveTooFar::MoveTooFar() : Exception("MoveTooFar") {}
    CellOccupied::CellOccupied() : Exception("CellOccupied") {}
    OutOfRange::OutOfRange() : Exception("OutOfRange") {}
    OutOfAmmo::OutOfAmmo() : Exception("OutOfAmmo") {}
    IllegalTarget::IllegalTarget() : Exception("IllegalTarget") {}
}