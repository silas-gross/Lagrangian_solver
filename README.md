## Forum
<Theo> So, focusing on the point defined function.  Maybe it would be more effective to recall points on demand from a "cache" hashmap instead of storing a vector of 
points p where p[x] = f(x).  A point (x, f(x)) could be requested from the function, and the hashmap cache could be checked quickly for x as a key.  If present, the cached
value could be returned, otherwise the value would be calculated, the point would be cached for the future, and then returned.  This could also allow for some potential optimization 
using multithreading and predicting other points of interest, although this would prevent a significant difficulty in managing the communal cache.  This approach allows us to get 
around float indices and allows for sparse defintions for simpler functions, saving a lot of memory.
