#ifndef HISTORY_H_INCLUDED
#define HISTORY_H_INCLUDED

#include <list>

template<typename Type>
class History
{
public:
    History() : current_state(history.begin()) {};

    // set history state to current/previous/next state and return it
    // all three are invalid if history is empty (add was never called)
    // previous and next will stay on current state if  history begining / end
    // is reached
    const Type& current() const;
    const Type& previous();
    const Type& next();

    // add in history after current state
    // Everything after current state is erased
    void add(const Type&);

    // full read-only access to history
    const std::list<Type>& gethistory() const;
    typename std::list<Type>::const_iterator& getiterator() const;


    bool empty() { return history.empty(); };

    // reset to the same state as just after construction
    void clear() { history.clear(); current_state = history.begin(); };

private:
    std::list<Type> history;
    typename std::list<Type>::iterator current_state;
};

#include "history.tcc"

#endif // HISTORY_H_INCLUDED
