
#include "core/types.h"
#include "runtime/types.h"
#include "runtime/long.h"

namespace pyston {

BoxBitmap::BoxBitmap(size_t size) : Bitmap(size) {
  addGCField(offsetof(Box, cls));
}

BoxedClassBitmap::BoxedClassBitmap(size_t size) : BoxVarBitmap(size) {
  // pretty sure there's something here...
}

BoxedHeapClassBitmap::BoxedHeapClassBitmap(size_t size) : BoxedClassBitmap(size) {
  // pretty sure there's something here...
}

BoxedTupleBitmap::BoxedTupleBitmap(size_t size) : BoxBitmap(size) {
  // pretty sure there's something here...
}

BoxedListBitmap::BoxedListBitmap(size_t size) : BoxBitmap(size) {
  // XXX(toshok) elts
}

BoxedFunctionBitmap::BoxedFunctionBitmap(size_t size) : BoxBitmap(size) {
  addGCField(offsetof(BoxedFunction, closure));
  addGCField(offsetof(BoxedFunction, modname));
  // XXX more here -- defaults, attrs, etc
}


BoxedModuleBitmap::BoxedModuleBitmap(size_t size) : BoxBitmap(size) {
  // XXX more here -- attrs, futureflags?
}

BoxedDictBitmap::BoxedDictBitmap(size_t size) : BoxBitmap(size) {
  // XXX(toshok) add the DictMap
}

BoxedInstanceMethodBitmap::BoxedInstanceMethodBitmap(size_t size) : BoxBitmap(size) {
  addGCField(offsetof(BoxedInstanceMethod, obj));
  addGCField(offsetof(BoxedInstanceMethod, func));
}

BoxVarBitmap::BoxVarBitmap(size_t size) : BoxBitmap(size) { /* no gc fields */ }

BoxedBoolBitmap::BoxedBoolBitmap(size_t size) : BoxedIntBitmap(size) { /* no gc fields */ }
BoxedIntBitmap::BoxedIntBitmap(size_t size) : BoxBitmap(size) { /* no gc fields */ }
BoxedFloatBitmap::BoxedFloatBitmap(size_t size) : BoxBitmap(size) { /* no gc fields */ }
BoxedFileBitmap::BoxedFileBitmap(size_t size) : BoxBitmap(size) { /* no gc fields */ }
BoxedComplexBitmap::BoxedComplexBitmap(size_t size) : BoxBitmap(size) { /* no gc fields */ }
BoxedLongBitmap::BoxedLongBitmap(size_t size) : BoxBitmap(size) { /* no gc fields */ }
BoxedStringBitmap::BoxedStringBitmap(size_t size) : BoxBitmap(size) { /* no gc fields */ }
BoxedUnicodeBitmap::BoxedUnicodeBitmap(size_t size) : BoxBitmap(size) { /* no gc fields */ }
BoxedMemberDescriptorBitmap::BoxedMemberDescriptorBitmap(size_t size) : BoxBitmap(size) { /* no gc fields */ }

BoxBitmap Box::bitmap (sizeof(Box));
BoxVarBitmap BoxVar::bitmap (sizeof(BoxVar));

BoxedBoolBitmap BoxedBool::bitmap (sizeof(BoxedBool));
BoxedFileBitmap BoxedFile::bitmap (sizeof(BoxedFile));
BoxedIntBitmap BoxedInt::bitmap (sizeof(BoxedInt));
BoxedFloatBitmap BoxedFloat::bitmap (sizeof(BoxedFloat));
BoxedComplexBitmap BoxedComplex::bitmap (sizeof(BoxedComplex));
BoxedMemberDescriptorBitmap BoxedMemberDescriptor::bitmap (sizeof(BoxedMemberDescriptor));
BoxedLongBitmap BoxedLong::bitmap (sizeof(BoxedLong));
BoxedTupleBitmap BoxedTuple::bitmap (sizeof(BoxedTuple));
BoxedListBitmap BoxedList::bitmap (sizeof(BoxedList));
BoxedClassBitmap BoxedClass::bitmap (sizeof(BoxedClass));
BoxedFunctionBitmap BoxedFunction::bitmap (sizeof(BoxedFunction));
BoxedModuleBitmap BoxedModule::bitmap (sizeof(BoxedModule));
BoxedStringBitmap BoxedString::bitmap (sizeof(BoxedString));
BoxedUnicodeBitmap BoxedUnicode::bitmap (sizeof(BoxedUnicode));
BoxedHeapClassBitmap BoxedHeapClass::bitmap (sizeof(BoxedHeapClass));
BoxedDictBitmap BoxedDict::bitmap (sizeof(BoxedDict));
BoxedInstanceMethodBitmap BoxedInstanceMethod::bitmap (sizeof(BoxedInstanceMethod));


};
