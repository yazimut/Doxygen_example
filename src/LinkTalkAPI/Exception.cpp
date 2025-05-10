#include <LinkTalkAPI/Exception.hpp>

using namespace std;
using namespace LinkTalk;

Exception::Exception():
mErrorMessage("") {}

Exception::Exception(const string &What):
mErrorMessage(What) {}

Exception::~Exception() {}

void Exception::setErrorMessage(const string &Msg) {
    mErrorMessage = Msg;
}

const string &Exception::what() const {
    return mErrorMessage;
}

ostream &operator << (ostream &Out, const LinkTalk::Exception &E) {
    Out << E.what();
    return Out;
}
