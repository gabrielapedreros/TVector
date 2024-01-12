//Gabriela Pedreros - gp21j - COP4530 - section 6
//Template vector class and iterator class 
    //Iterator over a container traversal
//Make a new file, tvector.hpp, to implement functions declared in tvector.h
#include <iostream>                     //for input and output 
#include <utility>                      //for swap() and move()
#include <string>
using std::ostream;
using std::cout;

//DO NOT use container classes defined in STL
//DO use C++ libraries like I/O and string

//Make a makefile which has the tag "-std=c++1" and files tvector.h, tvector.cpp, driver.cpp. Driver will be compiled into an executable called proj1.x.
//Write multiple test cases. 
//Debug until result provided in driver_output.txt are outputted

//TAR the tvector.hpp and Makefile into a single tar archive and submit. Format: pedreros_gabriela_p1.tar

//Updating array size, double it 
//Clean up DMA in appropriate places and leave no memory leaks 

//* Im confused about the dummy- used for error checking, for empty containers, return reference to the dummy, depends on declaration 

//Do i do TVector<T> or just TVector ?
template<typename T>
TVector<T>::TVector()
{ //make an empty vector(no data elements), capacity = SPARECAPACITY
//cout << "\nIn default constructor.\n";
    size = 0;                           //empty vector, no data elements
    capacity = SPARECAPACITY;           //default capacity 
    array = new T[capacity];            //starting allocation 
    dummy = T();                        //initialize dummy to default T value
}

template<typename T>
TVector<T>::TVector(T val, int num)
{ //vector containing num copies of data element 'val', capacity = what is needed for stored data + SPACECAPACITY
//cout << "\nIn 2 param constructor.\n";
    size = num;                         //set size equal to second int parameter passed
    capacity = SPARECAPACITY + num;     //set capacity equal to SPARECAPACITY + size
    array = new T[capacity];            //set array type T with size capactiy 
    for(int i = 0; i < size; i++)
    {
        array[i] = val;                 //set each element in the array equal to the first
    }                                   //parameter passed
}

template<typename T>   
void TVector<T>::Clear() 
{ //clear out the vector so it represents an empty container (no data elements)
//cout << "\nIn Clear() function.\n"; 
    //old code:
    // int s = size;
    // dummy;
    // for(int i = 0; i < s; i++)          //go through the array and
    // {
    //     array[i] = array[i+1];          //set element equal to the element before it and 
    //     size = size - 1;                //decrease the size after element values change     
    // }   
    //fixing this function (1/10/24)
    size = 0;
}

//big five
template<typename T>
TVector<T>::~TVector() 
{ //destructor- clean up, no memory leaks 
//cout << "\nIn Destructor function\n";
    if(array != 0)                  //if array is pointing to data and not null/zero
    {
        delete [] array;            //delete data and open up memory 
    }
    array = nullptr;            //point pointer to nothing 
}

template<typename T>
TVector<T>::TVector(const TVector<T>& v)
{ //copy constructor- deep copy
//cout << "\nIn copy constructor function\n";
    //set variable equal to values from the object passed in the parameter
    capacity = v.capacity;
    size = v.size;
    dummy = v.dummy;
    array = new T[capacity];
    for(int i = 0; i < size; i++)   //go through array and set array equal to 
    {                               //array of obj passed in parameter
        array[i] = v.array[i];
    }
}
    
template<typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& v)
{ //copy assignment operator- deep copy 
//cout << "\nIn copy assignment operator function\n";
    if(this != &v)                   //if addresses are not the same
    {
        delete [] array;             //clean up old array
        size = v.size;
        capacity = v.capacity;       //set values equal to calling obj
        dummy = v.dummy;
        array = new T[capacity];     //allocate new space with new size
        for(int i = 0; i < size; i++)//go through array and set elements of array
        {
            array[i] = v.array[i];   //equal to obj passed
        }
    }
    return *this;                        //return calling obj
    /*could also use swap*/
}

template<typename T>
TVector<T>::TVector(TVector<T> && v)
{ //move constructor - constructor with standard move semantics
//cout << "\nIn move constructor function\n";
    capacity = v.capacity;
    size = v.size;
    array = v.array;                //steal data from pointer v
    //destroy v
    v.array = nullptr;              //null out pointer v so v's destructor will not delete array
    v.capacity = v.size = 0;        //null v values
    dummy = v.dummy;
}

template<typename T>
TVector<T>& TVector<T>::operator=(TVector<T> && v)
{ //move assignment operator- assignment with standard move semantics
    //member by member swap, exchange pointer instead of pointee 
//cout << "\nIn move assignment operator function\n";
    std::swap(capacity, v.capacity);//swaps values of capacity and the capacity of object passed in parameter
    std::swap(size, v.size);        //swaps values of size and the size of object passed in parameter
    std::swap(array, v.array);      //swaps values of array and the array of object passed in parameter
    std::swap(dummy,v.dummy);
    //dummy
    return *this;                   //*this is obj, return reference to obj
}

//accessors
template<typename T>
bool TVector<T>::IsEmpty() const
{ //retuns true if container is empty, false otherwise
//cout << "\nIn IsEmpty() function\n";
    //is size = 0?
    if(size == 0)                  //if array is empty 
    {
        return true;        
    }
    else
    {
        return false;
    }
}

template<typename T>
int TVector<T>::GetSize() const
{ //returns the size of container, number of data elements
//cout <<"\nIn GetSize() function\n";
    return size;
    //return dummy when empty
}

template<typename T>
T& TVector<T>::GetFirst() const
{ //returns first data element by reference, use dummy when empty
//cout << "\nIn GetFirst() function\n";
    /*if statement if empty, use dummy*/
    //old code:
    //return array[0];
    //new code (1/10)
    if(size>0)
    {
        return array[0];
    }
    else{
        return dummy;
    }
}

template<typename T>
T& TVector<T>::GetLast() const
{ //returns last data element by reference, use dummy when empty
//cout << "\nIn GetLast() function\n";
    /*if statement if empty use dummy*/
    //old code
    // return array[size - 1];
    //new code (1/10)
    if(size>0)
    {
        return array[size-1];
    }
    else{
        return dummy;
    }
}

//endpoint insert/removes
template<typename T>
void TVector<T>::InsertBack(const T& d)
{
    //insert the data(param) as the last item in container
    //cout <<"\nIn InsertBack one param function\n";
    //from rec
    //cout << "in insert back \n";
    if (size == capacity)
    {
        //cout << "if size too big\n";
        //grow capacity 
    //change what code i am using (1/10)
        SetCapacity((capacity * 2) + 2);
        //used this before: capacity = (capacity*2)+2;
    }
    /*wouldnt it be size? not size++ test this*/
    //cout << "inserting value\n";
    array[size++] = d;              //set d equal to last element
    //cout << "value inserted\n";
}

template<typename T>
void TVector<T>::RemoveBack()
{
    //remove the last element in container, if empty leave it empty 
    //cout << "\nIn RemoveBack() function\n";
    if (size > 0)                   //if not empty
    {
        // array[size - 1] = array [size];//set second to last value equal to last value
        size = size - 1;            //decrease size by one
    }
}

//iterator retrieval 
template<typename T>
TVectorIterator<T> TVector<T>::GetIterator() const
{
    //create and return positioned on the first data item on vector. If empty return default iterator 
    //cout << "\nIn GetIterator() function\n";
    //from rec
    TVectorIterator<T> it;          //create TVectorIterator object
    if(size > 0)                    //if array is not empty
    {
        it.ptr = array;             //set iterator variables equal to array variables
        it.index = 0;
        it.vsize = size;            //set index to the first element in the array
    }
    return it;                      //return iterator 
}

template<typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const
{
    //create and return iterator that is positioned on last data
    //item. If empty return default iterator   
    //cout << "\nIn GetIteratorEnd() function\n";
    TVectorIterator<T> it;          //reate TVectorIterator object
    if(size > 0)                    
    {
        it.ptr =array+size-1;
        // it.ptr = array;
        // it.vsize = size;
        // it.index = size -1;         //the index is equal to the last element 
    }
    return it;
}
    
template<typename T>
void TVector<T>::SetCapacity(unsigned int c)
{
    T* temp = new T[c];
    //cout << "\nIn SetCapacity one param function\n";
    for(int i = 0; i < size; i++)
    {
        temp[i] = array[i];
    }
    delete [] array;
    array = temp;
    capacity = c;
    if(c <size)                     //shrink 
    {
        //cout << "if c less than size\n";
        size = capacity;
    }
}  


template<typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d)
{
    /*
            for(int i = size - 1; i>0; i--)
            {
                array[i] = array[i-1];
                cout <<array[i] << " ";
            }
            array[0] = 2;
            cout << array[0];
    */
    int position = pos.index;
    if(size == capacity)
    {
        SetCapacity((capacity*2)+2);
    }
    // int i = size - 1;

    for(int i= size; i>position; i--)
    {
        array[i] = array[i-1];
        //mcout << array[i+1] << " \n";
    }
    array[position] = d;
    //cout << array[i+1] << "\n";
    //cout << "array done\n";

    size ++;

    pos.index = position;
    pos.vsize = size;
    pos.ptr = array;

    return pos;
    //return TVectorIterator<T>(array, pos.d, size);
}
    
template<typename T>    
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos)
{
    //remove data item given by iterator and return iterator to next data item
    //from recitation 
    //cout <<"\nIn Remove one param function\n";
    if(size == 0 || pos.index >= size || pos.index < 0) //if array is empty or index outside of array range
    {                                                   //do not remove 
        TVectorIterator<T> returnPos;                       //create return iterator 
        return returnPos;               //return default iterator 
    }
    for(int i = pos.index; i<size-1; i++)//from index to size
    {
        array[i] = array[i+1];          //remove data item given by iterator
    }
    size--;                         //decrease aray size by one
    TVectorIterator<T> returnPos = pos;   //create return iterator 
    returnPos.vsize = size;         //update size of returnPos  
    return returnPos;               //return iterator 
    //change?
    // if (pos.index >= 0 && pos.index < size) {
    //     for (int i = pos.index; i < size - 1; i++) {
    //         array[i] = array[i + 1];
    //     }
    //     size--;
    // }
    // return TVectorIterator<T>(array, pos.index, size);
}

template<typename T>    
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2)
{
    cout <<"\nIn Remove two param function\n";
    int start = pos1.index;
    int end = pos2.index;
    if(size != 0)
    {
        TVectorIterator<T> returnPos;
        //remove data items in range from pos1 to up to and not including pos2
        //return iterator to next data item, after deleted items
        for(int i = 0; i < (end-start); i++)
        {
            for(int i = start; i < size; i++)
            {
            array[i] = array[i+1];
            //returnPos.index = size;
            }
            size = size - 1;
            //returnPos.Next();
        }
        returnPos.vsize = size;
        return returnPos;
    }
    else if(end < start)
    {
        //if pos2 < pos1, dont do anything and return first iterator (pos1)
        return pos1;
    }
    else
    {
        //if vector is empty, nothing to delete - if size !=0
        //return default
        TVectorIterator<T> returnPos;
        returnPos;
    }
    //change
    // if (pos1.index < pos2.index && pos1.index >= 0 && pos2.index <= size) {
    //     int count = pos2.index - pos1.index;
    //     for (int i = pos1.index; i < size - count; i++) {
    //         array[i] = array[i + count];
    //     }
    //     size -= count;
    // }
    // return TVectorIterator<T>(array, pos1.index, size);
}

template<typename T>    
void TVector<T>::Print(std::ostream& os , char delim) const
{
    //from rec
    //os << "\nIn Print two param function\n";
    if(size==0)
    {
        os << "Nothing to print. Size is 0." << std::endl;
    }
    //os << array[0];
    for(int i = 0; i < size; i++)
    {
        os << delim << array [i];
    }
}
     
//stand alone 
template<typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2)
{
    //return TVector obj that is the result of concatenating two TVector
    //obj together  - in param order
    TVector<T> v = t1;
    int max = t1.GetSize() + t2.GetSize();
    cout << max << "\n";
    //cout << t1.GetSize() << " " <<  t2.GetSize() << " ";
    v.SetCapacity(max);

    if(!t2.IsEmpty())
    {
        TVectorIterator<T> itr = t2.GetIterator();
        v.InsertBack(itr.GetData());
        while(itr.HasNext())
        {
            itr.Next();
            v.InsertBack(itr.GetData());
        }
    }
    /*
    TVectorIterator<T> itr = t2.GetIterator();
    for(int i = 0; i < t2.GetSize(); i++)
    {
    //cout << "in loop\n";
    v.InsertBack(itr.GetData());
    itr.Next();
    }
    */   
    return v;
}

//TVectorIterator class
template<typename T>
TVectorIterator<T>::TVectorIterator()
{
    //default const
    // cout << "\nIn Iterator constructor\n";
    ptr = nullptr;                       //store null pointer internally
    vsize = 0;                           //referring to empty vector 
    index = 0;
}

template<typename T>
bool TVectorIterator<T>::HasNext() const
{
    //cout << "\nIn Iterator HasNext() function\n";
    //if(index + 1 < arr.size)            //if there is another data element after current one
    if(index + 1 < vsize)
    {
        return true;                    //return true
    }
    else
    {
        return false;
    }
}

template<typename T>
bool TVectorIterator<T>::HasPrevious() const
{
    //cout <<"\nIn Iterator HasPrevious() function\n";
    //if(index - 1 < arr.size && index - 1 > 0)//if there is a data element before current data element
    if(index - 1 >= 0 )
    {
        return true;                        //return true
    }
    else
    {
        return false;
    }
}

template<typename T>
TVectorIterator<T> TVectorIterator<T>::Next()
{
        // TVectorIterator<T> next;
        // //cout << "\nIn Iterator Next() function\n";
        // if(ptr != nullptr && HasNext() == true)                      //if ptr is not storing nullptr
        // {   
        //     if(index + 1 < vsize )               //and if index + 1 is less than vsize
        //     {
        //         ptr[index++];                   //move iterator to index + 1
        //         next.vsize = vsize;
        //         //ptr++
        //         next.ptr++;
        //         next.index = index + 1;
        //         return next;                    //return ptr
        //     }
        //     else                                //if index + 1 is equal to or greater than vsize
        //     {
        //         ptr[index];                     //iterator stays in current position 
        //         next.vsize = vsize;
        //         next.index = index;
        //         return next;                     //return iterator
        //     }
        // }

    if (index < vsize - 1) {
    index++; // Move to the next element
    }
    return *this;
}

template<typename T>
TVectorIterator<T> TVectorIterator<T>::Previous()
{
        //cout << "\nIn Iterator Previous() function\n";
        // TVectorIterator<T> prev;
        // if(ptr != nullptr)                      //if ptr is not storing nullptr
        // {
        //     if(index - 1 > 0)                   //if index - 1 is bigger than vsize and 0
        //     {
        //         ptr[index--];                    //update iterator to index - 1
        //         prev.vsize = vsize;
        //         prev.index = index -1;
        //         return prev;                      //return iterator
        //     }
        //     else                                //if index - 1 =< 0
        //     {
        //         ptr[index];                     //keep current index for iterator
        //         prev.vsize = vsize;
        //         prev.index = index;
        //         return prev;                     //return iterator
        //     }
        // }
    if (index > 0) {
        index--; // Move to the previous element
    }
    return *this;
}

template<typename T>
T& TVectorIterator<T>::GetData() const 
{
    TVector<T> temp;
    if(index >= 0 && index <vsize)
    {
        //cout <<"getting data\n";
        return ptr[index];
    }
    // return temp.dummy;
    // throw std::out_of_range("Iterator is out of range");
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
