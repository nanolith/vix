#ifndef  VIX_COMMAND_HEADER_GUARD
# define VIX_COMMAND_HEADER_GUARD

#include <memory>
#include <vix/Buffer.h>
#include <vix/Line.h>
#include <vix/Serializable.h>

namespace vix
{
    /**
     * A Command provides two methods: apply and revert.  The apply method is
     * sticky, meaning that it remembers what it did and how to revert the
     * change.  A Command is instantiated with a range of lines on which it is
     * to operate within the Buffer.  A Command must be serializable, so it can
     * be stored in a journal for managing undo and redo.
     */
    class Command : virtual public Serializable
    {
    public:

        /**
         * Apply a command to the buffer.
         */
        virtual void apply(std::weak_ptr<Buffer> buffer) = 0;

        /**
         * Revert the previously applied command.
         */
        virtual void revert(std::weak_ptr<Buffer> buffer) = 0;
    };
}

#endif //VIX_COMMAND_HEADER_GUARD
