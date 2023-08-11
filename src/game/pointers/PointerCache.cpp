#include "PointerCache.hpp"

namespace NewBase
{
	PointerCache::PointerCache(File cacheFile) :
        m_CacheFile(cacheFile)
	{

	}

	nlohmann::json PointerCache::Dump() const
	{
        std::map<std::string, std::uint64_t> output;
        for (const auto& [ name, ptr ] : *m_PtrCache)
        {
            output.insert({ name, reinterpret_cast<std::uintptr_t>(ptr.Get()) - m_Module->Base()});
        }

		return output;
	}

	bool PointerCache::Load()
	{
        if (!m_CacheFile.Exists())
            return false;

        const auto original = Dump();
        nlohmann::json loaded;
        try
        {
            std::ifstream file(m_CacheFile.Path());
            loaded << file;
        }
        catch(...)
        {
            LOG(WARNING) << "Failed to load ptr cache.";

            return false;
        }
        
        for (const auto& [ key, val ] : original.items())
        {
            if (!loaded.contains(key))
            {
                return false;
            }

            (*m_PtrCache)[key] = reinterpret_cast<void*>(loaded[key].get<std::uint64_t>());
        }

		return true;
	}

	void PointerCache::SetModule(Module* module)
	{
        m_Module = module;
	}
}