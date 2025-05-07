#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

namespace {
struct TestPass : public FunctionPass {
  static char ID;
  TestPass() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    errs() << "Function-";
	errs()<<"Name:\t";
	errs().write_escaped(F.getName()) << '\n';
	
	Type* retType = F.getReturnType();
	errs() << "Ret type:\t";
	retType->print(errs());
	errs()<<'\n';
	for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I)
	{
		Instruction& _instruction = *I;
		errs()<<_instruction.getOpcodeName()<<'\n';
		//errs() << *I << "\n";
	}
	errs() << "\n\n";
	//retType->dump();
    return false;
  }
}; // end of struct TestPass
}  // end of anonymous namespace

char TestPass::ID = 0;
static RegisterPass<TestPass> X("TestPass", "-",
                             false /* Only looks at CFG */,
                             false /* Analysis Pass */);
