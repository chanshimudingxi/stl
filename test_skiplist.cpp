#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <cstdio>
#include <cstring>
#include "skiplist.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::SafeMatcherCast;

class  VSkipList
{
public:
	VSkipList(){}
	virtual ~VSkipList(){}
	virtual SkipListNode* Find(const std::string& key){return NULL;}
	virtual bool Insert(const std::string& key,const std::string& value){return true;}
	virtual bool Delete(const std::string& key){return true;}
};

class MockVSkipList : public VSkipList
{
public:
	MOCK_METHOD1(Find, SkipListNode*(const std::string& key));
	MOCK_METHOD2(Insert, bool(const std::string& key, const std::string& value));
	MOCK_METHOD1(Delete, bool(const std::string& key));
};

TEST(SkipListTest,testcase1)
{
	MockVSkipList skiplist;
	std::string data_1 = "key=11";
	EXPECT_CALL(skiplist,Insert("11",data_1)).Times(1);
	ON_CALL(skiplist,Insert("11",data_1)).WillByDefault(Return(1));
	skiplist.Insert("11",data_1);
}

TEST(SkipListTest,testcase2)
{
  SkipList sl;
  std::string str1 = "you are a dog";
  ASSERT_TRUE(sl.Insert("1", str1));
  std::string str2 = "you are a dog";
  ASSERT_TRUE(sl.Insert("2",str2));
  ASSERT_STREQ(sl.Find("1")->value.c_str(),sl.Find("2")->value.c_str());
}

TEST(SkipListTest,testcase3)
{
  SkipList sl;
  std::string str1 = "you are a dog";
  ASSERT_TRUE(sl.Insert("1", str1));
  std::string str2 = "you are a dog";
  ASSERT_TRUE(sl.Insert("2",str2));

  ASSERT_TRUE(sl.Delete("2"));
  ASSERT_TRUE(NULL == sl.Find("2"));
  ASSERT_TRUE(sl.Delete("1"));
  ASSERT_TRUE(NULL == sl.Find("1"));
}

TEST(SkipListTest,testcase4)
{
  SkipList sl;
  std::string str1 = "you are a dog";
  ASSERT_TRUE(sl.Insert("1", str1));
  ASSERT_TRUE(sl.Delete("1"));
  ASSERT_TRUE(NULL == sl.Find("1"));
}

TEST(SkipListTest,testcase5)
{
  SkipList sl;
  ASSERT_TRUE(sl.Insert("1", "1"));
  ASSERT_TRUE(sl.Insert("2", "2"));
  ASSERT_TRUE(sl.Insert("3", "3"));
  ASSERT_TRUE(sl.Insert("4", "4"));
  ASSERT_TRUE(sl.Insert("7", "7"));
  ASSERT_TRUE(sl.Insert("8", "8"));
  ASSERT_TRUE(sl.Insert("5", "5"));
  ASSERT_TRUE(sl.Insert("6", "6"));
  ASSERT_TRUE(sl.Insert("9", "9"));
  SkipListNode* p=sl.Head();
  ASSERT_TRUE(NULL != p);
  int i = 0;
  while((p=sl.Next(p)))
  {
    ASSERT_TRUE(NULL != p);
    ++i;
    char a[32];
    sprintf(a,"%d",i);
    ASSERT_TRUE(p->key == a);
  }
}

int main(int argc,char** argv)
{
	testing::InitGoogleMock(&argc, argv);   
	return RUN_ALL_TESTS();  
}