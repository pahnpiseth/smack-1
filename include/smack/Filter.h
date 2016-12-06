//
// This file is distributed under the MIT License. See LICENSE for details.
//
#ifndef FILTER_H
#define FILTER_H

#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/InstIterator.h"
#include <string>

using namespace llvm;

namespace smack {

class Filter : public llvm::ModulePass {
  
public:
  static char ID; // Pass identification, replacement for typeid

  Filter() : ModulePass(ID) {}
  
  virtual bool runOnModule(llvm::Module& m) {
    for (Function &F : m) {
      if (F.hasName() && F.getName().find("devirtbounce") != std::string::npos) {
        bool hasCall = false;
        for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
          if (isa<CallInst>(&*I)) {
            hasCall = true;
            break;
          }
        }
        if (!hasCall)
          F.addFnAttr("bounce-function-no-targets");
        
      }
    }
    return true;
  }
  
  virtual void getAnalysisUsage(llvm::AnalysisUsage& AU) const {
    AU.setPreservesAll();
  } 
};

char Filter::ID = 0;
}

#endif // BPLPRINTER_H

