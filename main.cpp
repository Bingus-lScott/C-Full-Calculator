#include <iostream>

using std::cout;
using std::string;

#pragma region Function Prototypes

string getUserExpression ();

#pragma endregion

#pragma region Classes

class dynamicCharArray
{
private:
            // An array actually holding data, stored as a pointer
            char *array = NULL;
            // The actual size of the capacity being used
            int size;
            // The total capacity of the array (new or current)
            int capacity;
public:
            // Default constructor
            dynamicCharArray ()
            {
                        capacity = 1;
                        array = new char[capacity];
                        size = 0;
            }

            // Parameter input constructor
            dynamicCharArray (int inputtedCapacity)
            {
                        // same as this.capacity, but its in c++ language
                        this->capacity = inputtedCapacity;
                        array = new char[capacity];
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
                        char *tempArray = new char[capacity];

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
                        
                        char *tempArray = new char[capacity];

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
            void pushBack (char character)
            {
                        if (size == capacity)
                        {
                                    growArray (1);
                        }
                        size++;

                        array[size - 1] = character;
            }

            // Deletes the last element of the array
            void popBack ()
            {
                        array[size - 1] = ' ';
                        size--;
            }

            // Inserts the value at the index provided, if the capacity of the array is smaller than index then it will pushBack()
            void insertAt (int index, char value)
            {   
                        if (index > capacity - 1)
                        {           
                                    pushBack (value);
                                    return;
                        }
                        
                        if (index == size)
                        {
                                    pushBack(value);
                                    return;
                        }
                       
                        if (size == capacity)
                        {
                                    growArray (1);
                        }
                        size++;

                        char *tempArray = new char[capacity];

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
                        char *tempArray = new char[capacity];

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
                        cout << "Size: " << getSize () << " Capacity: " << getCapacity () << "\n";
            }
};

#pragma endregion

int main () 
{
            //string expression = getUserExpression ();

            dynamicCharArray chars;

            chars.pushBack ('1');
            chars.pushBack ('2');
            chars.pushBack ('3');
            chars.printValues ();

            chars.insertAt (3, 'a');
            chars.printValues ();

            chars.deleteAt (5);
            chars.printValues ();

            chars.growArray (10);
            cout << "\n" << chars.getCapacity () << "\n";
            chars.shrinkArray (5);
            cout << "\n" << chars.getCapacity () << "\n";

            chars.shrinkArray (6);
            chars.growArray (1);
            chars.printValues ();

            
            return 0;
}


#pragma region Function Definitions

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

#pragma endregion