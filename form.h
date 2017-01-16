/* !
 * @brief Form class
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * Describe all shape of the 1010 game.
 * This class stores forms made of squares and keeps it's boundary box,
 * ie the smallest rectangle that contains the form.
 *
 */

#ifndef FORM_H_INCLUDED
#define FORM_H_INCLUDED

#include <cstddef>      // size_t
#include <string>       // i/o


#define FORM_DEFAULT_SIZE 5

/*!
 * @brief Form class
 *
 * Considers forms as squares's group with a bounding box.
 *
 */
class Form
{
public:
    /*!
     * @brief Point structure
     *
     * Has two coordinates.
     *
     */
    struct Point
    {
        int x, y;
    };

    /*!
    * @brief Default constructor
    *
    * Create an empty shape.
    *
    */
    Form();

    /*!
    * @brief Constructor by copying
    *
    * Create a form which is the perfect copy of another.
    *
    * @param _form : The form to copy.
    *
    */
    Form(const Form& _form);

    /*!
    * @brief Destructor
    *
    */
    ~Form();

    /*!
    * @brief Overload of affectation operator
    *
    * Change the form radicaly.
    *
    * @param _form : The form to take
    *
    * @return The new form
    *
    */
    Form& operator= (const Form& _form);

    /*!
    * @brief Clear the form
    *
    * Set form's values as they'll be if the form was just created.
    *
    */
    void clear();

    /*!
    * @brief Add a square
    *
    * @param _x : New square's X location
    * @param _y : New square's Y location
    *
    */
    void add(int _x, int _y);


    /*!
    * @brief Accesor to the form's size
    *
    * @return The size
    *
    */
    size_t getsize() const;

    /*!
    * @brief Accesor to a specific square
    *
    * @return the square location
    *
    */
    Point operator[](size_t) const;

    /*!
    * @brief Accesor to the minimal bounding box
    *
    * @return The minimal bounding box
    *
    */
    Point getboxmin() const;

    /*!
    * @brief Accesor to the maximal bounding box
    *
    * @return The maximal bounding box
    *
    */
    Point getboxmax() const;

    // I/O

    /*!
    * @brief Form's display
    *
    * @return Corresponding string
    *
    */
    std::string write() const;

    // keep old squares
    /*!
    * @brief Form reading
    *
    * Read a string that save form's values.
    *
    */
    void read(const std::string&);

private:
    size_t size;            /*!< Form size */
    size_t capacity;        /*!< Form capacity */
    Point *squares;         /*!< Part of the form */
    Point boxmin;           /*!< Minimal bounding box */
    Point boxmax;           /*!<  Maximal bounding box */

    /*!
    * @brief Resize form capacity
    *
    * Change form capacity in function of the current size.
    *
    */
    void resize();
};

#endif // FORM_H_INCLUDED
