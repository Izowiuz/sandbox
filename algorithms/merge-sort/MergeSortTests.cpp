#include <gtest/gtest.h>

#include "merge-sort.h"

#include <spdlog/spdlog.h>

#include <vector>

using namespace seeker::algorithms;

class MergeSortTests : public ::testing::Test
{
public:
    MergeSortTests() = default;
};

TEST_F(MergeSortTests, MergeSort_v1)
{
    std::vector<int> vec{ 0, 5, 2, 6, 3, 89, 11, 4, 100, 12, 1001 };
    std::vector<int> sorted_vec{ 0, 2, 3, 4, 5, 6, 11, 12, 89, 100, 1001 };

    const auto sorted = seeker::algorithms::merge_sort_v1(vec);

    ASSERT_EQ(sorted, sorted_vec);
}
