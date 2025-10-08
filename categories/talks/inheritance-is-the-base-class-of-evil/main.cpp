#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

namespace ObjectTools
{

template <typename T>
void draw(const T& x, std::ostream& out)
{
    out << x << std::endl;
}

}   // namespace ObjectTools

class Object
{
public:
    template <typename T>
    explicit Object(T x)
        : mData{ std::make_shared<Model<T>>(std::move(x)) }
    {
    }

    // inline friend function definition
    friend void draw(const Object& object, std::ostream& out)
    {
        object.mData->draw(out);
    }

private:
    struct Concept {
        virtual ~Concept() = default;
        virtual void draw(std::ostream& out) const = 0;
    };

    template <typename T>
    struct Model : public Concept {
        explicit Model(T x)
            : mData{ std::move(x) }
        {
        }

        void draw(std::ostream& out) const override
        {
            ObjectTools::draw(mData, out);
        }

        T mData;
    };

    std::shared_ptr<const Concept> mData;
};

int main()
{
    std::vector<Object> vec;
    vec.reserve(4);

    vec.emplace_back(1);
    vec.emplace_back(std::string{ "lalala" });
    vec.emplace_back(1.1F);
    vec.emplace_back("ddd");

    for (const auto& e : vec) {
        draw(e, std::cout);
    }

    return EXIT_SUCCESS;
}
