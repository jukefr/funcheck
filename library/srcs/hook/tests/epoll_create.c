#include <errno.h>
#include <sys/epoll.h>
#include "../hook.h"
#include "../../utils/export.h"
#include "../../events/event_sender.h"
#include "../../function_search/function_search.h"

int EXPORT epoll_create(int size)
{
    typeof(&epoll_create) original_function = get_original_function();
    if (!is_hooks_enabled())
        return original_function(size);

    disable_hooks();
    t_shared_info *shared_memory = get_shared_memory();
    get_backtrace(shared_memory->backtrace);
    if (should_block(shared_memory->backtrace))
    {
        errno = EAGAIN;
        enable_hooks();
        return -1;
    }
    int save_result = original_function(size);
    send_function_call_event(shared_memory);
    enable_hooks();

    return save_result;
}