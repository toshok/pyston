t = (1, "h")
print t, str(t), repr(t)
if 1:
    t = (3,)
print t

def f():
    t = (1, 3)
    print t
f()

print ()
print (1,)
print (1, 2)
print (1, 2, 3)

t = 1, 3
print t

print (2,) < (2,)
print (2,) < (2, 3)
print (3,) < (2, 3)

print

class T(object):
    def __init__(self, n):
        self.n = n

    def __lt__(self, rhs):
        print "lt", self.n, rhs.n
        return self.n < rhs.n

    def __le__(self, rhs):
        print "le", self.n, rhs.n
        return self

    def __gt__(self, rhs):
        print "gt", self.n, rhs.n
        return False

    def __ge__(self, rhs):
        print "ge", self.n, rhs.n
        return False

    def __eq__(self, rhs):
        print "eq", self.n, rhs.n
        return self.n == rhs.n

    def __hash__(self):
        return hash(self.n)

    def __repr__(self):
        return "<T>"

def t(l, r):
    print l < r
    print l <= r
    print l > r
    print l >= r
    print l == r
    print l != r
    print "same hash: " , hash(l) == hash(r)

t(T(1), T(2))
t(T(1), T(1))
t((T(1),), (T(1),))
t((T(1),), (T(2),))
t((T(1),1), (T(2),))
t((T(1),), (T(2),1))

print ("hello", "world", ["test"])

# __add__
print () + ()
print (1, 2, 3) + ()
print () + (1, 2, 3)
print (1, 2) + (2, 3)

## __new__
print tuple()
print tuple((1,3,7,42))
print tuple(['i', 42, 'j', 318])
print tuple('hello world')
print tuple({'a': 1})
#print tuple({1,2,3,4})

print tuple(sequence=(1,3,7,42))
print tuple(sequence=['i', 42, 'j', 318])
print tuple(sequence='hello world')
print tuple(sequence={'a': 1})
#print tuple(sequence={1,2,3,4})

print tuple((1,3,7,42)) == tuple(sequence=(1,3,7,42))
print tuple(['i', 42, 'j', 318]) == tuple(sequence=['i', 42, 'j', 318])
print tuple('hello world') == tuple(sequence='hello world')
print tuple({'a': 1}) == tuple(sequence={'a': 1})
#print tuple({1,2,3,4}) == tuple(sequence={1,2,3,4})

# too many arguments
try:
    tuple((1,2), (3,4))
except TypeError, e:
    print e

try:
    tuple((1,2), sequence=(3,4))
except TypeError, e:
    print e

try:
    tuple(sequence=(3,4), test='test', rest='rest')
except TypeError, e:
    print e

# invalid keyword argument for function
try:
    tuple(oops='invalid keyword')
except TypeError, e:
    print e
