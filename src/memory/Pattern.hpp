#pragma once
#include <string_view>

namespace NewBase
{
    template<std::size_t N>
    struct Signature
    {
        char m_Signature[N]{};
        std::size_t m_SignatureByteLength;

        constexpr Signature(char const (&signature)[N]) :
            m_SignatureByteLength(0)
        {
            std::ranges::copy(signature, m_Signature);

            for (std::size_t i = 0; i < N; i++)
            {
                if (m_Signature[i] == ' ' || m_Signature[i] == '\0')
                    m_SignatureByteLength++;
            }
        }

        inline constexpr const decltype(m_Signature)& Get() const
        { return m_Signature; }
        constexpr std::size_t Length() const
        { return N; }
        constexpr std::size_t ByteLength() const
        { return m_SignatureByteLength; }
    };

    template<Signature S>
    class Pattern final
    {
    private:
        const std::string_view m_Name;
        std::array<std::optional<std::uint8_t>, S.ByteLength()> m_Signature;

    public:
        constexpr Pattern(const std::string_view name);

        inline const std::string_view Name() const
        { return m_Name; }
        inline constexpr const std::array<std::optional<std::uint8_t>, S.ByteLength()>& Signature() const
        { return m_Signature; }

        friend std::ostream& operator<< <>(std::ostream& os, const Pattern<S>& signature);
    };

    inline constexpr auto StrToHex(const char& ch) noexcept -> std::uint8_t
    {
        if (ch >= '0' && ch <= '9')
                return ch - '0';

        if (ch >= 'A' && ch <= 'F')
            return ch - 'A' + 10;

        return ch - 'a' + 10;
    };

	template<Signature S>
	inline constexpr Pattern<S>::Pattern(const std::string_view name) :
        m_Name(name)
	{
        for (size_t i = 0, pos = 0; i < S.Length(); i++)
        {
            const auto c = S.Get()[i];
            if (c == ' ')
                continue;
            if (c == '\0')
                break;

            if (S.Get()[i] == '?')
            {
                if (S.Get()[i + 1] == '?')
                    i++;

                m_Signature[pos++] = std::nullopt;
                
                continue;
            }


            m_Signature[pos++] = static_cast<std::uint8_t>(StrToHex(S.Get()[i]) * 0x10 + StrToHex(S.Get()[++i]));
        }
	}

    template<Signature S>
    inline std::ostream& operator<<(std::ostream& os, const Pattern<S>& pattern)
    {
        os << pattern.Name() <<  ": { ";
        for (const auto byte : pattern.Signature())
        {
            if (byte == std::nullopt)
            {
                os << "?? ";
                continue;
            }
            os << std::hex << std::uppercase << DWORD64(byte.value()) << std::nouppercase << std::dec << ' ';
        }
        os << "}";
        return os;
    }
}