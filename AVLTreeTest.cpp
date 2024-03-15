//
// Created by Lior on 23/02/2024.
//

#include "../wet2util.h"
#include "gtest/gtest.h"
#include "../AVL_Tree.h"

#define SUCCESS StatusType::SUCCESS
#define FAILURE StatusType::FAILURE
#define SUITE AVLTreeTest

class AVLTreeFixture : public ::testing::Test
{
protected:
	AVL_Tree<int, int> avlTree = AVL_Tree<int, int>();
	
	std::vector<Pair<int, int>> vec = {{0,  5},
									   {1,  70},
									   {2,  70},
									   {4,  70},
									   {5,  70},
									   {6,  70},
									   {7,  70},
									   {8,  70},
									   {10, 50},
									   {11, 30},
									   {30, 13}};
	
	std::string str;
	
	int size = vec.size();
	
	void SetUp() override
	{
		// Insert some elements into the AVL tree
		avlTree.insert(10, 50);
		avlTree.insert(11, 30);
		avlTree.insert(0, 5);
		avlTree.insert(30, 13);
		avlTree.insert(1, 70);
		avlTree.insert(2, 70);
		avlTree.insert(4, 70);
		avlTree.insert(5, 70);
		avlTree.insert(6, 70);
		avlTree.insert(7, 70);
		avlTree.insert(8, 70);
		
		for (const auto& p : vec)
		{
			str += "(" + std::to_string(p.get_first()) + ", " + std::to_string(p.get_second()) + ")\n";
		}
	}
};

TEST(SUITE, Constructor)
{
	AVL_Tree<int, int> tree = AVL_Tree<int, int>();
	ASSERT_TRUE(tree.is_valid());
	EXPECT_EQ(tree.get_size(), 0);
	EXPECT_EQ(tree.get_max().status(), FAILURE);
	EXPECT_EQ(tree.get_min().status(), FAILURE);
	EXPECT_EQ(tree.find(0).status(), FAILURE);
	std::vector<Pair<int, int>> res = std::vector<Pair<int, int>>();
	EXPECT_EQ(tree.to_vec(), res);
	std::stringstream ss;
	tree.inorder(ss);
	EXPECT_EQ(ss.str(), "");
}

TEST_F(AVLTreeFixture, Size)
{
	EXPECT_EQ(avlTree.get_size(), size);
}

TEST(SUITE, SizeEmptyTree)
{
	auto tree = AVL_Tree<int, int>();
	EXPECT_EQ(tree.get_size(), 0);
}

TEST(SUITE, Insert)
{
	AVL_Tree<int, int> tree = AVL_Tree<int, int>();
	EXPECT_EQ(tree.insert(1, 1), SUCCESS);
	EXPECT_EQ(tree.insert(2, 2), SUCCESS);
	EXPECT_EQ(tree.insert(3, 3), SUCCESS);
	EXPECT_EQ(tree.insert(4, 4), SUCCESS);
	EXPECT_EQ(tree.insert(5, 5), SUCCESS);
	EXPECT_EQ(tree.insert(6, 6), SUCCESS);
	ASSERT_TRUE(tree.is_valid());
	EXPECT_EQ(tree.get_size(), 6);
	std::vector<Pair<int, int>> res = {{1, 1},
									   {2, 2},
									   {3, 3},
									   {4, 4},
									   {5, 5},
									   {6, 6}};
	EXPECT_EQ(tree.to_vec(), res);
	std::stringstream ss;
	tree.inorder(ss);
	EXPECT_EQ(ss.str(), "(1, 1)\n(2, 2)\n(3, 3)\n(4, 4)\n(5, 5)\n(6, 6)\n");
}

TEST(SUITE, Insert_Duplicated)
{
	AVL_Tree<int, int> tree = AVL_Tree<int, int>();
	EXPECT_EQ(tree.insert(1, 1), SUCCESS);
	EXPECT_EQ(tree.insert(2, 2), SUCCESS);
	EXPECT_EQ(tree.insert(3, 3), SUCCESS);
	EXPECT_EQ(tree.insert(4, 4), SUCCESS);
	EXPECT_EQ(tree.insert(5, 5), SUCCESS);
	EXPECT_EQ(tree.insert(6, 6), SUCCESS);
	ASSERT_TRUE(tree.is_valid());
	EXPECT_EQ(tree.get_size(), 6);
	std::vector<Pair<int, int>> res = {Pair<int, int>(1, 1), Pair<int, int>(2, 2), Pair<int, int>(3, 3),
									   Pair<int, int>(4, 4), Pair<int, int>(5, 5), Pair<int, int>(6, 6)};
	EXPECT_EQ(tree.to_vec(), res);
	std::stringstream ss;
	tree.inorder(ss);
	EXPECT_EQ(ss.str(), "(1, 1)\n(2, 2)\n(3, 3)\n(4, 4)\n(5, 5)\n(6, 6)\n");
	
	EXPECT_EQ(tree.insert(2, 3), FAILURE);
	ASSERT_TRUE(tree.is_valid());
	EXPECT_EQ(tree.get_size(), 6);
	EXPECT_EQ(tree.to_vec(), res);
	ss.str(std::string());
	tree.inorder(ss);
	EXPECT_EQ(ss.str(), "(1, 1)\n(2, 2)\n(3, 3)\n(4, 4)\n(5, 5)\n(6, 6)\n");
}

TEST_F(AVLTreeFixture, Find)
{
	for (auto pair : vec)
	{
		auto res = avlTree.find(pair.get_first());
		EXPECT_EQ(res.status(), SUCCESS);
		EXPECT_EQ(res.ans(), pair.get_second());
	}
}

TEST_F(AVLTreeFixture, FindNonExistent)
{
	EXPECT_EQ(avlTree.find(-1).status(), FAILURE);
}

TEST(SUITE, FindInEmptyTree)
{
	auto tree = AVL_Tree<int, int>();
	EXPECT_EQ(tree.find(0).status(), FAILURE);
}

TEST_F(AVLTreeFixture, MinMax)
{
	// Get the minimum element
	EXPECT_EQ(avlTree.get_min().status(), SUCCESS);
	EXPECT_EQ(avlTree.get_min().ans(), vec[0].get_second());
	
	// Get the maximum element
	EXPECT_EQ(avlTree.get_max().status(), SUCCESS);
	EXPECT_EQ(avlTree.get_max().ans(), vec[vec.size() - 1].get_second());
}

TEST_F(AVLTreeFixture, MinMaxEmptyTree)
{
	auto tree = AVL_Tree<int, int>();
	EXPECT_EQ(tree.get_min().status(), FAILURE);
	EXPECT_EQ(tree.get_max().status(), FAILURE);
}

TEST_F(AVLTreeFixture, Remove)
{
	for (auto pair : vec)
	{
		EXPECT_EQ(avlTree.remove(pair.get_first()), SUCCESS);
		ASSERT_TRUE(avlTree.is_valid());
		--size;
		EXPECT_EQ(avlTree.get_size(), size);
		EXPECT_EQ(avlTree.find(pair.get_first()).status(), FAILURE);
	}
	ASSERT_EQ(avlTree.get_size(), 0);
	ASSERT_TRUE(avlTree.is_valid());
}
TEST_F(AVLTreeFixture, ConstructFromSortedArray)
{
	int* values = new int[vec.size()];
	int* keys = new int[vec.size()];
	for (int i = 0; i < vec.size(); ++i)
	{
		keys[i] = vec[i].get_first();
		values[i] = vec[i].get_second();
	}
	
	auto tree = AVL_Tree<int, int>(values, keys, vec.size());
	ASSERT_TRUE(tree.is_valid());
	EXPECT_EQ(tree.to_vec(), vec);
	std::stringstream ss;
	tree.inorder(ss);
	EXPECT_EQ(ss.str(), str);
	EXPECT_EQ(tree.get_size(), vec.size());
	EXPECT_EQ(tree.get_min().status(), SUCCESS);
	EXPECT_EQ(tree.get_min().ans(), vec[0].get_second());
	EXPECT_EQ(tree.get_max().status(), SUCCESS);
	EXPECT_EQ(tree.get_max().ans(), vec[vec.size() - 1].get_second());
	for (auto pair : vec)
	{
		auto res = tree.find(pair.get_first());
		EXPECT_EQ(res.status(), SUCCESS);
		EXPECT_EQ(res.ans(), pair.get_second());
	}
}

TEST(SUITE, ConstructFromEmptyArray)
{
	auto tree = AVL_Tree<int, int>(nullptr, nullptr, 0);
	ASSERT_TRUE(tree.is_valid());
	EXPECT_EQ(tree.get_size(), 0);
	std::vector<Pair<int, int>> v = std::vector<Pair<int, int>>();
	EXPECT_EQ(tree.to_vec(), v);
	std::stringstream ss;
	tree.inorder(ss);
	EXPECT_EQ(ss.str(), "");
}

TEST_F(AVLTreeFixture, checkExtra)
{
	int* values = new int[vec.size()];
	int* keys = new int[vec.size()];
	for (int i = 0; i < vec.size(); ++i)
	{
		keys[i] = vec[i].get_first();
		values[i] = vec[i].get_second();
	}
	auto tree = AVL_Tree<int, int>(values, keys, vec.size());
	ASSERT_TRUE(tree.is_valid());
	tree.add_extra(8, 4);
	for(auto pair : vec)
	{
		output_t<int> valueByTree = tree.get_path_extra(pair.get_first());
		EXPECT_EQ(valueByTree.status(), SUCCESS);
		if(pair.get_first() > 8)
		{
			EXPECT_EQ(valueByTree.ans(), 0);
		}
		else
		{
			EXPECT_EQ(valueByTree.ans(), 4);
		}
	}
	tree.add_extra(4, -3);
	for(auto pair : vec)
	{
		output_t<int> valueByTree = tree.get_path_extra(pair.get_first());
		EXPECT_EQ(valueByTree.status(), SUCCESS);
		if(pair.get_first() > 8)
		{
			EXPECT_EQ(valueByTree.ans(), 0);
		}
		else if(pair.get_first() > 4)
		{
			EXPECT_EQ(valueByTree.ans(), 4);
		}
		else
		{
			EXPECT_EQ(valueByTree.ans(), 1);
		}
	}
}


TEST_F(AVLTreeFixture, checkExtraWithRotates)
{
	auto copyVec = std::vector<Pair<int, int>>(vec);
	int* values = new int[copyVec.size()];
	int* keys = new int[copyVec.size()];
	for (int i = 0; i < copyVec.size(); ++i)
	{
		keys[i] = copyVec[i].get_first();
		values[i] = copyVec[i].get_second();
	}
	auto tree = AVL_Tree<int, int>(values, keys, copyVec.size());
	ASSERT_TRUE(tree.is_valid());
	tree.add_extra(8, 4);
	tree.add_extra(4, -3);

	for(int i = 0, count = 0; count <= 10; i++){
		bool flag2 = true;
		for(const auto& pair : copyVec)
		{
			if(pair.get_first()==i)
				flag2 = false;
		}
		if(flag2){
			count++;
			tree.insert(i, i);
			copyVec.emplace_back(i, i);
		}
	}
	for(const auto& pair : copyVec)
	{
		bool isInOriginal = false;
		for(const auto& pair2 : vec)
		{
			if(pair.get_first() == pair2.get_first())
			{
				isInOriginal = true;
				break;
			}
		}
		output_t<int> valueByTree = tree.get_path_extra(pair.get_first());
		EXPECT_EQ(valueByTree.status(), SUCCESS);
		if(!isInOriginal)
		{
			EXPECT_EQ(valueByTree.ans(), 0);
		}
		else if(pair.get_first() > 8 )
		{
			EXPECT_EQ(valueByTree.ans(), 0);
		}
		else if(pair.get_first() > 4)
		{
			EXPECT_EQ(valueByTree.ans(), 4);
		}
		else
		{
			EXPECT_EQ(valueByTree.ans(), 1);
		}
	}
}

