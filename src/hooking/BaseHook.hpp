#pragma once
#include <string_view>

namespace NewBase
{
    class BaseHook
    {
    private:
        const std::string_view m_Name;

    protected:
        bool m_Enabled;

    public:
        BaseHook(const std::string_view name);
        virtual ~BaseHook() = default;
        BaseHook(const BaseHook&) = delete;
        BaseHook(BaseHook&&) noexcept = delete;
        BaseHook& operator=(const BaseHook&) = delete;
        BaseHook& operator=(BaseHook&&) noexcept = delete;
        
        const std::string_view Name() const
        { return m_Name; }
        inline bool IsEnabled() const
        { return m_Enabled; }
        
        virtual bool Enable() = 0;
        virtual bool Disable() = 0;

        static void EnableAll();
        static void DisableAll();

    private:
        inline static std::vector<BaseHook*> m_Hooks;
        
    };
    
}
