#include "memory.hpp"

namespace memory {
	uintptr_t find_ida_sig(std::string module, std::string signature) {

		/// @credits: MarkHC, although slightly modified by me and also documented

		static auto pattern_to_byte = [](const char* pattern) {
			/// Prerequisites
			auto bytes = std::vector<int>{};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern) + strlen(pattern);

			/// Convert signature into corresponding bytes
			for (auto current = start; current < end; ++current)
			{
				/// Is current byte a wildcard? Simply ignore that that byte later
				if (*current == '?')
				{
					++current;

					/// Check if following byte is also a wildcard
					if (*current == '?')
						++current;

					/// Dummy byte
					bytes.push_back(-1);
				}
				else
				{
					/// Convert character to byte on hexadecimal base
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
		};

		const auto module_handle = GetModuleHandleA(module.c_str());
		if (!module_handle)
			return {};

		/// Get module information to search in the given module
		MODULEINFO module_info;
		GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_handle), &module_info, sizeof(MODULEINFO));

		/// The region where we will search for the byte sequence
		const auto image_size = module_info.SizeOfImage;

		/// Check if the image is faulty
		if (!image_size)
			return {};

		/// Convert IDA-Style signature to a byte sequence
		auto pattern_bytes = pattern_to_byte(signature.c_str());

		const auto image_bytes = reinterpret_cast<byte*>(module_handle);

		const auto signature_size = pattern_bytes.size();
		const auto signature_bytes = pattern_bytes.data();

		/// Now loop through all bytes and check if the byte sequence matches
		for (auto i = 0ul; i < image_size - signature_size; ++i){
			auto byte_sequence_found = true;

			/// Go through all bytes from the signature and check if it matches
			for (auto j = 0ul; j < signature_size; ++j){
				if (image_bytes[i + j] != signature_bytes[j] /// Bytes don't match
					&& signature_bytes[j] != -1) /*Byte isn't a wildcard either, WHAT THE HECK*/ {
					byte_sequence_found = false;
					break;
				}
			}

			/// All good, now return the right address
			if (byte_sequence_found)
				return uintptr_t(&image_bytes[i]);
		}

		/// Byte sequence wasn't found
		return {};
	}
}
