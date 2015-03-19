def test(string, encoding):
 s = string.encode(encoding)
 print encoding, s
 assert string == s.decode(encoding)

test("hello world", "hex")
test("hello world", "base64")
test("\r\n\\", "string-escape")


try:
    u'\U0001f4a9'.decode()
except UnicodeEncodeError as e:
    print str(e).split(' ')[0]
