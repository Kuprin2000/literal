// Cтандарт C++11 добавляет средства для создания т. н. пользовательских литералов (user-defined literals) для суффиксов. Определите структуру для строк с кастомными литералами
// template <char ...c> struct TString { };
// и необходимые операторы так, чтобы компилировался код:
// constexpr auto hello = "hello"_s + " world"_s;
// static_assert(hello == "hello world"_s);

template<char ... c>
struct TString
{
	static constexpr const char value[sizeof...(c) + 1u] = { c..., '\0' };
};

template <class A, class B>
struct Concat;

template <char... a, char... b>
struct Concat<TString<a...>, TString<b...>>
{
	using type = TString<a..., b...>;
};

template <class T>
struct Get;

template <char... c>
struct Get<TString<c...>>
{
	static constexpr char value[sizeof...(c) + 1u] = { c..., '\0' };
};

template <char... a, char... b>
constexpr auto operator+(const TString<a...>&, const TString<b...>&)
{
	return typename Concat<TString<a...>, TString<b...>>::type{};
}

template <char... a, char... b>
constexpr bool operator==(const TString<a...>&, const TString<b...>&)
{
	return Get<TString<a...>>::value == Get<TString<b...>>::value;
}

template<typename TChar, TChar ...s>
constexpr TString<s...> operator"" _s()
{
	return TString<s...>{};
}

constexpr auto hello = "hello"_s + " world"_s;
static_assert(hello == "hello world"_s);

int main()
{
	return 0;
}