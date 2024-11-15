**1.** The `add(...)` function and `operator+(...)` function are very similar, but the
function adds an exterior fraction to the current object, whereas the operator
overload creates a new fraction, and returns that as a value. The operator overload
is also more natural to use.

**2.** Because the class manages no memory, the default destructor works perfectly.
