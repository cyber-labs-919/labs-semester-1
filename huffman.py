
# huffman compression

class GroupNode:
    def __init__(self, left, right):
        self.left = left
        self.right = right
        self.freq = left.freq + right.freq

    def get_full_str(self):
        return f"{self.get_char_str()}:{self.freq}"

    def get_char_str(self):
        return f"{self.left.get_char_str()}{self.right.get_char_str()}"

    def __repr__(self):
        return self.get_full_str()

class CharNode:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq

    def get_full_str(self):
        return f"{self.char}:{self.freq}"

    def get_char_str(self):
        return self.char

    def __repr__(self):
        return self.get_full_str()

def get_initial_frequency_list(s):
    """
    Returns a sorted list of CharNodes.
    """
    table = {}
    for c in s:
        if c in table:
            table[c] += 1
        else:
            table[c] = 1

    freq_list = []
    for k, v in table.items():
        freq_list.append(CharNode(k, v))

    return sort_frequency_list(freq_list)

def sort_frequency_list(freq_list):
    return list(sorted(freq_list, key=lambda x: x.freq))

def visit_node(node, code_map, cur_code):
    if isinstance(node, CharNode):
        code_map[node.char] = cur_code
        return

    code_1 = cur_code + "0"
    code_2 = cur_code + "1"
    visit_node(node.left, code_map, code_1)
    visit_node(node.right, code_map, code_2)


def root_node_to_code_map(root_node):
    code_map = {}

    cur_code = ""
    visit_node(root_node, code_map, cur_code)
    return code_map


def encode(s):
    freq_list = get_initial_frequency_list(s)
    while len(freq_list) > 1:
        l, r = freq_list[0], freq_list[1]
        root_node = GroupNode(l, r)
        freq_list = sort_frequency_list([root_node, *freq_list[2:]])

    char_to_path = root_node_to_code_map(freq_list[0])

    result = ""
    for char in s:
        result += char_to_path[char]

    return result, char_to_path

def decode(stream, char_to_path):
    path_to_char = {v: k for k, v in char_to_path.items()}
    result = ""
    cur_code = ""
    for bit in stream:
        cur_code += bit
        if cur_code in path_to_char:
            result += path_to_char[cur_code]
            cur_code = ""

    return result

def main():
    print("Here are some tests (higher compression ratio = better)")
    tests = [
        "Hello world!",
        "A_DEAD_DAD_CEDED_A_BAD_BABE_A_BEADED_ABACA_BED",
        'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque vulputate vestibulum orci nec finibus. Nunc iaculis id leo at euismod. Curabitur lobortis justo vel purus tristique sagittis. Suspendisse semper risus eget congue laoreet. Nunc vulputate, arcu ac imperdiet faucibus, urna nibh gravida quam, vel semper massa massa non tellus. Pellentesque eget ex id purus feugiat faucibus. Aenean convallis urna condimentum quam pulvinar, vitae varius diam sodales. Suspendisse rhoncus tincidunt justo, eu eleifend felis lobortis sit amet. Pellentesque vestibulum quis magna ac semper. Sed euismod lectus ac nulla vestibulum ultrices. Donec porta suscipit ultricies. Integer tincidunt ac turpis tincidunt congue. Donec ut ipsum ligula. Vestibulum sit amet nisl feugiat, ultricies lacus a, fermentum quam. Phasellus pellentesque gravida lacus, quis tristique nisi efficitur vel. Vestibulum tempus sed ex aliquet tempor.',
        'TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaXBpc2NpbmcgZWxpdC4gUGVsbGVudGVzcXVlIHZ1bHB1dGF0ZSB2ZXN0aWJ1bHVtIG9yY2kgbmVjIGZpbmlidXMuIE51bmMgaWFjdWxpcyBpZCBsZW8gYXQgZXVpc21vZC4gQ3VyYWJpdHVyIGxvYm9ydGlzIGp1c3RvIHZlbCBwdXJ1cyB0cmlzdGlxdWUgc2FnaXR0aXMuIFN1c3BlbmRpc3NlIHNlbXBlciByaXN1cyBlZ2V0IGNvbmd1ZSBsYW9yZWV0LiBOdW5jIHZ1bHB1dGF0ZSwgYXJjdSBhYyBpbXBlcmRpZXQgZmF1Y2lidXMsIHVybmEgbmliaCBncmF2aWRhIHF1YW0sIHZlbCBzZW1wZXIgbWFzc2EgbWFzc2Egbm9uIHRlbGx1cy4gUGVsbGVudGVzcXVlIGVnZXQgZXggaWQgcHVydXMgZmV1Z2lhdCBmYXVjaWJ1cy4gQWVuZWFuIGNvbnZhbGxpcyB1cm5hIGNvbmRpbWVudHVtIHF1YW0gcHVsdmluYXIsIHZpdGFlIHZhcml1cyBkaWFtIHNvZGFsZXMuIFN1c3BlbmRpc3NlIHJob25jdXMgdGluY2lkdW50IGp1c3RvLCBldSBlbGVpZmVuZCBmZWxpcyBsb2JvcnRpcyBzaXQgYW1ldC4gUGVsbGVudGVzcXVlIHZlc3RpYnVsdW0gcXVpcyBtYWduYSBhYyBzZW1wZXIuIFNlZCBldWlzbW9kIGxlY3R1cyBhYyBudWxsYSB2ZXN0aWJ1bHVtIHVsdHJpY2VzLiBEb25lYyBwb3J0YSBzdXNjaXBpdCB1bHRyaWNpZXMuIEludGVnZXIgdGluY2lkdW50IGFjIHR1cnBpcyB0aW5jaWR1bnQgY29uZ3VlLiBEb25lYyB1dCBpcHN1bSBsaWd1bGEuIFZlc3RpYnVsdW0gc2l0IGFtZXQgbmlzbCBmZXVnaWF0LCB1bHRyaWNpZXMgbGFjdXMgYSwgZmVybWVudHVtIHF1YW0uIFBoYXNlbGx1cyBwZWxsZW50ZXNxdWUgZ3JhdmlkYSBsYWN1cywgcXVpcyB0cmlzdGlxdWUgbmlzaSBlZmZpY2l0dXIgdmVsLiBWZXN0aWJ1bHVtIHRlbXB1cyBzZWQgZXggYWxpcXVldCB0ZW1wb3Iu'
    ]
    for test_case in tests:
        test(test_case)
        print("\n")

    print("\n\n\n")

    while True:
        s = input("String: ")
        s_size = len(s.encode('utf-8'))
        print(f"Size of your string: {s_size} bytes")

        encoded, char_to_path = encode(s)
        print(f"Encoded: {encoded}")

        encoded_bits = len(encoded)
        encoded_bytes = encoded_bits // 8
        if encoded_bits % 8 != 0:
            encoded_bytes += 1

        print(f"Encoded size: {encoded_bytes} bytes")

        decoded = decode(encoded, char_to_path)
        print(f"Decoded: {decoded}")


def test(s):
    encoded, code_map = encode(s)
    decoded = decode(encoded, code_map)

    original_size = len(s.encode('utf-8'))
    encoded_bits = len(encoded)
    encoded_bytes = encoded_bits // 8
    if encoded_bits % 8 != 0:
        encoded_bytes += 1
    compressed_size = encoded_bytes

    # round to two decimal places
    compression_ratio = round(original_size / compressed_size, 2)

    print(s)
    print(f"Success: {'True' if s == decoded else 'False'} (compression ratio = {compression_ratio})")


if __name__ == "__main__":
    main()


