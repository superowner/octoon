#include <octoon/io/json_reader.h>

namespace octoon
{
    namespace io
    {
        JsonReader::JsonReader(istream &stream) noexcept
            :StreamReader(stream)
        {
        }

        JsonReader::JsonObject
        JsonReader::readJson() except
        {
            std::string data = this->readToEnd();
            JsonObject json = nlohmann::json::parse(data.begin(), data.end());
            return json;
        }
    }
}