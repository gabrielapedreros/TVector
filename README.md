# TVector
Templated vector class with iterator class

# Requirements for project
- Do not use any container classes defined in STL
- Create a Makefile that compiles the driver.cpp file into executable 'proj1.x'
- Write test cases (driver.cpp test case,... to screen out crashing when running proj1.x)

# Important information
- Define all of the functions for these classes in the file tvector.hpp.
- Always make sure there is ROOM in the array before inserting a new item. If you ever try to insert data, and the array is full (to capacity), then increase the capacity by doubling it.
- Do NOT change any of the prototypes or member data declarations in the tvector.h file at all. All current declarations have the intended prototypes, and they will need to work with my main programs.
- Clean up dynamic memory in appropriate places and do not leave any memory leaks.

# Tvector class template
- The member data of this class consists of a pointer to a dynamically managed array, along with tracking variables for the capacity and the size. Note that the capacity refers to how much space is currently allocated, and size refers to how many data items are currently stored.
- There is a dummy variable of type T that can be used for error-checking situations. Specifically, whenever a function is to return a stored data item but the container is empty, return (a reference to) the dummy object. Whether you should return the dummy object itself or a reference to it depends on how the function is declared.
- A static constant called SPARECAPACITY is in the member data so that it can be used to add some extra capacity when constructing vector objects.
  
# Iterators
- The small class called TVectorIterator is a helper class that can be used in conjunction with the vector class. This is a common feature used in container classes like this. The purpose of an iterator is to provide a common and non-implementation-specific way of traversing a container, so that mulitple containers could potentially use common algorithms (like sorting and searching functions, for example).
- The TVectorIterator class has three member data variables -- a pointer to the data to which it currently refers, the size of the associated vector, and the index from the associated vector. We need data variables for size and index, because the array itself is not inside an iterator object. The pointer will be used to access the data (i.e. it will be needed by the GetData function).
- The iterator is not intended to be built as a stand-alone item, but rather is created and returned BY member functions in the TVector class, so that it is associated with the vector.
  
# Output given driver.cpp
v1 size is: 10
v1 = 0 3 6 9 12 15 18 21 24 27

v1 size is: 18
v1 = 400 350 300 250 200 150 100 50 0 3 6 9 12 15 18 21 24 27

v1 size is: 17
v1 = 400 350 300 250 200 150 100 50 0 3 6 9 12 15 18 21 24

v1 size is: 16
v1 = 400 350 300 250 200 150 100 50 0 3 6 9 12 15 18 21

v1 size is: 15
v1 = 350 300 250 200 150 100 50 0 3 6 9 12 15 18 21

v1 size is: 14
v1 = 300 250 200 150 100 50 0 3 6 9 12 15 18 21

Testing some inserts with an iterator

v1 size is: 17
v1 = 999 300 888 250 200 777 150 100 50 0 3 6 9 12 15 18 21

Testing some removes (with iterator)

v1 size is: 16
v1 = 999 300 888 250 200 777 150 50 0 3 6 9 12 15 18 21

v1 size is: 15
v1 = 999 300 250 200 777 150 50 0 3 6 9 12 15 18 21

Building a new list
v2 size is: 10
v2 = 1 4 7 10 13 16 19 22 25 28

Testing operator+ overload
v3 size is: 22
v3 = 999 300 250 200 777 150 50 0 3 6 9 12 15 18 21 100 100 100 100 100 100 100

v4 size is: 25
v4 = 1 4 7 10 13 16 19 22 25 28 999 300 250 200 777 150 50 0 3 6 9 12 15 18 21

Testing a call to the 2-param delete
itr1 is attached to: 7
itr2 is attached to: 25
Calling:  v4.Remove(itr1, itr2);
v4 size is: 19
v4 = 1 4 25 28 999 300 250 200 777 150 50 0 3 6 9 12 15 18 21
