
class Foo(object):
    def __hash__(self):
        return 5

o = Foo()
i = 0
j = 10000000
h = 0
while i < j:
    i += 1
    h = hash(o)
