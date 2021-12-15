#ifndef MTM_EXCEPTIONS_H
#define MTM_EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>
namespace mtm
{
    class Exception : public std::exception
    {
    public:
        Exception(std::string name);
        ~Exception() noexcept
        {
            if(msg != nullptr)
            {
                delete[] msg;
            }
        }
        virtual const char *what() const noexcept;
        char *msg;
    };

    class IllegalArgument : public Exception
    {
    public:
        explicit IllegalArgument();
    };
    class IllegalCell : public Exception
    {
    public:
        explicit IllegalCell();
    };
    class CellEmpty : public Exception
    {
    public:
        explicit CellEmpty();
    };
    class MoveTooFar : public Exception
    {
    public:
        explicit MoveTooFar();
    };
    class CellOccupied : public Exception
    {
    public:
        explicit CellOccupied();
    };
    class OutOfRange : public Exception
    {
    public:
        explicit OutOfRange();
    };
    class OutOfAmmo : public Exception
    {
    public:
        explicit OutOfAmmo();
    };
    class IllegalTarget : public Exception
    {
    public:
        explicit IllegalTarget();
    };
}
#endif