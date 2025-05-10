#include <LinkTalkAPI/SyscallException.hpp>
#include <cerrno>
#include <cstring>

using namespace std;
using namespace LinkTalk;

SyscallException::SyscallException(const string &What):
Exception(), mErrnoCode(errno) {
    char ErrorMessage[1024] = "\0";
    sprintf(
        ErrorMessage,
        "%s. ERRNO = %s (0x%x): %s",
        What.c_str(),
        strerrorname_np(mErrnoCode),
        mErrnoCode,
        strerror(mErrnoCode)
    );
    setErrorMessage(ErrorMessage);
}

SyscallException::~SyscallException() {}

uint32_t SyscallException::getErrnoCode() const {
    return mErrnoCode;
}
