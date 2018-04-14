#ifndef OCTOON_JSON_READER_H
#define OCTOON_JSON_READER_H

#include <string>
#include <cstdint>
#include <octoon/io/text_reader.h>
#include <octoon/io/stream_reader.h>
#include <octoon/io/istream.h>
#include <octoon/runtime/json/json.hpp>

namespace octoon
{
    namespace io
    {
        class OCTOON_EXPORT JsonReader : public StreamReader
        {
		public:
			using JsonObject = nlohmann::json;
        public:
            JsonReader(istream &stream);

            JsonObject readJson();
        private:
	        JsonReader(const JsonReader&) noexcept = delete;
	        JsonReader& operator=(const JsonReader&) noexcept = delete;
        };
    }
}

#endif