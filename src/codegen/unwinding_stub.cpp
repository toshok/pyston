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

llvm::DenseMap<uint64_t /*ip*/, std::vector<Location>> decref_infos;
void addDecrefInfoEntry(uint64_t ip, std::vector<class Location> location) {
    assert(!decref_infos.count(ip) && "why is there already an entry??");
    decref_infos[ip] = std::move(location);
}
void removeDecrefInfoEntry(uint64_t ip) {
    decref_infos.erase(ip);
}


class TracebacksEventListener : public llvm::JITEventListener {
public:
    virtual void NotifyObjectEmitted(const llvm::object::ObjectFile& Obj,
                                     const llvm::RuntimeDyld::LoadedObjectInfo& L) {}
};

llvm::JITEventListener* makeTracebacksListener() {
    return new TracebacksEventListener();
}

static FrameInfo* getTopFrameInfo() {
    return (FrameInfo*)cur_thread_state.frame_info;
}

ExcInfo* getFrameExcInfo() {
    std::vector<ExcInfo*> to_update;
    ExcInfo* copy_from_exc = NULL;
    ExcInfo* cur_exc = NULL;

    FrameInfo* frame_info = getTopFrameInfo();
    while (frame_info) {
        if (copy_from_exc)
            to_update.push_back(copy_from_exc);

        copy_from_exc = &frame_info->exc;
        if (!cur_exc)
            cur_exc = copy_from_exc;

        if (copy_from_exc->type)
            break;

        frame_info = frame_info->back;
    };

    assert(copy_from_exc); // Only way this could still be NULL is if there weren't any python frames

    if (!copy_from_exc->type) {
        // No exceptions found:
        *copy_from_exc = ExcInfo(incref(Py_None), incref(Py_None), NULL);
    }

    for (auto* ex : to_update) {
        assert(ex != copy_from_exc);
        *ex = *copy_from_exc;
        Py_INCREF(ex->type);
        Py_INCREF(ex->value);
        Py_XINCREF(ex->traceback);
    }
    assert(cur_exc);
    return cur_exc;
}

void RegisterEHFrame::updateAndRegisterFrameFromTemplate(uint64_t code_addr, size_t code_size, uint64_t eh_frame_addr,
                                                         size_t eh_frame_size) {}

void RegisterEHFrame::registerFrame(uint64_t code_addr, size_t code_size, uint64_t eh_frame_addr,
                                    size_t eh_frame_size) {}

void RegisterEHFrame::deregisterFrame() {}

DeoptState getDeoptState() {
    abort();
}

void updateFrameExcInfoIfNeeded(ExcInfo* latest) {
    abort();
}

BoxedCode* getTopPythonFunction() {
    FrameInfo* frame_info = getTopFrameInfo();
    if (!frame_info)
        return NULL;
    return frame_info->code;
}

BORROWED(Box*) getGlobals() {
    FrameInfo* frame_info = getTopFrameInfo();
    if (!frame_info)
        return NULL;
    return frame_info->globals;
}

BORROWED(Box*) getGlobalsDict() {
    Box* globals = getGlobals();
    if (globals && PyModule_Check(globals))
        globals = globals->getAttrWrapper();
    return globals;
}

BORROWED(BoxedModule*) getCurrentModule() {
    BoxedCode* code = getTopPythonFunction();
    if (!code)
        return NULL;
    return code->source->parent_module;
}

FrameInfo* getPythonFrameInfo(int depth) {
    FrameInfo* frame_info = getTopFrameInfo();
    while (depth > 0) {
        if (!frame_info)
            return NULL;
        frame_info = frame_info->back;
        --depth;
    }
    if (!frame_info)
        return NULL;
    assert(frame_info->globals);
    assert(frame_info->code);
    return frame_info;
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
