/*

Usage:

Put your declaration and implementation of MyString in `mystring.h`
and compile & run this file with modern C++ features enabled.

For example, in Linux: g++ -std=c++14 tester.cpp -o tester && ./tester

 */

#include <cstdio>
#include <cassert>
#include <cstring>
#include "mystring.h"
#include "testhelper.h"

using std::printf;
using namespace test_helper;

const int CLASS_SIZE_MAX = 100;

int main() {
  init();
  alloc_trace_enabled = true;

  printf("===== Testing Basic Functionalities =====\n");

  run_test([] {
    {
      MyString *s = new MyString;
      test_assert(__LINE__, s->size() == 0, "MyString.size() should be zero when it is initialized without parameters");
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const MyString *s = new MyString;
      test_assert(__LINE__, s->size() == 0, "MyString.size() should be zero when it is initialized without parameters");
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      MyString *s = new MyString(str.get());
      test_assert(__LINE__, s->size() == strlen(str.get()), "MyString.size() should be the length without \'\\0\' when it is initialized with a \'const char *\'");
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      int alloc_data_size = 0;
      const auto str = build_magic_string();
      alloc_data_size = alloc_mem;
      MyString *s = new MyString(str.get());
      test_assert(__LINE__, alloc_mem - alloc_data_size < CLASS_SIZE_MAX + strlen(str.get()), "MyString should only keep 1 copy of the string");
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      MyString *s1 = new MyString(str.get());
      MyString *s2 = new MyString(*s1);
      test_assert(__LINE__, s2->size() == strlen(str.get()), "MyString.size() should be the length of string when it is copy initialized");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      const MyString *s1 = new MyString(str.get());
      MyString *s2 = new MyString(*s1);
      test_assert(__LINE__, s2->size() == strlen(str.get()), "MyString.size() should be the length of string when it is copy initialized");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      MyString *s1 = new MyString(str.get());
      const MyString *s2 = new MyString(*s1);
      test_assert(__LINE__, s2->size() == strlen(str.get()), "MyString.size() should be the length of string when it is copy initialized");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      const MyString *s1 = new MyString(str.get());
      const MyString *s2 = new MyString(*s1);
      test_assert(__LINE__, s2->size() == strlen(str.get()), "MyString.size() should be the length of string when it is copy initialized");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      MyString *s = new MyString(str.get());
      for (int skip = 0, i = 0; i < strlen(str.get()) && !skip; ++i) {
        test_assert(__LINE__, (*s)[i] == str[i], "MyString[size_t i] should be the i'th element of the string") || (skip = 1, false);
      }
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      const MyString *s = new MyString(str.get());
      for (int skip = 0, i = 0; i < strlen(str.get()) && !skip; ++i) {
        test_assert(__LINE__, (*s)[i] == str[i], "MyString[size_t i] should be the i'th element of the string") || (skip = 1, false);
      }
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      const auto str_backup = copy_string(str);
      MyString *s = new MyString(str.get());
      for (int skip = 0, i = 0; i < strlen(str_backup.get()) && !skip; ++i) {
        str[i] += 1;
        test_assert(__LINE__, (*s)[i] == str_backup[i], "MyString should copy the original string") || (skip = 1, false);
        test_assert(__LINE__, (*s)[i] == str[i] - 1, "MyString should copy the original string") || (skip = 1, false);
      }
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      const auto str_backup = copy_string(str);
      MyString *s = new MyString(str.get());
      for (int skip = 0, i = 0; i < strlen(str_backup.get()) && !skip; ++i) {
        (*s)[i] += 1;
        test_assert(__LINE__, (*s)[i] == str_backup[i] + 1, "MyString[size_t] should be mutable") || (skip = 1, false);
        test_assert(__LINE__, str[i] == str_backup[i], "MyString should not mutate original \'const char *\'") || (skip = 1, false);
      }
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str = build_magic_string();
      const auto str_backup = copy_string(str);
      MyString *s1 = new MyString(str.get());
      MyString *s2 = new MyString(*s1);
      for (int skip = 0, i = 0; i < strlen(str_backup.get()) && !skip; ++i) {
        (*s2)[i] += 1;
        test_assert(__LINE__, (*s2)[i] == str_backup[i] + 1, "MyString[size_t] should be mutable") || (skip = 1, false);
        test_assert(__LINE__, str[i] == str_backup[i], "Copies of MyString should not mutate each other") || (skip = 1, false);
        test_assert(__LINE__, (*s1)[i] == str_backup[i], "Copies of MyString should not mutate each other") || (skip = 1, false);
      }
      for (int skip = 0, i = 0; i < strlen(str_backup.get()) && !skip; ++i) {
        (*s1)[i] -= 1;
        test_assert(__LINE__, (*s1)[i] == str_backup[i] - 1, "MyString[size_t] should be mutable") || (skip = 1, false);
        test_assert(__LINE__, str[i] == str_backup[i], "Copies of MyString should not mutate each other") || (skip = 1, false);
        test_assert(__LINE__, (*s1)[i] + 2 == (*s2)[i], "Copies of MyString should not mutate each other") || (skip = 1, false);
      }
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      int alloc_data_size = 0;
      const auto str_1 = build_magic_string();
      const auto str_2 = build_magic_string();
      const auto str_2_backup = copy_string(str_2);
      int len_1 = strlen(str_1.get());
      int len_2 = strlen(str_2.get());
      alloc_data_size = alloc_mem;
      MyString *s = new MyString(str_1.get());
      s->append(str_2.get());
      test_assert(__LINE__, s->size() == len_1 + len_2, "MyString.append(const char *) should update \'.size()\'");
      test_assert(__LINE__, alloc_mem - alloc_data_size < CLASS_SIZE_MAX + len_1 + len_2, "MyString should only keep 1 copy of the string");
      for (int skip = 0, i = 0; i < len_1 && !skip; ++i) {
        test_assert(__LINE__, (*s)[i] == str_1[i], "MyString.append(const char *) should append new string at the end of original string") || (skip = 1, false);
      }
      for (int skip = 0, i = len_1; i < len_1 + len_2 && !skip; ++i) {
        test_assert(__LINE__, (*s)[i] == str_2[i - len_1], "MyString.append(const char *) should append new string at the end of original string") || (skip = 1, false);
      }
      for (int skip = 0, i = 0; i < len_2 && !skip; ++i) {
        str_2[i]++;
        test_assert(__LINE__, (*s)[i + len_1] == str_2_backup[i], "MyString.append(const char *) should copy the original string") || (skip = 1, false);
      }
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      int alloc_data_size = 0;
      const auto str_1 = build_magic_string();
      const auto str_2 = build_magic_string();
      int len_1 = strlen(str_1.get());
      int len_2 = strlen(str_2.get());
      alloc_data_size = alloc_mem;
      MyString *s1 = new MyString(str_1.get());
      MyString *s2 = new MyString(str_2.get());
      s1->append(*s2);
      test_assert(__LINE__, s1->size() == len_1 + len_2, "MyString.append(MyString) should update \'.size()\'");
      test_assert(__LINE__, alloc_mem - alloc_data_size < CLASS_SIZE_MAX * 2 + len_1 + len_2 + len_2, "MyString should only keep 1 copy of the string");
      for (int skip = 0, i = 0; i < len_1 && !skip; ++i) {
        test_assert(__LINE__, (*s1)[i] == str_1[i], "MyString.append(MyString) should append new string at the end of original string") || (skip = 1, false);
      }
      for (int skip = 0, i = len_1; i < len_1 + len_2 && !skip; ++i) {
        test_assert(__LINE__, (*s1)[i] == str_2[i - len_1], "MyString.append(MyString) should append new string at the end of original string") || (skip = 1, false);
      }
      test_assert(__LINE__, s2->size() == len_2, "MyString.append(MyString) should not mutate the string to be appended");
      for (int skip = 0, i = 0; i < len_2 && !skip; ++i) {
        test_assert(__LINE__, (*s2)[i] == str_2[i], "MyString.append(MyString) should not mutate the string to be appended") || (skip = 1, false);
      }
      for (int skip = 0, i = 0; i < len_2 && !skip; ++i) {
        (*s2)[i]++;
        test_assert(__LINE__, (*s1)[i + len_1] == str_2[i], "MyString.append(MyString) should copy the original string") || (skip = 1, false);
      }
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcde");
      MyString *s2 = new MyString("abcde");
      test_assert(__LINE__,  (*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__,  (*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__, !(*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__, !(*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcde");
      MyString *s2 = new MyString("abcdef");
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__, !(*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__,  (*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__, !(*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__,  (*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcdefg");
      MyString *s2 = new MyString("abcdef");
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__, !(*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__,  (*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("aacdefg");
      MyString *s2 = new MyString("abcdef");
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__, !(*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__,  (*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__, !(*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__,  (*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcdeg");
      MyString *s2 = new MyString("abcdef");
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__, !(*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__,  (*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcdegabc");
      MyString *s2 = new MyString("abcdefabc");
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__, !(*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__,  (*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  printf("===== Testing Edge Cases =====\n");

  run_test([] {
    {
      MyString *s = new MyString("");
      test_assert(__LINE__, s->size() == 0, "MyString.size() incorrect");
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("");
      MyString *s2 = new MyString(*s1);
      test_assert(__LINE__, s2->size() == 0, "MyString.size() incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("");
      MyString *s2 = new MyString("");
      s1->append(*s2);
      s1->append(*s2);
      test_assert(__LINE__, s1->size() == 0, "MyString.size() incorrect after appending");
      test_assert(__LINE__, s2->size() == 0, "MyString.size() incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcdef");
      MyString *s2 = new MyString("");
      s1->append(*s2);
      test_assert(__LINE__, s1->size() == 6, "MyString.size() incorrect after appending");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("");
      MyString *s2 = new MyString("");
      test_assert(__LINE__,  (*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__,  (*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__, !(*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__, !(*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("a");
      MyString *s2 = new MyString("");
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__, !(*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__,  (*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  printf("===== Testing Null Character =====\n");

  run_test([] {
    {
      const auto str_1 = build_magic_string();
      const auto str_2 = build_magic_string();
      int len_1 = strlen(str_1.get());
      int len_2 = strlen(str_2.get());
      MyString *s1 = new MyString(str_1.get());
      MyString *s2 = new MyString(str_2.get());

      (*s1)[10] = '\0';
      test_assert(__LINE__, s1->size() == len_1, "MyString.size() incorrect when there are null chars");
      for (int skip = 0, i = 0; i < len_1 && !skip; ++i) {
        if (i == 10) {
          test_assert(__LINE__, (*s1)[i] == '\0', "MyString[size_t] incorrect when there are null chars") || (skip = 1, false);
        } else {
          test_assert(__LINE__, (*s1)[i] == str_1[i], "MyString[size_t] incorrect when there are null chars") || (skip = 1, false);
        }
      }

      s1->append(*s2);
      test_assert(__LINE__, s1->size() == len_1 + len_2, "MyString.size() incorrect after appending when there are null chars");
      for (int skip = 0, i = 0; i < len_1 && !skip; ++i) {
        if (i == 10) {
          test_assert(__LINE__, (*s1)[i] == '\0', "MyString[size_t] incorrect when there are null chars") || (skip = 1, false);
        } else {
          test_assert(__LINE__, (*s1)[i] == str_1[i], "MyString[size_t] incorrect when there are null chars") || (skip = 1, false);
        }
      }
      for (int skip = 0, i = len_1; i < len_1 + len_2 && !skip; ++i) {
        test_assert(__LINE__, (*s1)[i] == str_2[i - len_1], "MyString[size_t] incorrect after appending when there are null chars") || (skip = 1, false);
      }

      s2->append(*s1);
      test_assert(__LINE__, s2->size() == len_1 + len_2 * 2, "MyString.size() incorrect after appending when there are null chars");
      for (int skip = 0, i = 0; i < len_2 && !skip; ++i) {
        test_assert(__LINE__, (*s2)[i] == str_2[i], "MyString[size_t] incorrect after appending when there are null chars") || (skip = 1, false);
      }
      for (int skip = 0, i = len_2; i < len_2 + len_1 && !skip; ++i) {
        if (i == 10 + len_2) {
          test_assert(__LINE__, (*s2)[i] == '\0', "MyString[size_t] incorrect when there are null chars") || (skip = 1, false);
        } else {
          test_assert(__LINE__, (*s2)[i] == str_1[i - len_2], "MyString[size_t] incorrect when there are null chars") || (skip = 1, false);
        }
      }
      for (int skip = 0, i = len_2 + len_1; i < len_2 * 2 + len_1 && !skip; ++i) {
        test_assert(__LINE__, (*s2)[i] == str_2[i - len_2 - len_1], "MyString[size_t] incorrect when there are null chars") || (skip = 1, false);
      }

      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcde");
      MyString *s2 = new MyString("abcde");
      (*s1)[3] = '\0';
      (*s2)[3] = '\0';
      test_assert(__LINE__,  (*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__,  (*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__, !(*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__, !(*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcde");
      MyString *s2 = new MyString("abcdef");
      (*s1)[3] = '\0';
      (*s2)[3] = '\0';
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__, !(*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__,  (*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__, !(*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__,  (*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcdefg");
      MyString *s2 = new MyString("abcdef");
      (*s1)[3] = '\0';
      (*s2)[3] = '\0';
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__, !(*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__,  (*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("aacdefg");
      MyString *s2 = new MyString("abcdef");
      (*s1)[0] = '\0';
      (*s2)[0] = '\0';
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__, !(*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__,  (*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__, !(*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__,  (*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcdeg");
      MyString *s2 = new MyString("abcdef");
      (*s1)[3] = '\0';
      (*s2)[3] = '\0';
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__, !(*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__,  (*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      MyString *s1 = new MyString("abcdegabc");
      MyString *s2 = new MyString("abcdefabc");
      (*s1)[3] = '\0';
      (*s2)[3] = '\0';
      test_assert(__LINE__, !(*s1 == *s2), "MyString.operator== incorrect");
      test_assert(__LINE__,  (*s1 >= *s2), "MyString.operator>= incorrect");
      test_assert(__LINE__, !(*s1 <= *s2), "MyString.operator<= incorrect");
      test_assert(__LINE__,  (*s1 != *s2), "MyString.operator!= incorrect");
      test_assert(__LINE__,  (*s1 >  *s2), "MyString.operator> incorrect");
      test_assert(__LINE__, !(*s1 <  *s2), "MyString.operator< incorrect");
      delete s1;
      delete s2;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  printf("===== Testing COW =====\n");

  run_test([] {
    {
      const auto str = build_magic_string();
      MyString *s = new MyString(str.get());
      int last_alloc_mem = alloc_mem;
      for (int skip = 0, i = 0; i < strlen(str.get()) && !skip; ++i) {
        (*s)[i]++;
      }
      test_assert(__LINE__, alloc_mem - last_alloc_mem == 0, "Mutating MyString[size_t] should not allocate new memory when its buffer is not shared");
      delete s;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  run_test([] {
    {
      const auto str_1 = build_magic_string();
      const auto str_2 = build_magic_string();
      int len_1 = strlen(str_1.get());
      int len_2 = strlen(str_2.get());
      int last_alloc_mem = alloc_mem;
      MyString *s1 = new MyString(str_1.get());
      MyString *s2 = new MyString(*s1);
      const MyString *s3 = new MyString(*s1);
      MyString *s4 = new MyString(*s2);
      MyString *s5 = new MyString(*s2);

      test_assert(__LINE__, alloc_mem - last_alloc_mem < CLASS_SIZE_MAX * 6 + len_1, "MyString should share the same buffer when it is copy constructed");

      s1->append(str_2.get());
      // memory usage of s1 ~= len_1 + len_2
      // memory usage of (s2, s3, s4) ~= len_1
      // so that total memory usage is `len_1 * 2 + len_2`.......[1]
      test_assert(__LINE__, alloc_mem - last_alloc_mem < CLASS_SIZE_MAX * 6 + (len_1 * 2 + len_2), "MyString should not share the same buffer when it is mutated by append");

      s1->append(str_2.get());
      // append again.
      // total memory usage is `[1] + len_2`........[2]
      test_assert(__LINE__, alloc_mem - last_alloc_mem < CLASS_SIZE_MAX * 6 + ((len_1 * 2 + len_2) + len_2), "MyString should not share the same buffer when it is mutated by append");

      (*s2)[5] = '\0';
      // mutate s2.
      // buffers are now (s1), (s2), (s3, s4, s5).
      // total memory usage is `[2] + len_1`........[3]
      test_assert(__LINE__, alloc_mem - last_alloc_mem < CLASS_SIZE_MAX * 6 + ((len_1 * 2 + len_2) + len_2 + len_1), "MyString should not share the same buffer when it is mutated by append");

      char v = (*s3)[0];
      // read s3. total memory usage is unchanged.
      test_assert(__LINE__, alloc_mem - last_alloc_mem < CLASS_SIZE_MAX * 6 + ((len_1 * 2 + len_2) + len_2 + len_1), "MyString should not share the same buffer when it is mutated by append");

      s4->append(*s3);
      // mutate s4.
      // buffers are now (s1), (s2), (s3, s5), (s4).
      // total memory usage is `[3] + len_1 (from append) + len_1 (from copy-on-write)`
      test_assert(__LINE__, alloc_mem - last_alloc_mem < CLASS_SIZE_MAX * 6 + ((len_1 * 2 + len_2) + len_2 + len_1 + len_1 + len_1), "MyString should not share the same buffer when it is mutated by append");

      delete s5;
      // delete s5. total memory usage is unchanged.
      test_assert(__LINE__, alloc_mem - last_alloc_mem < CLASS_SIZE_MAX * 6 + ((len_1 * 2 + len_2) + len_2 + len_1 + len_1 + len_1), "MyString should not share the same buffer when it is mutated by append");

      delete s1;
      delete s2;
      delete s3;
      delete s4;
    }
    test_assert(__LINE__, alloc_mem == 0, "MyString should free all allocated memory");
  });

  alloc_trace_enabled = false;
  return 0;
}
