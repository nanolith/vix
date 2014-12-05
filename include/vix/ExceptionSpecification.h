#ifndef  VIX_EXCEPTION_SPECIFICATION_HEADER_GUARD
# define VIX_EXCEPTION_SPECIFICATION_HEADER_GUARD

    /**
     * The EXCEPTION_SPECIFICATION macro provides a simple way by which
     * redundant exception boilerplate can be automated.  Each exception defined
     * in this way has a unique name, and derives from a base exception type
     * that eventually joins the STL exception hierarchy.  Two constructors are
     * provided - one that takes a const char* and the other that takes a const
     * std::string reference.
     */
    #define EXCEPTION_SPECIFICATION(EXCEPTION, BASE_EXCEPTION) \
        class EXCEPTION : public BASE_EXCEPTION \
        { \
        public: \
            explicit EXCEPTION(const std::string& what_arg) \
                : BASE_EXCEPTION(what_arg) \
            { \
            } \
            \
            explicit EXCEPTION(const char* what_arg) \
                : BASE_EXCEPTION(what_arg) \
            { \
            } \
        }

#endif //VIX_EXCEPTION_SPECIFICATION_HEADER_GUARD
