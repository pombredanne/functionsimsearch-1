// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DISASSEMBLY_HPP
#define DISASSEMBLY_HPP

#include <string>
#include "CodeObject.h"

// A thin wrapper class around Dyninst to deal with some boilerplate code
// required for switching between PE and ELF files. Will be obsoleted when
// DynInst acquires "native" PE parsing capability.

class Disassembly {
public:
  Disassembly(const std::string& filetype, const std::string& inputfile);
  virtual ~Disassembly();

  bool Load(bool perform_parsing = true);
  void DisassembleFromAddress(uint64_t address, bool recursive);
  Dyninst::ParseAPI::CodeObject* getCodeObject() { return code_object_; };

private:
  const std::string type_;
  const std::string inputfile_;
  Dyninst::ParseAPI::CodeObject* code_object_;
  Dyninst::ParseAPI::CodeSource* code_source_;
};

// A helper function used to detect functions which have shared basic blocks
// with other functions. This is mainly used to detect situations where 
// Dyninst failed to properly disassembly a binary.
bool ContainsSharedBasicBlocks(Dyninst::ParseAPI::Function* function);

#endif // DISASSEMBLY_HPP

