#include <iostream>

using std::cout;
using std::string;

#pragma region Classes

template <typename T> class dynamicArray
{
private:
            // An array actually holding data, stored as a pointer
            T *array = NULL;
            // The actual size of the capacity being used
            int size;
            // The total capacity of the array (new or current)
            int capacity;

public:
            // Default constructor
            dynamicArray<T> ()
            {
                        capacity = 1;
                        array = new T[capacity];
                        size = 0;
            }

            // Parameter input constructor
            dynamicArray<T> (int inputtedCapacity)
            {
                        // same as this.capacity, but its in c++ language
                        this->capacity = inputtedCapacity;
                        array = new T[capacity];
                        size = 0;
            }

            // Returns the used slots of the total capacity of the array 
            int getSize ()
            {
                        return size;
            }

            // Returns the total capacity of the array
            int getCapacity ()
            {
                        return capacity;
            }

            // Adds the specified number of slots to the capacity
            void growArray (int addCapacity) 
            {
                        capacity += addCapacity;
                        T *tempArray = new T[capacity];

                        for (int value = 0; value < size; ++value)
                        {
                                    tempArray[value] = array[value];
                        }

                        // Delete the old array's data
                        delete array;

                        // Assign the newly sized array to the pointer
                        array = tempArray;  
            }

            // Shrinks array capacity by specificed number of slots. Will delete data if you delete into the array's size
            void shrinkArray (int removeCapacity)
            {
                        capacity -= removeCapacity;

                        if (capacity < size)
                        {
                                    size = removeCapacity - capacity;
                        }
                        
                        T *tempArray = new T[capacity];

                        for (int value = 0; value < size; ++value)
                        {
                                    tempArray[value] = array[value];
                        }

                        // Delete the old array's data
                        delete array;

                        // Assign the newly sized array to the pointer
                        array = tempArray;
            }

            // Adds an element to the back of the array
            void pushBack (int value)
            {
                        if (size == capacity)
                        {
                                    growArray(1);
                        }
                        size++;

                        array[size - 1] = value;
            }

            // Deletes the last element of the array
            void popBack ()
            {
                        array[size - 1] = ' ';
                        size--;
            }

            // Inserts the value at the index provided, if the capacity of the array is smaller than index then it will pushBack()
            void insertAt (int index, int value)
            {   
                        if (index > capacity - 1)
                        {           
                                    pushBack(value);
                                    return;
                        }
                        
                        if (index == size)
                        {
                                    pushBack(value);
                                    return;
                        }
                       
                        if (size == capacity)
                        {
                                    growArray(1);
                        }
                        size++;

                        T *tempArray = new T[capacity];

                        // This block can definitely be simplified. Look into that in the future
                        for (int front = 0; front < index; ++front)
                        {
                                    tempArray[front] = array[front];
                        }
                        tempArray[index] = value;

                        for (int back = index + 1; back < size ; ++back)
                        {
                                    tempArray[back] = array[back - 1];
                        }

                        delete array;

                        array = tempArray;
            }

            // Deletes the value at the specified index, if index > capacity it will popBack (through a nice loophole)
            void deleteAt (int index) 
            {
                        T *tempArray = new T[capacity];

                        for (int front = 0; front < index; ++front)
                        {
                                    tempArray[front] = array[front];
                        }
                        
                        // Pops back if index > capacity
                        for (int back = index; back < size; ++back) 
                        {
                                    tempArray[back] = array[back + 1];
                        }
                        size--;

                        delete array;

                        array = tempArray;  
            }

            // Prints all values of the array to the console
            void printValues ()
            {
                        for (int value = 0; value < size; ++value)
                        {
                                    cout << "Position #" << value << ": " << array[value] << "\n";          
                        }
                        cout << "Size: " << getSize() << " Capacity: " << getCapacity() << "\n";
            }

            // Searches for the first occurance of the specified key, returns its index, if not found returns -1
            int search (int key)
            {
                        for (int iterator = 0; iterator < size; ++iterator)
                        {
                                    if(array[iterator] == key)
                                    {
                                                return iterator;
                                    } 
                        }

                        return -1;
            }

            int atIndex (int index)
            {
                        return array[index];
            }

            void deallocate ()
            {
                        delete array;
                        size = 0;
                        capacity = 1;
            }
};

#pragma endregion

#pragma region Function Prototypes

string getUserExpression ();
void removeWhitespace (dynamicArray<char> &characters);

dynamicArray<char> searchAll(dynamicArray<char> array, int key);
dynamicArray<int> searchAll(dynamicArray<int> array, char key);

#pragma endregion

int main() 
{
            string expression = getUserExpression();

            dynamicArray<char> chars;
            for (char character : expression)
            {
                        chars.pushBack(character);
            }

            removeWhitespace(chars);

            chars.printValues();

            return 0;
}


#pragma region Function Definitions

// Returns all indexes in a dynamic int array
dynamicArray<int> searchAll (dynamicArray<char> array, char key)
{
            dynamicArray<int> indexes;

            for (int iterator = 0; iterator < array.getSize(); ++iterator)
            {
                        if(array.atIndex(iterator) == key)
                        {
                                    indexes.pushBack(iterator);
                        } 
            }

            return indexes;
}

dynamicArray<int> searchAll (dynamicArray<int> array, int key)
{
            dynamicArray<int> indexes;

            for (int iterator = 0; iterator < array.getSize(); ++iterator)
             {
                        if (array.atIndex(iterator) == key)
                        {
                                    indexes.pushBack(iterator);
                        } 
            }

            return indexes;
}


// Types a greeting to the console and requests the input of a mathmatical expression. Returns the expression
string getUserExpression ()
{
            const string USER_GREETING = "You may use * to multiply, / to divide, + to add, - to subtract \nas well as ^n to exponent";
            string expression;

            cout << USER_GREETING << std::endl;
            cout << "Type your mathmatical expression: ";

            std::getline(std::cin, expression);

            return expression;
}

// Removes all spaces, tabs, and newlines from the inputted expression
void removeWhitespace (dynamicArray<char> &expression)
{
            dynamicArray<int> whitespaceIndexes = searchAll(expression, ' ');

            for (int index = 0; index < whitespaceIndexes.getSize(); ++index)
            {
                        expression.deleteAt(whitespaceIndexes.atIndex(index));
            }

            whitespaceIndexes.deallocate();
}
#pragma endregion