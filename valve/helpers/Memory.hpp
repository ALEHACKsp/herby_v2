#pragma once
#include <memory>
#include <string>
#include <thread>
#include <Windows.h>
namespace memory
{
	std::uintptr_t ScanLocation(const std::uintptr_t location,
		const std::size_t size,
		const std::string& signature,
		const std::intptr_t displacement = 0,
		const std::size_t read = 0);

	std::uintptr_t ScanImage(const std::string& image_name,
		const std::string& signature,
		const std::intptr_t displacement = 0,
		const std::size_t read = 0);

	template< typename T >
	T scan(const std::string& image_name,
		const std::string& signature,
		const std::intptr_t displacement = 0,
		const std::size_t read = 0)
	{
		const auto scan_result = ScanImage(image_name, signature, displacement, read);
		return (T)(scan_result);
	}
}