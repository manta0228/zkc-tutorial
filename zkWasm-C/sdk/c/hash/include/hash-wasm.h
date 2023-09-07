#include <stdint.h>
#include <stdalign.h>

static __inline__ void *memset(void *dst, const uint8_t value, uint32_t cnt)
{
  uint8_t *p = dst;
  while (cnt--)
  {
    *p++ = value;
  }
  return dst;
}

static __inline__ void *memcpy2(void *dst, const void *src, uint32_t cnt)
{
  uint64_t *destination64 = dst;
  const uint64_t *source64 = src;
  while (cnt >= 8)
  {
    *(destination64++) = *(source64++);
    cnt -= 8;
  }

  uint8_t *destination = (uint8_t *)destination64;
  const uint8_t *source = (uint8_t *)source64;
  while (cnt)
  {
    *(destination++) = *(source++);
    --cnt;
  }
  return dst;
}

static __inline__ void memcpy16(void *dst, const void *src)
{
  uint64_t *dst64 = (uint64_t *)dst;
  uint64_t *src64 = (uint64_t *)src;

  dst64[0] = src64[0];
  dst64[1] = src64[1];
}

static __inline__ void memcpy32(void *dst, const void *src)
{
  uint64_t *dst64 = (uint64_t *)dst;
  uint64_t *src64 = (uint64_t *)src;

#pragma clang loop unroll(full)
  for (int i = 0; i < 4; i++)
  {
    dst64[i] = src64[i];
  }
}

static __inline__ void memcpy64(void *dst, const void *src)
{
  uint64_t *dst64 = (uint64_t *)dst;
  uint64_t *src64 = (uint64_t *)src;

#pragma clang loop unroll(full)
  for (int i = 0; i < 8; i++)
  {
    dst64[i] = src64[i];
  }
}

static __inline__ uint64_t widen8to64(const uint8_t value)
{
  return value | (value << 8) | (value << 16) | (value << 24);
}

static __inline__ void memset16(void *dst, const uint8_t value)
{
  uint64_t val = widen8to64(value);
  uint64_t *dst64 = (uint64_t *)dst;

  dst64[0] = val;
  dst64[1] = val;
}

static __inline__ void memset32(void *dst, const uint8_t value)
{
  uint64_t val = widen8to64(value);
  uint64_t *dst64 = (uint64_t *)dst;

#pragma clang loop unroll(full)
  for (int i = 0; i < 4; i++)
  {
    dst64[i] = val;
  }
}

static __inline__ void memset64(void *dst, const uint8_t value)
{
  uint64_t val = widen8to64(value);
  uint64_t *dst64 = (uint64_t *)dst;

#pragma clang loop unroll(full)
  for (int i = 0; i < 8; i++)
  {
    dst64[i] = val;
  }
}

static __inline__ void memset128(void *dst, const uint8_t value)
{
  uint64_t val = widen8to64(value);
  uint64_t *dst64 = (uint64_t *)dst;

#pragma clang loop unroll(full)
  for (int i = 0; i < 16; i++)
  {
    dst64[i] = val;
  }
}

void sha256_new(uint64_t x);
void sha256_push(uint64_t x);
uint64_t sha256_finalize(void);

void sha256(uint8_t* data, uint32_t size, uint64_t* r);

void poseidon_new(uint64_t x);
void poseidon_push(uint64_t x);
uint64_t poseidon_finalize(void);

void poseidon(uint64_t* data, uint32_t size, uint64_t* r);
