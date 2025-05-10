#pragma once
#include <cstdint>
#include <ostream>
#include <string>

namespace LinkTalk {
    /**
     * @brief Represents basic C++ exception
     *
     */
    class Exception {
        /// @brief Description
        std::string mErrorMessage;

    protected:
        /**
         * @brief Construct a new empty Exception object
         * @warning Only for inheritors!
         */
        Exception();

        /**
         * @brief Copy constructor
         *
         * @param[in] Other Exception instance to copy
         * @warning Copying Exception object is explicitly prohibited!
         */
        Exception(const Exception &Other) = delete;

        /**
         * @brief Move constructor
         *
         * @param[in, out] Other Exception instance to move
         * @warning Moving Exception object is explicitly prohibited!
         */
        Exception(Exception &&Other) = delete;

        /**
         * @brief Copy assignment operator
         *
         * @param[in] Right Exception instance to copy
         * @return Reference to current Exception
         * @warning Copying Exception object is explicitly prohibited!
         */
        virtual Exception &operator = (const Exception &Right) = delete;

        /**
         * @brief Move assignment operator
         *
         * @param[in, out] Right Exception instance to move
         * @return Reference to current Exception
         * @warning Moving Exception object is explicitly prohibited!
         */
        virtual Exception &operator = (Exception &&Right) = delete;

        /**
         * @brief Set the error message
         *
         * @param[in] Msg New error message
         */
        void setErrorMessage(const std::string &Msg);

    public:
        /**
         * @brief Construct a new Exception object
         *
         * @param[in] What Description
         */
        Exception(const std::string &What);

        /**
         * @brief Destroy the Exception object
         *
         */
        virtual ~Exception();

        /**
         * @brief Get description
         *
         * @return Description
         */
        virtual const std::string &what() const;
    };
}

/**
 * @brief Print std::string representation
 * of Exception instance to std::ostream
 *
 * @param[in, out] Out Output stream
 * @param[in] E Exception instance to print
 * @return Reference to output stream
 */
std::ostream &operator << (std::ostream &Out, const LinkTalk::Exception &E);
