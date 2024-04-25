/*******************************************************************
 *  FILE DESCRIPTION
-----------------------
 *  Author: Khaled El-Sayed @t0ti20
 *  File: Circular_Buffer_Test.cpp
 *  Date: November 30, 2024
 *  Description: Test Casses File For Circular_Buffer Implementation
 *  Class Name:  Circular_Buffer_Test
 *  Namespace:  None
 *  (C) 2023 "@t0ti20". All rights reserved.
*******************************************************************/
/*****************************************
-----------     INCLUDES     -------------
*****************************************/
#include "Circular_Buffer.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <vector>
#include <array>
/*****************************************
----------    GLOBAL DATA     ------------
*****************************************/
/*****************************************
-------    Circular_Buffer_Test     ------
*****************************************/
class Circular_Buffer_Test : public testing::Test
{
public:
    void SetUp()override{}
    void TearDown()override{}
};

TEST_F(Circular_Buffer_Test,PUSH_BACK_CHECK_HEAD_TAIL)
{
    Data_Structure::Circular_Buffer<int,5> Buffer{};
    EXPECT_EQ(Buffer.Is_Empty(),true);
    /* [ 0 0 0 0 0 ] */
    /* [ X         ] */
    EXPECT_EQ(Buffer.Head(),0);
    EXPECT_EQ(Buffer.Tail(),0);
    /* [ 1 0 0 0 0 ] */
    /* [ H T       ] */
    Buffer.Push(1);
    EXPECT_EQ(Buffer.Head(),1);
    EXPECT_EQ(Buffer.Tail(),0);
    /* [ 1 2 0 0 0 ] */
    /* [ H   T     ] */
    Buffer.Push(2);
    EXPECT_EQ(Buffer.Head(),1);
    EXPECT_EQ(Buffer.Tail(),0);
    /* [ 1 2 3 0 0 ] */
    /* [ H     T   ] */
    Buffer.Push(3);
    EXPECT_EQ(Buffer.Head(),1);
    EXPECT_EQ(Buffer.Tail(),0);
    /* [ 1 2 3 4 0 ] */
    /* [ H       T ] */
    Buffer.Push(4);
    EXPECT_EQ(Buffer.Head(),1);
    EXPECT_EQ(Buffer.Tail(),0);
    /* [ 1 2 3 4 5 ] */
    /* [ X         ] */
    Buffer.Push(5);
    EXPECT_EQ(Buffer.Head(),1);
    EXPECT_EQ(Buffer.Tail(),1);
    /* [ 6 2 3 4 5 ] */
    /* [   X       ] */
    Buffer.Push(6);
    EXPECT_EQ(Buffer.Head(),2);
    EXPECT_EQ(Buffer.Tail(),2);
    /* [ 6 7 3 4 5 ] */
    /* [     X     ] */
    Buffer.Push(7);
    EXPECT_EQ(Buffer.Head(),3);
    EXPECT_EQ(Buffer.Tail(),3);
    /* [ 6 7 8 4 5 ] */
    /* [       X   ] */
    Buffer.Push(8);
    EXPECT_EQ(Buffer.Head(),4);
    EXPECT_EQ(Buffer.Tail(),4);
    EXPECT_EQ(Buffer.Size(),5);
    EXPECT_EQ(Buffer.Is_Empty(),false);
}

TEST_F(Circular_Buffer_Test,PUSH_BACK_CHECK_HEAD)
{
    Data_Structure::Circular_Buffer<int,5> Buffer{};
    EXPECT_EQ(Buffer.Is_Empty(),true);
    for(int Counter{};Counter<=5;Counter++)
    {
        /* [5,1,2,3,4] */
        Buffer.Push(Counter);
    }
    EXPECT_EQ(Buffer.Head(),1);
    EXPECT_EQ(Buffer.Tail(),1);
}

TEST_F(Circular_Buffer_Test,PUSH_BACK_WITH_POP)
{
    Data_Structure::Circular_Buffer<int,5> Buffer{};
    EXPECT_EQ(Buffer.Is_Empty(),true);
    for(int Counter{};Counter<=10;Counter++)
    {
        Buffer.Push(Counter);
        EXPECT_EQ(Buffer.Pop(),Counter);
    }
}

TEST_F(Circular_Buffer_Test,PUSH_BACK_CHECK_HEAD_3)
{
    std::vector<int> Result{6,7,8,9,10};
    Data_Structure::Circular_Buffer<int,5> Buffer{};
    for(int Counter{};Counter<=10;Counter++)
    {
        Buffer.Push(Counter);
    }
    /* [ 6 7 8 9 10 ] */
    /* [ X          ] */
    EXPECT_EQ(Buffer.Head(),6);
    for(auto Variable:Result)
    {
        EXPECT_EQ(Variable,Buffer.Head());
        EXPECT_EQ(Variable,Buffer.Pop());
    }
}

TEST_F(Circular_Buffer_Test,EXPECT_THROW)
{
    std::vector<int> Result{6,7,8,9,10};
    Data_Structure::Circular_Buffer<int,5> Buffer{};
    EXPECT_THROW(Buffer.Pop(),std::runtime_error);
    EXPECT_THROW(Buffer.Pop(),std::runtime_error);
    EXPECT_THROW(Buffer.Pop(),std::runtime_error);
}

TEST_F(Circular_Buffer_Test,PUSH_BACK_CHECK_HEAD_2)
{
    std::vector<int> Result{6,7,8,9,10};
    Data_Structure::Circular_Buffer<int,5> Buffer{};
    EXPECT_EQ(Buffer.Is_Empty(),true);
    for(int Counter{};Counter<=10;Counter++)
    {
        Buffer.Push(Counter);
    }
    /* [ 6 7 8 9 10 ] */
    /* [ X          ] */
    EXPECT_EQ(Buffer.Head(),6);
    EXPECT_EQ(Buffer.Tail(),6);
    Result.reserve(Result.size()-1);
    for(auto Variable:Result)
    {
        EXPECT_EQ(Variable,Buffer.Head());
        EXPECT_EQ(Variable,Buffer.Pop());
    }
    /* [ 6 7 8 9 10 ] */
    /* [ X          ] */
    EXPECT_EQ(Buffer.Head(),6);
    EXPECT_EQ(Buffer.Size(),0);
    EXPECT_THROW(Buffer.Pop(),std::runtime_error);
    EXPECT_EQ(Buffer.Head(),6);
    EXPECT_EQ(Buffer.Tail(),6);
    EXPECT_EQ(Buffer.Size(),0);
}

TEST_F(Circular_Buffer_Test,EXAMPLE_TEST)
{
    Data_Structure::Circular_Buffer<int,5> Q{};
    /* [ 0 0 0 0 0 ] */
    /* [ X         ] */
    Q.Push(5);
    /* [ 5 0 0 0 0 ] */
    /* [ H T       ] */
    Q.Push(10);
    /* [ 5 10 0 0 0 ] */
    /* [ H    T     ] */
    Q.Push(15);
    /* [ 5 10 15 0 0 ] */
    /* [ H        T  ] */
    Q.Push(20);
    /* [ 5 10 15 20 0 ] */
    /* [ H          T ] */
    Q.Push(25);
    /* [ 5 10 15 20 25 ] */
    /* [ X             ] */
    Q.Push(30);
    /* [ 30 10 15 20 25 ] */
    /* [     X          ] */
    EXPECT_EQ(Q.Head(), 10);
    EXPECT_EQ(Q.Tail(), 10);
    Q.Pop();
    /* [ 30 10 15 20 25 ] */
    /* [     T  H       ] */
    EXPECT_EQ(Q.Head(), 15);
    EXPECT_EQ(Q.Tail(), 10);
    Q.Pop();
    /* [ 30 10 15 20 25 ] */
    /* [     T     H    ] */
    EXPECT_EQ(Q.Head(), 20);
    EXPECT_EQ(Q.Tail(), 10);
    Q.Push(35);
    /* [ 30 35 15 20 25 ] */
    /* [        T  H    ] */  
    EXPECT_EQ(Q.Head(), 20);
    EXPECT_EQ(Q.Tail(), 15);
    Q.Push(40);
    /* [ 30 35 40 20 25 ] */
    /* [          X    ] */  
    EXPECT_EQ(Q.Head(), 20);
    EXPECT_EQ(Q.Tail(), 20);
}

TEST_F(Circular_Buffer_Test,INITIALIZER_LIST)
{
    std::array<int,5> Result{6,7,8,9,10};
    Data_Structure::Circular_Buffer<int,5> Buffer{6,7,8,9,10};
    EXPECT_EQ(Buffer.Is_Empty(), false);
    for(auto Variable : Result)
    {
        EXPECT_EQ(Variable, Buffer.Pop());
    }
    EXPECT_THROW(Buffer.Pop(), std::runtime_error);
    EXPECT_EQ(Buffer.Size(), 0);
}

TEST_F(Circular_Buffer_Test,ARRAY_EQUAL)
{
    std::array<int,5> Result{6,7,8,9,10};
    Data_Structure::Circular_Buffer<int,5> Buffer{6,7,8,9,10};
    EXPECT_EQ(Buffer.Is_Empty(), false);
    EXPECT_EQ(Buffer==Result,true);
}

TEST_F(Circular_Buffer_Test,THROW_IITIALIZER_LIST)
{
    auto Initialize=[]()
    {Data_Structure::Circular_Buffer<int,5> Buffer{6,7,8,9,10,11};};
    EXPECT_THROW(Initialize(),std::runtime_error);
    
}

TEST_F(Circular_Buffer_Test,CUSTOM_ITERATOR_FOREACH)
{
    Data_Structure::Circular_Buffer<int,5> Q{};
    /* [ 0 0 0 0 0 ] */
    /* [ X         ] */
    Q.Push(5);
    /* [ 5 0 0 0 0 ] */
    /* [ H T       ] */
    Q.Push(10);
    /* [ 5 10 0 0 0 ] */
    /* [ H    T     ] */
    Q.Push(15);
    /* [ 5 10 15 0 0 ] */
    /* [ H        T  ] */
    Q.Push(20);
    /* [ 5 10 15 20 0 ] */
    /* [ H          T ] */
    Q.Push(25);
    /* [ 5 10 15 20 25 ] */
    /* [ X             ] */
    Q.Push(30);
    /* [ 30 10 15 20 25 ] */
    /* [     X          ] */
    EXPECT_EQ(Q.Head(), 10);
    EXPECT_EQ(Q.Tail(), 10);
    Q.Pop();
    /* [ 30 10 15 20 25 ] */
    /* [     T  H       ] */
    EXPECT_EQ(Q.Head(), 15);
    EXPECT_EQ(Q.Tail(), 10);
    Q.Pop();
    /* [ 30 10 15 20 25 ] */
    /* [     T     H    ] */
    EXPECT_EQ(Q.Head(), 20);
    EXPECT_EQ(Q.Tail(), 10);
    Q.Push(35);
    /* [ 30 35 15 20 25 ] */
    /* [        T  H    ] */  
    EXPECT_EQ(Q.Head(), 20);
    EXPECT_EQ(Q.Tail(), 15);
    Q.Push(40);
    /* [ 30 35 40 20 25 ] */
    /* [          X    ] */  
    EXPECT_EQ(Q.Head(), 20);
    EXPECT_EQ(Q.Tail(), 20);
    EXPECT_EQ(Q.Size(), 5);
    std::array<int, 5> RESULT{20,25,30,35,40};
    Data_Structure::Circular_Buffer<int,5> Buffer_2{};
    int counter{};
    std::for_each(Q.begin(),Q.end(),[&Buffer_2,&counter,&RESULT](int Value)
    {
        EXPECT_EQ(Value,RESULT[counter++]);
    });
}

TEST_F(Circular_Buffer_Test,CUSTOM_ITERATOR_FORLOOP)
{
    Data_Structure::Circular_Buffer<int,5> Q1{1,2,3,4,5};
    Data_Structure::Circular_Buffer<int,5> Q2{};
    for(auto &Value:Q1){Q2.Push(Value);}
    EXPECT_EQ(Q1, Q2);
}
/********************************************************************
 *  END OF FILE:  Circular_Buffer_Test.cpp
********************************************************************/
