template<typename Type>
const Type& History<Type>::current() const
{
    return *current_state;
}

template<typename Type>
const Type& History<Type>::previous()
{
    if(current_state == history.begin()) return *current_state;
    else return *--current_state;
}

template<typename Type>
const Type& History<Type>::next()
{
    if(current_state == --history.end()) return *current_state;
    else return *++current_state;
}

template<typename Type>
void History<Type>::add(const Type &new_state)
{
    if(history.empty()) {
        history.push_back(new_state);
    } else {
        // erase everything past current state
        history.erase(++current_state, history.end());
        history.push_back(new_state);
    }
    // after add(), current_state is last in the history
    current_state = --history.end();
}

template<typename Type>
const std::list<Type>& History<Type>::gethistory() const
{
    return history;
}

template<typename Type>
typename std::list<Type>::const_iterator& History<Type>::getiterator() const
{
    return current_state;
}
