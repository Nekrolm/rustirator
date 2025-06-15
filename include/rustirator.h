#include <vector>
#include <cstdint>
#include <ranges>
#include <concepts>

// Rust-like Iterator wrapper to provide convenient and
// autocomlete friendly way to use C++20 ranges in your code base
//
// Example
// 
// vector<int> v = {1, 2, 3, 4, 5};
// vector<float> result = into_iter(v).map([](int x) -> float {
//      return x * x / 10.0;
// }).collect();
//

namespace rustirator {

namespace views = ::std::views;
namespace range = ::std::ranges;

template<typename C, typename R>
concept Collectable = range::range<R> && 
                      std::constructible_from<C, 
                                range::iterator_t<R>, 
                                range::sentinel_t<R>>;

template <range::range R> 
struct Collector {
    template <Collectable<R> C>
    operator C() && {
        return C(range::begin(range), range::end(range));
    }

    explicit Collector(auto&& r) : range{ std::forward<decltype(r)>(r) } {}

private:
    R range;
};

template <range::range R>
struct Iterator {
    auto collect() &&;

    auto map(std::invocable<range::range_value_t<R>> auto && f) &&;
    auto filter(std::predicate<range::range_value_t<R>> auto && f) &&;
    auto take(std::size_t n) &&;
    auto drop(std::size_t n) &&;
    auto take_while(std::predicate<range::range_value_t<R>> auto&& f) &&;

    explicit Iterator(auto&& r) : range{ std::forward<decltype(r)>(r) } {}

private:
    R range;
};

auto into_iter = []<range::range R>(R&& r) {
    return Iterator<std::remove_cvref_t<R>>{std::forward<R>(r)};
};


auto iter = []<range::range R>(R&& r) {
    return into_iter(std::forward<R>(r) | views::all);
};

template <range::range R>
auto Iterator<R>::filter(std::predicate<range::range_value_t<R>> auto && f) && 
{
    return into_iter(std::move(range) | views::filter(
        std::forward<decltype(f)>(f)));
}

template <range::range R>
auto Iterator<R>::take(std::size_t n) && 
{
    return into_iter(std::move(range) | views::take(n));
}

template <range::range R>
auto Iterator<R>::drop(std::size_t n) && 
{
    return into_iter(std::move(range) | views::drop(n));
}

template <range::range R>
auto Iterator<R>::take_while(std::predicate<range::range_value_t<R>> auto&& f) && 
{
    return into_iter(std::move(range) | views::take_while(
        std::forward<decltype(f)>(f)));
}




template <range::range R>
auto Iterator<R>::map(std::invocable<range::range_value_t<R>> auto && f) && {
    return into_iter(std::move(range) | views::transform(
        std::forward<decltype(f)>(f)));
}

template <range::range R>
auto Iterator<R>::collect() &&{
    return Collector<R> {
        std::move(range)
    };
}

} // rustirator