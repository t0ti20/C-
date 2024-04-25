/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: Circular_Buffer.hpp
 *  Date: November 30, 2024
 *  Description: This Is Default Test File For CPP Generator
 *  Class Name:  Circular_Buffer
 *  Namespace:  Data_Structure
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include <array>
#include <cstddef>
#include <stdexcept>
#include <initializer_list>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
namespace Data_Structure
{
/*****************************************
---------    Circular_Buffer     ---------
*****************************************/
template <typename Type=int,size_t TOTAL_SIZE=10>
class Circular_Buffer
{
private:
/*****************************************
---------    Buffer_Iterator     ---------
*****************************************/
struct Buffer_Iterator
{
using difference_type=std::ptrdiff_t;
using value_type=Type;
using pointer=Type*;
using reference=Type&;
using iterator_category=std::forward_iterator_tag;
/****************************************************************************************************
* Constructor       : Buffer_Iterator
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Constructs a Buffer_Iterator object.
* Parameters (in)   : 
*   - Buffer        : Pointer to the buffer "Data Array".
*   - Current_Index : Current index of the iterator to start from.
*   - Total_Elements: Total elements in the buffer should I iterate through.
* Notes             : None
*****************************************************************************************************/
constexpr Buffer_Iterator(pointer Buffer,size_t Current_Index,size_t Total_Elements);
/****************************************************************************************************
* Function Name     : operator*
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Dereferences the iterator, returning a reference to the current element.
* Parameters (in)   : None
* Parameters (out)  : None
* Return value      : reference - Reference to the current element in the buffer.
* Notes             : None
*****************************************************************************************************/
constexpr reference operator*();
/****************************************************************************************************
* Function Name     : operator!=
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Inequality comparison operator for Buffer_Iterator objects.
* Parameters (in)   : 
*   - Object        : Another Buffer_Iterator object to compare with.
* Parameters (out)  : None
* Return value      : bool - True if the iterators are unequal, false otherwise.
* Notes             : Returns true if the iterators have different current indices or total elements.
*****************************************************************************************************/
constexpr bool operator!=(const Buffer_Iterator& Object);
/****************************************************************************************************
* Function Name     : operator==
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Equality comparison operator for Buffer_Iterator objects.
* Parameters (in)   : 
*   - Object        : Another Buffer_Iterator object to compare with.
* Parameters (out)  : None
* Return value      : bool - True if the iterators are equal, false otherwise.
* Notes             : None
*****************************************************************************************************/
constexpr bool operator==(const Buffer_Iterator& Object);
/****************************************************************************************************
* Function Name     : operator++
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Pre-increment operator for Buffer_Iterator objects.
* Parameters (in)   : None
* Parameters (out)  : None
* Return value      : Buffer_Iterator - The iterator after being incremented.
* Notes             : Increments the current index and the total elements in the iterator.
*****************************************************************************************************/
constexpr Buffer_Iterator operator++();
private:
    /* Current Index Of Iterator */
    size_t m_Current_Index{};
    /* Total Elements Iterator Already Count */
    size_t m_Total_Elements{};
    /* Array Base Containing ELements */
    pointer m_Buffer{};
};
public:
/****************************************************************************************************
* Constructor Name : Circular_Buffer (Initializer List)
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Constructor for the Circular_Buffer class that initializes the buffer with elements
*                    from an initializer list.
* Parameters (in)  : Values - An initializer list of elements to initialize the buffer.
* Parameters (out) : None
* Return value     : None
* Notes            : Initializes member variables and pushes elements from the initializer list into
*                    the buffer. Throws a runtime error if the size of the initializer list exceeds
*                    the total size of the buffer.
*****************************************************************************************************/
Circular_Buffer(const std::initializer_list<Type>& Values);
/****************************************************************************************************
* Constructor Name : Circular_Buffer
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Default constructor for the Circular_Buffer class.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : None
* Notes            : Initializes member variables to their default values.
*****************************************************************************************************/
Circular_Buffer();
/****************************************************************************************************
* Function Name    : ~Circular_Buffer (Destructor)
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Destructor for the Circular_Buffer class.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : None
* Notes            : Does not perform any specific cleanup as the buffer does not allocate dynamic
*                    memory.
*****************************************************************************************************/
~Circular_Buffer();
/****************************************************************************************************
* Function Name    : operator==
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Overloaded equality operator for Circular_Buffer.
* Parameters (in)  : Array - An array to compare with the Circular_Buffer data.
* Parameters (out) : None
* Return value     : bool - True if the arrays are equal, false otherwise.
*****************************************************************************************************/
bool operator ==(std::array<Type,TOTAL_SIZE> Array)const;
/****************************************************************************************************
* Function Name    : operator==
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Overloaded equality operator for comparing two circular buffers.
* Parameters (in)  : Object - The circular buffer to compare with.
* Parameters (out) : None
* Return value     : bool - True if the circular buffers are equal, false otherwise.
* Notes            : None
*****************************************************************************************************/
bool operator==(const Circular_Buffer& Object)const;
/****************************************************************************************************
* Function Name    : Head
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Returns a reference to the element at the head of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : const Type& - Reference to the element at the head of the buffer.
* Notes            : None
*****************************************************************************************************/
const Type& Head(void)const;
/****************************************************************************************************
* Function Name    : Tail
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Returns a reference to the element at the tail of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : const Type& - Reference to the element at the tail of the buffer.
* Notes            : None
*****************************************************************************************************/
const Type& Tail(void)const;
/****************************************************************************************************
* Function Name    : Push
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Pushes a new element into the circular buffer.
* Parameters (in)  : Element - The element to be pushed into the buffer.
* Parameters (out) : None
* Return value     : None
* Notes            : - Appends the new element to the buffer.
*                    - Adjusts the head and tail indices if necessary to handle overflow.
*****************************************************************************************************/
void Push(const Type& Element);
/****************************************************************************************************
* Function Name    : Pop
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Removes and returns the element from the head of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : Type - The element removed from the buffer.
* Notes            : - Returns a default zero-initialized value if the buffer is empty.
*                    - Throws a runtime error if the buffer is empty.
*****************************************************************************************************/
Type Pop(void);
/****************************************************************************************************
* Function Name    : Size
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Returns the current size of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : size_t - The current size of the buffer.
* Notes            : None
*****************************************************************************************************/
size_t Size(void);
/****************************************************************************************************
* Function Name    : Is_Empty
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Checks if the circular buffer is empty.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : bool - True if the buffer is empty, false otherwise.
* Notes            : None
*****************************************************************************************************/
bool Is_Empty(void);
/****************************************************************************************************
* Function Name    : end
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Returns a constant iterator pointing to the end of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : constexpr Buffer_Iterator - Constant iterator pointing to the end of the buffer.
* Notes            : None
*****************************************************************************************************/
constexpr Buffer_Iterator end() noexcept;
/****************************************************************************************************
* Function Name    : begin
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Returns a constant iterator pointing to the beginning of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : constexpr Buffer_Iterator - Constant iterator pointing to the beginning of the buffer.
* Notes            : None
*****************************************************************************************************/
constexpr Buffer_Iterator begin() noexcept;
private:
    /* Total Size Of Current Elements In Buffer */
    size_t m_Current_Size{};
    /* Index Of Head To Pop From*/
    size_t m_Head_Index{};
    /* Index Of Tain To Push In */
    size_t m_Tail_Index{};
    /* Data Structure Storing Elements */
    std::array<Type,TOTAL_SIZE> m_Data{};
};
/****************************************************************************************************
-----------------------------------------    Definition     -----------------------------------------
****************************************************************************************************/
/*****************************************
---------    Buffer_Iterator     ---------
*****************************************/
/****************************************************************************************************
* Constructor       : Buffer_Iterator
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Constructs a Buffer_Iterator object.
* Parameters (in)   : 
*   - Buffer        : Pointer to the buffer "Data Array".
*   - Current_Index : Current index of the iterator to start from.
*   - Total_Elements: Total elements in the buffer should I iterate through.
* Notes             : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
constexpr Circular_Buffer<Type, TOTAL_SIZE>::Buffer_Iterator::Buffer_Iterator(typename Circular_Buffer<Type, TOTAL_SIZE>::Buffer_Iterator::pointer Buffer,size_t Current_Index,size_t Total_Elements):
m_Buffer(Buffer),m_Total_Elements(Total_Elements),m_Current_Index(Current_Index)
{}
/****************************************************************************************************
* Function Name     : operator*
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Dereferences the iterator, returning a reference to the current element.
* Parameters (in)   : None
* Parameters (out)  : None
* Return value      : reference - Reference to the current element in the buffer.
* Notes             : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
constexpr typename Circular_Buffer<Type, TOTAL_SIZE>::Buffer_Iterator::reference Circular_Buffer<Type, TOTAL_SIZE>::Buffer_Iterator::operator*()
{
    return m_Buffer[m_Current_Index];
}
/****************************************************************************************************
* Function Name     : operator!=
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Inequality comparison operator for Buffer_Iterator objects.
* Parameters (in)   : 
*   - Object        : Another Buffer_Iterator object to compare with.
* Parameters (out)  : None
* Return value      : bool - True if the iterators are unequal, false otherwise.
* Notes             : Returns true if the iterators have different current indices or total elements.
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
constexpr bool Circular_Buffer<Type, TOTAL_SIZE>::Buffer_Iterator::operator!=(const Buffer_Iterator& Object)
{
    /* If The Iterator Looped On All Elements IN The Buffer */
    return (Object.m_Current_Index!=m_Current_Index)||(m_Total_Elements!=Object.m_Total_Elements);
}
/****************************************************************************************************
* Function Name     : operator==
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Equality comparison operator for Buffer_Iterator objects.
* Parameters (in)   : 
*   - Object        : Another Buffer_Iterator object to compare with.
* Parameters (out)  : None
* Return value      : bool - True if the iterators are equal, false otherwise.
* Notes             : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
constexpr bool Circular_Buffer<Type, TOTAL_SIZE>::Buffer_Iterator::operator==(const Buffer_Iterator& Object)
{
    return (Object.m_Current_Index==m_Current_Index)&&(m_Total_Elements==Object.m_Total_Elements);
}
/****************************************************************************************************
* Function Name     : operator++
* Type              : Public
* Class             : Buffer_Iterator
* Namespace         : Data_Structure::Circular_Buffer
* Description       : Pre-increment operator for Buffer_Iterator objects.
* Parameters (in)   : None
* Parameters (out)  : None
* Return value      : Buffer_Iterator - The iterator after being incremented.
* Notes             : Increments the current index and the total elements in the iterator.
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
constexpr typename Circular_Buffer<Type,TOTAL_SIZE>::Buffer_Iterator Circular_Buffer<Type,TOTAL_SIZE>::Buffer_Iterator::operator++()
{
    m_Current_Index=(m_Current_Index+1)%TOTAL_SIZE;
    return Buffer_Iterator{m_Buffer,m_Current_Index,++m_Total_Elements};
}
/*****************************************
---------    Circular_Buffer     ---------
*****************************************/
/****************************************************************************************************
* Constructor Name : Circular_Buffer (Initializer List)
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Constructor for the Circular_Buffer class that initializes the buffer with elements
*                    from an initializer list.
* Parameters (in)  : Values - An initializer list of elements to initialize the buffer.
* Parameters (out) : None
* Return value     : None
* Notes            : Initializes member variables and pushes elements from the initializer list into
*                    the buffer. Throws a runtime error if the size of the initializer list exceeds
*                    the total size of the buffer.
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
Circular_Buffer<Type, TOTAL_SIZE>::Circular_Buffer(const std::initializer_list<Type>& Values):
m_Current_Size{},m_Head_Index{},m_Tail_Index{},m_Data{}
{
    /* Check If Initializer Size Is Valid */
    if(Values.size()<=TOTAL_SIZE)
    {
        /* Push All Elements In Initializer_List */
        for(size_t Counter{};Counter<Values.size();Counter++)
        {
            Push(Values.begin()[Counter]);
        }
    }
    /* Throw Runtime Exception Invalid Initializer_List Size */
    else{throw std::runtime_error("Buffer Initializer Out Of Range");}
}
/****************************************************************************************************
* Constructor Name : Circular_Buffer
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Default constructor for the Circular_Buffer class.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : None
* Notes            : Initializes member variables to their default values.
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
Circular_Buffer<Type, TOTAL_SIZE>::Circular_Buffer():
m_Current_Size{},m_Head_Index{},m_Tail_Index{},m_Data{}
{}
/****************************************************************************************************
* Function Name    : ~Circular_Buffer (Destructor)
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Destructor for the Circular_Buffer class.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : None
* Notes            : Does not perform any specific cleanup as the buffer does not allocate dynamic
*                    memory.
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
Circular_Buffer<Type, TOTAL_SIZE>::~Circular_Buffer()
{}
/****************************************************************************************************
* Function Name    : operator==
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Overloaded equality operator for Circular_Buffer.
* Parameters (in)  : Array - An array to compare with the Circular_Buffer data.
* Parameters (out) : None
* Return value     : bool - True if the arrays are equal, false otherwise.
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
bool Circular_Buffer<Type, TOTAL_SIZE>::operator ==(std::array<Type,TOTAL_SIZE> Array)const
{
    return Array==m_Data;
}
/****************************************************************************************************
* Function Name    : operator==
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Overloaded equality operator for comparing two circular buffers.
* Parameters (in)  : Object - The circular buffer to compare with.
* Parameters (out) : None
* Return value     : bool - True if the circular buffers are equal, false otherwise.
* Notes            : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
bool Circular_Buffer<Type, TOTAL_SIZE>::operator==(const Circular_Buffer& Object)const
{
    return (Object.m_Data==m_Data)&&(Object.m_Current_Size==m_Current_Size)&&(Object.m_Head_Index==m_Head_Index)&&(Object.m_Tail_Index==m_Tail_Index);
}
/****************************************************************************************************
* Function Name    : Head
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Returns a reference to the element at the head of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : const Type& - Reference to the element at the head of the buffer.
* Notes            : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
const Type& Circular_Buffer<Type, TOTAL_SIZE>::Head(void)const
{
    return m_Data[m_Head_Index];
}
/****************************************************************************************************
* Function Name    : Tail
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Returns a reference to the element at the tail of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : const Type& - Reference to the element at the tail of the buffer.
* Notes            : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
const Type& Circular_Buffer<Type, TOTAL_SIZE>::Tail(void)const
{
    return m_Data[m_Tail_Index];
}
/****************************************************************************************************
* Function Name    : Push
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Pushes a new element into the circular buffer.
* Parameters (in)  : Element - The element to be pushed into the buffer.
* Parameters (out) : None
* Return value     : None
* Notes            : - Appends the new element to the buffer.
*                    - Adjusts the head and tail indices if necessary to handle overflow.
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
void Circular_Buffer<Type, TOTAL_SIZE>::Push(const Type& Element)
{
    /* Appned New Element */
    m_Data.at(m_Tail_Index)=Element;
    /* Check If Head Need Move "Care About Head Overflow" */
    m_Head_Index=(m_Current_Size==TOTAL_SIZE)?((m_Head_Index+1)%TOTAL_SIZE):m_Head_Index;
    /* Increment Current Size "Care About Overflow" */
    m_Current_Size=(++m_Current_Size>TOTAL_SIZE)?TOTAL_SIZE:m_Current_Size;
    /* Increment Tail New Posion "Care About OverFlow" */
    m_Tail_Index=((m_Tail_Index+1)%TOTAL_SIZE);
}
/****************************************************************************************************
* Function Name    : Pop
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Namespace        : Data_Structure
* Type             : Public
* Description      : Removes and returns the element from the head of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : Type - The element removed from the buffer.
* Notes            : - Returns a default zero-initialized value if the buffer is empty.
*                    - Throws a runtime error if the buffer is empty.
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
Type Circular_Buffer<Type, TOTAL_SIZE>::Pop(void)
{
    /* Default Zero Return Data */
    Type Return_Data{};
    /* Buffer In Not Embty */
    if(!Is_Empty())
    {
        /* Return Data From Head */
        Return_Data=m_Data.at(m_Head_Index);
        /* Update Current Size */
        m_Current_Size--;
        /* Update Next Head */
        m_Head_Index=((m_Head_Index+1)%TOTAL_SIZE);
    }
    else{throw std::runtime_error("Buffer Is Empty !");}
    /* Return Data */
    return Return_Data;
}
/****************************************************************************************************
* Function Name    : Size
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Returns the current size of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : size_t - The current size of the buffer.
* Notes            : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
size_t Circular_Buffer<Type, TOTAL_SIZE>::Size(void)
{
    return m_Current_Size;
}
/****************************************************************************************************
* Function Name    : Is_Empty
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Checks if the circular buffer is empty.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : bool - True if the buffer is empty, false otherwise.
* Notes            : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
bool Circular_Buffer<Type, TOTAL_SIZE>::Is_Empty(void)
{
    return m_Current_Size==0;
}
/****************************************************************************************************
* Function Name    : end
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Returns a constant iterator pointing to the end of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : constexpr Buffer_Iterator - Constant iterator pointing to the end of the buffer.
* Notes            : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
constexpr typename Circular_Buffer<Type,TOTAL_SIZE>::Buffer_Iterator Circular_Buffer<Type,TOTAL_SIZE>::end() noexcept
{
    return Buffer_Iterator(m_Data.begin(),m_Tail_Index,m_Current_Size);
}
/****************************************************************************************************
* Function Name    : begin
* Class            : Circular_Buffer<Type, TOTAL_SIZE>
* Type             : Public
* Namespace        : Data_Structure
* Description      : Returns a constant iterator pointing to the beginning of the circular buffer.
* Parameters (in)  : None
* Parameters (out) : None
* Return value     : constexpr Buffer_Iterator - Constant iterator pointing to the beginning of the buffer.
* Notes            : None
*****************************************************************************************************/
template <typename Type, size_t TOTAL_SIZE>
constexpr typename Circular_Buffer<Type, TOTAL_SIZE>::Buffer_Iterator Circular_Buffer<Type, TOTAL_SIZE>::begin() noexcept
{
   return Buffer_Iterator(m_Data.begin(),m_Head_Index,0);
}
}
/********************************************************************
 *  END OF FILE:  Circular_Buffer.hpp
********************************************************************/