// Copyright (c) 2014-2016 Dropbox, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "codegen/unwinding.h"

#include <dlfcn.h>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>

#if LLVMREV < 227586
#include "llvm/DebugInfo/DIContext.h"
#else
#include "llvm/DebugInfo/DWARF/DIContext.h"
#endif
#include "llvm/ExecutionEngine/JITEventListener.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/Object/ObjectFile.h"

#include "analysis/scoping_analysis.h"
#include "asm_writing/types.h"
#include "codegen/ast_interpreter.h"
#include "codegen/codegen.h"
#include "codegen/compvars.h"
#include "codegen/irgen/hooks.h"
#include "codegen/irgen/irgenerator.h"
#include "codegen/stackmaps.h"
#include "core/cfg.h"
#include "core/util.h"
#include "runtime/ctxswitching.h"
#include "runtime/generator.h"
#include "runtime/objmodel.h"
#include "runtime/types.h"

namespace pyston {

void addDecrefInfoEntry(uint64_t ip, std::vector<class Location> location) {
    abort();
}
void removeDecrefInfoEntry(uint64_t ip) {
    abort();
}

llvm::JITEventListener* makeTracebacksListener() {
    abort();
}

ExcInfo* getFrameExcInfo() {
    abort();
}

void RegisterEHFrame::updateAndRegisterFrameFromTemplate(uint64_t code_addr, size_t code_size, uint64_t eh_frame_addr,
                                                         size_t eh_frame_size) {
    abort();
}

void RegisterEHFrame::registerFrame(uint64_t code_addr, size_t code_size, uint64_t eh_frame_addr,
                                    size_t eh_frame_size) {
    abort();
}

void RegisterEHFrame::deregisterFrame() {
    abort();
}

DeoptState getDeoptState() {
    abort();
}

void updateFrameExcInfoIfNeeded(ExcInfo* latest) {
    abort();
}

BoxedCode* getTopPythonFunction() {
    abort();
}

BORROWED(Box*) getGlobals() {
    abort();
}

BORROWED(Box*) getGlobalsDict() {
    abort();
}

BORROWED(BoxedModule*) getCurrentModule() {
    abort();
}

FrameInfo* getPythonFrameInfo(int depth) {
    abort();
}

BORROWED(Box*) fastLocalsToBoxedLocals() {
    abort();
}

static BoxedDict* localsForFrame(Box** vregs, CFG* cfg) {
    abort();
}

BORROWED(Box*) FrameInfo::updateBoxedLocals() {
    abort();
}

void setupUnwinding() {}
}
