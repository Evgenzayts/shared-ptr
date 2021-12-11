// Copyright 2021 Evgenzayts evgenzaytsev2002@yandex.ru

#include <stdexcept>
#include <gtest/gtest.h>
#include <My_SharedPtr.h>

TEST(SharedPtr, EmptyConstructor) {
  My_SharedPtr<int> smth;
  EXPECT_EQ(smth.get(), nullptr);
}

TEST(SharedPtr, PtrContructor) {
  My_SharedPtr<int> smth(new int(1));
  EXPECT_EQ(smth.use_count(), 1);
}

TEST(SharedPtr, CopyContructor) {
  const My_SharedPtr<int> smth1(new int(1));
  My_SharedPtr<int> smth2(smth1);
  EXPECT_EQ(*smth1, *smth2);
}

TEST(SharedPtr, MoveContructor) {
  My_SharedPtr<int> smth1(new int(1));
  My_SharedPtr<int> smth2(std::move(smth1));
  EXPECT_EQ(smth2.use_count(), 1);
}

TEST(SharedPtr, Copy) {
  const My_SharedPtr<int> smth1(new int(1));
  My_SharedPtr<int> smth2(new int(2));
  smth2 = smth1;
  EXPECT_EQ(*smth2, *smth2);
}

TEST(SharedPtr, Move) {
  My_SharedPtr<int> smth1(new int(1));
  My_SharedPtr<int> smth2(new int(2));
  smth2 = std::move(smth1);
  EXPECT_EQ(smth2.use_count(), 1);
}

TEST(SharedPtr, Bool) {
  My_SharedPtr<int> smth(new int(1));
  EXPECT_EQ(smth.operator bool(), true);
}

TEST(SharedPtr, Reset) {
  My_SharedPtr<int> smth(new int(1));
  smth.reset();
  EXPECT_EQ(smth.get(), nullptr);
}

TEST(SharedPtr, PtrReset) {
  My_SharedPtr<int> smth(new int(1));
  smth.reset(new int(2));
  EXPECT_EQ(*smth, 2);
}

TEST(SharedPtr, Swap) {
  My_SharedPtr<int> smth1(new int(1));
  My_SharedPtr<int> smth2(new int(2));
  smth1.swap(smth2);
  EXPECT_EQ(*smth1, 2);
}
