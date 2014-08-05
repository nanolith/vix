#ifndef  BUFFER_CHANGE_OBSERVER_MOCK_HEADER_GUARD
# define BUFFER_CHANGE_OBSERVER_MOCK_HEADER_GUARD

#include <vix/Buffer.h>
#include <mockpp/mockpp.h>

namespace vix {

    /**
     * Simple mock for BufferChangeObserver.
     */
    class BufferChangeObserverMock : public BufferChangeObserver, public mockpp::Mock<BufferChangeObserver>
    {
    public:
        ~BufferChangeObserverMock() { }

        MOCK_FUNCTION_VOID_ARGS(onBufferChanged, const Buffer*);
    };

} /* namespace vix */

#endif //BUFFER_CHANGE_OBSERVER_MOCK_HEADER_GUARD
