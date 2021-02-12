// Copyright 2018 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_OBJECTS_STACK_FRAME_INFO_H_
#define V8_OBJECTS_STACK_FRAME_INFO_H_

#include "src/objects/struct.h"
#include "torque-generated/bit-fields.h"

// Has to be the last include (doesn't have include guards):
#include "src/objects/object-macros.h"

namespace v8 {
namespace internal {

class FrameArray;
class WasmInstanceObject;

#include "torque-generated/src/objects/stack-frame-info-tq.inc"

class StackTraceFrame
    : public TorqueGeneratedStackTraceFrame<StackTraceFrame, Struct> {
 public:
  NEVER_READ_ONLY_SPACE

  // Dispatched behavior.
  DECL_PRINTER(StackTraceFrame)

  static int GetLineNumber(Handle<StackTraceFrame> frame);
  static int GetOneBasedLineNumber(Handle<StackTraceFrame> frame);
  static int GetColumnNumber(Handle<StackTraceFrame> frame);
  static int GetOneBasedColumnNumber(Handle<StackTraceFrame> frame);
  static int GetScriptId(Handle<StackTraceFrame> frame);
  static int GetPromiseCombinatorIndex(Handle<StackTraceFrame> frame);
  static int GetFunctionOffset(Handle<StackTraceFrame> frame);
  static int GetWasmFunctionIndex(Handle<StackTraceFrame> frame);

  static Handle<Object> GetFileName(Handle<StackTraceFrame> frame);
  static Handle<Object> GetScriptNameOrSourceUrl(Handle<StackTraceFrame> frame);
  static Handle<Object> GetFunctionName(Handle<StackTraceFrame> frame);
  static Handle<Object> GetMethodName(Handle<StackTraceFrame> frame);
  static Handle<Object> GetTypeName(Handle<StackTraceFrame> frame);
  static Handle<Object> GetEvalOrigin(Handle<StackTraceFrame> frame);
  static Handle<Object> GetWasmModuleName(Handle<StackTraceFrame> frame);
  static Handle<WasmInstanceObject> GetWasmInstance(
      Handle<StackTraceFrame> frame);

  static bool IsEval(Handle<StackTraceFrame> frame);
  static bool IsConstructor(Handle<StackTraceFrame> frame);
  static bool IsMethodCall(Handle<StackTraceFrame> frame);
  static bool IsWasm(Handle<StackTraceFrame> frame);
  static bool IsAsmJsWasm(Handle<StackTraceFrame> frame);
  static bool IsUserJavaScript(Handle<StackTraceFrame> frame);
  static bool IsToplevel(Handle<StackTraceFrame> frame);
  static bool IsAsync(Handle<StackTraceFrame> frame);
  static bool IsPromiseAll(Handle<StackTraceFrame> frame);
  static bool IsPromiseAny(Handle<StackTraceFrame> frame);

 private:
  TQ_OBJECT_CONSTRUCTORS(StackTraceFrame)
};

// Small helper that retrieves the FrameArray from a stack-trace
// consisting of a FixedArray of StackTraceFrame objects.
// This helper is only temporary until all FrameArray use-sites have
// been converted to use StackTraceFrame and StackFrameInfo objects.
V8_EXPORT_PRIVATE
Handle<FrameArray> GetFrameArrayFromStackTrace(Isolate* isolate,
                                               Handle<FixedArray> stack_trace);

class IncrementalStringBuilder;
void SerializeStackTraceFrame(Isolate* isolate, Handle<StackTraceFrame> frame,
                              IncrementalStringBuilder* builder);
V8_EXPORT_PRIVATE
MaybeHandle<String> SerializeStackTraceFrame(Isolate* isolate,
                                             Handle<StackTraceFrame> frame);

}  // namespace internal
}  // namespace v8

#include "src/objects/object-macros-undef.h"

#endif  // V8_OBJECTS_STACK_FRAME_INFO_H_
