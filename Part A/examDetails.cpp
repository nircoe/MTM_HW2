#include <iostream>
#include "examDetails.h"
#define MAX_MONTH 12
#define MAX_DAY 30
#define HALF 0.5
#define MAX_HOUR 23.5

namespace mtm
{
    /**
     * @brief parameters c`tor
     * @param course_number_new Course number, must be positive.
     * @param month_new The month of the exam. must be between 1 and 12.
     * @param day_new The day of the exam, must be between 1 and 30.
     * @param hour_new The hour of the exam, must be end with .0 or .5 (like 4.0 or 2.5)
     * @param length_new The length of the exam, must be positive.
     * @param zoom_link_new The exam`s zoom link represented as a string. default is empty string.
     * 
     * @exception InvalidArgsException if the course number is not positive.
     * @exception InvalidDateException if the month or day dont match the demands.
     * @exception InvalidTimeException if the hour or length dont match the demands.
     */
    ExamDetails::ExamDetails(int course_number_new, int month_new, int day_new, double hour_new, 
                            int length_new, std::string zoom_link_new) : zoom_link(zoom_link_new)
    {
        if (course_number_new <= 0)
        {
            throw InvalidArgsException();
        }
        if (month_new <= 0 || month_new > MAX_MONTH || day_new <= 0 || day_new > MAX_DAY)
        {
            throw InvalidDateException();
        }
        if ((hour_new < 0 || hour_new > MAX_HOUR) ||
            ((hour_new - (int)hour_new != 0) && (hour_new - (int)hour_new != HALF)) ||
            (length_new <= 0))
        {
            throw InvalidTimeException();
        }
        course_number = course_number_new;
        month = month_new;
        day = day_new;
        hour = hour_new;
        length = length_new;
    }

    /**
     * @brief copy c`tor.
     * @param exam The exam we copy.
     */
    ExamDetails::ExamDetails(const ExamDetails &exam)
        : course_number(exam.course_number), month(exam.month), day(exam.day),
          hour(exam.hour), length(exam.length), zoom_link(exam.zoom_link) {}

    /**
     * @brief Getter for the zoom link
     * @return zoom link as string.
     */
    std::string ExamDetails::getLink() const
    {
        return zoom_link;
    }

    /**
     * @brief Setter for the zoom link
     * @param new_link new link to set
     */
    void ExamDetails::setLink(const std::string new_link)
    {
        zoom_link = new_link;
    }

    /**
     * @brief operator - override.
     * @param exam exam to subtract from this exam
     * @return the difference between the exams in days (assuming 30 days a month)
     */
    int ExamDetails::operator-(const ExamDetails &exam) const
    {
        return (month - exam.month) * 30 + (day - exam.day);
    }

    /**
     * @brief operator < override.
     * @param exam exam to compare
     * @return true if the exam is happening before the compared one.
     */
    bool ExamDetails::operator<(const ExamDetails &exam) const
    {
        return (*this - exam == 0) ? (*this - exam) < 0 : (hour - exam.hour) < 0;
    }

    /**
     * @brief Printing operator << override.
     * @param os ostream to write to.
     * @param exam exam to put in the ostream.
     * @return ostream after inserting the print of the exam
     * example print:
     * Course Number: 234123
     * Time: 28.7 at 13:00
     * Duration: 3:00
     * Zoom Link: https://tinyurl.com/59hzps6m
     */
    std::ostream &operator<<(std::ostream &os, const ExamDetails &exam)
    {
        std::string hour = ((exam.hour - (int)exam.hour) == 0) ? ":00" : ":30";
        os << "Course Number: " << exam.course_number << std::endl;
        os << "Time: " << exam.day << "." << exam.month << " at ";
        os << (int)exam.hour << hour << std::endl;
        os << "Duration: " << exam.length << ":00" << std::endl;
        os << "Zoom Link: " << exam.zoom_link << std::endl;
        return os;
    }

    /**
     * @brief Static c`tor for default exam 
     * @return default matam exam explained in << operator.
     */
    ExamDetails ExamDetails::makeMatamExam()
    {
        return ExamDetails(234124, 7, 28, 13.00, 3, "https://tinyurl.com/59hzps6m");
    }
}
