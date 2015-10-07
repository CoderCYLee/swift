//===---- MemLocationDumper.cpp - Dump all memory locations in program ----===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2015 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See http://swift.org/LICENSE.txt for license information
// See http://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This pass dumps all the memory locations accessed in the function, as well
// as their expansions.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "sil-memlocation-dumper"
#include "swift/SILPasses/Passes.h"
#include "swift/SIL/MemLocation.h"
#include "swift/SIL/SILFunction.h"
#include "swift/SIL/SILValue.h"
#include "swift/SILAnalysis/Analysis.h"
#include "swift/SILPasses/Transforms.h"
#include "llvm/Support/Debug.h"

using namespace swift;

//===----------------------------------------------------------------------===//
//                              Top Level Driver
//===----------------------------------------------------------------------===//

namespace {

/// Dumps the alias relations between all instructions of a function.
class MemLocationDumper : public SILFunctionTransform {

  void run() override {
    SILFunction &Fn = *getFunction();
    llvm::outs() << "@" << Fn.getName() << "\n";
    MemLocationList Locs;

    for (auto &BB : Fn) {
      for (auto &II : BB) {
        MemLocation L;
        if (auto *LI = dyn_cast<LoadInst>(&II)) {
          L.initialize(LI->getOperand());
          if (!L.isValid())
            continue;
          MemLocation::expand(L, &Fn.getModule(), Locs);
        } else if (auto *SI = dyn_cast<StoreInst>(&II)) {
          L.initialize(SI->getDest());
          if (!L.isValid())
            continue;
          MemLocation::expand(L, &Fn.getModule(), Locs);
        }
      }

      unsigned Counter = 0;
      for (auto &Loc : Locs) {
        llvm::outs() << "#" << Counter++ << Loc; 
      }

      Locs.clear();
    }
    llvm::outs() << "\n";
  }

  StringRef getName() override { return "Mem Location Dumper"; }
};

} // end anonymous namespace

SILTransform *swift::createMemLocationDumper() {
  return new MemLocationDumper();
}
