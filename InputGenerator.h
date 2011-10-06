/**
 * @brief C++ wrapper to Dr. Violet S's generator code.
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef _INPUTGENERATOR
#define _INPUTGENERATOR

#include <tr1/memory>
#include <string>

using std::string;
class InputGenerator
{
public:
    typedef std::tr1::shared_ptr<InputGenerator> Ptr;
    typedef std::tr1::weak_ptr<InputGenerator> WeakPtr;
    static InputGenerator::Ptr construct();
    virtual ~InputGenerator();
    string createFile(size_t n);
private:
    InputGenerator();
    InputGenerator::WeakPtr self;
    
};

#endif /* end of include guard: _INPUTGENERATOR */
