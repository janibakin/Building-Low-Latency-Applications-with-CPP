#include <cstdio>
#include <cstdint>
#include <cstddef>

struct PoorlyAlignedData {
  char c;     // 1 byte
              // 1 byte padding
  uint16_t u; // 2 bytes
              // 4 bytes padding
  double d;   // 8 bytes
  int16_t i;  // 2 bytes
              // 6 bytes padding
};

struct WellAlignedData {
  double d;   // 8 bytes
  uint16_t u; // 2 bytes
  int16_t i;  // 2 bytes
  char c;     // 1 byteS
              // 3 bytes padding
};

#pragma pack(push, 1)
struct PackedData {
  double d;   // 8 bytes
  uint16_t u; // 2 bytes
  int16_t i;  // 2 bytes
  char c;     // 1 byte
              // no more padding
};
#pragma pack(pop)

int main() {
  printf("PoorlyAlignedData c:%lu u:%lu d:%lu i:%lu size:%lu\n",
         offsetof(struct PoorlyAlignedData, c), offsetof(struct PoorlyAlignedData,u), offsetof(struct PoorlyAlignedData,d), offsetof(struct PoorlyAlignedData,i), sizeof(PoorlyAlignedData));
  printf("WellAlignedData d:%lu u:%lu i:%lu c:%lu size:%lu\n",
         offsetof(struct WellAlignedData,d), offsetof(struct WellAlignedData,u), offsetof(struct WellAlignedData,i), offsetof(struct WellAlignedData,c), sizeof(WellAlignedData));
  printf("PackedData d:%lu u:%lu i:%lu c:%lu size:%lu\n",
         offsetof(struct PackedData,d), offsetof(struct PackedData,u), offsetof(struct PackedData,i), offsetof(struct PackedData,c), sizeof(PackedData));
}