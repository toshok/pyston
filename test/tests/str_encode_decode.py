import sys

def test(string, encoding):
    s = string.encode(encoding)
    print encoding, s
    assert string == s.decode(encoding)

def testempty(string):
    s = string.encode()
    print sys.getdefaultencoding(), string
    assert string == s.decode()

test("hello world", "hex")
test("hello world", "base64")
test("\r\n\\", "string-escape")

testempty("hello world")
testempty("hello world")
testempty("\r\n\\")
