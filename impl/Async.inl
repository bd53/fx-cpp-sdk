namespace fx
{

inline void ResourceContext::createThread(BookmarkHandle handle, std::shared_ptr<void> prevent_destruct)
{
    if (!m_scheduleBookmark || !handle)
    {
        if (handle) handle.destroy();
        trace("createThread: bookmark scheduling not available\n");
        return;
    }
    uint64_t id = m_nextBookmarkId++;
    m_bookmarks[id] = {handle, std::move(prevent_destruct)};
    m_scheduleBookmark(id, 0); // schedule immediately (fires next cycle)
}

inline void ResourceContext::resumeBookmarks(uint64_t* bookmarks, int32_t numBookmarks)
{
    for (int32_t i = 0; i < numBookmarks; i++)
    {
        auto it = m_bookmarks.find(bookmarks[i]);
        if (it == m_bookmarks.end()) continue;

        auto handle = it->second.first;
        handle.promise().waitMs = 0;

        try
        {
            handle.resume();
        }
        catch (...)
        {
            // shouldn't happen (unhandled_exception captures)
            trace("Exception escaped coroutine resume\n");
            handle.destroy();
            m_bookmarks.erase(it);
            continue;
        }

        if (handle.done())
        {
            if (handle.promise().exception)
            {
                try { std::rethrow_exception(handle.promise().exception); }
                catch (const std::exception& e) { trace("Unhandled exception in thread: %s\n", e.what()); }
                catch (...) { trace("Unhandled non-standard exception in thread\n"); }
            }
            handle.destroy();
            m_bookmarks.erase(it);
        }
        else
        {
            int64_t waitMs = handle.promise().waitMs;
            if (m_scheduleBookmark)
                m_scheduleBookmark(bookmarks[i], -waitMs);
        }
    }
}

inline void ResourceContext::cleanupBookmarks()
{
    for (auto& [id, entry] : m_bookmarks)
    {
        if (entry.first) entry.first.destroy();
    }
    m_bookmarks.clear();
}

}
