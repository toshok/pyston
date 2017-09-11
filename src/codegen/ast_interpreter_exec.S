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

// This functions sets up a fixed stack frame which we use to detect ASTInterpreter frames
// and which makes it easy retrieve the passed ASTInterpreter pointer (stored at frame_ptr-8). 
// It's written in ASM to make sure the stack layout keeps being the same and that nothing gets inlined.
// Our unwinder treats this function specialy.

// Box* executeInnerAndSetupFrame(ASTInterpreter& interpreter, CFGBlock* start_block, AST_stmt* start_at)
.text
.globl _executeInnerAndSetupFrame
#ifndef __APPLE__
.type _executeInnerAndSetupFrame,@function
#endif
.align 16
_executeInnerAndSetupFrame:
    .cfi_startproc
    push %rbp
    .cfi_def_cfa_offset     16
    .cfi_offset             rbp,-16
    mov %rsp, %rbp
    .cfi_def_cfa_register   rbp
    sub $16, %rsp
    mov %rdi, -8(%rbp)
    call _executeInnerFromASM
    add $16, %rsp
    pop %rbp
    .cfi_def_cfa            rsp,8
    ret
    .cfi_endproc
#ifndef __APPLE__
.size executeInnerAndSetupFrame,.-executeInnerAndSetupFrame
#endif

// This function is just a small wrapper around astInterpretDeoptFromASM.
// Our unwinder must be able to detect deopt frames and by writing this wrapper in assembler we can be sure to correctly
// detect the frame independent of compiler optimizations because this function will always appear in the call stack.
//
// Box* astInterpretDeopt(FunctionMetadata* cf, AST_stmt* enclosing_stmt, Box* expr_val,
//                        FrameStackState frame_state);
.text
.globl _astInterpretDeopt
#ifndef __APPLE__
.type _astInterpretDeopt,@function
#endif
.align 16
_astInterpretDeopt:
    .cfi_startproc
    push %rbp
    .cfi_def_cfa_offset     16
    .cfi_offset             rbp,-16
    mov %rsp, %rbp
    .cfi_def_cfa_register   rbp
    call _astInterpretDeoptFromASM
    pop %rbp
    .cfi_def_cfa            rsp,8
    ret
    .cfi_endproc
#ifndef __APPLE__
.size astInterpretDeopt,.-astInterpretDeopt
.section .note.GNU-stack,"",%progbits // we don't need executable stack
#endif

