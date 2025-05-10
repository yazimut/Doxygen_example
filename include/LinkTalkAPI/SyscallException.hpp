#pragma once
#include <LinkTalkAPI/Exception.hpp>

namespace LinkTalk {
    /**
     * @brief Represents an exception based on ERRNO
     *
     */
    class SyscallException final: public Exception {
        /// @brief Current ERRNO code
        uint32_t mErrnoCode;

    public:
        /**
         * @brief Construct a new Syscall Exception object
         *
         * @param[in] What Description
         */
        SyscallException(const std::string &What);

        /**
         * @brief Destroy the Syscall Exception object
         *
         */
        virtual ~SyscallException() override;

        /**
         * @brief Get the ERRNO code
         *
         * @return Current ERRNO code
         */
        uint32_t getErrnoCode() const;
    };
}
