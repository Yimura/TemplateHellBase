#pragma once
#include "core/memory/Module.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "Pointer.hpp"

namespace NewBase
{
    using PointerMap = std::unordered_map<std::string, Pointer<void*>>;

    class PointerCache
    {
    private:
        File m_CacheFile;
        Module* m_Module;

    protected:
        PointerMap* m_PtrCache;

    public:
        PointerCache(File cacheFile);

        nlohmann::json Dump() const;
        bool Load();
        void SetModule(Module* module);

    };

}