#ifndef STREAM_GUARD_H
#define STREAM_GUARD_H

#include <ios>

class StreamGuard {
public:
    explicit StreamGuard(std::basic_ios<char>& stream)
        : stream_(stream)
        , precision_(stream.precision())
        , flags_(stream.flags()) {
    }

    ~StreamGuard() {
        stream_.precision(precision_);
        stream_.flags(flags_);
    }

private:
    std::basic_ios<char>& stream_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;
};

#endif
