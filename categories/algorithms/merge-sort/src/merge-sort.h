#pragma once

#include <spdlog/spdlog.h>

namespace seeker::algorithms
{

template <typename VecType>
std::vector<VecType> merge_v1(std::vector<VecType> const& left, std::vector<VecType> const& right)
{
    std::vector<VecType> out;
    out.reserve(left.size() + right.size());

    int leftItr = 0;
    int rightItr = 0;

    for (int i = 0; i < left.size() + right.size(); ++i) {
        if (leftItr < left.size() && rightItr < right.size()) {
            if (left[leftItr] < right[rightItr]) {
                out.push_back(left[leftItr++]);
            } else {
                out.push_back(right[rightItr++]);
            }
        } else if (leftItr < left.size()) {
            out.push_back(left[leftItr++]);
        } else if (rightItr < right.size()) {
            out.push_back(right[rightItr++]);
        }
    }

    return { out };
}

template <typename VecType>
std::vector<VecType> merge_sort_v1(std::vector<VecType> const& vec)
{
    // end recursion - single element vector is by definition sorted
    if (vec.size() == 1) {
        return { vec };
    }

    std::size_t const middleIndex = vec.size() / 2;

    std::vector<VecType> const leftUnsorted(vec.begin(), vec.begin() + middleIndex);
    std::vector<VecType> const rightUnsorted(vec.begin() + middleIndex, vec.end());

    auto leftSorted = merge_sort_v1(leftUnsorted);
    auto rightSorted = merge_sort_v1(rightUnsorted);

    return merge_v1(leftSorted, rightSorted);
}

}   // namespace seeker::algorithms
