#pragma once
#include <string_view>

namespace NewBase
{
    template<std::size_t N>
    class Pattern final
    {
    private:
        const std::string_view m_Name;
        std::array<std::optional<std::uint8_t>, (N + 1) / 3> m_Signature;

    public:
        consteval Pattern(const std::string_view name, char const (&signature)[N]);

        inline const std::string_view Name() const
        { return m_Name; }
        inline constexpr const std::array<std::optional<std::uint8_t>, (N + 1) / 3>& Signature() const
        { return m_Signature; }
    };

    inline consteval auto StrToHex(const char& ch) noexcept -> std::uint8_t
    {
        if (ch >= '0' && ch <= '9')
                return ch - '0';

        if (ch >= 'A' && ch <= 'F')
            return ch - 'A' + 10;

        return ch - 'a' + 10;
    };

	template<std::size_t N>
	inline consteval Pattern<N>::Pattern(const std::string_view name, char const (&signature)[N])
	{
        for (size_t i = 0, pos = 0; i < N; i++)
        {
            const auto c = signature[i];
            if (c == ' ')
                continue;
            if (c == '\0')
                break;

            if (signature[i] == '?')
            {
                if (signature[i + 1] == '?')
                    i++;

                m_Signature[pos++] = std::nullopt;
                
                continue;
            }


            m_Signature[pos++] = static_cast<std::uint8_t>(StrToHex(signature[i]) * 0x10 + StrToHex(signature[++i]));
        }
	}
}