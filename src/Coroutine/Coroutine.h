#pragma once

#include "../Resource.h"

#include <coroutine>
#include <exception>
#include <cstdint>

namespace fx
{

struct BookmarkPromise
{
    int64_t waitMs = 0;
    std::exception_ptr exception;
    auto get_return_object();
    std::suspend_always initial_suspend() noexcept { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() { exception = std::current_exception(); }
};

struct ScriptTask
{
    using promise_type = BookmarkPromise;
    using handle_type = BookmarkHandle;
    handle_type handle;
};

inline auto BookmarkPromise::get_return_object()
{
    return ScriptTask{BookmarkHandle::from_promise(*this)};
}

struct Wait
{
    int64_t ms;
    explicit Wait(int64_t ms) : ms(ms) {}
    bool await_ready() const noexcept { return false; }
    void await_suspend(BookmarkHandle h) const noexcept
    {
        h.promise().waitMs = ms;
    }
    void await_resume() const noexcept {}
};

template<typename F>
inline void createThread(F&& fn)
{
    if (auto* ctx = detail::g_ctx)
    {
        auto stored = std::make_shared<std::decay_t<F>>(std::forward<F>(fn));
        ctx->createThread((*stored)().handle, std::move(stored));
    }
}

}

#include "../Impl/Async.inl"
