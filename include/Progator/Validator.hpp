#ifndef ProgatorValidator_hpp
#define ProgatorValidator_hpp 

#include "Progator/Types.hpp"

namespace Progator
{
    enum ValidatorCodes
    {
        Ok                      = 0,
        NoFile,
        FailedToCreateObject,
        FailedAllocation,
        FailedInitializeSDL,
        FailedCreateWindow,
        /* OpenGL errors: */
        FailedCreateOpenGLContext,
        FailedCreateOpenGLPointersUsingGLEW,
        FailedCompileOpenGLVertexShader,
        FailedCompileOpenGLFragmentShader,
        FailedLinkOpenGLShaders,
        /* ... */
        Unknown                 = UINT8_MAX
    };

    typedef struct Validator
    {
        Progator::U8        status = Progator::ValidatorCodes::Ok;
        Progator::Character log[256];
    } Validator;
    
    Progator::Validator* ValidatorNew();
    void ValidatorDestroy(Progator::Validator* validator);

    /* TODO: this function doesn't include '\n' on the end by default: */
    void ValidatorError(Progator::Validator* validator, const Progator::U8 code, const Progator::Character* format, ...);
};

#define ProgatorHelperPerformWhenValidated(validator, do)               \
    if(validator->status == Progator::ValidatorCodes::Ok)  do;

#define ProgatorHelperHandleErrorValidator(validator, do)               \
    if(validator->status != Progator::ValidatorCodes::Ok)  do;

#define ProgatorHelperTreatErrorValidator(validator, do)                \
    if(validator->status != Progator::ValidatorCodes::Ok)  do;          \
    validator->status = Progator::ValidatorCodes::Ok;

#endif