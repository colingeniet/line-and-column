/* !
 * @brief History class template
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * History class model.
 *
 */

#ifndef HISTORY_H_INCLUDED
#define HISTORY_H_INCLUDED

#include <list>


/*!
 * @brief History class template
 *
 * Basic history implemented as double linked list
 *
 */
template<typename Type>
class History
{
public:
    /*!
    * @brief Default constructor
    *
    * Create empty history.
    *
    */
    History() : current_state(history.begin()) {};

    /*!
    * @brief Access current position
    *
    * Invalid if history is empty.
    *
    * @return Current history state.
    */
    const Type& current() const;

    /*!
    * @brief Go backward in history
    *
    * Move one step backward in history. Do nothing if begining was reached.
    * Invalid if history is empty
    *
    * @return New history state.
    */
    const Type& previous();

    /*!
    * @brief Go forward in history
    *
    * Move one step forward in history. Do nothing if end was reached.
    * Invalid if history is empty
    *
    * @return New history state.
    */
    const Type& next();

    /*!
    * @brief Add new state in history
    *
    * Delete history past current state, add new state at the end.
    * After call, current state will be at the new end.
    *
    * @param new_state ; state to add
    */
    void add(const Type &new_state);

    /*!
    * @brief Get full history
    *
    * Read only access to full history
    *
    * @return The history as a list
    */
    const std::list<Type>& gethistory() const;

    /*!
    * @brief Get current state
    *
    * Read only access to current state.
    *
    * @return The current state as a const_iterator
    */
    typename std::list<Type>::const_iterator& getiterator() const;

    /*!
    * @brief Test for empty history
    *
    * History is empty iff no call to add() was done since construction or last call to clear().
    *
    * @return true if history is empty, else false
    */
    bool empty() { return history.empty(); };

    /*!
    * @brief Clear history
    *
    * Reset to the same state as after construction
    */
    void clear() { history.clear(); current_state = history.begin(); };

private:
    std::list<Type> history;                            /*!< History */
    typename std::list<Type>::iterator current_state;   /*!< Position in history */
};

#include "history.tcc"

#endif // HISTORY_H_INCLUDED
