#include <gtest/gtest.h>
#include <matrix.h>
#include <iterator> // std::prev

// matrix(r,c) => r=row; c=column
TEST(Matrix, constructor_4args){
  Matrix<int> m{3,1,3,0}; // 3x4 matrix
  EXPECT_EQ( std::size_t{3}, m.n_row );
  EXPECT_EQ( std::size_t{4}, m.n_col );
}

TEST(Matrix, constructor_2args){
  Matrix<int> m{3,5}; // 3x5 matrix
  EXPECT_EQ( std::size_t{3}, m.n_row );
  EXPECT_EQ( std::size_t{5}, m.n_col );
}

TEST(Matrix, initialization){
  Matrix<int> m{2,2}; // 2x2 matrix
  EXPECT_EQ( 0, m(1,1) );
  EXPECT_EQ( 0, m(1,2) );
  EXPECT_EQ( 0, m(2,1) );
  EXPECT_EQ( 0, m(2,2) );

  #ifndef NDEBUG
  EXPECT_ANY_THROW( m(0,0)); 
  EXPECT_ANY_THROW( m(3,3));
 #else
  EXPECT_NO_THROW( m(0,0) );
  EXPECT_NO_THROW( m(3,3) );
  #endif
}

TEST(Matrix, begin){
  Matrix<int> m{2,2}; // 2x2 matrix
  m(1,1) = 1;
  m(1,2) = 2;
  m(2,1) = 3;
  m(2,2) = 4;
  EXPECT_EQ( 1, *(m.begin()) );
}

TEST(Matrix, end){
  Matrix<int> m{2,2}; // 2x2 matrix
  m(1,1) = 1;
  m(1,2) = 2;
  m(2,1) = 3;
  m(2,2) = 4;
  EXPECT_EQ( 4, *std::prev(m.end()) );
}

TEST(Matrix, range_for){
  Matrix<double> m{2,2}; // 2x2 matrix
  double c{1.0};
  m(1,1) = -9999;
  m(2,2) = -9999;

  for (auto &x : m)
    x = ++c;
  
  EXPECT_DOUBLE_EQ( 2.0, m(1,1) );
  EXPECT_DOUBLE_EQ( 3.0, m(1,2) );
  EXPECT_DOUBLE_EQ( 4.0, m(2,1) );
  EXPECT_DOUBLE_EQ( 5.0, m(2,2) );
}

TEST(Matrix, range_for_zero){
  Matrix<double> m{1,0,1,0}; // 2x2 matrix
  double c{0.0};
  m(0,0) = -9999;
  m(1,1) = -9999;

  for (auto &x : m)
    x = ++c;
  
  EXPECT_DOUBLE_EQ( 1.0, m(0,0) );
  EXPECT_DOUBLE_EQ( 2.0, m(0,1) );
  EXPECT_DOUBLE_EQ( 3.0, m(1,0) );
  EXPECT_DOUBLE_EQ( 4.0, m(1,1) );
}

TEST(Matrix, set_value){
  Matrix<double> m{1,0,1,0};
  double c{0.0};
  
  for (auto &x : m)
    x = ++c;

  m = -9999.;

  EXPECT_DOUBLE_EQ( m(0,0), -9999. );
  EXPECT_DOUBLE_EQ( m(0,1), -9999. );
  EXPECT_DOUBLE_EQ( m(1,0), -9999. );
  EXPECT_DOUBLE_EQ( m(1,1), -9999. );
}

TEST(Matrix, copy_constructor){
  Matrix<double> m{2,2};
  double c{0.0};
  
  for (auto &x : m)
    x = ++c;
  
  Matrix<double> m1{m};

  EXPECT_DOUBLE_EQ( m1(1,1), 1 );
  EXPECT_DOUBLE_EQ( m1(1,2), 2 );
  EXPECT_DOUBLE_EQ( m1(2,1), 3 );
  EXPECT_DOUBLE_EQ( m1(2,2), 4 );
 
}

TEST(Matrix, out_of_range){
  Matrix<double> m{3,3};

  // testing "at" 
  EXPECT_NO_THROW( m.at(1,1) );
  EXPECT_NO_THROW( m.at(2,2) );
  EXPECT_NO_THROW( m.at(3,3) );
  
  EXPECT_ANY_THROW( m.at(0,0) );
  EXPECT_ANY_THROW( m.at(0,1) );
  EXPECT_ANY_THROW( m.at(1,0) );
  EXPECT_ANY_THROW( m.at(4,4) );

  // testing "()"
  EXPECT_NO_THROW( m(1,1) );
  EXPECT_NO_THROW( m(2,2) );
  EXPECT_NO_THROW( m(3,3) );

#ifndef NDEBUG 
  EXPECT_ANY_THROW( m(0,0) );
  EXPECT_ANY_THROW( m(0,1) );
  EXPECT_ANY_THROW( m(1,0) );
  EXPECT_ANY_THROW( m(4,4) );
#else
  EXPECT_NO_THROW( m(0,0) );
  EXPECT_NO_THROW( m(0,1) );
  EXPECT_NO_THROW( m(1,0) );
  EXPECT_NO_THROW( m(4,4) );
#endif
}

TEST(Matrix, out_of_range_zero){
  Matrix<double> m{3,0,3,0};
  
  EXPECT_NO_THROW( m.at(0,0) );
  EXPECT_NO_THROW( m.at(1,1) );
  EXPECT_NO_THROW( m.at(2,2) );
  EXPECT_NO_THROW( m.at(3,3) );
  
  EXPECT_ANY_THROW( m.at(-3,-3) );
  EXPECT_ANY_THROW( m.at(4,4) );
  EXPECT_ANY_THROW( m.at(5000,5000) );
  
}

TEST(Matrix, copy_from_to){
  Matrix<double> from{2,2};
  double c{0.0};
  for (auto &x : from)
    x = ++c;

  Matrix<double> to{2,2};
  to = from;
	
  EXPECT_DOUBLE_EQ( to(1,1), 1 );
  EXPECT_DOUBLE_EQ( to(1,2), 2 );
  EXPECT_DOUBLE_EQ( to(2,1), 3 );
  EXPECT_DOUBLE_EQ( to(2,2), 4 );
 
}
