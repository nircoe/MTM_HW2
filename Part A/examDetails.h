#ifndef EXAMDETAILS_H_
#define EXAMDETAILS_H_

#include <string>

namespace mtm
{
    class ExamDetails
    {
        int course_number; 
        int month;
        int day;
        double hour;
        int length;
        std::string zoom_link;

    public:
        class InvalidDateException
        {
        };
        class InvalidTimeException
        {
        };
        class InvalidArgsException
        {
        };
        /**
         * @brief Constructor for ExamDetails
         * @param course_number
         * @param month
         * @param day         
         * @param hour
         * @param length
         * @param zoom_link
         */
        ExamDetails(int course_number,
         int month, int day, double hour, int length, std::string zoom_link = "");
        /**
         * @brief Copy constructor for ExamDetails
         * @param exam
         */
        ExamDetails(const ExamDetails &exam);
        /**
         * @brief default destructor for ExamDetails
         * @param 
         */
        ~ExamDetails() = default;
        /**
         * @brief operator= for ExamDetails
         * @param exam
         * @return ExamDetails&
         */
        ExamDetails &operator=(const ExamDetails &exam) = default;
        /**
         * @brief get Test link
         * @return string link
         */
        std::string getLink() const;
        /**
         * @brief set Test link
         * @param new_link
         * @return (void)
         */
        void setLink(const std::string new_link);
        /**
         * @brief operator- for ExamDetails
         * @param const ExamDetails&
         * @return the difference between 2 ExamDetails
         */
        int operator-(const ExamDetails &) const;
        /**
         * @brief operator- for ExamDetails
         * @param const ExamDetails&
         * @return is ExamDetails smaller than the other
         */
        bool operator<(const ExamDetails &) const;
        /**
         * @brief operator<< for ExamDetails
         * @param os
         * @param exam
         * @return the output of the ExamDetails
         */
        friend std::ostream &operator<<(std::ostream &os, const ExamDetails &exam);
        /**
         * @brief static function for make specific matam Exam
         * @return the specific ExamDetails
         */
        static ExamDetails makeMatamExam();
    };
}

#endif