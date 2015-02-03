
namespace pyston {
struct Bitmap {
  Bitmap(size_t sizeof_type) : _sizeof_type(sizeof_type) {
    _bitmap_size = sizeof_type / 8;
    _bitmap = (size_t*)calloc(sizeof(size_t), _bitmap_size);
  }
  
  void addGCField(int offset) {
    int word = offset / 8;
    int bit = offset % 8;
    _bitmap[word] |= 1 << bit;
  }

  size_t* gc_bitmap() const { return _bitmap; }
  int gc_bitmap_size() const { return _bitmap_size; }

  size_t *_bitmap;
  int _bitmap_size;
  size_t _sizeof_type;
};

struct BoxBitmap : public Bitmap {
  BoxBitmap(size_t size);
};

struct BoxVarBitmap : public BoxBitmap {
  BoxVarBitmap(size_t size);
};

struct BoxedFileBitmap : public BoxBitmap {
  BoxedFileBitmap(size_t size);
};

struct BoxedIntBitmap : public BoxBitmap {
  BoxedIntBitmap(size_t size);
};

struct BoxedBoolBitmap : public BoxedIntBitmap {
  BoxedBoolBitmap(size_t size);
};

struct BoxedDictBitmap : public BoxBitmap {
  BoxedDictBitmap(size_t size);
};

struct BoxedFloatBitmap : public BoxBitmap {
  BoxedFloatBitmap(size_t size);
};

struct BoxedComplexBitmap : public BoxBitmap {
  BoxedComplexBitmap(size_t size);
};

struct BoxedMemberDescriptorBitmap : public BoxBitmap {
  BoxedMemberDescriptorBitmap(size_t size);
};

struct BoxedLongBitmap : public BoxBitmap {
  BoxedLongBitmap(size_t size);
};

struct BoxedTupleBitmap : public BoxBitmap {
  BoxedTupleBitmap(size_t size);
};

struct BoxedStringBitmap : public BoxBitmap {
  BoxedStringBitmap(size_t size);
};

struct BoxedUnicodeBitmap : public BoxBitmap {
  BoxedUnicodeBitmap(size_t size);
};

struct BoxedFunctionBitmap : public BoxBitmap {
  BoxedFunctionBitmap(size_t size);
};

struct BoxedModuleBitmap : public BoxBitmap {
  BoxedModuleBitmap(size_t size);
};

struct BoxedListBitmap : public BoxBitmap {
  BoxedListBitmap(size_t size);
};

struct BoxedClassBitmap : public BoxVarBitmap {
  BoxedClassBitmap(size_t size);
};

struct BoxedHeapClassBitmap : public BoxedClassBitmap {
  BoxedHeapClassBitmap(size_t size);
};

struct BoxedInstanceMethodBitmap : public BoxBitmap {
  BoxedInstanceMethodBitmap(size_t size);
};

};
