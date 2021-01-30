#include "utils.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

class FirstNRepeatingStream
{
public:
    explicit FirstNRepeatingStream(int N) : mN(N) {}

    char next(char c)
    {
        // Count chars
        const int code = c;
        ++mCharCount[code];
        // Remember input chars
        if (const int count = mCharCount[code]; count <= mN)
            mInputChars.emplace_back(code);
        else
            mInputChars.erase(std::remove(mInputChars.begin(), mInputChars.end(), code),
                              mInputChars.end());
        return !mInputChars.empty() ? mInputChars.front() : '0';
    }

private:
    const int mN = 0;
    std::array<int, 255> mCharCount = {0};
    std::vector<char> mInputChars;
};

std::string ConvertInput(const int N, std::string_view input)
{
    FirstNRepeatingStream fs(N);
    std::string out;
    out.reserve(input.length());
    for (auto ch : input)
        out.push_back(fs.next(ch));
    return out;
};

struct Test
{
public:
    virtual void run() const = 0;
};

struct test1 : Test
{
    void run() const override
    {
        {
            FirstNRepeatingStream fs(1);
            char n = fs.next('a');
            assert(n == 'a');
        }
        {
            FirstNRepeatingStream fs(1);
            char n = fs.next('0');
            assert(n == '0');
        }
        {
            FirstNRepeatingStream fs(1);
            char n = fs.next('1');
            assert(n == '1');
        }
    }
};

struct test2 : Test
{
    void run() const override
    {
        {
            auto out = ConvertInput(1, "aaaaa");
            assert(out == "a0000");
        }
        {
            auto out = ConvertInput(1, "abbc");
            assert(out == "aaaa");
        }
        {
            auto out = ConvertInput(1, "cbba");
            assert(out == "cccc");
        }
    }
};

struct test3 : Test
{
    void run() const override
    {
        auto out = ConvertInput(1, "abbcacfg");
        assert(out == "aaaac0ff");
    }
};

struct test4 : Test
{
    void run() const override
    {
        auto out = ConvertInput(2, "bcfbfcbccfccbb");
        assert(out == "bbbbbbcff00000");
    }
};

struct test5 : Test
{
    void run() const override
    {
        {
            auto out = ConvertInput(2, "aaa");
            assert(out == "aa0");
        }
        {
            auto out = ConvertInput(3, "aaa");
            assert(out == "aaa");
        }
        {
            auto out = ConvertInput(3, "aaababbb");
            assert(out == "aaaabbb0");
        }
        {
            auto out = ConvertInput(3, "abcabcabc");
            assert(out == "aaaaaaaaa");
        }
    }
};

struct perfomance_test1 : Test
{
    void run() const override
    {
        auto out = ConvertInput(
            1,
            "bcfbfcbccfccbbgkhkkgloyptyptyiovneutyoyjgjfjdjjfgjfkjdhmnbbbbbvcvcbfgdfhhtfhgfdsfsdfdf"
            "dgfdgfhfhpoyoprteoiiiiiiiiiiiaaaaaaaaaaaekkkkvkkkvkvkfgkfjkfjhkfjhkgjhjhkhjkgjlfghklfg"
            "khljgfhjfhjlkfgjhrtueryhuhqqwewqewretretretkkfjhklgjhurhgjfjhgjfhjfhjjfjljldfjglkdfjgl"
            "kdfjklvbbcccccccccccxxxxxxxxxxxxxqqqqqqqqqqqjjjdfhjkdhgkjfdhgt");
        assert(
            out
            == "bbbcc000000000ggggghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhlllllllllllllllllllllllllllll"
               "llllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllluu"
               "uuuuuuuuuuuuuuuuuuuuuuuuummmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm"
               "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");
    }
};

struct perfomance_test2 : Test
{
    void run() const override
    {
        auto out = ConvertInput(
            2,
            "bcfbfcbccfccbbgkhkkgloyptyptyiovneutyoyjgjfjdjjfgjfkjdhmnbbbbbvcvcbfgdfhhtfhgfdsfsdfdf"
            "dgfdgfhfhpoyoprteoiiiiiiiiiiiaaaaaaaaaaaekkkkvkkkvkvkfgkfjkfjhkfjhkgjhjhkhjkgjlfghklfg"
            "khljgfhjfhjlkfgjhrtueryhuhqqwewqewretretretkkfjhklgjhurhgjfjhgjfhjfhjjfjljldfjglkdfjgl"
            "kdfjklvbbcccccccccccxxxxxxxxxxxxxqqqqqqqqqqqjjjdfhjkdhgkjfdhgt");
        assert(
            out
            == "bbbbbbcff00000gggggggggggggggggggggggggghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhllllllllllll"
               "lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll"
               "lllnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn"
               "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn");
    }
};

struct perfomance_test3 : Test
{
    void run() const override
    {
        auto out = ConvertInput(
            3,
            "bcfbfcbccfccbbgkhkkgloyptyptyiovneutyoyjgjfjdjjfgjfkjdhmnbbbbbvcvcbfgdfhhtfhgfdsfsdfdf"
            "dgfdgfhfhpoyoprteoiiiiiiiiiiiaaaaaaaaaaaekkkkvkkkvkvkfgkfjkfjhkfjhkgjhjhkhjkgjlfghklfg"
            "khljgfhjfhjlkfgjhrtueryhuhqqwewqewretretretkkfjhklgjhurhgjfjhgjfhjfhjjfjljldfjglkdfjgl"
            "kdfjklvbbcccccccccccxxxxxxxxxxxxxqqqqqqqqqqqjjjdfhjkdhgkjfdhgt");
        assert(
            out
            == "bbbbbbbbbbbbffffffffffffffffffffffffffffffggggggkkkhhhhhhhhhhhhhhhhhhhhhlllllllllll"
               "lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll"
               "llllllllnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn"
               "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn");
    }
};

struct perfomance_test4 : Test
{
    void run() const override
    {
        auto out = ConvertInput(
            3,
            "bcfbfcbccfccbbgkhkkgloyptyptyiovneutyoyjgjfjdjjfgjfkjdhmnbbbbbvcvcbfgdfhhtfhgfdsfsdfdf"
            "dgfdgfhfhpoyoprteoiiiiiiiiiiiaaaaaaaaaaaekkkkvkkkvkvkfgkfjkfjhkfjhkgjhjhkhjkgjlfghklfg"
            "khljgfhjfhjlkfgjhrtueryhuhqqwewqewretretretkkfjhklgjhurhgjfjhgjfhjfhjjfjljldfjglkdfjgl"
            "kdfjklvbbcccccccccccxxxxxxxxxxxxxqqqqqqqqqqqjjjdfhjkdhgkjfdhgt");
        assert(
            out
            == "bbbbbbbbbbbbffffffffffffffffffffffffffffffggggggkkkhhhhhhhhhhhhhhhhhhhhhlllllllllll"
               "lllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll"
               "llllllllnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn"
               "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn");
    }
};

struct perfomance_test5 : Test
{
    void run() const override
    {
        auto out = ConvertInput(
            10,
            "bcfbfcbccfccbbgkhkkgloyptyptyiovneutyoyjgjfjdjjfgjfkjdhmnbbbbbvcvcbfgdfhhtfhgfdsfsdfdf"
            "dgfdgfhfhpoyoprteoiiiiiiiiiiiaaaaaaaaaaaekkkkvkkkvkvkfgkfjkfjhkfjhkgjhjhkhjkgjlfghklfg"
            "khljgfhjfhjlkfgjhrtueryhuhqqwewqewretretretkkfjhklgjhurhgjfjhgjfhjfhjjfjljldfjglkdfjgl"
            "kdfjklvbbcccccccccccxxxxxxxxxxxxxqqqqqqqqqqqjjjdfhjkdhgkjfdhgt");
        assert(
            out
            == "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccc"
               "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
               "ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc"
               "ccccccccccccccccccccooooooooooooooooooooooooooooooooooooooooooooooooooo");
    }
};

int main()
{
    std::vector<std::unique_ptr<Test>> tests;
    tests.push_back(std::make_unique<test1>());
    tests.push_back(std::make_unique<test2>());
    tests.push_back(std::make_unique<test3>());
    tests.push_back(std::make_unique<test4>());
    tests.push_back(std::make_unique<test5>());
    tests.push_back(std::make_unique<perfomance_test1>());
    tests.push_back(std::make_unique<perfomance_test2>());
    tests.push_back(std::make_unique<perfomance_test3>());
    tests.push_back(std::make_unique<perfomance_test4>());
    tests.push_back(std::make_unique<perfomance_test5>());

    size_t count = 0;
    for (const auto& item : tests) {
        std::cout << "Test " << ++count << ": ";
        Timer t;
        t.start();
        item->run();
        t.stop();
        std::cout << "duration: " << t.duration() << "\n";
    }
    return 0;
}
