#include <cstdlib>
#include <limits>
#include <spdlog/spdlog.h>
#include <unordered_map>

/*
Pete likes to bake some cakes. He has some recipes and ingredients. Unfortunately he is not good in
maths. Can you help him to find out, how many cakes he could bake considering his recipes?

Write a function cakes(), which takes the recipe (unordered_map<string, int>) and the available
ingredients (also an unordered_map<string, int>) and returns the maximum number of cakes Pete can
bake (integer). For simplicity there are no units for the amounts (e.g. 1 lb of flour or 200 g of
sugar are simply 1 or 200). Ingredients that are not present in the objects, can be considered as 0.

Examples:

// must return 2
cakes({{"flour", 500}, {"sugar", 200}, {"eggs", 1}}, {{"flour", 1200}, {"sugar", 1200}, {"eggs", 5},
{"milk", 200}});
// must return 0
cakes({{"apples", 3}, {"flour", 300}, {"sugar", 150}, {"milk", 100}, {"oil", 100}}, {{"sugar", 500},
{"flour", 2000}, {"milk", 2000}});
*/

using Ingredients = std::unordered_map<std::string, int>;

int checkIngredient(int needs, int available)
{
    if (available < needs || needs <= 0 || available <= 0) {
        return 0;
    }

    return available / needs;
}

int cakes(const Ingredients& recipe, const Ingredients& available)
{
    int cakes = std::numeric_limits<int>::max();

    for (auto const& [ingredient, needs] : recipe) {
        auto it = available.find(ingredient);
        if (it == available.end()) {
            return 0;
        }

        auto const cakesFromIngredient = checkIngredient(needs, it->second);
        cakes = std::min(cakes, cakesFromIngredient);
    }

    return cakes;
}

int main()
{
    spdlog::info(cakes({ { "flour", 500 }, { "sugar", 200 }, { "eggs", 1 } },
                       { { "flour", 1200 }, { "sugar", 1200 }, { "eggs", 5 }, { "milk", 200 } }));

    spdlog::info(cakes(
        { { "apples", 3 }, { "flour", 300 }, { "sugar", 150 }, { "milk", 100 }, { "oil", 100 } },
        { { "sugar", 500 }, { "flour", 2000 }, { "milk", 2000 } }));

    return EXIT_SUCCESS;
}
