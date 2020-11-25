/*
)����������� �� ���������               My_TEST 1 ++++++++++++++++++++++++++++++++++++++++
2)����������� ������������              My_TEST 1 ++++++++++++++++++++++++++++++++++++++++
3)����������� ������������� ����

4)�������� ������ ���������( ������������ ���������� ���������)                             My_TEST 1 ++++++++++++++++++++++++++++++++++++
    4.1. �������� ������ GetMaxPower (�������� �� ��������������� ����������� �������)
5)������ ���� �� ������� � ���������                                                        My_TEST 1 ++++++++++++++++++++++++++++++++++++
6)�������� �������
    6.1. �������� ������ InsElem (�������� �� ����������������� ����������� �������� �������������� ����)
    6.2. �������� ������ InsElem (������� ������������ ���� �� �������� - �������� �� ����������������� ����������� �������� �������������� ����)
    6.3. �������� ������ InsElem (��������, ������ �� ������������� ��� ����)
7)������� ������� �� ���������
    7.1.  �������� ������ DelElem (�������� �� ��������������� �������� ���� � 0)
    7.2.  �������� ������ DelElem (�������� �� ��������������� �������� ���� � 0)

8)�������� ������������                 My_TEST 1 ++++++++++++++++++++++++++++++++++++    
9)��������� ==
    9.1. ��������� ���� �������� � ����������� ��������� � � �������� ����������
    9.2. ��������� ���� �������� ����� �������� ������������
    9.3. ��������� ���� �������� ����� �������� ������������, ����������� � ��������� � ������� ��������
    9.4. ��������� ���� �������� ����� �������� ������������, ����������� � ��������� � ������� ��������
10)��������� !=
    10.1. ��������� ���� �������� � ��������� ���������
    10.2. ��������� ���� �������� � ������� ���������, �� ������� ����������

11)����������� � ����������
    11.1. �������� ���������� �������� �� ������������ ���������1 = ���������2 + ���������3
    11.2. �������� ���������� ���� ��������, ���� �� ������� ������ ������������ ���� ������, � ������ ������ �� ����������, ������������ ��� ����������� ���� ������ ��������
    11.3. �������� ���������� �������� �� ������������(�����������) ����������3 = ���������1<������� ������> + ���������2<������� ������>
    11.4. �������� ���������� ���� ��������, ���� �� ������� ������ �������������(�� �����������) ���� ������ ����������3 = ���������1<������� ������> + ���������2<������� ������>, � ������ ������ �� ����������, ������������ ��� ����������� ���� ������ ��������
12)����������� � ���������
    12.1 ����������� � ���������, ������� � �������, ����������� � ���������, �������������� � (������_��������� + <��������_+_� ���������>. ���������2 = ���������1 + �������
    12.2 ����������� � ���������, ������� ��� �������, ����������� � ���������, �������������� � (������_��������� + <��������_+_� ���������>. ���������2 = ���������1 + �������
    12.3 ~(12.1.)
13)����� � ���������               My_TEST 1 ++++++++++++++++++++++++++++++++++++  
14)���������� � ����������
    14.1. �������� ���������� �������� �� ����������� ���������1 = ���������2 * ���������3
    14.2. �������� ���������� �������� �� ������������(�����������) ����������3 = ���������1<������� ������> * ���������2<������� ������>
    14.3.
15)���������� ���������
    15.1. �������� ���������� ���� �������� �� ���., ���� �� ������� ������� ��������� ���������, � ������ ���������� ����������� �������� ����������

16)���������� �����
17)���������� ������
*/

#include "tset.h"

#include <gtest.h>

//MY_TESTS
//1)�������� �� �������� ������� ���������
TEST(TSet, can_create_empty_set)
{
    TSet set(1);

    EXPECT_EQ(set.IsMember(0), 0);
}
//2)�������� ������������ ������������
TEST(TSet, can_create_same_set_by_construktor_copy)
{
    int size = 6;
    TSet set(size);
    set.InsElem(1);
    TSet set2(set);

    EXPECT_EQ(set, set2);
}
//3)�������� GetMaxPower
TEST(TSet, Check_GetMaxPower)
{
    int size = 6;
    TSet set(size);

    EXPECT_EQ(set.GetMaxPower(), size);
}
//4) �������� �� ������� �������� InsElem
TEST(TSet, Check_when_is_member_3_is_1Bit)
{
    int size = 6;
    TSet set(size);
    set.InsElem(3);

    EXPECT_EQ(set.IsMember(3), 1);
}
//5)������������
TEST(TSet, Check_equally)
{
    int size = 6;
    TSet set(size);
    set.InsElem(3);
    TSet set1 = set;

    EXPECT_EQ(set1, set);
}
//6)�������� ����� �������
TEST(TSet, Check_sub_el)
{
    int size = 6;
    TSet set(size);
    set.InsElem(3);
    set.InsElem(4);
    TSet set1(size);
    set1.InsElem(3);
    TSet set2(size);
    set2 = set - 4;

    EXPECT_EQ(set2, set1);
}



//4.1.
TEST(TSet, can_get_max_power_set)
{
  const int size = 5;
  TSet set(size);

  EXPECT_EQ(size, set.GetMaxPower());
}

//6.1
TEST(TSet, can_insert_non_existing_element)
{
  const int size = 5, k = 3;
  TSet set(size);
  set.InsElem(k);

  EXPECT_NE(set.IsMember(k), 0);
}

//6.2.
TEST(TSet, can_insert_existing_element)
{
  const int size = 5;
  const int k = 3;
  TSet set(size);
  set.InsElem(k);
  set.InsElem(k);

  EXPECT_NE(set.IsMember(k), 0);
}

//7.1.
TEST(TSet, can_delete_non_existing_element)
{
  const int size = 5, k = 3;
  TSet set(size);
  set.DelElem(k);

  EXPECT_EQ(set.IsMember(k), 0);
}

//6.3. +
//7.2. +
TEST(TSet, can_delete_existing_element)
{
  const int size = 5, k = 3;
  TSet set(size);

  set.InsElem(k);
  EXPECT_GT(set.IsMember(k), 0);

  set.DelElem(k);
  EXPECT_EQ(set.IsMember(k), 0);
}

//10.1.
TEST(TSet, compare_two_sets_of_non_equal_sizes)
{
  const int size1 = 4, size2 = 6;
  TSet set1(size1), set2(size2);

  EXPECT_EQ(1, set1 != set2);
}

//9.1.
TEST(TSet, compare_two_equal_sets)
{
  const int size = 4;
  TSet set1(size), set2(size);
  // set1 = set2 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  set2.InsElem(1);
  set2.InsElem(3);

  EXPECT_EQ(set1, set2);
}

//10.2.
TEST(TSet, compare_two_non_equal_sets)
{
  const int size = 4;
  TSet set1(size), set2(size);
  // set1 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  // set2 = {1, 2}
  set2.InsElem(1);
  set2.InsElem(2);

  EXPECT_EQ(1, set1 != set2);
}

//9.2. +
TEST(TSet, can_assign_set_of_equal_size)
{
  const int size = 4;
  TSet set1(size), set2(size);
  // set1 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  set2 = set1;

  EXPECT_EQ(set1, set2);
}

//9.3. +
TEST(TSet, can_assign_set_of_greater_size)
{
  const int size1 = 4, size2 = 6;
  TSet set1(size1), set2(size2);
  // set1 = {1, 3}
  set1.InsElem(1);
  set1.InsElem(3);
  set2 = set1;

  EXPECT_EQ(set1, set2);
}

//9.4. +
TEST(TSet, can_assign_set_of_less_size)
{
  const int size1 = 6, size2 = 4;
  TSet set1(size1), set2(size2);
  // set1 = {1, 3, 5}
  set1.InsElem(1);
  set1.InsElem(3);
  set1.InsElem(5);
  set2 = set1;

  EXPECT_EQ(set1, set2);
}

//12.1.
TEST(TSet, can_insert_non_existing_element_using_plus_operator)
{
  const int size = 4;
  const int k = 3;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(2);
  updatedSet = set + k;

  EXPECT_NE(0, updatedSet.IsMember(k));
}

//12.2.
TEST(TSet, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
  const int size = 4;
  const int k = 6;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(2);

  ASSERT_ANY_THROW(updatedSet = set + k);
}

//12.3.
TEST(TSet, can_insert_existing_element_using_plus_operator)
{
  const int size = 4;
  const int k = 3;
  TSet set(size), updatedSet(size);
  set.InsElem(0);
  set.InsElem(k);
  updatedSet = set + k;

  EXPECT_NE(0, set.IsMember(k));
}

//11.1.
TEST(TSet, check_size_of_the_combination_of_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;

  EXPECT_EQ(size, set3.GetMaxPower());
}

//11.2.
TEST(TSet, can_combine_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size), expSet(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;
  // expSet = {0, 1, 2, 4}
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);

  EXPECT_EQ(expSet, set3);
}

//11.3.
TEST(TSet, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 + set2;

  EXPECT_EQ(size2, set3.GetMaxPower());
}

//11.4.
TEST(TSet, can_combine_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2, 6}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set2.InsElem(6);
  set3 = set1 + set2;
  // expSet = {0, 1, 2, 4, 6}
  expSet.InsElem(0);
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);
  expSet.InsElem(6);

  EXPECT_EQ(expSet, set3);
}

//14.1.
TEST(TSet, can_intersect_two_sets_of_equal_size)
{
  const int size = 5;
  TSet set1(size), set2(size), set3(size), expSet(size);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set3 = set1 * set2;
  // expSet = {1, 2}
  expSet.InsElem(1);
  expSet.InsElem(2);

  EXPECT_EQ(expSet, set3);
}

//14.2.
TEST(TSet, can_intersect_two_sets_of_non_equal_size)
{
  const int size1 = 5, size2 = 7;
  TSet set1(size1), set2(size2), set3(size1), expSet(size2);
  // set1 = {1, 2, 4}
  set1.InsElem(1);
  set1.InsElem(2);
  set1.InsElem(4);
  // set2 = {0, 1, 2, 4, 6}
  set2.InsElem(0);
  set2.InsElem(1);
  set2.InsElem(2);
  set2.InsElem(4);
  set2.InsElem(6);
  set3 = set1 * set2;
  // expSet = {1, 2, 4}
  expSet.InsElem(1);
  expSet.InsElem(2);
  expSet.InsElem(4);

  EXPECT_EQ(expSet, set3);
}

//15.1.
TEST(TSet, check_negation_operator)
{
  const int size = 4;
  TSet set(size), set1(size), expSet(size);
  // set1 = {1, 3}
  set.InsElem(1);
  set.InsElem(3);
  set1 = ~set;
  // expSet = {0, 2}
  expSet.InsElem(0);
  expSet.InsElem(2);

  EXPECT_EQ(expSet, set1);
}
