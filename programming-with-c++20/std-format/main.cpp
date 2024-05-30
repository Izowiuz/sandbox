#include <cstdlib>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"

class StockIndex
{
    std::string mName{};
    double mLastPoints{ 0 };
    double mPoints{ 0 };

public:
    StockIndex(std::string&& name)
        : mName{ std::move(name) }
    {
    }

    const std::string& name() const
    {
        return mName;
    }

    void setPoints(double points)
    {
        mLastPoints = mPoints;
        mPoints = points;
    }

    double points() const
    {
        return mPoints;
    }

    double pointsDiff() const
    {
        return mPoints - mLastPoints;
    }

    double pointsPercent() const
    {
        if (0.0 == mLastPoints) {
            return 0.0;
        }

        return (mPoints - mLastPoints) / mLastPoints * 100.0;
    }
};

template <>
struct std::formatter<StockIndex> {
    constexpr auto parse(auto& ctx)
    {
        if (*ctx.end() == ':') {
            throw format_error("invalid format");
        }

        return ctx.begin();
    }

    auto format(StockIndex const& index, auto& ctx) const
    {
        return std::format_to(ctx.out(),
                              "{:10} {:>8.2f} {:>6.2f} {:>6.2f}%",
                              index.name(),
                              index.points(),
                              index.pointsDiff(),
                              index.pointsPercent());
    }
};

std::vector<StockIndex> getIndices()
{
    StockIndex dax{ "DAX" };
    dax.setPoints(13'052.95);
    dax.setPoints(13'108.50);

    StockIndex dow{ "DOW" };
    dow.setPoints(29'080.17);
    dow.setPoints(29'290.00);

    StockIndex sp{ "S&P 500" };
    sp.setPoints(3'537.01);
    sp.setPoints(3'561.50);

    return { dax, dow, sp };
}

int main()
{
    // control character escape
    std::cout << std::format("String \"{}\" and a curly bracket {{ yo!\n", "lalala");
    std::cout << "\n";

    // formatting table
    for (auto const& index : getIndices()) {
        std::cout << std::format("{:10} {:>8.2f} {:>6.2f} {:>6.2f}%\n",
                                 index.name(),
                                 index.points(),
                                 index.pointsDiff(),
                                 index.pointsPercent());
    }
    std::cout << "\n";

    // formatting by custom fromatter
    for (auto const& index : getIndices()) {
        std::cout << std::format("{}\n", index);
    }

    return EXIT_SUCCESS;
}
