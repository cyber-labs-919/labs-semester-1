/*
# lz77
WINDOW = 20
LOOKAHEAD = 10

# oh hello my hellishly handsome friend
#

"""
Returns None or a tuple: distance of the match from the end of the buffer and length of the match

Algorithm:
 
1. i = 0, offset = 0, cur_longest_match = 0, cur_distance = None
2. if i + offset >= len(buffer): 
   if offset > 0 and offset < min_match_length: return None
   if offset > 0 and offset >= min_match_length: return (offset, len(buffer) - i + offset)
   if offset == 0 cur_longest_match < min_match_length: return None
   else: return (cur_distance, min_match_length)
3. if offset is greater than the substring length - we've found an exact match, return (len(buffer)-i+offset, len(substr))
4. if buffer[i] letter matches substr[offset] - increment offset and i, go to step 2
5. else, if it doesn't match - if offset > cur_longest_match - we've found a new longest match,
set cur_longest_match to offset and cur_distance to len(buffer)-i
6. reset offset, increment i and go to step 2
"""
def find_longest_match(buffer, substr, min_match_length=2):
    i = 0
    offset = 0
    cur_longest_match = 0
    cur_distance = None
    while i < len(buffer):
        if offset >= len(substr):
            if offset < min_match_length:
                return None
            return (len(buffer) - i + offset, len(substr))
        if buffer[i] == substr[offset]:
            offset += 1
        else:
            if offset > cur_longest_match:
                cur_longest_match = offset
                cur_distance = len(buffer) - i + offset
            offset = 0
        i += 1

    if offset > 0:
        if offset < min_match_length:
            return None

        return (len(buffer) - i + offset, offset)

    if cur_longest_match < min_match_length:
        return None

    return (cur_distance, cur_longest_match)


def test_find_longest_match():
    test_cases = [
        ("hello world", "hello", (11, 5)),
        ("oh shells are nice", "hello", (14, 4)),
        ("oh shells are nice", "shells", (15, 6)),
        ("ababababa", "bab", (8, 3)),
        ("hello", "green", None),
        ("brother", "oh", None),
        ("hello world", "world", (5, 5)),
        ("hello worlds", "world", (6, 5)),
        ("hello world", "worldwide", (5, 5)),
        ("hello worlds", "worldwide", (6, 5)),
    ]

    failure = False
    for test_i in range(len(test_cases)):
        buffer, substr, expected = test_cases[test_i]
        actual = find_longest_match(buffer, substr)
        if not actual == expected:
            failure = True
            print(f"Test {test_i+1} failed: expected {expected}, got {actual}")

    if failure:
        raise Exception("Test failed")

def compress(inp):
    res = []

    i = 0
    while i < len(inp):
        substr_end = min(i + LOOKAHEAD, len(inp))
        substr = inp[i:substr_end]
        window_start = max(0, i - WINDOW)
        buffer = inp[window_start:i]
        match = find_longest_match(buffer, substr)
        if match is None:
            res.append((False, substr[0]))
            i += 1
        else:
            distance, length = match
            res.append((True, match))
            i += length

    return res

def decode(inp):
    res = ""
    for i in range(len(inp)):

        if inp[i][0]:
            distance, length = inp[i][1]
            substr = res[-distance:-distance+length]
            res += substr
        else:
            res += inp[i][1]

    return res

if __name__ == "__main__":
    test_find_longest_match();
    while True:
        s = input("String: ")
        compressed = compress(s)
        print(compressed)
        print(decode(compressed))

*/

// translate the above to c++

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define WINDOW 20
#define LOOKAHEAD 10

void find_longest_match(const char* buffer, const char* substr, int min_match_length, int* match_start, int* match_length) {
    int i = 0;
    int offset = 0;
    int cur_longest_match = 0;
    int cur_distance = 0;
    while (i < strlen(buffer)) {
        if (offset >= strlen(substr)) {
            if (offset < min_match_length) {
                *match_start = -1;
                *match_length = 0;
                return;
            }
            *match_start = strlen(buffer) - i + offset;
            *match_length = strlen(substr);
            return;
        }
        if (buffer[i] == substr[offset]) {
            offset++;
        } else {
            if (offset > cur_longest_match) {
                cur_longest_match = offset;
                cur_distance = strlen(buffer) - i + offset;
            }
            offset = 0;
        }
        i++;
    }
    if (offset > 0) {
        if (offset < min_match_length) {
            *match_start = -1;
            *match_length = 0;
            return;
        }
        *match_start = strlen(buffer) - i + offset;
        *match_length = offset;
        return;
    }
    if (cur_longest_match < min_match_length) {
        *match_start = -1;
        *match_length = 0;
        return;
    }
    *match_start = cur_distance;
    *match_length = cur_longest_match;
}

struct TestCase {
    const char* buffer;
    const char* substr;
    int expected_start;
    int expected_length;
};

void test_find_longest_match() {
    TestCase test_cases[] = {
        {"hello world", "hello", 11, 5},
        {"oh shells are nice", "hello", 14, 4},
        {"oh shells are nice", "shells", 15, 6},
        {"ababababa", "bab", 8, 3},
        {"hello", "green", -1, 0},
        {"brother", "oh", -1, 0},
        {"hello world", "world", 5, 5},
        {"hello worlds", "world", 6, 5},
        {"hello world", "worldwide", 5, 5},
        {"hello worlds", "worldwide", 6, 5},
    };

    for (int i = 0; i < sizeof(test_cases) / sizeof(TestCase); i++) {
        TestCase test_case = test_cases[i];
        int match_start = 0;
        int match_length = 0;
        find_longest_match(test_case.buffer, test_case.substr, 2, &match_start, &match_length);
        if (match_start != test_case.expected_start || match_length != test_case.expected_length) {
            std::cout << "Test " << i + 1 << " failed: expected (" << test_case.expected_start << ", " << test_case.expected_length << "), got (" << match_start << ", " << match_length << ")" << std::endl;
        }
    }
}

class CompressedEntry {
public:
    bool isJump;
};

class CompressedJumpEntry : public CompressedEntry {
public:
    int distance;
    int length;

    CompressedJumpEntry(int distance, int length) {
        isJump = true;
        this->distance = distance;
        this->length = length;
    }
};

class CompressedCharEntry : public CompressedEntry {
public:
    char c;

    CompressedCharEntry(char c) {
        isJump = false;
        this->c = c;
    }
};

void compress(const char* inp, std::vector<CompressedEntry*>* res) {
    int i = 0;
    while (i < strlen(inp)) {
        int substr_end = std::min(i + LOOKAHEAD, (int)strlen(inp));
        std::string cppSubstr(inp + i, inp + substr_end);
        const char* cSubstr = cppSubstr.c_str();
        int window_start = std::max(0, i - WINDOW);
        std::string cppBuffer(inp + window_start, inp + i);
        const char* cBuffer = cppBuffer.c_str();
        int match_start = 0;
        int match_length = 0;
        find_longest_match(cBuffer, cSubstr, 2, &match_start, &match_length);
        if (match_start == -1) {
            CompressedCharEntry* entry = new CompressedCharEntry(inp[i]);
            res->push_back(entry);
            ++i;
        } else {
            CompressedJumpEntry* entry = new CompressedJumpEntry(match_start, match_length);
            res->push_back(entry);
            i += match_length;
        }
    }
}

void decode(const std::vector<CompressedEntry*>& inp, std::string* res) {
    for (int i = 0; i < inp.size(); i++) {
        if (inp[i]->isJump) {
            CompressedJumpEntry* entry = (CompressedJumpEntry*)inp[i];
            int distance = entry->distance;
            int length = entry->length;
            std::string substr = res->substr(res->size() - distance, length);
            *res += substr;
        } else {
            CompressedCharEntry* entry = (CompressedCharEntry*)inp[i];
            *res += entry->c;
        }
    }
}

int  main() {
    test_find_longest_match();
    while (true) {
        std::string s;
        std::getline(std::cin, s);
        std::vector<CompressedEntry*> compressed;
        compress(s.c_str(), &compressed);
        // output vector of compressed entries
        for (int i = 0; i < compressed.size(); i++) {
            if (compressed[i]->isJump) {
                CompressedJumpEntry* entry = (CompressedJumpEntry*)compressed[i];
                std::cout << "J " << entry->distance << " " << entry->length << std::endl;
            } else {
                CompressedCharEntry* entry = (CompressedCharEntry*)compressed[i];
                std::cout << "C " << entry->c << std::endl;
            }
        }
        std::string decoded;
        decode(compressed, &decoded);
        std::cout << decoded << std::endl;
    }
}