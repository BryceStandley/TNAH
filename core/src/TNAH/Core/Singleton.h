#pragma once

namespace tnah
{
    /**
    * @class singleton
    * @brief A templated class that uses the singleton design pattern to provide one instance of any specified class.
    *
    * @author Dylan Blereau
    * @version 01
    * @date 30/03/2021 Dylan Blereau, Started
    *
    *
    **/
    template<class T>
    class singleton
    {
    public:

        /**
        * @brief gets and returns the instance of the class provided to the singleton
        * @return static instance of the given class
        *
        */
        static T& getInstance()
        {
            static T instance;
            return instance;
        }

    private:
        /**
        * @brief default constructor
        *
        */
        singleton() {}

        /**
        * @brief destructor
        *
        */
        ~singleton() {}

        /// Singletons shouldn't be cloneable
        singleton(singleton const&) = delete;

        /// Singletons shouldn't be assignable
        singleton& operator=(singleton const&) = delete;
    };
}
