#ifndef __BUFFER_MAN_HPP__
#define __BUFFER_MAN_HPP__
#include <GraphicsExtractor.hpp>
#include <wrl.h>
#include <vector>
#include <set>
#include <memory>

using Microsoft::WRL::ComPtr;

struct Partition {
    std::uint64_t offsetFromBase;
    std::uint64_t size;
    std::uint32_t pageIndex;

    constexpr bool operator()(const Partition& x, const Partition& y) const;
};

struct Page {
    ComPtr<ID3D12Resource> memory;
    std::uint8_t* cpuPTR;
    std::uint64_t size;

    std::multiset <Partition, Partition> m_FreePartitions;
};

struct Memory {
    Memory(std::uint8_t* ptr, D3D12_GPU_VIRTUAL_ADDRESS gPtr, Partition&& partition);

    std::uint8_t* cpuPTR;
    D3D12_GPU_VIRTUAL_ADDRESS gpuPTR;
    Partition partitionInPage;
};

class BufferMan : public GraphicsExtractor {
public:
    BufferMan(Graphics& gfx);

    static void Init(Graphics& gfx) noexcept;

    static std::unique_ptr<Memory> RequestMemory(
        std::uint64_t bufferSize, std::uint64_t alignment = 4u
    ) noexcept;

    static void FreePartition(Partition&& partition) noexcept;

private:

    std::unique_ptr<Memory> _RequestMemory(
        std::uint64_t bufferSize, std::uint64_t alignment
    ) noexcept;

    void Allocate(std::uint64_t bufferSize);

    void Free(Partition&& partition) noexcept;

    std::uint64_t AlignUp(std::uint64_t number, std::uint64_t alignment) noexcept;

private:
    Graphics& m_gfx;
    std::uint64_t m_DefaultSize;

    std::vector<Page> m_Memories;

    static std::unique_ptr<BufferMan> s_Instance;

    HRESULT hr;
};

std::uint64_t operator"" _B(unsigned long long number);
std::uint64_t operator"" _KB(unsigned long long number);
std::uint64_t operator"" _MB(unsigned long long number);
std::uint64_t operator"" _GB(unsigned long long number);
#endif
