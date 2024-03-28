//
// Created by liangjie on 2024/3/26.
//

#include "cc/pixels.h"
#include "SDL2/SDL_pixels.h"

const CC::UInt32 CC::Pixel::Type::Unknown = SDL_PIXELTYPE_UNKNOWN;
const CC::UInt32 CC::Pixel::Type::Index1 = SDL_PIXELTYPE_INDEX1;
const CC::UInt32 CC::Pixel::Type::Index4 = SDL_PIXELTYPE_INDEX4;
const CC::UInt32 CC::Pixel::Type::Index8 = SDL_PIXELTYPE_INDEX8;
const CC::UInt32 CC::Pixel::Type::Packed8 = SDL_PIXELTYPE_PACKED8;
const CC::UInt32 CC::Pixel::Type::Packed16 = SDL_PIXELTYPE_PACKED16;
const CC::UInt32 CC::Pixel::Type::Packed32 = SDL_PIXELTYPE_PACKED32;
const CC::UInt32 CC::Pixel::Type::ArrayU8 = SDL_PIXELTYPE_ARRAYU8;
const CC::UInt32 CC::Pixel::Type::ArrayU16 = SDL_PIXELTYPE_ARRAYU16;
const CC::UInt32 CC::Pixel::Type::ArrayU32 = SDL_PIXELTYPE_ARRAYU32;
const CC::UInt32 CC::Pixel::Type::ArrayF16 = SDL_PIXELTYPE_ARRAYF16;
const CC::UInt32 CC::Pixel::Type::ArrayF32 = SDL_PIXELTYPE_ARRAYF32;

const CC::UInt32 CC::Pixel::BitmapOrder::None = SDL_BITMAPORDER_NONE;
const CC::UInt32 CC::Pixel::BitmapOrder::By4321 = SDL_BITMAPORDER_4321;
const CC::UInt32 CC::Pixel::BitmapOrder::By1234 = SDL_BITMAPORDER_1234;

const CC::UInt32 CC::Pixel::Format::UNKNOWN = SDL_PIXELFORMAT_UNKNOWN;
const CC::UInt32 CC::Pixel::Format::INDEX1LSB = SDL_PIXELFORMAT_INDEX1LSB;
const CC::UInt32 CC::Pixel::Format::INDEX1MSB = SDL_PIXELFORMAT_INDEX1MSB;
const CC::UInt32 CC::Pixel::Format::INDEX4LSB = SDL_PIXELFORMAT_INDEX4LSB;
const CC::UInt32 CC::Pixel::Format::INDEX4MSB = SDL_PIXELFORMAT_INDEX4MSB;
const CC::UInt32 CC::Pixel::Format::INDEX8 = SDL_PIXELFORMAT_INDEX8;
const CC::UInt32 CC::Pixel::Format::RGB332 = SDL_PIXELFORMAT_RGB332;
const CC::UInt32 CC::Pixel::Format::XRGB4444 = SDL_PIXELFORMAT_XRGB4444;
const CC::UInt32 CC::Pixel::Format::RGB444 = SDL_PIXELFORMAT_RGB444;
const CC::UInt32 CC::Pixel::Format::XBGR4444 = SDL_PIXELFORMAT_XBGR4444;
const CC::UInt32 CC::Pixel::Format::BGR444 = SDL_PIXELFORMAT_BGR444;
const CC::UInt32 CC::Pixel::Format::XRGB1555 = SDL_PIXELFORMAT_XRGB1555;
const CC::UInt32 CC::Pixel::Format::RGB555 = SDL_PIXELFORMAT_RGB555;
const CC::UInt32 CC::Pixel::Format::XBGR1555 = SDL_PIXELFORMAT_XBGR1555;
const CC::UInt32 CC::Pixel::Format::BGR555 = SDL_PIXELFORMAT_BGR555;
const CC::UInt32 CC::Pixel::Format::ARGB4444 = SDL_PIXELFORMAT_ARGB4444;
const CC::UInt32 CC::Pixel::Format::RGBA4444 = SDL_PIXELFORMAT_RGBA4444;
const CC::UInt32 CC::Pixel::Format::ABGR4444 = SDL_PIXELFORMAT_ABGR4444;
const CC::UInt32 CC::Pixel::Format::BGRA4444 = SDL_PIXELFORMAT_BGRA4444;
const CC::UInt32 CC::Pixel::Format::ARGB1555 = SDL_PIXELFORMAT_ARGB1555;
const CC::UInt32 CC::Pixel::Format::RGBA5551 = SDL_PIXELFORMAT_RGBA5551;
const CC::UInt32 CC::Pixel::Format::ABGR1555 = SDL_PIXELFORMAT_ABGR1555;
const CC::UInt32 CC::Pixel::Format::BGRA5551 = SDL_PIXELFORMAT_BGRA5551;
const CC::UInt32 CC::Pixel::Format::RGB565 = SDL_PIXELFORMAT_RGB565;
const CC::UInt32 CC::Pixel::Format::BGR565 = SDL_PIXELFORMAT_BGR565;
const CC::UInt32 CC::Pixel::Format::RGB24 = SDL_PIXELFORMAT_RGB24;
const CC::UInt32 CC::Pixel::Format::BGR24 = SDL_PIXELFORMAT_BGR24;
const CC::UInt32 CC::Pixel::Format::XRGB8888 = SDL_PIXELFORMAT_XRGB8888;
const CC::UInt32 CC::Pixel::Format::RGB888 = SDL_PIXELFORMAT_RGB888;
const CC::UInt32 CC::Pixel::Format::RGBX8888 = SDL_PIXELFORMAT_RGBX8888;
const CC::UInt32 CC::Pixel::Format::XBGR8888 = SDL_PIXELFORMAT_XBGR8888;
const CC::UInt32 CC::Pixel::Format::BGR888 = SDL_PIXELFORMAT_BGR888;
const CC::UInt32 CC::Pixel::Format::BGRX8888 = SDL_PIXELFORMAT_BGRX8888;
const CC::UInt32 CC::Pixel::Format::ARGB8888 = SDL_PIXELFORMAT_ARGB8888;
const CC::UInt32 CC::Pixel::Format::RGBA8888 = SDL_PIXELFORMAT_RGBA8888;
const CC::UInt32 CC::Pixel::Format::ABGR8888 = SDL_PIXELFORMAT_ABGR8888;
const CC::UInt32 CC::Pixel::Format::BGRA8888 = SDL_PIXELFORMAT_BGRA8888;
const CC::UInt32 CC::Pixel::Format::ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010;

// 32bit
const CC::UInt32 CC::Pixel::Format::RGBA32 = SDL_PIXELFORMAT_RGBA32;
const CC::UInt32 CC::Pixel::Format::ARGB32 = SDL_PIXELFORMAT_ARGB32;
const CC::UInt32 CC::Pixel::Format::BGRA32 = SDL_PIXELFORMAT_BGRA32;
const CC::UInt32 CC::Pixel::Format::ABGR32 = SDL_PIXELFORMAT_ABGR32;

// video
const CC::UInt32 CC::Pixel::Format::YV12 = SDL_PIXELFORMAT_YV12;
const CC::UInt32 CC::Pixel::Format::IYUV = SDL_PIXELFORMAT_IYUV;
const CC::UInt32 CC::Pixel::Format::YUY2 = SDL_PIXELFORMAT_YUY2;
const CC::UInt32 CC::Pixel::Format::UYVY = SDL_PIXELFORMAT_UYVY;
const CC::UInt32 CC::Pixel::Format::YVYU = SDL_PIXELFORMAT_YVYU;
const CC::UInt32 CC::Pixel::Format::NV12 = SDL_PIXELFORMAT_NV12;
const CC::UInt32 CC::Pixel::Format::NV21 = SDL_PIXELFORMAT_NV21;
const CC::UInt32 CC::Pixel::Format::EXTERNAL_OES = SDL_PIXELFORMAT_EXTERNAL_OES;