/// *==============================================================*
///  xc.cpp
/// *==============================================================*
#include "include/xc.hpp"
#include "include/sourcefile.hpp"
#include "include/tokenizer.hpp"
#include "include/parser.hpp"
#include "include/analyzer.hpp"
#include "include/cgenerator.hpp"

using namespace XC;

void XC::compile(const std::string target) {
    const std::unique_ptr<Module> module = std::make_unique<Module>();

    if ((module->source = SourceFile::loadContent(target)) == nullptr) {
        exit(EXIT_FAILURE);
    }

    if ((module->tokens = Tokenizer::extractTokenStream(module)) == nullptr) {
        exit(EXIT_FAILURE);
    }

    if ((module->program = Parser::getProgramTree(module)) == nullptr) {
        exit(EXIT_FAILURE);
    }

    if ((module->symbols = Analyzer::validateSemantics(module)) == nullptr) {
        exit(EXIT_FAILURE);
    } 

    if ((module->code = CGenerator::generateCode(module)) == nullptr) {
        exit(EXIT_FAILURE);
    }

    module->code->writeOut();
}