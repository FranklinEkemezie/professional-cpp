#include <format>
#include <iostream>
#include <string>
#include <string_view>


class KeyValue
{
    public:
        KeyValue(std::string_view key, int value) 
            : m_key { key }, m_value { value } {}

        const std::string& getKey() const { return m_key; }
        int getValue() const { return m_value; }

    private:
        std::string m_key;
        int m_value { 0 };
};

template <>
class std::formatter<KeyValue>
{
    public:
        constexpr auto parse(auto& context)
        {
            std::string keyFormat, valueFormat;
            size_t numberOfParsedColons { 0 };
            auto iter { begin(context) };

            for (; iter != end(context); ++iter)
            {
                if (*iter == '}') { break; }

                if (numberOfParsedColons == 0)
                {
                    // Parsing output type
                    switch (*iter)
                    {
                        case 'k': 
                        case 'K':
                            m_outputType = OutputType::KeyOnly;
                            break;

                        case 'v': 
                        case 'V':
                            m_outputType = OutputType::ValueOnly;
                            break;

                        case 'b': 
                        case 'B':
                            m_outputType = OutputType::KeyAndValue;
                            break;

                        case ':':
                            ++numberOfParsedColons;
                            break;

                        default:

                            if (m_outputType != OutputType::KeyAndValue)
                            {
                                throw format_error { "Invalid KeyValue format." };
                            }

                            // 
                            separator+= *iter;
                            break;
                    }
                }
                else if (numberOfParsedColons == 1)
                {
                    if (*iter == ':') { ++numberOfParsedColons; }
                    else { keyFormat += *iter; }

                }
                else if (numberOfParsedColons == 2)
                {
                    valueFormat += *iter;
                }
            }

            // Validate key format specifier.
            if (! keyFormat.empty())
            {
                format_parse_context keyFormatterContext { keyFormat };
                m_keyFormatter.parse(keyFormatterContext);
            }

            // Validate value format specifier.
            if (! valueFormat.empty())
            {
                format_parse_context valueFormatterContext { valueFormat };
                m_valueFormatter.parse(valueFormatterContext);
            }

            if (iter != end(context) && *iter != '}')
            {
                throw format_error { "Invalid KeyValue format." };
            }

            return iter;
        }

        auto format(const KeyValue& kv, auto& ctx) const
        {
            switch (m_outputType)
            {
                using enum OutputType;
                case KeyOnly:
                    ctx.advance_to(m_keyFormatter.format(kv.getKey(), ctx));
                    break;
                
                case ValueOnly:
                    ctx.advance_to(m_valueFormatter.format(kv.getValue(), ctx));
                    break;

                default:
                    ctx.advance_to(m_keyFormatter.format(kv.getKey(), ctx));
                    ctx.advance_to(format_to(ctx.out(), " {} ", separator.empty() ? "_" : separator));
                    ctx.advance_to(m_valueFormatter.format(kv.getValue(), ctx));
                    break;
            }

            return ctx.out();
        }

    private:
        enum class OutputType { KeyOnly, ValueOnly, KeyAndValue };
        OutputType m_outputType { OutputType::KeyAndValue };
        formatter<string> m_keyFormatter;
        formatter<int> m_valueFormatter;

        string separator { "" };

};

int main()
{

    // --- Support for Custom Types
    // The formatting library can be extended to add support for custom types.
    // This involves writing a specialisation of the `std::formatter` class
    // template with two member functions: `parse()` and `format()`.

    const size_t len { 34 };    // label field length
    KeyValue kv { "Key 1", 255 };

    std::cout << std::format("{:>{}} {}", "Default: ", len, kv) << std::endl;
    std::cout << std::format("{:>{}} {:k}", "Key only: ", len, kv) << std::endl;
    std::cout << std::format("{:>{}} {:v}", "Value only: ", len, kv) << std::endl;
    std::cout << std::format("{:>{}} {:b}", "Key and value with default format: ", len, kv) << std::endl;
    std::cout << std::format("{:>{}} {:k:*^11}", "Key only with special format: ", len, kv) << std::endl;
    std::cout << std::format("{:>{}} {:v::#06X}", "Value only with special format: ", len, kv) << std::endl;
    std::cout << std::format("{:>{}} {::*^11:#06X}", "Key and value with special format: ", len, kv) << std::endl;

    std::cout << std::format("{:>{}} {:b->}", "Key and value with default format: ", len, kv) << std::endl;


    try
    {
        auto formatted { std::vformat("{:k<-->}", // specifying "only key" but with separator string
            std::make_format_args(kv)) };
        std::cout << std::format("{}", formatted) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    


    
}