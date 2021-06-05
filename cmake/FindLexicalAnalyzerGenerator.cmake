set(FIND_LEXICALANALYZERGENERATOR_PATHS cmake/LexicalAnalyzerGenerator)

find_path(LEXICALANALYZERGENERATOR_INCLUDE_DIR Nfa.h Dfa.h InputParser.h InputLanguageParser.h Token.h MinimizedDfa.h
        PATH_SUFFIXES include
        PATHS ${FIND_LEXICALANALYZERGENERATOR_PATHS})

find_library(LEXICALANALYZERGENERATOR_LIBRARY
        NAMES LexicalAnalyzerGenerator
        PATH_SUFFIXES lib
        PATHS ${FIND_LEXICALANALYZERGENERATOR_PATHS})
