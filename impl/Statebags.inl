namespace fx
{

inline void ResourceContext::setStateBagValue(const std::string& bagName, const std::string& key, const json::Value& value, bool replicated)
{
    auto encoded = msgpack::encode(value);
    invokeNative(HashString("SET_STATE_BAG_VALUE"), reinterpret_cast<uintptr_t>(bagName.c_str()), reinterpret_cast<uintptr_t>(key.c_str()), reinterpret_cast<uintptr_t>(encoded.data()), encoded.size(), uintptr_t(replicated ? 1u : 0u));
}

inline void ResourceContext::setPlayerState(int serverId, const std::string& key, const json::Value& value, bool replicated)
{
    setStateBagValue("player:" + std::to_string(serverId), key, value, replicated);
}

inline void ResourceContext::setEntityState(int netId, const std::string& key, const json::Value& value, bool replicated)
{
    setStateBagValue("entity:" + std::to_string(netId), key, value, replicated);
}

inline void ResourceContext::setGlobalState(const std::string& key, const json::Value& value, bool replicated)
{
    setStateBagValue("global", key, value, replicated);
}

inline json::Value ResourceContext::getStateBagValue(const std::string& bagName, const std::string& key)
{
    auto ctx = invokeNativeResult(HashString("GET_STATE_BAG_VALUE"), reinterpret_cast<uintptr_t>(bagName.c_str()), reinterpret_cast<uintptr_t>(key.c_str()));
    const char* data = reinterpret_cast<const char*>(ctx.arguments[0]);
    size_t size = static_cast<size_t>(ctx.arguments[1]);
    if (!data || size == 0) return json::makeNull();
    return msgpack::decode(data, static_cast<uint32_t>(size));
}

inline json::Value ResourceContext::getPlayerState(int serverId, const std::string& key)
{
    return getStateBagValue("player:" + std::to_string(serverId), key);
}

inline json::Value ResourceContext::getEntityState(int netId, const std::string& key)
{
    return getStateBagValue("entity:" + std::to_string(netId), key);
}

inline json::Value ResourceContext::getGlobalState(const std::string& key)
{
    return getStateBagValue("global", key);
}

inline bool ResourceContext::stateBagHasKey(const std::string& bagName, const std::string& key)
{
    auto ctx = invokeNativeResult(HashString("STATE_BAG_HAS_KEY"), reinterpret_cast<uintptr_t>(bagName.c_str()), reinterpret_cast<uintptr_t>(key.c_str()));
    return static_cast<bool>(ctx.arguments[0]);
}

inline std::vector<std::string> ResourceContext::getStateBagKeys(const std::string& bagName)
{
    auto ctx = invokeNativeResult(HashString("GET_STATE_BAG_KEYS"), reinterpret_cast<uintptr_t>(bagName.c_str()));
    const char* data = reinterpret_cast<const char*>(ctx.arguments[0]);
    size_t size = static_cast<size_t>(ctx.arguments[1]);
    if (!data || size == 0) return {};
    json::Value arr = msgpack::decode(data, static_cast<uint32_t>(size));
    std::vector<std::string> keys;
    for (size_t i = 0; i < arr.size(); i++)
        keys.push_back(arr.at(i).asStr());
    return keys;
}

}
